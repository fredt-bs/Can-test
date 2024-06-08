#include <Arduino.h>
#include <pins.h>
#include <can_bus_manager.h>
#include <SPI.h>
#include <HC595.h>
#include <CanReader.h>
#include <LEDStrip.h>
// #ifndef DEBUG_LOOP
// #define DEBUG_LOOP 1
// #endif

// comment the next line to disable sending can messages (for debug purposes)
#define SEND_CAN_MESSAGES
HC595 HCM;
CAN_device_t CAN_cfg;
CanBusManager can(CAN_cfg);
CanReader CanR;
CAN_frame_t can_msg;
LedStrip stripM;
// const uint32_t CAN_ID_BAT_V_LVLS = 1600;
// const uint32_t CAN_ID_BAT_ACTIVE = 1601;
// const uint32_t CAN_ID_LED_STATE = 1602;
// const uint32_t Cansendid = 1610;
const uint32_t TestLow = 1791; 
const uint32_t battery_confic = 1793;
const uint32_t battery_switching = 1794;
const uint32_t battery_charging = 1795;
const uint32_t fan_command = 1808;
const uint32_t speaker_config  = 1824 ;
const uint32_t speaker_command = 1825;
const uint32_t power_supply_command = 1841;
const uint32_t testHigh = 1872;

 uint8_t can_data[8] = {0, 1, 2, 3, 4, 5, 6, 7};




void setup()
{
  // Serial.begin(115200);
  log_i("Start");
  can.activate_filter(1792, true); // 1600-1603
  can.init(CAN_SPEED_500KBPS, GPIO_NUM_22, GPIO_NUM_21);

  // stripM.LEDStripINIT();
  // SPI.begin();
  // pinMode(PINS::CS1, OUTPUT);
  // pinMode(PINS::CS2, OUTPUT);
  // pinMode(PINS::CS3, OUTPUT);

  // stripM.init_sequence();

  //activate turn lights
  
  // HCM.setallLOW(CS1);
  // HCM.setallLOW(CS2);
  // HCM.setallLOW(CS3);
  delay(50);
  log_i("Setup finished");

}

void loop()
{

#ifdef DEBUG_LOOP

init_sequence();

#endif

#ifndef DEBUG_LOOP
  // log_i("loop");
  //  check for incoming messages
  if (can.is_msg_available(can_msg))
  {
    log_i("can");
    can.print_can_msg(can_msg);
   CanR.read(can_msg);
  }

#ifdef SEND_CAN_MESSAGES
  // fill the 8 bytes and send the can message

  can.send_can_msg(can_data, 8, TestLow);
#endif

//  delay(750);
//  log_i("debug delay");

#endif
}