#include <HC595.h>



void HC595::save_shiftstate_bit(uint8_t bit_index, uint8_t bit_value, int shift_arr[8])
{
    shift_arr[bit_index] = bit_value;
    
}

void HC595::send_shiftstate(uint8_t cs_pin, int shift_arr[8]) 
{

    uint8_t send_val = 0;
    for (int i = 0; i < 8; i++) 
    {
        send_val += shift_arr[i] << i;
        // log_i("[%u]: %u", i, shift_arr[i]);
    }
    digitalWrite(cs_pin, LOW);
   
    SPI.beginTransaction(SPISettings(1000000u, MSBFIRST, SPI_MODE0));
    SPI.transfer(send_val);
    SPI.endTransaction();

    digitalWrite(cs_pin, HIGH);
}

void HC595::setallLOW(uint8_t cs_pin)
{
    uint8_t send_val = 0;
    digitalWrite(cs_pin, LOW);
   
    SPI.beginTransaction(SPISettings(1000000u, MSBFIRST, SPI_MODE0));
    SPI.transfer(send_val);
    SPI.endTransaction();

    digitalWrite(cs_pin, HIGH);

}