/*
 * copro_commands.h
 *
 *  Created on: Jul 16, 2018
 *      Author: Besitzer
 */

#ifndef COPRO_COMMANDS_H_
#define COPRO_COMMANDS_H_

/************************************************************************/
/*                		Includes                                		*/
/************************************************************************/
#include "stdint.h"
/************************************************************************/
/*                		Definitions                               		*/
/************************************************************************/

/************************************************************************/
/*                		Constants                               		*/
/************************************************************************/

/************************************************************************/
/*                		Variables	                              		*/
/************************************************************************/

/************************************************************************/
/*                		Global Variables                           		*/
/************************************************************************/

/************************************************************************/
/*                		Local Functions                           		*/
/************************************************************************/

void cmd_clock(int x, int y, int r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms);
void cmd_gauge(int x, int y, int r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range);
void cmd_text(int x, int y, int font, int options, char* s);
void cmd_number(int x, int y, int font, int options, uint32_t n);
void cmd_track(int x, int y, int w, int h, int tag);
void cmd_bgcolor(uint32_t x);
void cmd_fgcolor(uint32_t x);
void cmd_button(int x,int y, int w, int h, int font, int options, char* s);
void cmd_dial(int x, int y, int r, uint16_t options, uint16_t val);
void cmd_keys(int x,int y, int w, int h, int font, int options, char* s);
void cmd_gradient(int x0, int y0, uint32_t rgb0, int x1, int y1, uint32_t rgb1);
void cmd_progress(int x, int y, int w, int h, uint16_t options, uint16_t val, uint16_t range);
void cmd_scrollbar(int x, int y, int w, int h, int options, int val, int size, int range);
void cmd_slider(int x, int y, int w, int h, uint16_t options, uint16_t val, uint16_t range);
void cmd_spinner(int x, int y, uint16_t style, uint16_t scale);
void cmd_coldstart(void);
void cmd_dlstart(void);
void cmd_stop(void);
void cmd_setfont(uint32_t font, uint32_t ptr);
void cmd_swap();
void cmd_logo(void);
void cmd_memzero(uint32_t ptr,uint32_t num);
void cmd_calibrate(void);
void cmd();

#endif /* COPRO_COMMANDS_H_ */
