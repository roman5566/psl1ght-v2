ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

ifneq (,$(findstring MINGW,$(shell uname -s)))
	host		:= win32
endif

ifneq (,$(findstring Linux,$(shell uname -s)))
	host		:= linux
endif

ifneq (,$(findstring Darwin,$(shell uname -s)))
	host		:= osx
endif

all:
	@make -C sprxlinker --no-print-directory
	@make -C ps3load --no-print-directory
	@make -C generic --no-print-directory
	@make -C cgcomp --no-print-directory
	@make -C ps3py --no-print-directory
	
install-socat:
	@[ -d $(PSL1GHT)/host/bin ] || mkdir -p $(PSL1GHT)/host/bin
	@cp -frv $(CURDIR)/socat/$(host)/* $(PSL1GHT)/host/bin
		
install:
	@make -C sprxlinker install --no-print-directory
	@make -C ps3load install --no-print-directory
	@make -C generic install --no-print-directory
	@make -C cgcomp install --no-print-directory
	@make -C ps3py install --no-print-directory
	
clean:
	@make -C sprxlinker clean --no-print-directory
	@make -C ps3load clean --no-print-directory
	@make -C generic clean --no-print-directory
	@make -C cgcomp clean --no-print-directory
	@make -C ps3py clean --no-print-directory
	
.PHONY: all clean install install-socat
