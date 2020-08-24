/**
 *@file MAX17048.h
 *@brief Device driver
 *@date Jul 2, 2019
 *@author Tecrea - Ing. Manuel Posada
 *@version 1.0.0
 */

#ifndef DRIVERS_HD_MAX17048_H_
#define DRIVERS_HD_MAX17048_H_

  #include <stdint.h>


  #define MAX17048_REV		    "1.0.0"
  #define MAX17048_CAPTION     "MAX17048 " MAX17048_REV

  #define MAX17048_SLEEP_ON                     ( 0x01u )  
  #define MAX17048_SLEEP_OFF                    ( 0x00u )

  #define MAX17048_VCELL                        ( 0x02u )  /*!< address register voltage*/
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

  /**
   *@brief structure containing all data 
   */
  typedef struct {
    Write_Fcn Write;
    Read_Fcn  Read;
    uint8_t   Address;
  }MAX17048_t;

  /**
   * @brief Initialize max17048 module to work
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @param Write pointer to function i2c write
   * @param Read  pointer to function i2c read
   * @param Addres_Device slave addres device 
   */
  void MAX17048_Init(MAX17048_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device);
  
  /**
   * @brief this function read register
   * @param Obj     Obj Structure containing all data from the max17048 module.
   * @param Reg     address register to write
   * @param data    data to write 
   * @param amount  length bytes to write
   */
  void MAX17048_Write(MAX17048_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount);
  
  /**
   * @brief this function read register
   * @param Obj     Obj Structure containing all data from the max17048 module.
   * @param Reg     address register to read
   * @param amount  length bytes to read
   * @return        data received in 2 bytes
   */
  uint16_t MAX17048_Read(MAX17048_t *Obj, uint8_t Reg, uint8_t amount);
  
  /**
   * @brief This function request version
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @return version module
   */
  uint16_t MAX17048_Version(MAX17048_t *Obj);
  
  /**@param this function read voltage from battery
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @return Voltage read on battery in mV
   */
  uint16_t MAX17048_Voltage(MAX17048_t *Obj);
  
  /**
   * @brief this function read soc in float
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @return state of charge [0-100%]
   */
  uint16_t MAX1708_SOC_Int(MAX17048_t *Obj);
  
  /**
   * @brief this function read soc in float
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @return state of charge float
   */
  float MAX1708_SOC(MAX17048_t *Obj);
  
  /**
   * @brief     
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @param RComp   compensation resistance
   */
  void MAX17048_Compensation(MAX17048_t *Obj, uint8_t RComp);
  
  /**
   * @brief reset by software module
   * @param Obj Obj Structure containing all data from the max17048 module.
   */
  void MAX17048_Reset(MAX17048_t *Obj);
  
  /**
   * @brief enable device for entry in mode sleep
   * @param Obj Obj Structure containing all data from the max17048 module.
   */
  void MAX17048_SleepEnable(MAX17048_t *Obj);
  
  /**
   * @brief device runnig
   * @param Obj Obj Structure containing all data from the max17048 module.
   */
  void MAX17048_QStart(MAX17048_t *Obj);
  
  /**
   * @brief device entry in mode sleep
   * @param Obj Obj Structure containing all data from the max17048 module.
   * @param On_Off turn on or turn off device
   */
  void MAX17048_Sleep(MAX17048_t *Obj, uint8_t On_Off);

  
  /*=======================================================================
                EXAMPLE FOR I2C READ/WRITE wrappers
   ========================================================================*/
       
  /* 
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
  
#endif /* DRIVERS_HD_MAX17048_H_ */
