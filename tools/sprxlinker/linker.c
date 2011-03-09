#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include <libelf.h>

#if defined(_WIN32)
#define OFLAGS		(O_RDWR|O_BINARY)
#else
#define OFLAGS		(O_RDWR)
#endif

#ifdef __BIG_ENDIAN__
#define BE16(num) (num)
#define BE32(num) (num)
#define BE64(num) (num)
#else
#define BE16(num) ((uint16_t)(((uint16_t)((num) << 8)) | (uint8_t)((num) >> 8)))
#define BE32(num) ((uint32_t)((uint32_t)BE16(num) << 16) | BE16(num >> 16))
#define BE64(num) ((uint64_t)((uint64_t)BE32(num) << 32ULL) | BE32(num >> 32ULL))
#endif


typedef struct _stub
{
	uint32_t header1;
	uint16_t header2;
	uint16_t imports;
	uint32_t zero1;
	uint32_t zero2;
	uint32_t name;
	uint32_t fnid;
	uint32_t stub;
	uint32_t zero3;
	uint32_t zero4;
	uint32_t zero5;
	uint32_t zero6;
} __attribute__((packed)) Stub;

typedef struct _opd64
{
	uint64_t func;
	uint64_t rtoc;
	uint64_t data;
} __attribute__((packed)) Opd64;

unsigned char prx_magic[] = {
	0x00,0x00,0x00,0x28,
	0x1b,0x43,0x4c,0xec
};

Elf_Scn* getSection(Elf *elf,const char *name)
{
	Elf64_Ehdr *ehdr = elf64_getehdr(elf);
	if(!ehdr) return NULL;

	Elf_Data *data = elf_getdata(elf_getscn(elf,ehdr->e_shstrndx),NULL);
	if(!data) return NULL;

	for(Elf_Scn *scn = NULL;(scn = elf_nextscn(elf,scn));) {
		Elf64_Shdr *shdr = elf64_getshdr(scn);
		if(shdr && !strcmp(name,(const char*)data->d_buf + shdr->sh_name)) return scn;
	}
	return NULL;
}

int main(int argc,char *argv[])
{
	if(argc<2) {
		printf("Usage: %s [elf path]\n",argv[0]);
		return 0;
	}

	int fd = open(argv[1],OFLAGS);
	if(fd<0) {
		fprintf(stderr,"Unable to open elf file: %s\n",argv[1]);
		return 1;
	}

	elf_version(EV_CURRENT);
	
	Elf *elf = elf_begin(fd,ELF_C_READ,NULL);
	if(!elf) {
		fprintf(stderr,"libelf could not read elf file: %s\n",elf_errmsg(elf_errno()));
		return 1;
	}

	Elf_Scn *prx = getSection(elf,".sys_proc_prx_param");
	if(!prx || memcmp(elf_getdata(prx,NULL)->d_buf,prx_magic,sizeof(prx_magic))) {
		fprintf(stderr,"elf does not have a prx parameter section.\n");
		return 1;
	}

	Elf_Scn *stubsection = getSection(elf,".lib.stub");
	Elf_Data *stubdata = elf_getdata(stubsection,NULL);
	Elf64_Shdr *stubshdr = elf64_getshdr(stubsection);
	Stub *stubbase = (Stub*)stubdata->d_buf;
	size_t stubcount = stubdata->d_size/sizeof(Stub);
	Elf_Scn *fnidsection = getSection(elf,".rodata.sceFNID");
	Elf64_Shdr *fnidshdr = elf64_getshdr(fnidsection);
	for(Stub *stub = stubbase;stub<stubbase + stubcount;stub++) {
		uint32_t fnid = BE32(stub->fnid);
		uint32_t end = fnidshdr->sh_addr + fnidshdr->sh_size;
		for(Stub *substub = stubbase;substub<(stubbase + stubcount);substub++) {
			if(stub==substub) continue;

			uint32_t newfnid = BE32(substub->fnid);
			if(newfnid>=fnid && newfnid<end) end = newfnid;
		}

		uint16_t fnidcount = (end - fnid)/4;
		if(BE16(stub->imports)!=fnidcount) {
			lseek(fd,stubshdr->sh_offset + (stub - stubbase)*sizeof(Stub)+offsetof(Stub,imports),SEEK_SET);
			fnidcount = BE16(fnidcount);
			if(write(fd,&fnidcount,sizeof(fnidcount))!=sizeof(fnidcount)) {
				printf("Error occurred during write in %s:%d\n",__FILE__,__LINE__);
			}
		}
	}

	Elf_Scn *opdsection = getSection(elf,".opd");
	Elf_Data *opddata = elf_getdata(opdsection,NULL);
	Elf64_Shdr *opdshdr = elf64_getshdr(opdsection);

	Opd64 *opdbase = (Opd64*)opddata->d_buf;
	size_t opdcount = opddata->d_size/sizeof(Opd64);
	for(Opd64 *opd = opdbase;opd<(opdbase + opdcount);opd++) {
		opd->data = BE64(((BE64(opd->func)<<32ULL) | (BE64(opd->rtoc)&0xffffffffULL)));
		lseek(fd,opdshdr->sh_offset + (opd - opdbase)*sizeof(Opd64),SEEK_SET);
		if(write(fd,opd,sizeof(Opd64))!=sizeof(Opd64)) {
			printf("Error occurred during write in %s:%d\n",__FILE__,__LINE__);
		}
	}

	elf_end(elf);
	close(fd);

	return 0;
}
