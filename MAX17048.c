/**
 *@file MAX17048.c
 *@brief Device driver
 *@date Jul 2, 2019
 *@author Tecrea - Ing. Manuel Posada
 *@version 1.0.0
 */

#include "MAX17048.h"

/*============================================================================*/
void MAX17048_Init(MAX17048_t *Obj, MAX17048_Write_Fcn_t Write, MAX17048_Read_Fcn_t Read, uint8_t Addres_Device){
  Obj->Write = Write;
  Obj->Read = Read;
  Obj->Address = Addres_Device;
}

/*============================================================================*/
void MAX17048_Write(MAX17048_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount){
  uint8_t buffer[3];    
  
  buffer[0] = Reg;
  buffer[1] = data >> 8;
  buffer[2] = data;
  Obj->Write(Obj->Address, (void*)buffer, (amount+1));
}

/*============================================================================*/
uint16_t MAX17048_Read(MAX17048_t *Obj, uint8_t Reg, uint8_t amount){
  uint8_t buffer[2];
  buffer[0] = Reg;
  Obj->Read(Obj->Address, buffer, amount, MAX17048_SIZEREG);
  return buffer[0] << 8 | buffer[1];
}

/*============================================================================*/
uint16_t MAX17048_Version(MAX17048_t *Obj){
  return MAX17048_Read(Obj, MAX17048_VERSION, 2);
}

/*============================================================================*/
uint16_t MAX17048_Voltage(MAX17048_t *Obj){
  return (uint16_t) ((uint32_t)(MAX17048_Read(Obj, MAX17048_VCELL, 2)*MAX17048_VCELL_RESOLUTION)/1000000);
  //return (uint16_t)(((MAX17048_Read(Obj, VCELL, 2)>>4)*5)>>2);   //*0.078125);
}

/*============================================================================*/
/*The first update is available approximately 1s after POR of the IC */
float MAX1708_SOC(MAX17048_t *Obj){
  uint16_t RetVal;
  RetVal = MAX17048_Read(Obj, MAX17048_SOC, 2);	/*RetVal*0.00390625*/
  return (RetVal >> 8) + ((RetVal & 0x00ff)/256.0); /* MSB LSB  ->  LSB -> 1/256%*/
}

/*============================================================================*/
uint16_t MAX1708_SOC_Int(MAX17048_t *Obj){
  return (MAX17048_Read(Obj, MAX17048_SOC, 2) >> 8);
}

/*============================================================================*/
void MAX17048_Compensation(MAX17048_t *Obj, uint8_t RComp){
  uint16_t data = MAX17048_Read(Obj, MAX17048_CONFIG, 2);
  data &= 0x00FF;
  data |= RComp << 8;
  MAX17048_Write(Obj, MAX17048_CONFIG, data, 2);
}

/*POR Power on Reset*/
/*============================================================================*/
void MAX17048_Reset(MAX17048_t *Obj){
  MAX17048_Write(Obj, MAX17048_CMD, MAX17048_RESET, 2);
}

/*============================================================================*/
void MAX17048_SleepEnable(MAX17048_t *Obj){
  uint16_t value = MAX17048_Read(Obj, MAX17048_MODE, 2);
  MAX17048_Write(Obj, MAX17048_MODE,(value | (0x0001<<MAX17048_MODE_EN_SLEEP_BIT)), 2);
}

/*============================================================================*/
void MAX17048_QStart(MAX17048_t *Obj){
  uint16_t value = MAX17048_Read(Obj, MAX17048_MODE, 2);
  MAX17048_Write(Obj, MAX17048_MODE,(value | (0x0001<<MAX17048_MODE_QUICK_START_BIT)), 2);
}

/*============================================================================*/
void MAX17048_Sleep(MAX17048_t *Obj, uint8_t On_Off){
  uint16_t value = MAX17048_Read(Obj, MAX17048_CONFIG, 2);
  
  if(On_Off){
    MAX17048_Write(Obj, MAX17048_CONFIG,(value | (0x0001<<MAX17048_CONFIG_SLEEP_BIT)), 2);
  }
  else{
    MAX17048_Write(Obj, MAX17048_CONFIG,(value & ~(0x0001<<MAX17048_CONFIG_SLEEP_BIT)), 2);
  }
}
/*============================================================================*/
