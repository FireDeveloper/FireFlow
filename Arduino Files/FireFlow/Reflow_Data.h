#ifndef Reflow_Data_h
#define Reflow_Data_h

#define LIBRARY_VERSION  1.0.0

#define Value_ID 0
#define Time_ID 1

class ReflowData
{
  public:
    ReflowData(); //Constructor

    void AddMainData(uint16_t Value, uint16_t Time);
    void AddAuxData(uint16_t Value, uint16_t Time);
    void AddFanData(uint16_t Value, uint16_t Time);
    void AddBuzzerData(uint16_t Value, uint16_t Time);
    void AddGPIOData(uint16_t Value, uint16_t Time);
    void Add_PID_P_Data(float Value);
    void Add_PID_I_Data(float Value);
    void Add_PID_D_Data(float Value);

    void SetMainSize(byte Size);
    void SetAuxSize(byte Size);
    void SetFanSize(byte Size);
    void SetBuzzerSize(byte Size);
    void SetGPIOSize(byte Size);

    void SetWidth(uint16_t Width);
    void SetHeight(uint16_t Height);
    void SetTimeBase(uint16_t Time_Base);

    byte getMainSize();
    byte getAuxSize();
    byte getFanSize();
    byte getBuzzerSize();
    byte getGPIOSize();

    uint16_t getMainValue(byte Pos);
    uint16_t getAuxValue(byte Pos);
    uint16_t getFanValue(byte Pos) ;
    uint16_t getBuzzerValue(byte Pos);
    uint16_t getGPIOValue(byte Pos);

    uint16_t getMainTime(byte Pos);
    uint16_t getAuxTime(byte Pos);
    uint16_t getFanTime(byte Pos);
    uint16_t getBuzzerTime(byte Pos);
    uint16_t getGPIOTime(byte Pos);

    float get_PID_P_Value(byte Pos);
    float get_PID_I_Value(byte Pos);
    float get_PID_D_Value(byte Pos);

  private:
    uint16_t Main_Data[40][2];
    uint16_t Aux_Data[40][2];
    uint16_t Fan_Data[40][2];
    uint16_t Buzzer_Data[40][2];
    uint16_t GPIO_Data[40][2];

    float PID_P[40];
    float PID_I[40];
    float PID_D[40];

    uint16_t _Width = 0;
    uint16_t _Height = 0;
    uint16_t _Time_Base = 0;

    byte _Main_Size;
    byte _Aux_Size;
    byte _Fan_Size;
    byte _Buzzer_Size;
    byte _GPIO_Size;

    byte _MainPos = 0;
    byte _AuxPos = 0;
    byte _FanPos = 0;
    byte _BuzzerPos = 0;
    byte _GPIOPos = 0;
    byte _PID_P_Pos = 0;
    byte _PID_I_Pos = 0;
    byte _PID_D_Pos = 0;

};
#endif
