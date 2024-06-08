#ifndef CANREADER_H
#define CANREADER_H

#include "can_bus_manager.h"
#include "CAN.h"
#include "Shift_Command.h"


class CanReader {

    private:
    public:
    void read(CAN_frame_t& canData);  
    
};


#endif /* CANREADER_H */
