#include <Shift_Command.h>
HC595 Shift1;
Shift_Command HC1;
unsigned long currenttime = 0;
void Shift_Command::turnsignal(uint8_t Mode, uint8_t time)
{   
    
  
    switch (Mode)
    {
    case 0:
        // Aus 
        Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode = 0;
        HC.time =0;
        break;
    case 1:
        Shift1.save_shiftstate_bit(0,1,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
        HC.BlinkMode= 0;
        HC.time = 0;
        break;
    case 2:
        Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,1,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode = 0;
        HC.time = 0;
        break;
    case 3:
        Shift1.save_shiftstate_bit(0,1,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,1,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode= 0;
        HC.time = 0;
        break;
    case 4:
        Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode = 1;
        HC.time = time*100;
        break;
    case 5:
        Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode = 2;
        HC.time = time*100;
        break;
    case 6:
        Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3 , Shift1.Shift.S3);
        HC.BlinkMode = 3;
        HC.time = time*100;
        break;
    default:
        break;
    }

}

void Shift_Command::blink()  // Main : Blink every Blink.time milliseconds
{
    
    switch (HC.BlinkMode)
    {
    case 0:
        
       

        break;
    case 1:
         Shift1.save_shiftstate_bit(0,1,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
        if(currenttime + HC.BlinkMode >= millis())
        {
            Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
            Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
            Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
            currenttime = millis();
        }
        break;
    case 2:
         Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,1,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
        if(currenttime + HC.time >= millis())
        {
            Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
            Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
            Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
            currenttime = millis();
        }
        break;
    case 3:
        Shift1.save_shiftstate_bit(0,1,Shift1.Shift.S3);
        Shift1.save_shiftstate_bit(6,1,Shift1.Shift.S3);
        Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
        if(currenttime + HC.time >= millis())
        {
            Shift1.save_shiftstate_bit(0,0,Shift1.Shift.S3);
            Shift1.save_shiftstate_bit(6,0,Shift1.Shift.S3);
            Shift1.send_shiftstate(CS3,Shift1.Shift.S3);
            currenttime = millis();
        }
        break;
    
    default:
        break;
    }


}


void Shift_Command::fan(uint8_t Fan)
{
    switch (Fan)
    {
    case 0:
        Shift1.save_shiftstate_bit(3,0,Shift1.Shift.S2);
        Shift1.send_shiftstate(CS2,Shift1.Shift.S2);
        break;
    case 1:
        Shift1.save_shiftstate_bit(3,1,Shift1.Shift.S2);
        Shift1.send_shiftstate(CS2,Shift1.Shift.S2);
        break;
    
    default:
        break;
    }

}
