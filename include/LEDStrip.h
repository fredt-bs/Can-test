#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Adafruit_NeoPixel.h>

class LedStrip {


private:
typedef struct
    {
      uint8_t  NUM_Pix = 43;
      uint8_t  NUM_Start_PXL = 1;
    } Pixel;
Pixel pix;

enum LED_SIDE {
  LEFT,
  RIGHT,
  BOTH
};
LED_SIDE Side1;

void AlloneColor(uint8_t red , uint8_t green, uint8_t blue, uint8_t white, int waitled);
void colorWipe(uint32_t color, int pixelnumber, int wait, int startpixel, int waitnext);
void SideColor(LED_SIDE side, uint32_t color);
public:
void LedstripMode(uint8_t Mode, uint8_t RED,uint8_t Green,uint8_t Blue,uint8_t White,uint8_t LED_LVL,uint8_t LED_LVL_Number,uint8_t SIDE);
void init_sequence();
void LEDStripINIT();
};

#endif /* LEDSTRIP_H */

