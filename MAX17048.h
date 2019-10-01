/*
 * MAX17048.h Device driver
 * Author : Ing. Manuel Posada
 * 
 *  Created on: Jul 2, 2019
 */

#ifndef DRIVERS_HD_MAX17048_H_
#define DRIVERS_HD_MAX17048_H_

  #include <stdint.h>

   
  /* EXAMPLE FOR I2C READ/WRITE wrappers
  void Write_I2C(uint8_t Address, void *data, uint8_t amount){
    uint8_t *DatatoSend = (uint8_t *)data;
    HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend,amount,10);
  }

  void Read_I2C(uint8_t Address, void *Register, uint8_t amount){
    uint8_t *DatatoSend = (uint8_t *)Register;
    HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend, 1, 10);
    HAL_I2C_Master_Receive(&hi2c1,Address,DatatoSend, amount, 10);
  }
  */   
  #define MAX17048_SLEEP_ON                     ( 0x01u )
  #define MAX17048_SLEEP_OFF                    ( 0x00u )

  #define MAX17048_VCELL                        ( 0x02u )
  #define MAX17048_SOC                          ( 0x04u )
  #define MAX17048_MODE                         ( 0x06u )
  #define MAX17048_VERSION                      ( 0x08u )
  #define MAX17048_CONFIG                       ( 0x0Cu )

  #define MAX17048_CMD                          ( 0xFEu  )
  #define MAX17048_RESET                        ( 0x5400 )

  #define MAX17048_ADDR_SLAVE                   ( 0x6Cu )
  #define MAX17048_RCOMP0	                ( 0x97u )

  /*MODE Register Format*/
  #define MAX17048_MODE_HI_STAT_BIT             ( 12 )
  #define MAX17048_MODE_EN_SLEEP_BIT	        ( 13 )
  #define MAX17048_MODE_QUICK_START_BIT	        ( 14 )

  /* CONFIG Register Format*/
  #define MAX17048_CONFIG_SLEEP_BIT		( 7 )

  /*Resolution for calculate Vcell*/
  #define MAX17048_VCELL_RESOLUTION	        ( 78125 )


  typedef void (*Write_Fcn )(uint8_t, void*, uint8_t);
  typedef void (*Read_Fcn  )(uint8_t, void*, uint8_t);

  typedef struct {
    Write_Fcn Write;
    Read_Fcn  Read;
    uint8_t   Address;
  }MAX17048_t;

  void MAX17048_Init(MAX17048_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device);
  void MAX17048_Write(MAX17048_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount);
  uint16_t MAX17048_Read(MAX17048_t *Obj, uint8_t Reg, uint8_t amount);
  uint16_t MAX17048_Version(MAX17048_t *Obj);
  uint16_t MAX17048_Voltage(MAX17048_t *Obj);
  uint16_t MAX1708_SOC_Int(MAX17048_t *Obj);
  float MAX1708_SOC(MAX17048_t *Obj);
  void MAX17048_Compensation(MAX17048_t *Obj, uint8_t RComp);
  void MAX17048_Reset(MAX17048_t *Obj);
  void MAX17048_SleepEnable(MAX17048_t *Obj);
  void MAX17048_QStart(MAX17048_t *Obj);
  void MAX17048_Sleep(MAX17048_t *Obj, uint8_t On_Off);

#endif /* DRIVERS_HD_MAX17048_H_ */
