/*
 * FT800_SPI.c
 *
 *  Created on: Jul 16, 2018
 *      Author: Besitzer
 */



/************************************************************************/
/*                		Includes                                		*/
/************************************************************************/
#include "FT800_HAL.h"

/************************************************************************/
/*                		Definitions                               		*/
/************************************************************************/	

////////////// Values for MEMORY_ACCESS_CONTROL register ///////////////////////
#define DEG0_NORMAL     0x08
#define DEG0_BMP        0x88
#define DEG90_NORMAL    0xA8
#define DEG90_BMP       0xE8
#define DEG180_NORMAL   0xC8      
#define DEG180_BMP      0x48
#define DEG270_NORMAL   0x68
#define DEG270_BMP      0x28

#define ft_pgm_read_byte(x)        (*(x))

#define Pi  3.14159
//////////////////// SPI Transfer description byte /////////////////////////////

//#define ID 1					// Use this if BS0 is connected to High
  #define ID 0					// Use this if BS0 is connected to low

///////////////////////////////////////////////////////////////////////////////

#define INDEX_WRITE       (0x70 | DisplayID)
#define REG_WRITE         (0x72 | DisplayID)
#define REG_READ          (0x73 | DisplayID)
#define INDEX_WRITE_WORD  ((INDEX_WRITE)<<8)
#define REG_WRITE_WORD    ((REG_WRITE)<<8)
#define REG_READ_WORD     ((REG_READ)<<8)

#define ChipOn  1      
#define ChipOff 0 

#define EVE_Power_off  	FT800_nPowerDown_ClrVal();
#define EVE_Power_on   	FT800_nPowerDown_SetVal();
/************************************************************************/
/*                		Constants                               		*/
/************************************************************************/

/************************************************************************/
/*                		Variables	                              		*/
/************************************************************************/
uint8_t fdhdgg[]={60,80,62,80,64,80,65,80,67,80,0,0};
extern unsigned int dli,cli;
extern unsigned time;
extern uint32_t currfreq;// = 40;

uint16_t __ft_cmd_fifo_wp = 0; //FT800 coprocessor fifo write pointer
extern uint16_t lum;
extern uint16_t ms,sek,hr,min;
/************************************************************************/
/*                		Global Variables                           		*/
/************************************************************************/

/************************************************************************/
/*                		Local Functions                           		*/
/************************************************************************/
void SelectChipOnOff(uint8_t ChipOnOff);
/************************************************************************
/! \fn			void SelectChipOnOff(uint8_t ChipOnOff)
*  \brief		switch CSN Signal
*  \param		uint8_t ChipOnOff
*  \exception	none
*  \return		none
************************************************************************/
void SelectChipOnOff(uint8_t ChipOnOff){
	
    unsigned char go=1;
    uint32_t timeout=1000000;
    if (ChipOnOff == ChipOn)
        FT800_nCS_ClrVal();
    else if (ChipOnOff == ChipOff){
        while(go){
            timeout--;
            if(timeout==0)go=0;    
            //if(USART_StatusGet()) 
            go=0;  //wait until TXC
        } 
    FT800_nCS_SetVal();  
    } 
        
}
/************************************************************************
/! \fn			void host_command(uint8_t cmd)
*  \brief		send host command
*  \param		uint8_t cmd
*  \exception	none
*  \return		none
************************************************************************/
void host_command(uint8_t cmd){
	
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar(cmd); 
    FT800_SPI_SendChar(0);
    FT800_SPI_SendChar(0);
    SelectChipOnOff(ChipOff);
}

/************************************************************************
/! \fn			void wr8(uint32_t address, uint8_t data)
*  \brief		write uint8_t data
*  \param		uint32_t address, uint8_t data
*  \exception	none
*  \return		none
************************************************************************/
void wr8(uint32_t address, uint8_t data){
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar ((uint8_t)(0x80|(address>>16)));
    FT800_SPI_SendChar ((uint8_t)(address>>8));
    FT800_SPI_SendChar ((uint8_t)(address));
    FT800_SPI_SendChar (data);
    SelectChipOnOff(ChipOff);
}

/************************************************************************
/! \fn			void wr16(uint32_t address, uint16_t data)
*  \brief		write uint16_t data
*  \param		uint32_t address, uint16_t data
*  \exception	none
*  \return		none
************************************************************************/
void wr16(uint32_t address, uint16_t data){
	
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar ((uint8_t)(0x80|(address>>16)));
    FT800_SPI_SendChar ((uint8_t)(address>>8));
    FT800_SPI_SendChar ((uint8_t)(address));
    FT800_SPI_SendChar ((uint8_t)(0xff&(data)));
    FT800_SPI_SendChar ((uint8_t)(0xff&(data>>8)));
    SelectChipOnOff(ChipOff);
}
/************************************************************************
/! \fn			void wr32(uint32_t address, uint32_t data)
*  \brief		write uint32_t data
*  \param		uint32_t address, uint32_t data
*  \exception	none
*  \return		none
************************************************************************/
void wr32(uint32_t address, uint32_t data){
	SelectChipOnOff(ChipOn);
	FT800_SPI_SendChar ((uint8_t)(0x80|(address>>16)));
	FT800_SPI_SendChar ((uint8_t)(address>>8));
	FT800_SPI_SendChar ((uint8_t)(address));
	FT800_SPI_SendChar ((uint8_t)(0xff&(data)));
	FT800_SPI_SendChar ((uint8_t)(0xff&(data>>8)));
	FT800_SPI_SendChar ((uint8_t)(0xff&(data>>16)));
    FT800_SPI_SendChar ((uint8_t)(0xff&(data>>24)));
	SelectChipOnOff(ChipOff);
}
/************************************************************************
/! \fn			uint8_t rd8(uint32_t address)
*  \brief		read an uint8_t value from adress
*  \param		uint32_t address
*  \exception	none
*  \return		uint8_t data
************************************************************************/
uint8_t rd8(uint32_t address){
    uint8_t data=0;
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar ((uint8_t)(0x00|(address>>16)));
    FT800_SPI_SendChar ((uint8_t)(address>>8));
    FT800_SPI_SendChar ((uint8_t)(address));
    FT800_SPI_SendChar (0x0);    //Dummybyte
    data=FT800_SPI_RecvChar();
    SelectChipOnOff(ChipOff);
    return (data);
}
/************************************************************************
/! \fn			uint16_t rd16(uint32_t address)
*  \brief		read an uint16_t value from adress
*  \param		uint32_t address
*  \exception	none
*  \return		uint16_t data
************************************************************************/
uint16_t rd16(uint32_t address){
	
    uint32_t data=0;
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar ((uint8_t)(0x00|(address>>16)));
    FT800_SPI_SendChar ((uint8_t)(address>>8));
    FT800_SPI_SendChar ((uint8_t)(address));
    FT800_SPI_SendChar (0x0);    //Dummybyte
    data=FT800_SPI_RecvChar();
    data|=FT800_SPI_RecvChar()<<8;
    SelectChipOnOff(ChipOff);
    return ((uint16_t)data);
}
/************************************************************************
/! \fn			uint32_t rd32(uint32_t address)
*  \brief		read an uint32_t value from adress
*  \param		uint32_t address
*  \exception	none
*  \return		uint32_t data
************************************************************************/
uint32_t rd32(uint32_t address){
	
    uint32_t data=0;
    SelectChipOnOff(ChipOn);
    FT800_SPI_SendChar ((uint8_t)(0x00|(address>>16)));
    FT800_SPI_SendChar ((uint8_t)(address>>8));
    FT800_SPI_SendChar ((uint8_t)(address));
    FT800_SPI_SendChar (0x0);    //Dummybyte
    data=FT800_SPI_RecvChar();
    data|=FT800_SPI_RecvChar()<<8;
    data|=FT800_SPI_RecvChar()<<16;
    data|=FT800_SPI_RecvChar()<<24;
    SelectChipOnOff(ChipOff);
    return (data);
}

/************************************************************************
/! \fn			uint8_t EVE_BootUp(void)
*  \brief		boot the FT800
*  \param		none
*  \exception	none
*  \return		uint8_t data
************************************************************************/
uint8_t EVE_BootUp(void){
	
    unsigned int x;

    EVE_Power_on; 
    EVE_Power_off; 
    for (x=0;x<1000000;x++)
    	;
    EVE_Power_on; 
    for (x=0;x<1000000;x++)
    	;
    //<11MHz SPI-Clock
    //read location 0 to wake up FT800
    host_command(ACTIVE);
    //send command to change the PLL to external clock
    host_command(CLKEXT);
	return OK;
}  

/************************************************************************
/! \fn			void updatecmdfifo(uint16_t count)
*  \brief		update cmd queue
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void updatecmdfifo(uint16_t count){
  
    __ft_cmd_fifo_wp  = (__ft_cmd_fifo_wp + count) & 4095;

    //4 byte alignment
    __ft_cmd_fifo_wp = (__ft_cmd_fifo_wp + 3) & 0xffc;
    wr16(REG_CMD_WRITE,__ft_cmd_fifo_wp);

}

/************************************************************************
/! \fn			void waitcmdfifo_empty()
*  \brief		Wait for the complete consumption of Coprocessor commands
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void waitcmdfifo_empty(){
    int cmdrdptr,cmdwrptr;

	do{
		cmdrdptr = rd16(REG_CMD_READ);
		cmdwrptr = rd16(REG_CMD_WRITE);
	}while (cmdwrptr != cmdrdptr);
    __ft_cmd_fifo_wp =rd16(REG_CMD_WRITE);
}
/************************************************************************
/! \fn			recover_co_processor()
*  \brief		reset coprocessor
*  \param		none
*  \exception	none
*  \return		none
************************************************************************/
void recover_co_processor(){
    wr8(REG_CPURESET,1);
    wr32(REG_CMD_WRITE,0);
    wr32(REG_CMD_READ,0);
    wr8(REG_CPURESET,0);
} 
