#ifndef SDKELI_LS_COMMANDS_
#define SDKELI_LS_COMMANDS_

/*
//for tcp
const char CMD_STOP_STREAM_DATA[]            = {"\x02sEN LMDscandata 0\x03\0"};
const char CMD_SET_MAINTENANCE_ACCESS_MODE[] = {"\x02sMN SetAccessMode 03 F4724744\x03\0"};
const char CMD_REBOOT[]                      = {"\x02sMN mSCreboot\x03\0"};
const char CMD_READ_IDENTIFY[]               = {"\x02sRI0\x03\0"};
const char CMD_READ_SERIAL_NUMBER[]          = {"\x02sRN SerialNumber\x03\0"};
const char CMD_READ_FIRMWARE_VERSION[]       = {"\x02sRN FirmwareVersion\x03\0"};
const char CMD_READ_DEVICE_STATE[]           = {"\x02sRN SCdevicestate\x03\0"};
const char CMD_START_STREAM_DATA[]           = {"\x02sEN LMDscandata 1\x03\0"};
*/

const char CMD_STOP_STREAM_DATA[]            = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x02, 0x02};
const char CMD_SET_MAINTENANCE_ACCESS_MODE[] = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x01, 0x01};
const char CMD_REBOOT[]                      = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x03, 0x03};
const char CMD_READ_IDENTIFY[]               = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x01, 0x01};
const char CMD_READ_SERIAL_NUMBER[]          = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x05, 0x05};
const char CMD_READ_FIRMWARE_VERSION[]       = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x01, 0x01};
const char CMD_READ_DEVICE_STATE[]           = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x04, 0x04};
const char CMD_START_STREAM_DATA[]           = {0xFA, 0x5A, 0xA5, 0xAA, 0x00, 0x02, 0x01, 0x01};
#define SIZE_OF_CMD sizeof(CMD_START_STREAM_DATA)

/*Message START and END definition*/
const unsigned char STX = 0xAA;
const unsigned char ETX = 0x66;

const unsigned int  FRAME_LENGTH = 1622; //1642;    //FRAME_LENGTH = 1631;

#define SWITCH_UINT16( _Value )   ((uint16_t) (((uint16_t)( _Value ) << 8) | \
                                   ((uint16_t)( _Value ) >> 8)) )
#undef CMD_STOP_STREAM_DATA
#undef CMD_REBOOT_DEVICE
#undef CMD_DEVICE_INFO

#endif //SDKELI_LS_COMMANDS_
