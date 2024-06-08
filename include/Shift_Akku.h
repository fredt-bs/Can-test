#ifndef SHIFT_AKKU_H
#define SHIFT_AKKU_H
#include <pins.h>
#include <Arduino.h>
#include <SPI.h>
// #include <wire.h>

class Shift_Akku
{
public:
    typedef struct
    {
        int S1[8] = {};
        int S2[8] = {};
        int S3[8] = {};
        int Sp;
        int Sv;
        int Sr;
        int Blink;
        int Akku1LOW = 0;
        int Akku2LOW = 0;
    } Shiftstate;

    Shiftstate Shiftvar;

    int Canverwertung(int Canid, uint8_t CanByte, uint8_t CanData);
  //  void Shiftout(uint8_t ShiftregisterNumber);
    int Srnb(int Sr, int Byte, int side);

    int Srb(int Sr, int Byte, int side);
    void Blink(int on, int Side);
    void Akkupow(int AkkuNr, float LEDSpannungsvareanz);
    void akkuswitch();
    int laden();
    int Akkustatus();
    void save_shiftstate_bit(uint8_t bit_index, uint8_t bit_value, int shift_arr[8]);
    void send_shiftstate(uint8_t cs_pin, int shift_arr[8]);
   // void Shiftstatesave(int Shiftpin, int Shiftvalue, int ShiftregisterNumber);

private:
   
};
#endif /* SHIFT_AKKU_H */
