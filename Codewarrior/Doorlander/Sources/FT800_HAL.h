/*
 * FT800_HAL.h
 *
 *  Created on: Jul 16, 2018
 *      Author: Besitzer
 */

#ifndef FT800_HAL_H_
#define FT800_HAL_H_


/************************************************************************/
/*                		Includes                                		*/
/************************************************************************/
#include "stdint.h"
#include "FT800_SPI.h"
#include "FT800_nPowerDown.h"
#include "FT800_nCS.h"
#include "FT_Gpu.h"
#include "copro_commands.h"
/************************************************************************/
/*                		Definitions                               		*/
/************************************************************************/	
#define INCR                 3UL
#define ZERO                 0UL
#define GEQUAL               4UL
#define ALWAYS               7UL
#define KEEP                 1UL

//Host Commands
#define ACTIVE               0x00
#define STANDBY              0x41
#define SLEEP                0x42
#define PWRDOWN              0x50
#define CLKEXT               0x44
#define CLK48M               0x62
#define CLK36M               0x61
#define CORERST              0x68

#define OPT_CENTER           1536UL
#define OPT_CENTERX          512UL
#define OPT_CENTERY          1024UL
#define OPT_FLAT             256UL
#define OPT_MONO             1UL
#define OPT_NOBACK           4096UL
#define OPT_NODL             2UL
#define OPT_NOHANDS          49152UL
#define OPT_NOHM             16384UL
#define OPT_NOPOINTER        16384UL
#define OPT_NOSECS           32768UL
#define OPT_NOTICKS          8192UL
#define OPT_RIGHTX           2048UL
#define OPT_SIGNED           256UL
#define PALETTED             8UL
#define FTPOINTS             2UL
#define ERROR 1
#define OK    0
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
void host_command(uint8_t cmd);
void wr8(uint32_t address, uint8_t data);
void wr16(uint32_t address, uint16_t data);
void wr32(uint32_t address, uint32_t data);
uint8_t rd8(uint32_t address);
uint16_t rd16(uint32_t address);
uint32_t rd32(uint32_t address);
uint8_t EVE_BootUp(void);
void updatecmdfifo(uint16_t count);
void waitcmdfifo_empty();
void recover_co_processor();
/*void test_disp(void);
void test_disp2(uint16_t loops);
void test(void);
void updatecmdfifo(uint16_t count);
void waitcmdfifo_empty();
void play_sound(uint8_t sound, uint8_t note, uint8_t volume);
void play_song(uint8_t device,uint8_t vol,  uint8_t *song);
void video_timing(void);
void cmd_dlstart(void);
void Logo();
void test_number();
void Touch();
void Time();
void Time2(uint16_t sek, uint16_t min, uint16_t hr);
void CLEAR_FRAMES();
void SAMAPP_Sound();
void GPU_Ball_Stencil();
void demo_IO();*/

#endif /* FT800_HAL_H_ */
