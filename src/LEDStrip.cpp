#include <LEDStrip.h>
#include <pins.h>
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 16
Adafruit_NeoPixel pixels(NUMPIXELS, LEDStrippin, NEO_RGBW + NEO_KHZ800);

void LedStrip::AlloneColor(uint8_t red , uint8_t green, uint8_t blue, uint8_t white , int waitled )
{
int currentmilli = millis();
pixels.begin();
pixels.clear();
for(int i=0; i<NUMPIXELS; ) { // For each pixel...
    // pixels.Color() takes RGBW values, from 0,0,0,0 up to 255,255,255,255
    pixels.setPixelColor(i, pixels.Color(red, green, blue,white));
    pixels.show();
    if(currentmilli + waitled <= millis())
    {
    i++;
    currentmilli = millis();
    }
}
}

void LedStrip::colorWipe(uint32_t color, int pixelnumber, int wait, int startpixel, int waitnext)
{
  
  unsigned long Count = millis();

  for (int i = startpixel; i < pixelnumber;)
  {                                // For each pixel in pixels...
    pixels.setPixelColor(i, color); //  Set pixel's color (in RAM)

    if (Count + wait <= millis())
    { // möglicher Timer
      i++;
      Count = millis();
    }
    //  Update pixels to match
  }
  for(int j = 0; j < 2;){
      if(Count + waitnext <= millis()){
        j++;
        Count = millis();
     }
  }
  pixels.show();
}

void LedStrip::SideColor(LED_SIDE side, uint32_t color)
{
  
  uint8_t start = pix.NUM_Start_PXL;
  uint8_t end = pix.NUM_Pix;

  if (side == LEFT) {
    end = (pix.NUM_Pix + pix.NUM_Start_PXL)/2;
  } else if (side ==  RIGHT) {
    start = (pix.NUM_Pix + pix.NUM_Start_PXL)/2;
  } else if (side == BOTH) {
   // start = NUM_Pix;  macht keinen sinn start = end
  }

  for (; start < end; start++)
  {
    pixels.setPixelColor(start, color);
  }
  pixels.show();
}

void LedStrip::init_sequence() {
  uint8_t test_color_br = 128;
  uint32_t init_colors[5] = {pixels.Color(test_color_br, 0, 0, 0), pixels.Color(0, test_color_br, 0, 0),
                             pixels.Color(0, 0, test_color_br, 0), pixels.Color(0, 0, 0, test_color_br), pixels.Color(0, 0, 0, 0)};
  for (uint8_t test_color = 0; test_color < 5; test_color++) {
    for(uint8_t i = 0; i < pix.NUM_Pix; i++) {
      pixels.setPixelColor(i, init_colors[test_color]);
    }
    pixels.show();
    delay(300);
  }
}
void LedStrip::LedstripMode(uint8_t Mode, uint8_t RED,uint8_t Green,uint8_t Blue,uint8_t White,uint8_t LED_LVL,uint8_t LED_LVL_Number,uint8_t SIDE)
{
    switch (Mode)
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }
}
void LedStrip::LEDStripINIT()
{
  pixels.begin(); // INITIALIZE NeoPixel pixels object (REQUIRED)
  pixels.show();  // Turn OFF all pixels ASAP
  pixels.setBrightness(255);


}