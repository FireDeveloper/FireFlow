#include "Arduino.h"
#include "Reflow_Data.h"

ReflowData::ReflowData() {
}

//Add Main Data
void ReflowData::AddMainData(uint16_t Value, uint16_t Time) {
  Main_Data[_MainPos][Value_ID] = Value;
  Main_Data[_MainPos][Time_ID] = Time;
  _MainPos++;
}
//Add Aux Data
void ReflowData::AddAuxData(uint16_t Value, uint16_t Time) {
  Aux_Data[_AuxPos][Value_ID] = Value;
  Aux_Data[_AuxPos][Time_ID] = Time;
  _AuxPos++;
}
//Add Fan Data
void ReflowData::AddFanData(uint16_t Value, uint16_t Time) {
  Fan_Data[_FanPos][Value_ID] = Value;
  Fan_Data[_FanPos][Time_ID] = Time;
  _FanPos++;
}
//Add Buzzer Data
void ReflowData::AddBuzzerData(uint16_t Value, uint16_t Time) {
  Buzzer_Data[_BuzzerPos][Value_ID] = Value;
  Buzzer_Data[_BuzzerPos][Time_ID] = Time;
  _BuzzerPos++;
}
//Add GPIO Data
void ReflowData::AddGPIOData(uint16_t Value, uint16_t Time) {
  GPIO_Data[_GPIOPos][Value_ID] = Value;
  GPIO_Data[_GPIOPos][Time_ID] = Time;
  _GPIOPos++;
}
//Add GPIO Data
void ReflowData::Add_PID_P_Data(float Value) {
  PID_P[_PID_P_Pos] = Value;
  _PID_P_Pos++;
}
//Add GPIO Data
void ReflowData::Add_PID_I_Data(float Value) {
  PID_I[_PID_I_Pos] = Value;
  _PID_I_Pos++;
}
//Add GPIO Data
void ReflowData::Add_PID_D_Data(float Value) {
  PID_D[_PID_D_Pos] = Value;
  _PID_D_Pos++;
}
//========================================================================================
void ReflowData::SetMainSize(byte Size) {
  _Main_Size = Size;
}
void ReflowData::SetAuxSize(byte Size) {
  _Aux_Size = Size;
}
void ReflowData::SetFanSize(byte Size) {
  _Fan_Size = Size;
}
void ReflowData::SetBuzzerSize(byte Size) {
  _Buzzer_Size = Size;
}
void ReflowData::SetGPIOSize(byte Size) {
  _GPIO_Size = Size;
}
//========================================================================================
void ReflowData::SetWidth(uint16_t Width) {
  _Width = Width;
}
void ReflowData::SetHeight(uint16_t Height) {
  _Height = Height;
}
void ReflowData::SetTimeBase(uint16_t Time_Base) {
  _Time_Base = Time_Base;
}
//========================================================================================
byte ReflowData::getMainSize() {
  return _Main_Size;
}
byte ReflowData::getAuxSize() {
  return _Aux_Size;
}
byte ReflowData::getFanSize() {
  return _Fan_Size;
}
byte ReflowData::getBuzzerSize() {
  return _Buzzer_Size;
}
byte ReflowData::getGPIOSize() {
  return _GPIO_Size;
}
//========================================================================================
uint16_t ReflowData::getMainValue(byte Pos) {
  return Main_Data[Pos][Time_ID];
}
uint16_t ReflowData::getAuxValue(byte Pos) {
  return Aux_Data[Pos][Time_ID];
}
uint16_t ReflowData::getFanValue(byte Pos) {
  return Fan_Data[Pos][Time_ID];
}
uint16_t ReflowData::getBuzzerValue(byte Pos) {
  return Buzzer_Data[Pos][Time_ID];
}
uint16_t ReflowData::getGPIOValue(byte Pos) {
  return GPIO_Data[Pos][Time_ID];
}
//========================================================================================
uint16_t ReflowData::getMainTime(byte Pos) {
  return Main_Data[Pos][Value_ID];
}
uint16_t ReflowData::getAuxTime(byte Pos) {
  return Aux_Data[Pos][Value_ID];
}
uint16_t ReflowData::getFanTime(byte Pos) {
  return Fan_Data[Pos][Value_ID];
}
uint16_t ReflowData::getBuzzerTime(byte Pos) {
  return Buzzer_Data[Pos][Value_ID];
}
uint16_t ReflowData::getGPIOTime(byte Pos) {
  return GPIO_Data[Pos][Value_ID];
}
//========================================================================================
float ReflowData::get_PID_P_Value(byte Pos) {
  return PID_P[Pos];
}
float ReflowData::get_PID_I_Value(byte Pos) {
  return PID_I[Pos];
}
float ReflowData::get_PID_D_Value(byte Pos) {
  return PID_D[Pos];
}
