#ifndef ACCU_H
#define ACCU_H
#include <HC595.h>
#include <pins.h>
class Accu
{
private:
    /* data */

public:
typedef struct
    {
        uint8_t Accu1LOW = 0;  
        uint8_t Accu2LOW = 0; 
        
    } AccuStatus;
    AccuStatus BAT;
    void Accumode(uint8_t Mode);
    void Accucontroll(uint8_t AccuNr);
   
};






#endif /* ACCU_H */
