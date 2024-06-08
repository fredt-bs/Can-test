#include <Accu.h>
HC595 HC;
void Accu::Accumode(uint8_t Mode)
{
    float voltage1 = (float)analogReadMilliVolts(Akku1Powerlvl) / 1000 * 11; //+ (analogReadMilliVolts(Akku1Powerlvl) / 1000) * (analogReadMilliVolts(Akku1Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt1 = (int)(voltage1 * 10);
    float voltage2 = (float)analogReadMilliVolts(Akku2Powerlvl) / 1000 * 11; // + (analogReadMilliVolts(Akku2Powerlvl) / 1000) * (analogReadMilliVolts(Akku2Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt2 = voltage2 * 10;
    switch (Mode)
    {
    case 0:
        // Accu 1 on ; Accu 2 off
        if (HC.Shift.S2[0] == 0 && volt1 >= 220 ) // voltage controll and Charge controll
        {
            HC.save_shiftstate_bit(1, 1, HC.Shift.S2);
            HC.save_shiftstate_bit(2, 0, HC.Shift.S2);
            HC.save_shiftstate_bit(2, 0, HC.Shift.S1);
            HC.save_shiftstate_bit(1, 1, HC.Shift.S1);
            HC.send_shiftstate(CS2, HC.Shift.S2);
            HC.send_shiftstate(CS1, HC.Shift.S1);
        }
        else if (HC.Shift.S2[0] == 1)
        {
            // send can message error
        }
        else if (true) // voltagecontrol < 22 V
        {
            // send can message error
        }
        break;
    case 1: // Accu 2 on ; Accu 1 off

        if (HC.Shift.S2[0] == 0 && volt2 >= 220 ) // voltage controll and Charge controll  (you can't see Accu 2 voltage if the robot is charge)
        {
            HC.save_shiftstate_bit(1, 0, HC.Shift.S2);
            HC.save_shiftstate_bit(2, 1, HC.Shift.S2);
            HC.save_shiftstate_bit(2, 1, HC.Shift.S1);
            HC.save_shiftstate_bit(1, 0, HC.Shift.S1);
            HC.send_shiftstate(CS2, HC.Shift.S2);
            HC.send_shiftstate(CS1, HC.Shift.S1);
        }
        else if (HC.Shift.S2[0] == 1)
        {
            // send can message error
        }
        else if (volt2 < 220) // voltagecontrol < 22 V
        {
            // send can message error
        }

        break;
    case 2:
        // Accu 1 and 2 Charge on

        HC.save_shiftstate_bit(0, 1, HC.Shift.S2);
        HC.send_shiftstate(CS2, HC.Shift.S2);

        break;
    case 3:
        // Accu 1 and 2 Charge off
        HC.save_shiftstate_bit(0, 1, HC.Shift.S2);
        HC.send_shiftstate(CS2, HC.Shift.S2);
        break;
    default:
        break;
    }
}

void Accu::Accucontroll(uint8_t AccuNr)
{
    float voltage1 = (float)analogReadMilliVolts(Akku1Powerlvl) / 1000 * 11; //+ (analogReadMilliVolts(Akku1Powerlvl) / 1000) * (analogReadMilliVolts(Akku1Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt1 = (int)(voltage1 * 10);
    float voltage2 = (float)analogReadMilliVolts(Akku2Powerlvl) / 1000 * 11; // + (analogReadMilliVolts(Akku2Powerlvl) / 1000) * (analogReadMilliVolts(Akku2Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt2 = voltage2 * 10;

    log_i("volt akku1: %u   akku2 %u", volt1, volt2);
    log_i("HC.Shift.S2[0]: %d   AkkuNr: %d", HC.Shift.S2[0], AccuNr);

    if (HC.Shift.S2[0] == 1) // laden an
    {
        if (AccuNr == 1)
        {

            if (volt1 > 220)
            {
               HC.save_shiftstate_bit(4, 1, HC.Shift.S2);

                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt1 > 240)
            {
                HC.save_shiftstate_bit(0, 1, HC.Shift.S1);

                HC.send_shiftstate(CS1, HC.Shift.S1);
            }
            if (volt1 > 260)
            {
                HC.save_shiftstate_bit(7, 1, HC.Shift.S2);

                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt1 > 280)
            {
                HC.save_shiftstate_bit(5, 1, HC.Shift.S2);
                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt1 > 290)
            {

                HC.save_shiftstate_bit(6, 1, HC.Shift.S2);
                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
        }
        else if (AccuNr == 2)
        {

            if (volt2 > 210)
            {
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);

                if (volt2 > 230)
                {
                    HC.save_shiftstate_bit(7, 1, HC.Shift.S1);
                    HC.send_shiftstate(CS1, HC.Shift.S1);
                    BAT.Accu1LOW = 0; //Warning
                }
                if (volt2 > 250)
                {
                    HC.save_shiftstate_bit(6, 1, HC.Shift.S1);
                    HC.send_shiftstate(CS1, HC.Shift.S1);
                }
                if (volt2 > 270)
                {
                    HC.save_shiftstate_bit(4, 1, HC.Shift.S1);
                    HC.send_shiftstate(CS1, HC.Shift.S1);
                }
                if (volt2 > 290)
                {
                    HC.save_shiftstate_bit(3, 1, HC.Shift.S1);
                    HC.send_shiftstate(CS1, HC.Shift.S1);
                }
            }
        }
    }
    if (HC.Shift.S2[0] == 0) // Laden Aus
    {
        if (AccuNr == 1)
        {

            if (volt1 < 205)
            {
                HC.save_shiftstate_bit(4, 0, HC.Shift.S2);

                if (HC.Shift.S1[1] == 1 && volt2 >= 220)
                {
                    HC.save_shiftstate_bit(1, 1, HC.Shift.S2);
                    HC.save_shiftstate_bit(2, 1, HC.Shift.S2);
                    HC.save_shiftstate_bit(2, 1, HC.Shift.S1);
                    HC.save_shiftstate_bit(1, 0, HC.Shift.S1);
                    BAT.Accu1LOW = 3; // LOW Voltage Bat OFF
                
                }
                else{
                    BAT.Accu1LOW = 4; // large warning
                }
                HC.send_shiftstate(CS1, HC.Shift.S1);
                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt1 < 210 && HC.Shift.S1[1] == 1)
            {
                BAT.Accu1LOW = 2; //Warning
            }
            if (volt1 < 225)
            {
                HC.save_shiftstate_bit(0, 0, HC.Shift.S1);
                HC.save_shiftstate_bit(4, 1, HC.Shift.S2);
                HC.send_shiftstate(CS2, HC.Shift.S2);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                 BAT.Accu1LOW = 1; //Warning
            }
            if (volt1 < 245)
            {
                HC.save_shiftstate_bit(7, 0, HC.Shift.S2);
                HC.save_shiftstate_bit(0, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(4, 1, HC.Shift.S2);

                HC.send_shiftstate(CS2, HC.Shift.S2);
                HC.send_shiftstate(CS1, HC.Shift.S1);
            }
            if (volt1 < 265)
            {
                HC.save_shiftstate_bit(5, 0, HC.Shift.S2);
                HC.save_shiftstate_bit(7, 1, HC.Shift.S2);
                HC.save_shiftstate_bit(0, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(4, 1, HC.Shift.S2);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt1 < 285)
            {
                HC.save_shiftstate_bit(6, 0, HC.Shift.S2);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S2);
                HC.save_shiftstate_bit(7, 1, HC.Shift.S2);
                HC.save_shiftstate_bit(0, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(4, 1, HC.Shift.S2);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                HC.send_shiftstate(CS2, HC.Shift.S2);
            }
            if (volt2 > 285)
                HC.save_shiftstate_bit(6, 1, HC.Shift.S2);
            HC.save_shiftstate_bit(5, 1, HC.Shift.S2);
            HC.save_shiftstate_bit(7, 1, HC.Shift.S2);
            HC.save_shiftstate_bit(0, 1, HC.Shift.S1);
            HC.save_shiftstate_bit(4, 1, HC.Shift.S2);
            HC.send_shiftstate(CS1, HC.Shift.S1);
            HC.send_shiftstate(CS2, HC.Shift.S2);
        }
        else if (AccuNr == 2)
        {

            if (volt2 < 205)
            {
                HC.save_shiftstate_bit(5, 0, HC.Shift.S1);

                if (HC.Shift.S1[2] == 1 && volt1 >= 220)
                {
                    HC.save_shiftstate_bit(1, 0, HC.Shift.S2);
                    HC.save_shiftstate_bit(2, 0, HC.Shift.S2);
                    HC.save_shiftstate_bit(2, 0, HC.Shift.S1);
                    HC.save_shiftstate_bit(1, 1, HC.Shift.S1);
                    BAT.Accu2LOW = 0;
                }
                else{
                    BAT.Accu1LOW = 4; // large warning
                }
                HC.send_shiftstate(CS1, HC.Shift.S1);
                HC.send_shiftstate(CS2, HC.Shift.S2);
                
                
            }
            if (volt2 < 210 && HC.Shift.S1[2] == 1)
            {
                BAT.Accu2LOW = 1;
            }
            if (volt2 < 225)
            {
                HC.save_shiftstate_bit(7, 0, HC.Shift.S1);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                ;
            }
            if (volt2 < 245)
            {
                HC.save_shiftstate_bit(7, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(6, 0, HC.Shift.S1);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                ;
            }
            if (volt2 < 265)
            {
                HC.save_shiftstate_bit(3, 0, HC.Shift.S1);
                HC.save_shiftstate_bit(6, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(7, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);
                ;
            }
            if (volt2 < 285)
            {
                HC.save_shiftstate_bit(4, 0, HC.Shift.S1);
                HC.save_shiftstate_bit(3, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(6, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(7, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);
            }
            if (volt2 > 285)
            {
                HC.save_shiftstate_bit(3, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(4, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(7, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(6, 1, HC.Shift.S1);
                HC.save_shiftstate_bit(5, 1, HC.Shift.S1);
                HC.send_shiftstate(CS1, HC.Shift.S1);
            }
        }
    }
}
