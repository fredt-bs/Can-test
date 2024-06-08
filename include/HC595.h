#ifndef HC595_H
#define HC595_H
#include <Arduino.h>
#include <SPI.h>
class HC595
{
private:

public:
typedef struct
    {
        int S1[8] = {};
        int S2[8] = {};
        int S3[8] = {};
        
    } Shiftstate;
Shiftstate Shift;
   void save_shiftstate_bit(uint8_t bit_index, uint8_t bit_value, int shift_arr[8]);
   void send_shiftstate(uint8_t cs_pin, int shift_arr[8]);
   void setallLOW(uint8_t cs_pin);
};




#endif /* HC595_H */
