
/*

Copyright (c) Future Technology Devices International 2014

THIS SOFTWARE IS PROVIDED BY FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FTDI DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON FTDI PARTS.

FTDI DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE INFORMATION IS NOT MODIFIED.

IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED, IT IS THE
RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES AND SUBSEQUENT WHQL
RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.


*/

#include "FT_Platform.h"

#ifdef FT900_PLATFORM
#include "ff.h"
#endif

#define F16(s)        ((ft_int32_t)((s) * 65536))
#define WRITE2CMD(a) Ft_Gpu_Hal_WrCmdBuf(phost,a,sizeof(a))
#define SCRATCH_BUFF_SZ 2048 //increase this value will increase the performance but will use more host RAM space.

/* Global variables for display resolution to support various display panels */
/* Default is WQVGA - 480x272 */
ft_int16_t FT_DispWidth = 480;
ft_int16_t FT_DispHeight = 272;
ft_int16_t FT_DispHCycle =  548;
ft_int16_t FT_DispHOffset = 43;
ft_int16_t FT_DispHSync0 = 0;
ft_int16_t FT_DispHSync1 = 41;
ft_int16_t FT_DispVCycle = 292;
ft_int16_t FT_DispVOffset = 12;
ft_int16_t FT_DispVSync0 = 0;
ft_int16_t FT_DispVSync1 = 10;
ft_uint8_t FT_DispPCLK = 5;
ft_char8_t FT_DispSwizzle = 0;
ft_char8_t FT_DispPCLKPol = 1;
ft_char8_t FT_DispCSpread = 1;
ft_char8_t FT_DispDither = 1;

/* Global used for buffer optimization */
Ft_Gpu_Hal_Context_t host,*phost;

ft_uint32_t Ft_CmdBuffer_Index;
ft_uint32_t Ft_DlBuffer_Index;

#ifdef FT900_PLATFORM
FATFS FatFs;
FIL 			 CurFile;
FRESULT          fResult;
SDHOST_STATUS    SDHostStatus;

DWORD get_fattime (void)
{
	/* Returns current time packed into a DWORD variable */
	return 0;
}
#endif

#ifdef BUFFER_OPTIMIZATION
ft_uint8_t  Ft_DlBuffer[FT_DL_SIZE];
ft_uint8_t  Ft_CmdBuffer[FT_CMD_FIFO_SIZE];
#endif
/* Boot up for FT800 followed by graphics primitive sample cases */
/* Initial boot up DL - make the back ground green color */
const ft_uint8_t FT_DLCODE_BOOTUP[12] =
{
    255,0,0,2,//GPU instruction CLEAR_COLOR_RGB
    7,0,0,38, //GPU instruction CLEAR

    0,0,0,0,  //GPU instruction DISPLAY
};
ft_void_t Ft_App_WrCoCmd_Buffer(Ft_Gpu_Hal_Context_t *phost,ft_uint32_t cmd)
{
#ifdef  BUFFER_OPTIMIZATION
   /* Copy the command instruction into buffer */
   ft_uint32_t *pBuffcmd;
   pBuffcmd =(ft_uint32_t*)&Ft_CmdBuffer[Ft_CmdBuffer_Index];
   *pBuffcmd = cmd;
#endif
#ifdef ARDUINO_PLATFORM
   Ft_Gpu_Hal_WrCmd32(phost,cmd);
#endif
#ifdef FT900_PLATFORM
   Ft_Gpu_Hal_WrCmd32(phost,cmd);
#endif
   /* Increment the command index */
   Ft_CmdBuffer_Index += FT_CMD_SIZE;
}

ft_void_t Ft_App_WrDlCmd_Buffer(Ft_Gpu_Hal_Context_t *phost,ft_uint32_t cmd)
{
#ifdef BUFFER_OPTIMIZATION
   /* Copy the command instruction into buffer */
   ft_uint32_t *pBuffcmd;
   pBuffcmd =(ft_uint32_t*)&Ft_DlBuffer[Ft_DlBuffer_Index];
   *pBuffcmd = cmd;
#endif

#ifdef ARDUINO_PLATFORM
   Ft_Gpu_Hal_Wr32(phost,(RAM_DL+Ft_DlBuffer_Index),cmd);
#endif
#ifdef FT900_PLATFORM
   Ft_Gpu_Hal_Wr32(phost,(RAM_DL+Ft_DlBuffer_Index),cmd);
#endif
   /* Increment the command index */
   Ft_DlBuffer_Index += FT_CMD_SIZE;
}

ft_void_t Ft_App_WrCoStr_Buffer(Ft_Gpu_Hal_Context_t *phost,const ft_char8_t *s)
{
#ifdef  BUFFER_OPTIMIZATION
  ft_uint16_t length = 0;
  length = strlen(s) + 1;//last for the null termination

  strcpy(&Ft_CmdBuffer[Ft_CmdBuffer_Index],s);

  /* increment the length and align it by 4 bytes */
  Ft_CmdBuffer_Index += ((length + 3) & ~3);
#endif
}

ft_void_t Ft_App_Flush_DL_Buffer(Ft_Gpu_Hal_Context_t *phost)
{
#ifdef  BUFFER_OPTIMIZATION
   if (Ft_DlBuffer_Index> 0)
     Ft_Gpu_Hal_WrMem(phost,RAM_DL,Ft_DlBuffer,Ft_DlBuffer_Index);
#endif
   Ft_DlBuffer_Index = 0;

}

ft_void_t Ft_App_Flush_Co_Buffer(Ft_Gpu_Hal_Context_t *phost)
{
#ifdef  BUFFER_OPTIMIZATION
   if (Ft_CmdBuffer_Index > 0)
     Ft_Gpu_Hal_WrCmdBuf(phost,Ft_CmdBuffer,Ft_CmdBuffer_Index);
#endif
   Ft_CmdBuffer_Index = 0;
}


/* API to give fadeout effect by changing the display PWM from 100 till 0 */
ft_void_t SAMAPP_fadeout()
{
   ft_int32_t i;

    for (i = 100; i >= 0; i -= 3)
    {
        Ft_Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);

        Ft_Gpu_Hal_Sleep(2);//sleep for 2 ms
    }
}

/* API to perform display fadein effect by changing the display PWM from 0 till 100 and finally 128 */
ft_void_t SAMAPP_fadein()
{
    ft_int32_t i;

    for (i = 0; i <=100 ; i += 3)
    {
        Ft_Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);
        Ft_Gpu_Hal_Sleep(2);//sleep for 2 ms
    }
    /* Finally make the PWM 100% */
    i = 128;
    Ft_Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);
}


/* API to check the status of previous DLSWAP and perform DLSWAP of new DL */
/* Check for the status of previous DLSWAP and if still not done wait for few ms and check again */
ft_void_t SAMAPP_GPU_DLSwap(ft_uint8_t DL_Swap_Type)
{
    ft_uint8_t Swap_Type = DLSWAP_FRAME,Swap_Done = DLSWAP_FRAME;

    if(DL_Swap_Type == DLSWAP_LINE)
    {
        Swap_Type = DLSWAP_LINE;
    }

    /* Perform a new DL swap */
    Ft_Gpu_Hal_Wr8(phost,REG_DLSWAP,Swap_Type);

    /* Wait till the swap is done */
    while(Swap_Done)
    {
        Swap_Done = Ft_Gpu_Hal_Rd8(phost,REG_DLSWAP);

        if(DLSWAP_DONE != Swap_Done)
        {
            Ft_Gpu_Hal_Sleep(10);//wait for 10ms
        }
    }
}

ft_void_t Ft_BootupConfig()
{
    Ft_Gpu_Hal_Powercycle(phost,FT_TRUE);

        /* Access address 0 to wake up the FT800 */
        Ft_Gpu_HostCommand(phost,FT_GPU_ACTIVE_M);
        Ft_Gpu_Hal_Sleep(20);

        /* Set the clk to external clock */
#ifndef ME800A_HV35R
        Ft_Gpu_HostCommand(phost,FT_GPU_EXTERNAL_OSC);
        Ft_Gpu_Hal_Sleep(10);
#endif

        {
            ft_uint8_t chipid;
            //Read Register ID to check if FT800 is ready.
            chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);
            while(chipid != 0x7C)
            {
                chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);
                ft_delay(100);
            }
    #if defined(MSVC_PLATFORM) || defined (FT900_PLATFORM)
            printf("VC1 register ID after wake up %x\n",chipid);
    #endif
    }
    /* Configuration of LCD display */
#ifdef DISPLAY_RESOLUTION_QVGA
    /* Values specific to QVGA LCD display */
    FT_DispWidth = 320;
    FT_DispHeight = 240;
    FT_DispHCycle =  408;
    FT_DispHOffset = 70;
    FT_DispHSync0 = 0;
    FT_DispHSync1 = 10;
    FT_DispVCycle = 263;
    FT_DispVOffset = 13;
    FT_DispVSync0 = 0;
    FT_DispVSync1 = 2;
    FT_DispPCLK = 8;
    FT_DispSwizzle = 2;
    FT_DispPCLKPol = 0;
    FT_DispCSpread = 1;
    FT_DispDither = 1;

#endif
#ifdef DISPLAY_RESOLUTION_WVGA
    /* Values specific to QVGA LCD display */
    FT_DispWidth = 800;
    FT_DispHeight = 480;
    FT_DispHCycle =  928;
    FT_DispHOffset = 88;
    FT_DispHSync0 = 0;
    FT_DispHSync1 = 48;
    FT_DispVCycle = 525;
    FT_DispVOffset = 32;
    FT_DispVSync0 = 0;
    FT_DispVSync1 = 3;
    FT_DispPCLK = 2;
    FT_DispSwizzle = 0;
    FT_DispPCLKPol = 1;
    FT_DispCSpread = 0;
    FT_DispDither = 1;
#endif
#ifdef DISPLAY_RESOLUTION_HVGA_PORTRAIT
    /* Values specific to HVGA LCD display */

    FT_DispWidth = 320;
    FT_DispHeight = 480;
    FT_DispHCycle =  400;
    FT_DispHOffset = 40;
    FT_DispHSync0 = 0;
    FT_DispHSync1 = 10;
    FT_DispVCycle = 500;
    FT_DispVOffset = 10;
    FT_DispVSync0 = 0;
    FT_DispVSync1 = 5;
    FT_DispPCLK = 4;
    FT_DispSwizzle = 2;
    FT_DispPCLKPol = 1;
    FT_DispCSpread = 1;
    FT_DispDither = 1;

#endif

#ifdef ME800A_HV35R
    /* After recognizing the type of chip, perform the trimming if necessary */
    Ft_Gpu_ClockTrimming(phost,LOW_FREQ_BOUND);
#endif

    Ft_Gpu_Hal_Wr16(phost, REG_HCYCLE, FT_DispHCycle);
    Ft_Gpu_Hal_Wr16(phost, REG_HOFFSET, FT_DispHOffset);
    Ft_Gpu_Hal_Wr16(phost, REG_HSYNC0, FT_DispHSync0);
    Ft_Gpu_Hal_Wr16(phost, REG_HSYNC1, FT_DispHSync1);
    Ft_Gpu_Hal_Wr16(phost, REG_VCYCLE, FT_DispVCycle);
    Ft_Gpu_Hal_Wr16(phost, REG_VOFFSET, FT_DispVOffset);
    Ft_Gpu_Hal_Wr16(phost, REG_VSYNC0, FT_DispVSync0);
    Ft_Gpu_Hal_Wr16(phost, REG_VSYNC1, FT_DispVSync1);
    Ft_Gpu_Hal_Wr8(phost, REG_SWIZZLE, FT_DispSwizzle);
    Ft_Gpu_Hal_Wr8(phost, REG_PCLK_POL, FT_DispPCLKPol);
    Ft_Gpu_Hal_Wr16(phost, REG_HSIZE, FT_DispWidth);
    Ft_Gpu_Hal_Wr16(phost, REG_VSIZE, FT_DispHeight);
    Ft_Gpu_Hal_Wr16(phost, REG_CSPREAD, FT_DispCSpread);
    Ft_Gpu_Hal_Wr16(phost, REG_DITHER, FT_DispDither);

#if (defined(ENABLE_FT_800) || defined(ENABLE_FT_810) ||defined(ENABLE_FT_812))
    /* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
    Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,RESISTANCE_THRESHOLD);
#endif
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO_DIR,0xff);
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0xff);


    /*It is optional to clear the screen here*/
    Ft_Gpu_Hal_WrMem(phost, RAM_DL,(ft_uint8_t *)FT_DLCODE_BOOTUP,sizeof(FT_DLCODE_BOOTUP));
    Ft_Gpu_Hal_Wr8(phost, REG_DLSWAP,DLSWAP_FRAME);


    Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD


#ifdef ENABLE_ILI9488_HVGA_PORTRAIT
    /* to cross check reset pin */
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0xff);
    ft_delay(120);
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0x7f);
    ft_delay(120);
    Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0xff);

    ILI9488_Bootup();

    /* Reconfigure the SPI */
#ifdef FT900_PLATFORM
    printf("after ILI9488 bootup \n");
    //spi
    // Initialize SPIM HW
    sys_enable(sys_device_spi_master);
    gpio_function(27, pad_spim_sck); /* GPIO27 to SPIM_CLK */
    gpio_function(28, pad_spim_ss0); /* GPIO28 as CS */
    gpio_function(29, pad_spim_mosi); /* GPIO29 to SPIM_MOSI */
    gpio_function(30, pad_spim_miso); /* GPIO30 to SPIM_MISO */

    gpio_write(28, 1);
    spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
#endif

#endif



    /* make the spi to quad mode - addition 2 bytes for silicon */
#ifdef FT_81X_ENABLE
    /* api to set quad and numbe of dummy bytes */
#ifdef ENABLE_SPI_QUAD
    Ft_Gpu_Hal_SetSPI(phost,FT_GPU_SPI_QUAD_CHANNEL,FT_GPU_SPI_TWODUMMY);
#elif ENABLE_SPI_DUAL
    Ft_Gpu_Hal_SetSPI(phost,FT_GPU_SPI_QUAD_CHANNEL,FT_GPU_SPI_TWODUMMY);
#else
    Ft_Gpu_Hal_SetSPI(phost,FT_GPU_SPI_SINGLE_CHANNEL,FT_GPU_SPI_ONEDUMMY);

#endif

#ifdef FT900_PLATFORM
    spi_init(SPIM, spi_dir_master, spi_mode_0, 32);
#ifdef ENABLE_SPI_QUAD
    spi_option(SPIM,spi_option_bus_width,4);
#elif ENABLE_SPI_DUAL
    spi_option(SPIM,spi_option_bus_width,2);
#else
    spi_option(SPIM,spi_option_bus_width,1);
#endif

    spi_option(SPIM,spi_option_fifo_size,64);
    spi_option(SPIM,spi_option_fifo,1);
    spi_option(SPIM,spi_option_fifo_receive_trigger,1);

#endif

#endif
phost->ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(phost,REG_CMD_WRITE);

}




#ifdef FT900_PLATFORM
    ft_void_t FT900_Config()
{
        sys_enable(sys_device_uart0);
        gpio_function(48, pad_uart0_txd); /* UART0 TXD */
        gpio_function(49, pad_uart0_rxd); /* UART0 RXD */
        uart_open(UART0,                    /* Device */
                  1,                        /* Prescaler = 1 */
                  UART_DIVIDER_115200_BAUD,  /* Divider = 1302 */
                  uart_data_bits_8,         /* No. Data Bits */
                  uart_parity_none,         /* Parity */
                  uart_stop_bits_1);        /* No. Stop Bits */

        /* Print out a welcome message... */
        uart_puts(UART0,

            "(C) Copyright 2014-2015, Future Technology Devices International Ltd. \r\n"
            "--------------------------------------------------------------------- \r\n"
            );

#ifdef ENABLE_ILI9488_HVGA_PORTRAIT
    /* asign all the respective pins to gpio and set them to default values */
    gpio_function(34, pad_gpio34);
    gpio_dir(34, pad_dir_output);
    gpio_write(34,1);

    gpio_function(27, pad_gpio27);
    gpio_dir(27, pad_dir_output);
    gpio_write(27,1);

    gpio_function(29, pad_gpio29);
    gpio_dir(29, pad_dir_output);
    gpio_write(29,1);

    gpio_function(33, pad_gpio33);
    gpio_dir(33, pad_dir_output);
    gpio_write(33,1);


    gpio_function(30, pad_gpio30);
    gpio_dir(30, pad_dir_output);
    gpio_write(30,1);

    gpio_function(28, pad_gpio28);
    gpio_dir(28, pad_dir_output);
    gpio_write(28,1);


    gpio_function(43, pad_gpio43);
    gpio_dir(43, pad_dir_output);
    gpio_write(43,1);
    gpio_write(34,1);
    gpio_write(28,1);
    gpio_write(43,1);
    gpio_write(33,1);
    gpio_write(33,1);

#endif
}
#endif




ft_void_t loadDataToCoprocessorCMDfifo(ft_char8_t* fileName){
#if defined(FT900_PLATFORM)
    ft_uint32_t fResult, fileLen;
    ft_uint32_t bytesread;
    FIL CurFile;
    ft_uint8_t pBuff[SCRATCH_BUFF_SZ];
    fResult = f_open(&CurFile, fileName, FA_READ);

    if(fResult == FR_OK){
    fileLen = f_size(&CurFile);
    while(fileLen > 0){
        ft_uint32_t blocklen = fileLen>SCRATCH_BUFF_SZ?SCRATCH_BUFF_SZ:fileLen;
        fResult = f_read(&CurFile,pBuff,blocklen,&bytesread);
        fileLen -= bytesread;
        Ft_Gpu_Hal_WrCmdBuf(phost,pBuff, bytesread);//alignment is already taken care by this api
    }
    f_close(&CurFile);
    }
    else{
        printf("Unable to open file\n");
    }


#else
    FILE *fp;
    ft_uint32_t fileLen;
    ft_uint8_t pBuff[SCRATCH_BUFF_SZ];
    fp = fopen(fileName, "rb+");

    if(fp){

        fseek(fp,0,SEEK_END);
        fileLen = ftell(fp);
        fseek(fp,0,SEEK_SET);
        while(fileLen > 0)
        {
            ft_uint32_t blocklen = fileLen>SCRATCH_BUFF_SZ?SCRATCH_BUFF_SZ:fileLen;
            fread(pBuff,1,blocklen,fp);
            fileLen -= blocklen;
            Ft_Gpu_Hal_WrCmdBuf(phost,pBuff, blocklen);//alignment is already taken care by this api
        }
        fclose(fp);
    }else{
        printf("Unable to open file: %s\n",fileName);
        //exit(1);
    }
#endif
}



#if defined MSVC_PLATFORM || defined FT900_PLATFORM
/* Main entry point */
ft_int32_t main(ft_int32_t argc,ft_char8_t *argv[])
#endif
#if defined(ARDUINO_PLATFORM)||defined(MSVC_FT800EMU)
ft_void_t setup()
#endif
{
#ifdef FT900_PLATFORM
    FT900_Config();

    sys_enable(sys_device_sd_card);
    sdhost_init();

            #define GPIO_SD_CLK  (19)
            #define GPIO_SD_CMD  (20)
            #define GPIO_SD_DAT3 (21)
            #define GPIO_SD_DAT2 (22)
            #define GPIO_SD_DAT1 (23)
            #define GPIO_SD_DAT0 (24)
            #define GPIO_SD_CD   (25)
            #define GPIO_SD_WP   (26)
            gpio_function(GPIO_SD_CLK, pad_sd_clk); gpio_pull(GPIO_SD_CLK, pad_pull_none);//pad_pull_none
            gpio_function(GPIO_SD_CMD, pad_sd_cmd); gpio_pull(GPIO_SD_CMD, pad_pull_pullup);
            gpio_function(GPIO_SD_DAT3, pad_sd_data3); gpio_pull(GPIO_SD_DAT3, pad_pull_pullup);
            gpio_function(GPIO_SD_DAT2, pad_sd_data2); gpio_pull(GPIO_SD_DAT2, pad_pull_pullup);
            gpio_function(GPIO_SD_DAT1, pad_sd_data1); gpio_pull(GPIO_SD_DAT1, pad_pull_pullup);
            gpio_function(GPIO_SD_DAT0, pad_sd_data0); gpio_pull(GPIO_SD_DAT0, pad_pull_pullup);
            gpio_function(GPIO_SD_CD, pad_sd_cd); gpio_pull(GPIO_SD_CD, pad_pull_pullup);
            gpio_function(GPIO_SD_WP, pad_sd_wp); gpio_pull(GPIO_SD_WP, pad_pull_pullup);
#endif
    Ft_Gpu_HalInit_t halinit;

    halinit.TotalChannelNum = 1;


    Ft_Gpu_Hal_Init(&halinit);
    host.hal_config.channel_no = 0;
    host.hal_config.pdn_pin_no = FT800_PD_N;
    host.hal_config.spi_cs_pin_no = FT800_SEL_PIN;
#ifdef MSVC_PLATFORM_SPI
    host.hal_config.spi_clockrate_khz = 12000; //in KHz
#endif
#ifdef ARDUINO_PLATFORM_SPI
    host.hal_config.spi_clockrate_khz = 4000; //in KHz
#endif
        Ft_Gpu_Hal_Open(&host);
    phost = &host;

    Ft_BootupConfig();

#if ((defined FT900_PLATFORM) || defined(MSVC_PLATFORM))
    printf("\n reg_touch_rz =0x%x ", Ft_Gpu_Hal_Rd16(phost, REG_TOUCH_RZ));
    printf("\n reg_touch_rzthresh =0x%x ", Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_RZTHRESH));
  printf("\n reg_touch_tag_xy=0x%x",Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TAG_XY));
    printf("\n reg_touch_tag=0x%x",Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TAG));
#endif
#ifdef FT900_PLATFORM
      SDHOST_STATUS sd_status;
      //
    if(sdhost_card_detect() == SDHOST_CARD_INSERTED)
    { printf("-------------1---------------");
    printf("\n sd_status=%s",sdhost_card_detect());
    }

        if (sdhost_card_detect() != SDHOST_CARD_INSERTED)
        {
        printf("Please Insert SD Card\r\n");
        }
        else
        { printf("\n SD Card inserted!");}


        if (f_mount(&FatFs, "", 0) != FR_OK)
        {
            printf("\n Mounted failed.");;
        }

            printf("\n Mounted succesfully.");

#endif

    /*It is optional to clear the screen here*/
    Ft_Gpu_Hal_WrMem(phost, RAM_DL,(ft_uint8_t *)FT_DLCODE_BOOTUP,sizeof(FT_DLCODE_BOOTUP));
    Ft_Gpu_Hal_Wr8(phost, REG_DLSWAP,DLSWAP_FRAME);

    Ft_Gpu_Hal_Sleep(1000);//Show the booting up screen.
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(31, 63, 127));
	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1, 1, 1));
	

    Ft_App_WrCoCmd_Buffer(phost, DISPLAY());
    Ft_Gpu_CoCmd_Swap(phost);
    Ft_App_Flush_Co_Buffer(phost);
    Ft_Gpu_Hal_WaitCmdfifo_empty(phost);



    /* Close all the opened handles */
    Ft_Gpu_Hal_Close(phost);
    Ft_Gpu_Hal_DeInit();
#ifdef MSVC_PLATFORM || defined FT900_PLATFORM
    return 0;
#endif
}

void loop()
{
}



/* Nothing beyond this */
