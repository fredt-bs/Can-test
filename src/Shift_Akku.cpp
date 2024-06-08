#include <Shift_Akku.h>

void Shift_Akku::save_shiftstate_bit(uint8_t bit_index, uint8_t bit_value, int shift_arr[8]) {
    shift_arr[bit_index] = bit_value;
}

// void Shift_Akku::Shiftstatesave(int Shiftpin, int Shiftvalue, int ShiftNumber)
// {
//     int newstate[8] = {};
    
//     if (ShiftNumber == 1 && Shiftpin < 8 && Shiftpin >= 0)
//     {
//         for (int i = 0; i < 8; i++)
//         {
//             newstate[i] = Shiftvar.S1[i];
//         }

//         newstate[Shiftpin] = Shiftvalue;
//         for (int i = 0; i < 8; i++)
//         {
//             Shiftvar.S1[i] = newstate[i];
//         }
//     }
//     else if (ShiftNumber == 2 && Shiftpin < 8 && Shiftpin >= 0)
//     {
//         for (int i = 0; i < 8; i++)
//         {
//             newstate[i] = Shiftvar.S2[i];
//         }

//         newstate[Shiftpin] = Shiftvalue;
//         for (int i = 0; i < 8; i++)
//         {
//             Shiftvar.S2[i] = newstate[i];
//         }
//     }
//     else if (ShiftNumber == 3 && Shiftpin < 8 && Shiftpin >= 0)
//     {
//         for (int i = 0; i < 8; i++)
//         {
//             newstate[i] = Shiftvar.S3[i];
//         }

//         newstate[Shiftpin] = Shiftvalue;
//         for (int i = 0; i < 8; i++)
//         {
//             Shiftvar.S3[i] = newstate[i];
//         }
//     }
//     else
//     {

//         // Errror
//     }
// }

void Shift_Akku::send_shiftstate(uint8_t cs_pin, int shift_arr[8]) {

    uint8_t send_val = 0;
    for (int i = 0; i < 8; i++) {
        send_val += shift_arr[i] << i;
        // log_i("[%u]: %u", i, shift_arr[i]);
    }

    // log_i("send_val: %u", send_val);

    digitalWrite(cs_pin, LOW);
   
    SPI.beginTransaction(SPISettings(1000000u, MSBFIRST, SPI_MODE0));
    SPI.transfer(send_val);
    SPI.endTransaction();

    digitalWrite(cs_pin, HIGH);
}

// void Shift_Akku::Shiftout(uint8_t ShiftNumber)
// {
//     // log_i("Shiftout ");
//     switch (ShiftNumber)
//     {
//     case 1:
//     {
//         for (int i = 0; i < 8; i++)
//         {
//             digitalWrite(CLK, HIGH);
//             digitalWrite(DATA, Shiftvar.S1[i]);
//             // log_i("%d", Shiftvar.S1[i]);
//             digitalWrite(CLK, LOW);
//         }

//         digitalWrite(CS1, HIGH);
//         digitalWrite(CS1, LOW);
//         // log_i("Shiftout 1 ");
//         break;
//     }
//     case 2:
//     {
//         for (int i = 0; i < 8; i++)
//         {

//             digitalWrite(CLK, HIGH);
//             digitalWrite(DATA, Shiftvar.S2[i]);
//             digitalWrite(CLK, LOW);
//         }

//         digitalWrite(CS2, HIGH);
//         digitalWrite(CS2, LOW);
//         break;
//     }
//     case 3:
//     {
//         for (int i = 0; i < 8; i++)
//         {

//             digitalWrite(CLK, HIGH);
//             digitalWrite(DATA, Shiftvar.S3[i]);
//             digitalWrite(CLK, LOW);
//         }

//         digitalWrite(CS3, HIGH);
//         digitalWrite(CS3, LOW);
//         break;
//     }
//     default:
//         break;
//     }
// }

int Shift_Akku::Srb(int Sr, int Byte, int side)
{
    switch (Sr)
    {
    case 1 /* constant-expression */:
        /* code */
        return Shiftvar.S1[Byte];
        break;
    case 2 /* constant-expression */:
        /* code */
        return Shiftvar.S2[Byte];
        break;
    case 3 /* constant-expression */:
        if (side == 1 && Byte == 7)
        {
            Shiftvar.S3[Byte] = 1;
        }
        if (side == 0 && Byte == 1)
        {
            Shiftvar.S3[Byte] = 1;
        }
        /* code */
        return Shiftvar.S3[Byte];
        break;
    default:
        log_e("Unknown case");
        return 0;
        break;
    }
}

int Shift_Akku::Srnb(int Sr, int Byte, int side)
{
    switch (Sr)
    {
    case 1 :
        return Shiftvar.S1[Byte];
        break;
    case 2 :
        /* code */
        return Shiftvar.S2[Byte];
        break;
    case 3 :
        /* code */ if (side == 1 && Byte == 7)
        {
            Shiftvar.S3[Byte] = 0;
        }
        if (side == 0 && Byte == 1)
        {
            Shiftvar.S3[Byte] = 0;
        }
        return Shiftvar.S3[Byte];
        break;
    default:
        log_e("Unknown case");
        return 0;
        break;
    }
}
int Shift_Akku::Canverwertung(int Canid, uint8_t CanByte, uint8_t CanData)
{

    switch (Canid)
    {
    case 1600 /* constant-expression */:
        if (CanByte == 0 && CanData == 0)
        {
            Shiftvar.Sr = 3;
            Shiftvar.Sp = 1;
            return 0; // Blink aus links
        }
        else if (CanByte == 0 && CanData == 1)
        {
            Shiftvar.Sr = 3;
            Shiftvar.Sp = 1;
            return 1; // Blink an links
        }
        else if (CanByte == 0 && CanData == 2)
        {
            Shiftvar.Sr = 3;
            Shiftvar.Sp = 7;
            return 2; // Blink aus rechts
        }
        else if (CanByte == 0 && CanData == 3)
        {
            Shiftvar.Sr = 3;
            Shiftvar.Sp = 7;
            return 3;
        }

        else if (CanByte == 0 && CanData == 10)
        {

            return 150;
        } // Warning

        break;

    case 1601 /* constant-expression */:
        if (CanByte == 0 && (CanData == 0 || CanData == 16))
        {
            return 10;
        }

        else if (CanByte == 0 && (CanData == 1 || CanData == 17))
        {
            return 11;
        }

        else if (CanByte == 0 && (CanData == 2 || CanData == 18))
        {
            return 12;
        }

        else if (CanByte == 0 && (CanData == 3 || CanData == 19))
        {
            return 13;
        }

        else if (CanByte == 0 && (CanData == 4 || CanData == 20))
        {
            return 14;
        }

        else if (CanByte == 0 && (CanData == 5 || CanData == 21))
        {
            return 15;
        }

        else if (CanByte == 0 && (CanData == 6 || CanData == 22))
        {
            return 16;
        }

        // SIDE with LEFT (7) or RIGHT (23)
        else if (CanByte == 0 && (CanData == 7 || CanData == 23))
        {
            return 17;
        }

        else if (CanByte == 0 && (CanData == 8 || CanData == 24))
        {
            return 18;
        }

        else if (CanByte == 0 && (CanData == 9 || CanData == 25))
        {
            return 19;
        }

        else
        {
            return 20;
            // Error
        }

        break;

    case 1602 /* constant-expression */:
        // Error beide Akkus aus

        if (CanByte == 0 && CanData == 1)
        { // Akku 1 An akku 2 Aus; kein Laden
            Shiftvar.Sr = 2;
            Shiftvar.Sp = 1;
            Shiftvar.Sv = 0;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 2;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 0;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            send_shiftstate(CS2,Shiftvar.S2);
            return 100;
        }

        else if (CanByte == 0 && CanData == 3)
        { // Akku 1 An akku 2 Aus; wärend Laden
            Shiftvar.Sr = 2;
            Shiftvar.Sp = 1;
            Shiftvar.Sv = 0;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 2;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 0;
            Shiftvar.Sv = 1;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            send_shiftstate(CS2,Shiftvar.S2);
            return 100;
        }
        else if (CanByte == 0 && CanData == 4)
        { // Akku 2 An akku 1 Aus;  Laden aus
            Shiftvar.Sr = 2;
            Shiftvar.Sp = 1;
            Shiftvar.Sv = 1;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 2;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 0;
            Shiftvar.Sv = 0;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);

            send_shiftstate(CS2,Shiftvar.S2);
            return 100;
        }
        else if (CanByte == 0 && CanData == 6)
        { // Akku 2 An akku 1 Aus; während laden
            Shiftvar.Sr = 2;
            Shiftvar.Sp = 1;
            Shiftvar.Sv = 1;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 2;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            Shiftvar.Sp = 0;
            save_shiftstate_bit(Shiftvar.Sp,Shiftvar.Sv, Shiftvar.S2);
            send_shiftstate(CS2,Shiftvar.S2);
            return 100;
        }

        else
        {
            return 101;
            // Error
        }

    case 1603 /* constant-expression */:

        log_w("1603 not implemented");
        break;

    default:
        log_e("Unknown case");
        return 0;
        break;
    }

    return 0;
}
void Shift_Akku::Blink(int on, int Side)
{
    
    for (int j = 0; j < 8; j++)
    {
        if (on == 0 && Side == 0)
        {
            log_i("LEDFront Links Aus");
            save_shiftstate_bit(0, 0, Shiftvar.S3);
        
            send_shiftstate(CS3,Shiftvar.S3);
        }
        else if (on == 1 && Side == 0)
        {
            log_i("LEDFront Links An");
            save_shiftstate_bit(0, 1, Shiftvar.S3);
          
            send_shiftstate(CS3,Shiftvar.S3);
        }
        else if (on == 0 && Side == 1)
        {
            log_i("LEDFront Rechts Aus");
            save_shiftstate_bit(6, 0, Shiftvar.S3);
            send_shiftstate(CS3,Shiftvar.S3);
        }
        else if (on == 1 && Side == 1)
        {
            log_i("LEDFront Rechts An");
            save_shiftstate_bit(6, 1, Shiftvar.S3);
            send_shiftstate(CS3,Shiftvar.S3);
        }
    }
    send_shiftstate(CS3,Shiftvar.S3);
}
void Shift_Akku::Akkupow(int AkkuNr, float LEDSpannungsvareanz)
{
    float voltage1 = (float)analogReadMilliVolts(Akku1Powerlvl) / 1000 * 13.2 ;//+ (analogReadMilliVolts(Akku1Powerlvl) / 1000) * (analogReadMilliVolts(Akku1Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt1 = (int)(voltage1 * 10);
    float voltage2 = (float)analogReadMilliVolts(Akku2Powerlvl) / 1000 * 13.2  ; // + (analogReadMilliVolts(Akku2Powerlvl) / 1000) * (analogReadMilliVolts(Akku2Powerlvl) / 1000) * 1.3; // Umrechnung in einen Spannungswert
    int volt2 = voltage2 * 10;

    log_i("volt akku1: %u   akku2 %u", volt1, volt2);
    log_i("Shiftvar.S2[0]: %d   AkkuNr: %d", Shiftvar.S2[0], AkkuNr);



    if (Shiftvar.S2[0] == 1)  // laden an
    {
        if (AkkuNr == 1)
        {

            if (volt1 > 220)
            {
                save_shiftstate_bit(4,1,Shiftvar.S2);
                
                send_shiftstate(CS2,Shiftvar.S2);
            }
            if (volt1 > 240)
            {
                save_shiftstate_bit(0,1,Shiftvar.S1);
               
                send_shiftstate(CS1,Shiftvar.S1);
            }
            if (volt1 > 260)
            {
                save_shiftstate_bit(7,1,Shiftvar.S2);
                
                send_shiftstate(CS2,Shiftvar.S2);
            }
            if (volt1 > 280)
            {
                save_shiftstate_bit(5,1,Shiftvar.S2);
                send_shiftstate(CS2,Shiftvar.S2);
            }
            if (volt1 > 290)
            {
                
                save_shiftstate_bit(6,1,Shiftvar.S2);
                send_shiftstate(CS2,Shiftvar.S2);
            }
        }
        else if (AkkuNr == 2)
        {

            if (volt2 > 210)
            {   
                save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);

                if (volt2 > 230)
                {
                    save_shiftstate_bit(7,1,Shiftvar.S1);
                    send_shiftstate(CS1,Shiftvar.S1);
                }
                if (volt2 > 250)
                {
                    save_shiftstate_bit(6,1,Shiftvar.S1);
                    send_shiftstate(CS1,Shiftvar.S1);
                }
                if (volt2 > 270)
                {
                    save_shiftstate_bit(4,1,Shiftvar.S1);
                    send_shiftstate(CS1,Shiftvar.S1);
                }
                if (volt2 > 290)
                {
                    save_shiftstate_bit(3,1,Shiftvar.S1);
                    send_shiftstate(CS1,Shiftvar.S1);
                }
            }
        }
    }
    if (Shiftvar.S2[0] == 0)  // Laden Aus
    {
        if (AkkuNr == 1)
        {

            if (volt1 < 205 - LEDSpannungsvareanz)
            {   
                save_shiftstate_bit(4,0,Shiftvar.S2);
                
                if (Shiftvar.S1[1] == 1 && volt2 >= 220)
                {   
                    save_shiftstate_bit(1,1,Shiftvar.S2);
                    save_shiftstate_bit(2,1,Shiftvar.S2);
                    save_shiftstate_bit(2,1,Shiftvar.S1);
                    save_shiftstate_bit(1,0,Shiftvar.S1);
                    Shiftvar.Akku1LOW = 0;
                }
                send_shiftstate(CS1,Shiftvar.S1);
                send_shiftstate(CS2,Shiftvar.S2);
                
            }
            if (volt1 < 210 - LEDSpannungsvareanz && Shiftvar.S1[1] == 1 )
            {
                Shiftvar.Akku1LOW = 1;
            }
            if (volt1 < 225 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(0,0,Shiftvar.S1);
                 save_shiftstate_bit(4,1,Shiftvar.S2);
                 send_shiftstate(CS2,Shiftvar.S2);
                
                send_shiftstate(CS1,Shiftvar.S1);
            
            }
            if (volt1 < 245 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(7,0,Shiftvar.S2);
                 save_shiftstate_bit(0,1,Shiftvar.S1);
                 save_shiftstate_bit(4,1,Shiftvar.S2);
                
                send_shiftstate(CS2,Shiftvar.S2);
                send_shiftstate(CS1,Shiftvar.S1);
                
            }
            if (volt1 < 265 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(5,0,Shiftvar.S2);
                save_shiftstate_bit(7,1,Shiftvar.S2);
                save_shiftstate_bit(0,1,Shiftvar.S1);
                save_shiftstate_bit(4,1,Shiftvar.S2);
                send_shiftstate(CS1,Shiftvar.S1);
                send_shiftstate(CS2,Shiftvar.S2);
            
            }
            if (volt1 < 285 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(6,0,Shiftvar.S2);
                save_shiftstate_bit(5,1,Shiftvar.S2);
                save_shiftstate_bit(7,1,Shiftvar.S2);
                save_shiftstate_bit(0,1,Shiftvar.S1);
                save_shiftstate_bit(4,1,Shiftvar.S2);
                send_shiftstate(CS1,Shiftvar.S1);
                send_shiftstate(CS2,Shiftvar.S2);
            }
            if(volt2 > 285 - LEDSpannungsvareanz)
                save_shiftstate_bit(6,1,Shiftvar.S2);
                save_shiftstate_bit(5,1,Shiftvar.S2);
                save_shiftstate_bit(7,1,Shiftvar.S2);
                save_shiftstate_bit(0,1,Shiftvar.S1);
                save_shiftstate_bit(4,1,Shiftvar.S2);
                send_shiftstate(CS1,Shiftvar.S1);
                send_shiftstate(CS2,Shiftvar.S2);
        }
        else if (AkkuNr == 2)
        {

            if (volt2 < 205 - LEDSpannungsvareanz)
            {   
                save_shiftstate_bit(5,0,Shiftvar.S1);
                
                if (Shiftvar.S1[2] == 1 && volt1 >= 220)
                {
                    save_shiftstate_bit(1,0,Shiftvar.S2);
                    save_shiftstate_bit(2,0,Shiftvar.S2);
                    save_shiftstate_bit(2,0,Shiftvar.S1);
                    save_shiftstate_bit(1,1,Shiftvar.S1);
                    Shiftvar.Akku1LOW = 0;
                }
                send_shiftstate(CS1,Shiftvar.S1);;
                send_shiftstate(CS2,Shiftvar.S2);;
            }
            if (volt2 < 210 - LEDSpannungsvareanz && Shiftvar.S1[2] == 1 ) 
            {
                Shiftvar.Akku2LOW = 1;
            }
            if (volt2 < 225 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(7,0,Shiftvar.S1);
                 save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);;
            }
            if (volt2 < 245 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(7,1,Shiftvar.S1);
                save_shiftstate_bit(6,0,Shiftvar.S1);
                save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);;
            }
            if (volt2 < 265 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(3,0,Shiftvar.S1);
                save_shiftstate_bit(6,1,Shiftvar.S1);
                save_shiftstate_bit(7,1,Shiftvar.S1);
                save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);;
            }
            if (volt2 < 285 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(4,0,Shiftvar.S1);
                save_shiftstate_bit(3,1,Shiftvar.S1);
                save_shiftstate_bit(6,1,Shiftvar.S1);
                save_shiftstate_bit(7,1,Shiftvar.S1);
                save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);
            }
            if ( volt2 > 285 - LEDSpannungsvareanz)
            {
                save_shiftstate_bit(3,1,Shiftvar.S1);
                save_shiftstate_bit(4,1,Shiftvar.S1);
                save_shiftstate_bit(7,1,Shiftvar.S1);
                save_shiftstate_bit(6,1,Shiftvar.S1);
                save_shiftstate_bit(5,1,Shiftvar.S1);
                send_shiftstate(CS1,Shiftvar.S1);

            }
        }
    }
}
void Shift_Akku::akkuswitch()
{
    float Volt1 = (float)analogReadMilliVolts(Akku1Powerlvl) * 14;
    float Volt2 = (float)analogReadMilliVolts(Akku2Powerlvl) * 14;
    if (Shiftvar.S1[1] == 1 && Volt2 > 22.0)
    {
    }
}

int Shift_Akku::laden()
{
    return Shiftvar.S2[0];
}
int Shift_Akku::Akkustatus()
{
    if (Shiftvar.S1[2] == 1)
    {
        return 2;
    }
    else if(Shiftvar.S1[1] == 1)
    {
        return 1;
    }
    else{

        return 0;
    }
}
