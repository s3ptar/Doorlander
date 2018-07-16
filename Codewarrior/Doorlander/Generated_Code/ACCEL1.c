/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ACCEL1.c
**     Project     : Doorlander
**     Processor   : MCF51JM128VLH
**     Component   : MMA7260Q
**     Version     : Component 01.111, Driver 01.00, CPU db: 3.00.063
**     Compiler    : CodeWarrior ColdFireV1 C Compiler
**     Date/Time   : 2018-07-15, 09:31, # CodeGen: 16
**     Abstract    :
**
**     Settings    :
**          Component name                                 : ACCEL1
**          HW Interface                                   : 
**            G Select                                     : Enabled
**              G Select 1 Signal                          : Accel_Gselect
**              G Select 2 Signal                          : Accel_Gselect
**            Sleep                                        : Enabled
**              Sleep Signal                               : Accel_Sleep
**              Enabled in init                            : yes
**              Enable/Disable A/D                         : no
**            A/D                                          : 
**              A/D Converter                              : AD1
**              X channel                                  : 0
**              Y channel                                  : 1
**              Z channel                                  : 2
**          Calibration                                    : 
**            X offset                                     : 0
**            X 1g value                                   : 6000
**            Y offset                                     : 0
**            Y 1g value                                   : 6000
**            Z offset                                     : 0
**            Z 1g value                                   : 6000
**          System                                         : 
**            Wait                                         : WAIT1
**          Shell                                          : Disabled
**     Contents    :
**         GetX           - int16_t ACCEL1_GetX(void);
**         GetY           - int16_t ACCEL1_GetY(void);
**         GetZ           - int16_t ACCEL1_GetZ(void);
**         Gselect        - void ACCEL1_Gselect(byte gSelect);
**         SensorOn       - void ACCEL1_SensorOn(void);
**         SensorOff      - void ACCEL1_SensorOff(void);
**         CalibrateX1g   - void ACCEL1_CalibrateX1g(void);
**         CalibrateY1g   - void ACCEL1_CalibrateY1g(void);
**         CalibrateZ1g   - void ACCEL1_CalibrateZ1g(void);
**         GetXmg         - int16_t ACCEL1_GetXmg(void);
**         GetYmg         - int16_t ACCEL1_GetYmg(void);
**         GetZmg         - int16_t ACCEL1_GetZmg(void);
**         MeasureGetRawX - word ACCEL1_MeasureGetRawX(void);
**         MeasureGetRawY - word ACCEL1_MeasureGetRawY(void);
**         MeasureGetRawZ - word ACCEL1_MeasureGetRawZ(void);
**         GetXOffset     - int16_t ACCEL1_GetXOffset(void);
**         GetYOffset     - int16_t ACCEL1_GetYOffset(void);
**         GetZOffset     - int16_t ACCEL1_GetZOffset(void);
**         GetX1gValue    - int16_t ACCEL1_GetX1gValue(void);
**         GetY1gValue    - int16_t ACCEL1_GetY1gValue(void);
**         GetZ1gValue    - int16_t ACCEL1_GetZ1gValue(void);
**         Deinit         - byte ACCEL1_Deinit(void);
**
**     License : Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2013, all rights reserved.
**     http://www.mcuoneclipse.com
**     This an open source software in the form of a Processor Expert Embedded Component.
**     This is a free software and is opened for education, research and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file ACCEL1.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup ACCEL1_module ACCEL1 module documentation
**  @{
*/         

/* MODULE ACCEL1. */

#include "ACCEL1.h"


typedef struct {
  int16_t NxOff; /* offset for X axis */
  int16_t NyOff; /* offset for Y axis */
  int16_t NzOff; /* offset for Z axis */
  int16_t Nx1g;  /* value for 1g for X axis */
  int16_t Ny1g;  /* value for 1g for Y axis */
  int16_t Nz1g;  /* value for 1g for Z axis */
} tAccelCal;

/* default calibration values from component properties */
const tAccelCal InitialCalibration = { /* Initial default calibration values */
  0, /* X offset */
  0, /* Y offset */
  0, /* Z offset */
  6000, /* X 1g */
  6000, /* Y 1g */
  6000  /* Z 1g */
};
static tAccelCal sCalValues; /* calibration values in RAM */

#define CalNxOff   sCalValues.NxOff
#define CalNyOff   sCalValues.NyOff
#define CalNzOff   sCalValues.NzOff
#define CalNx1g    sCalValues.Nx1g /* value for 1g */
#define CalNy1g    sCalValues.Ny1g /* value for 1g */
#define CalNz1g    sCalValues.Nz1g /* value for 1g */

#define ZeroGmilliVoltoffset  1650 /* Vdd/2, for 3.3V this is 1.65V */
#define milliVoltPerG         800 /* 800mV/g */
#define zeroGValue           (0xffff/2)   /* this is the value for zero g: midpoint */
/*
** ===================================================================
**     Method      :  ACCEL1_GetX (component MMA7260Q)
**     Description :
**         Retrieves the value for the X axis. The value is adjusted
**         with the zero calibration value (0 for 0 g, negative for
**         negative acceleration and positive for positive acceleration).
**     Parameters  : None
**     Returns     :
**         ---             - Measured X value
** ===================================================================
*/
int16_t ACCEL1_GetX(void)
{
  uint16_t value;

  value = ACCEL1_MeasureGetRawX();
  value -= CalNxOff; /* adjust with calibration offset */
  value -= zeroGValue; /* adjust with midpoint zero g value */
  return (int16_t)value;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetY (component MMA7260Q)
**     Description :
**         Retrieves the value for the Y axis. The value is adjusted
**         with the zero calibration value (0 for 0 g, negative for
**         negative acceleration and positive for positive acceleration).
**     Parameters  : None
**     Returns     :
**         ---             - Measured Y value
** ===================================================================
*/
int16_t ACCEL1_GetY(void)
{
  uint16_t value;

  value = ACCEL1_MeasureGetRawY();
  value -= CalNyOff; /* adjust with calibration offset */
  value -= zeroGValue; /* adjust with midpoint zero g value */
  return (int16_t)value;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetZ (component MMA7260Q)
**     Description :
**         Retrieves the value for the Z axis. The value is adjusted
**         with the zero calibration value (0 for 0 g, negative for
**         negative acceleration and positive for positive acceleration).
**     Parameters  : None
**     Returns     :
**         ---             - Measured Z value
** ===================================================================
*/
int16_t ACCEL1_GetZ(void)
{
  uint16_t value;

  value = ACCEL1_MeasureGetRawZ();
  value -= CalNzOff; /* adjust with calibration offset */
  value -= zeroGValue; /* adjust with midpoint zero g value */
  return (int16_t)value;
}

/*
** ===================================================================
**     Method      :  ACCEL1_SensorOn (component MMA7260Q)
**     Description :
**         Enables the sensor.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_SensorOn(void)
{
  Sleep1_SetVal(); /* the sleep pin is low active: setting it to high to enable sensor */
  //WAIT1_Waitms(10); /* wait some time to give the sensor some time to wake up */
}

/*
** ===================================================================
**     Method      :  ACCEL1_SensorOff (component MMA7260Q)
**     Description :
**         Disables the sensor (puts it in sleep mode).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_SensorOff(void)
{
  Sleep1_ClrVal(); /* the sleep pin is low active: setting it to low to put the sensor in sleep mode. */
}

/*
** ===================================================================
**     Method      :  ACCEL1_Gselect (component MMA7260Q)
**     Description :
**         Allows to select different g sensitivity levels.
**     Parameters  :
**         NAME            - DESCRIPTION
**         gSelect         - Pass 0 for 1.5g, 1 for 2g, 3 for
**                           4g and 4 for 6g sensitivity. The driver
**                           header file defines the values as macros as
**                           well.
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_Gselect(byte gSelect)
{
/* See following defines which can be used as arguments: g1_5, g2_0, g4_0 and g6_0 */
  if (gSelect&1) {
    G11_SetVal();
  } else {
    G11_ClrVal();
  }
  if (gSelect&2) {
    G21_SetVal();
  } else {
    G21_ClrVal();
  }
}

/*
** ===================================================================
**     Method      :  ACCEL1_CalibrateX1g (component MMA7260Q)
**     Description :
**         Performs a calibration of the sensor. It is assumed that the
**         Y and Z sensors have 0 g, and the X sensor has 1 g.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_CalibrateX1g(void)
{
  /* assumption is that accelerometer is placed with 1g for X and 0g for Y and Z */
  uint32_t X=0, Y=0, Z=0;
  uint8_t i;

  /* Get the raw data */
  for (i=0; i<8; i++) {
   X += ACCEL1_MeasureGetRawX();
   Y += ACCEL1_MeasureGetRawY();
   Z += ACCEL1_MeasureGetRawZ();
  }
  /* build average of 8 measured values */
  X >>= 3;
  Y >>= 3;
  Z >>= 3;
  /* store the calibration values */
  sCalValues.Nx1g  = (int16_t)(X-zeroGValue); /* we have 1g on X */
  /* offset: both Y and Z shall have zero g (midpoint) */
  sCalValues.NyOff = (int16_t)(Y-zeroGValue);
  sCalValues.NzOff = (int16_t)(Z-zeroGValue);
}

/*
** ===================================================================
**     Method      :  ACCEL1_CalibrateY1g (component MMA7260Q)
**     Description :
**         Performs a calibration of the sensor. It is assumed that the
**         X and Z sensors have 0 g, and the Y sensor has 1 g.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_CalibrateY1g(void)
{
  /* assumption is that accelerometer is placed with 1g for Y and 0g for X and Z */
  uint32_t X=0, Y=0, Z=0;
  uint8_t i;

  /* Get the raw data */
  for (i=0; i<8; i++) {
   X += ACCEL1_MeasureGetRawX();
   Y += ACCEL1_MeasureGetRawY();
   Z += ACCEL1_MeasureGetRawZ();
  }
  /* build average of 8 measured values */
  X >>= 3;
  Y >>= 3;
  Z >>= 3;
  /* store the calibration values */
  sCalValues.Ny1g  = (int16_t)(Y-zeroGValue); /* we have 1g on Y */
  /* offset: both X and Z shall have zero g (midpoint) */
  sCalValues.NxOff = (int16_t)(X-zeroGValue);
  sCalValues.NzOff = (int16_t)(Z-zeroGValue);
}
/*
** ===================================================================
**     Method      :  ACCEL1_CalibrateZ1g (component MMA7260Q)
**     Description :
**         Performs a calibration of the sensor. It is assumed that the
**         X and Y sensors have 0 g, and the Z sensor has 1 g.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ACCEL1_CalibrateZ1g(void)
{
  /* assumption is that accelerometer is placed with 1g for Z and 0g for X and Y */
  uint32_t X=0, Y=0, Z=0;
  uint8_t i;

  /* Get the raw data */
  for (i=0; i<8; i++) {
   X += ACCEL1_MeasureGetRawX();
   Y += ACCEL1_MeasureGetRawY();
   Z += ACCEL1_MeasureGetRawZ();
  }
  /* build average of 8 measured values */
  X >>= 3;
  Y >>= 3;
  Z >>= 3;
  /* store the calibration values */
  sCalValues.Nz1g  = (int16_t)(Z-zeroGValue); /* we have 1g on Z */
  /* offset: both X and Y shall have zero g (midpoint) */
  sCalValues.NxOff = (int16_t)(X-zeroGValue);
  sCalValues.NyOff = (int16_t)(Y-zeroGValue);
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetXmg (component MMA7260Q)
**     Description :
**         Returns the X value in mg
**     Parameters  : None
**     Returns     :
**         ---             - The g value in 1/1000g units
** ===================================================================
*/
int16_t ACCEL1_GetXmg(void)
{
  int32_t L;

  L = ACCEL1_MeasureGetRawX();
  L -= CalNxOff; /* apply offset */
  L -= zeroGValue; /* get based to zero g */
  L *= 1000; /* scale to milli g */
  L /= (CalNx1g-CalNxOff); /* apply 1g calibrated value */
  return (int16_t)L;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetYmg (component MMA7260Q)
**     Description :
**         Returns the Y value in mg
**     Parameters  : None
**     Returns     :
**         ---             - The g value in 1/1000g units
** ===================================================================
*/
int16_t ACCEL1_GetYmg(void)
{
  int32_t L;

  L = ACCEL1_MeasureGetRawY();
  L -= CalNyOff; /* apply offset */
  L -= zeroGValue; /* get based to zero g */
  L *= 1000; /* scale to milli g */
  L /= (CalNy1g-CalNyOff); /* apply 1g calibrated value */
  return (int16_t)L;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetZmg (component MMA7260Q)
**     Description :
**         Returns the Z value in mg
**     Parameters  : None
**     Returns     :
**         ---             - The g value in 1/1000g units
** ===================================================================
*/
int16_t ACCEL1_GetZmg(void)
{
  int32_t L;

  L = ACCEL1_MeasureGetRawZ();
  L -= CalNzOff; /* apply offset */
  L -= zeroGValue; /* get based to zero g */
  L *= 1000; /* scale to milli g */
  L /= (CalNz1g-CalNzOff); /* apply 1g calibrated value */
  return (int16_t)L;
}

/*
** ===================================================================
**     Method      :  ACCEL1_MeasureGetRawX (component MMA7260Q)
**     Description :
**         Performs a measurement on X channel and returns the raw
**         value.
**     Parameters  : None
**     Returns     :
**         ---             - X sensor value
** ===================================================================
*/
word ACCEL1_MeasureGetRawX(void)
{
  uint16_t val;

  (void)AD1_MeasureChan(TRUE, 0);
  (void)AD1_GetChanValue16(0,(uint16_t*) &val);
  return val;
}

/*
** ===================================================================
**     Method      :  ACCEL1_MeasureGetRawY (component MMA7260Q)
**     Description :
**         Performs a measurement on Y channel and returns the raw
**         value.
**     Parameters  : None
**     Returns     :
**         ---             - Y sensor value
** ===================================================================
*/
word ACCEL1_MeasureGetRawY(void)
{
  uint16_t val;

  (void)AD1_MeasureChan(TRUE, 1);
  (void)AD1_GetChanValue16(1, (uint16_t*)&val);
  return val;
}

/*
** ===================================================================
**     Method      :  ACCEL1_MeasureGetRawZ (component MMA7260Q)
**     Description :
**         Performs a measurement on Z channel and returns the raw
**         value.
**     Parameters  : None
**     Returns     :
**         ---             - Z sensor value
** ===================================================================
*/
word ACCEL1_MeasureGetRawZ(void)
{
  uint16_t val;

  (void)AD1_MeasureChan(TRUE, 2);
  (void)AD1_GetChanValue16(2, (uint16_t*)&val);
  return val;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetXOffset (component MMA7260Q)
**     Description :
**         Returns the offset applied to the X value.
**     Parameters  : None
**     Returns     :
**         ---             - Z offset value
** ===================================================================
*/
int16_t ACCEL1_GetXOffset(void)
{
  return CalNxOff;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetYOffset (component MMA7260Q)
**     Description :
**         Returns the offset applied to the Y value.
**     Parameters  : None
**     Returns     :
**         ---             - Z offset value
** ===================================================================
*/
int16_t ACCEL1_GetYOffset(void)
{
  return CalNyOff;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetZOffset (component MMA7260Q)
**     Description :
**         Returns the offset applied to the Z value.
**     Parameters  : None
**     Returns     :
**         ---             - Z offset value
** ===================================================================
*/
int16_t ACCEL1_GetZOffset(void)
{
  return CalNzOff;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetX1gValue (component MMA7260Q)
**     Description :
**         Returns the value for 1g for channel  X.
**     Parameters  : None
**     Returns     :
**         ---             - 1g value for X
** ===================================================================
*/
int16_t ACCEL1_GetX1gValue(void)
{
  return CalNx1g;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetY1gValue (component MMA7260Q)
**     Description :
**         Returns the value for 1g for channel  Y.
**     Parameters  : None
**     Returns     :
**         ---             - 1g value for Y
** ===================================================================
*/
int16_t ACCEL1_GetY1gValue(void)
{
  return CalNy1g;
}

/*
** ===================================================================
**     Method      :  ACCEL1_GetZ1gValue (component MMA7260Q)
**     Description :
**         Returns the value for 1g for channel  X.
**     Parameters  : None
**     Returns     :
**         ---             - 1g value for Y
** ===================================================================
*/
int16_t ACCEL1_GetZ1gValue(void)
{
  return CalNz1g;
}

/*
** ===================================================================
**     Method      :  ACCEL1_Init (component MMA7260Q)
**
**     Description :
**         Initializes the driver.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
byte ACCEL1_Init(void)
{
  sCalValues.NxOff = InitialCalibration.NxOff;
  sCalValues.Nx1g  = InitialCalibration.Nx1g;
  sCalValues.NyOff = InitialCalibration.NyOff;
  sCalValues.Ny1g  = InitialCalibration.Ny1g;
  sCalValues.NzOff = InitialCalibration.NzOff;
  sCalValues.Nz1g  = InitialCalibration.Nz1g;
  ACCEL1_SensorOn(); /* enable sensor */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  ACCEL1_Deinit (component MMA7260Q)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
byte ACCEL1_Deinit(void)
{
  return ERR_OK;
}

/* END ACCEL1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/