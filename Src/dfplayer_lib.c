
#include <stdio.h>
#include "dfplayer_lib.h"
#include <stdint.h>
#include <stdbool.h>

#include "uart.h"
#include "bsp.h"
#include "timebase.h"
#include "circular_buffer.h"


//portType  debug_port =DEBUG_PORT;
//portType slave_device_port=SLAVE_DEV_PORT;

//#define defplayer_port slave_device_port

//#define slave_device_port
#define CMD_FRAME_LEN 10
#define SHORT 200
#define LONG 500

#define NORMAL_VOL   30
#define START_REPEAT_PLAY   1


void deplayer_send_cmd(uint8_t cmd,uint8_t para1, uint8_t para2 ){
	uint16_t checksum;
	buffer_clear(SLAVE_DEV_PORT);
	checksum= VERSION_INFO+CMD_LEN+cmd+FEEDBACK_EN+para1+para2;
	checksum= ~checksum +1;
	uint8_t high_check_sum=(uint8_t)(checksum>>8)&0x00FF;
	uint8_t low_check_sum=(uint8_t)(checksum)&0x00FF;

	uint8_t cmd_frame[CMD_FRAME_LEN] ={START_BYTE,VERSION_INFO,CMD_LEN,cmd,FEEDBACK_EN,para1,para2,high_check_sum,low_check_sum,END_BYTE};
	buffer_send_byte(cmd_frame,sizeof(cmd_frame),SLAVE_DEV_PORT);

}
void dfplayer_init(void)
{

	deplayer_send_cmd(CMD_INIT_PARAM,NULL_PARM,PLAY_SOURCE_TF_CARD);
	delay(SHORT);
	deplayer_send_cmd(CMD_SET_VOL,NULL_PARM,NORMAL_VOL);
	delay(LONG);

}

void dfplayer_play_first_track(void){

	deplayer_send_cmd(CMD_REPEAT_PLAY,NULL_PARM,START_REPEAT_PLAY);
		delay(LONG);

}



void dfplayer_play_next_track(void){

	deplayer_send_cmd(CMD_NEXT,NULL_PARM,NULL_PARM);
		delay(LONG);

}


void dfplayer_play_prev_track(void){

	deplayer_send_cmd(CMD_NEXT,NULL_PARM,NULL_PARM);
		delay(LONG);

}


void dfplayer_play_pause_track(void){

	deplayer_send_cmd(CMD_PAUSE,NULL_PARM,NULL_PARM);
		delay(LONG);

}

void dfplayer_play_back_track(void){

	deplayer_send_cmd(CMD_PLAYBACK,NULL_PARM,TF);
		delay(LONG);

}


