#ifndef __EXPORTS_H__
#define __EXPORTS_H__

EXPORT(gcmInitBody, 0x15bae46b);
EXPORT(gcmSetDisplayBuffer, 0xa53d12ae);
EXPORT(gcmGetControlRegister, 0xa547adde);
EXPORT(gcmAddressToOffset, 0x21ac3697);
EXPORT(gcmGetConfiguration, 0xe315a0b2);
EXPORT(gcmGetCurrentField, 0xc8f3bd09);
EXPORT(gcmSetFlipMode, 0x4ae8d215);
EXPORT(gcmGetFlipStatus, 0x72a577ce);
EXPORT(gcmGetLastFlipTime, 0x63387071);
EXPORT(gcmGetVBlankCount, 0x723bbc7e);
EXPORT(gcmSetWaitFlip, 0x983fb9aa);
EXPORT(gcmSetFlipStatus, 0xa47c09ff);
EXPORT(gcmResetFlipStatus, 0xb2e761d4);
EXPORT(gcmSetFlip, 0xdc09357e);
EXPORT(gcmSetFlipImmediate, 0xacee8542);
EXPORT(gcmFunc15, 0x3a33c1fd);
EXPORT(gcmFunc3, 0x1bd633f8);
EXPORT(gcmFunc1, 0x5f909b17);
EXPORT(gcmFunc2, 0x8effb7fd);
EXPORT(gcmFunc4, 0x7fc034bc);
EXPORT(gcmFunc12, 0x661fe266);
EXPORT(gcmFunc13, 0xbb42a9dd);
EXPORT(gcmGetReport, 0x99d397ac);
EXPORT(gcmSetTile, 0xd0b1d189);
EXPORT(gcmBindTile, 0x4524cccd);
EXPORT(gcmUnbindTile, 0xd9b7653e);
EXPORT(gcmSetZcull, 0xd34a420d);
EXPORT(gcmBindZcull, 0x9dc04436);
EXPORT(gcmUnbindZcull, 0xa75640e8);
EXPORT(gcmGetTimeStamp, 0x5a41c10f);
EXPORT(gcmSetVBlankFrequency, 0xffe0160e);
EXPORT(gcmSetSecondVFrequency, 0x4d7ce993);
EXPORT(gcmSetDebugOutputLevel, 0x51c9d62b);
EXPORT(gcmGetLabelAddress, 0xf80196c1);
EXPORT(gcmSetVBlankHandlerEx, 0xa91b0402);
EXPORT(gcmSetFlipHandlerEx, 0xa41ef7e8);
EXPORT(gcmSetSecondVHandlerEx, 0xdc494430);
EXPORT(gcmSetGraphicsHandlerEx, 0xd01b570d);
EXPORT(gcmTerminate, 0x527c6439);
EXPORT(gcmMapMainMemory, 0xa114ec67);
EXPORT(gcmMapEaIoAddress, 0x63441cb4);
EXPORT(gcmUnmapEaIoAddress, 0xefd00f54);
EXPORT(gcmUnmapIoAddress, 0xdb23e867);
EXPORT(gcmIoOffsetToAddress, 0x2a6fba9c);
EXPORT(gcmSetDefaultCommandBuffer, 0xbc982946);
EXPORT(gcmSetTileInfo, 0xbd100dbc);
EXPORT(gcmGetTiledPitchSize, 0x055bd74d);
EXPORT(gcmSetInvalidateTile, 0xbd6d60d9);
EXPORT(gcmSetUserCommand, 0x8bde5ebf);
EXPORT(gcmSetUserHandlerEx, 0x06edea9e);
EXPORT(gcmSetQueueHandlerEx, 0x0a862772);
EXPORT(gcmSetPrepareFlip, 0x0b4b62d5);
EXPORT(gcmGetOffsetTable, 0x2922aed0);
EXPORT(gcmGetLastSecondVTime, 0x23ae55a3);
EXPORT(gcmSortRemapEaIoAddress, 0x25b40ab4);
EXPORT(gcmGetDisplayBufferByFlipIndex, 0x371674cf);
EXPORT(gcmGcmGetDefaultCommandWordSize, 0x5e2ee0f0);
EXPORT(gcmGcmGetDefaultSegmentWordSize, 0x8cdf8c70);
EXPORT(gcmSetDefaultCommandBufferAndSegmentWordSize, 0x172c3197);

#endif
