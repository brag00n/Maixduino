#ifndef __AXP192_H__
#define __AXP192_H__

#include <Wire.h>
#include <Arduino.h>

#define SLEEP_MSEC(us) (((uint64_t)us) * 1000L)
#define SLEEP_SEC(us)  (((uint64_t)us) * 1000000L)
#define SLEEP_MIN(us)  (((uint64_t)us) * 60L * 1000000L)
#define SLEEP_HR(us)   (((uint64_t)us) * 60L * 60L * 1000000L)

#define AXP_ADDR 0X34

#define CURRENT_100MA  (0b0000)
#define CURRENT_190MA  (0b0001)
#define CURRENT_280MA  (0b0010)
#define CURRENT_360MA  (0b0011)
#define CURRENT_450MA  (0b0100)
#define CURRENT_550MA  (0b0101)
#define CURRENT_630MA  (0b0110)
#define CURRENT_700MA  (0b0111)

class AXP192 {
public:

    enum CHGCurrent{
        kCHG_100mA = 0,
        kCHG_190mA,
        kCHG_280mA,
        kCHG_360mA,
        kCHG_450mA,
        kCHG_550mA,
        kCHG_630mA,
        kCHG_700mA,
        kCHG_780mA,
        kCHG_880mA,
        kCHG_960mA,
        kCHG_1000mA,
        kCHG_1080mA,
        kCHG_1160mA,
        kCHG_1240mA,
        kCHG_1320mA,
    };

    AXP192();
    /**
     * DCDC1: 3V3 Main rail. When not set the stick shuts down
     * DCDC2: 0V9 K210 VCore
     * DCDC3: 1V8 Use unknown
     * LDO1: Don't set GPIO1 as LDO
     * LDO2: 2V8 Display backlight
     * LDO3: 1V5 Display Control
     * GPIO0: LDO1 LCD_BL
     * EXTEN:
     */
    void  begin(bool isInited = false);
    void  ScreenBreath(uint8_t brightness);
    bool  GetBatState();
  
    uint8_t GetInputPowerStatus();
    uint8_t GetBatteryChargingStatus();

    void  EnableCoulombcounter(void);
    void  DisableCoulombcounter(void);
    void  StopCoulombcounter(void);
    void  ClearCoulombcounter(void);
    uint32_t GetCoulombchargeData(void);        // Raw Data for Charge
    uint32_t GetCoulombdischargeData(void);     // Raw Data for Discharge
    float GetCoulombData(void);                 // total in - total out and calc
    uint8_t GetBtnPress(void);
    void SetSleep(void);
    uint8_t GetWarningLeve(void);

public:
    // void SetChargeVoltage( uint8_t );
    void  SetChargeCurrent( uint8_t );
    float GetBatVoltage();
    float GetBatCurrent();
    float GetVinVoltage();
    float GetVinCurrent();
    float GetVBusVoltage();
    float GetVBusCurrent();
    float GetTempInAXP192();
    float GetBatPower();
    float GetBatChargeCurrent();
    float GetAPSVoltage();
    float GetBatCoulombInput();
    float GetBatCoulombOut();
    uint8_t GetWarningLevel(void);    
    void SetLDO2( bool State );     // Can turn LCD Backlight OFF for power saving
    void SetLDO3( bool State );
    void SetAdcState(bool State);
    
    // -- Power Off
    void PowerOff();

    // Power Maintained Storage
    void Read6BytesStorage( uint8_t *bufPtr );
    void Write6BytesStorage( uint8_t *bufPtr );

    
private:
    void Write1Byte( uint8_t Addr ,  uint8_t Data );
    uint8_t Read8bit( uint8_t Addr );
    uint16_t Read12Bit( uint8_t Addr);
    uint16_t Read13Bit( uint8_t Addr);
    uint16_t Read16bit( uint8_t Addr );
    uint32_t Read24bit( uint8_t Addr );
    uint32_t Read32bit( uint8_t Addr );
    void ReadBuff( uint8_t Addr , uint8_t Size , uint8_t *Buff );
}; 

#endif
