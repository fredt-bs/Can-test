#ifndef SHIFT_COMMAND_H
#define SHIFT_COMMAND_H
#include <HC595.h>
#include <pins.h>
class Shift_Command
{
private:
    
public:
typedef struct
    {
        int BlinkMode =0;
        int time = 0;
        
    } Blink;
Blink HC;
void turnsignal(uint8_t Mode , uint8_t time);
void blink();
void fan(uint8_t Fan);
};





#endif /* SHIFT_COMMAND_H */
