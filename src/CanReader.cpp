#include "CanReader.h"
#include <Accu.h> 
#include <LEDStrip.h>
LedStrip Strip;
Accu Bat;
Shift_Command Shift;
void CanReader::read( CAN_frame_t& canData)
{
    switch (canData.MsgID)
    {
    case 1600:
        //Turn Signal
        Shift.turnsignal(canData.data.u8[0], canData.data.u8[1]);
        //Fan 
        Shift.fan( canData.data.u8[2]);
        break;
    case 1601:
        // LED Strip
        Strip.LedstripMode(canData.data.u8[0], canData.data.u8[1], canData.data.u8[2], canData.data.u8[3], canData.data.u8[4], canData.data.u8[5], canData.data.u8[6], canData.data.u8[7]);
        break;
    case 1602:
        // Accu 
        Bat.Accumode(canData.data.u8[0] );
        break;
    case 1603:
        // Rearlift
        break;
    default:
        break;
    } 


}