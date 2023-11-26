#ifndef __DFPLAYER_LIB_H
#define __DFPLAYER_LIB_H
#include "stm32f4xx.h"
#include <stdint.h>
#define START_BYTE 0x7E
#define END_BYTE 0xEF
#define CMD_LEN  0x06
#define FEEDBACK_EN 0x01
#define VERSION_INFO 0xFF

#define CMD_NEXT 0x01
#define CMD_PREV 0x02
#define CMD_INC_VOL 0x04
#define CMD_DEC_VOL 0x05
#define CMD_SET_EQ 0x07
#define CMD_SET_PLAYBACKMODE 0x08
#define CMD_SET_PLAYBACKSRC 0x09
#define CMD_INIT_PARAM   0x3F
#define CMD_SET_VOL 0x06
#define CMD_REPEAT_PLAY   0x11

#define CMD_RESET 0x0C
#define CMD_PLAYBACK  0x0D
#define CMD_PAUSE 0x0E


#define CMD_GET_TRACK 0x03


#define PLAY_SOURCE_TF_CARD  0x02
#define NULL_PARM 0x00
typedef enum
{

	Normal = 0x00,
	Pop=0x01,
	Rock =0x02,
	Jazz= 0x03,
	Classic =0x04,
	Base= 0x05

}eq_type;

typedef enum
{
	Repeat=0x00,
	Folder_repeat0x01,
	Single_repeat0x02,
	Shuffle=0x03



}playbackmode_type;

typedef enum
{

	U = 0x00,
	TF=0x01,
	AUX =0x02,
	SLEEP= 0x03,
	FLASH_SRC = 0x04

}playbacksrc_type;

void deplayer_send_cmd(uint8_t cmd,uint8_t para1, uint8_t para2 );
void dfplayer_init(void);
void dfplayer_play_first_track(void);
void dfplayer_play_pause_track(void);
#endif

