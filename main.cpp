#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> //use the modified library by WereCatf for support of ESP8266


//all displays are connected to D2, D1, D6, D7, D6 with their corresponding pins


//pins for display one
const int8_t RST_PIN = D2; // reset pins of all displays getting up wired to this pin; but this pin is only initialized for the first display by the library
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;

// pins for software SPI
const int8_t DIN_PIN_SPI = D7;
const int8_t CLK_PIN_SPI = D5;

//additional pin needed once when more than one display is used
const int8_t Dummy_RST = D8;       // dummy reset pin to capture resets for all displays other the first one

//additional pin needed for every display other than the first one
//third display needs its own CS!
const int8_t CS_display_two = D0;  // CS (chip select) for 2nd display, every display needs its own CS pin

//first display display_esp1
Adafruit_PCD8544 display_esp1(CLK_PIN_SPI, DIN_PIN_SPI , DC_PIN , CE_PIN, RST_PIN);

//second display display_esp2
Adafruit_PCD8544 display_esp2(CLK_PIN_SPI, DIN_PIN_SPI , DC_PIN , CS_display_two, Dummy_RST); //initialized with its own CS pin and the Dummy_RST!

//hypothetical third display display_esp3
//Adafruit_PCD8544 display_esp3(CLK_PIN_SPI, DIN_PIN_SPI , DC_PIN , CS_display_three, Dummy_RST); //same Dummy_RST pin, but needs its own CS pin defined, here:CS_display_three



void setup()   {

  display_esp1.begin();               //start displays
  display_esp2.begin();

  display_esp1.setContrast(50);       //modify contrast level, can be modified indepently for each display
  display_esp2.setContrast(50);

  display_esp1.clearDisplay();        // prevents Adafruit logo from appearing that is loaded in the frame buffer by the library
  display_esp1.setCursor(0,0);        //position for text on display_esp1
  display_esp1.print("display_one");
  display_esp1.display();            //send changes to display1
  delay(30);                         //this delay prevents crosstalk from the first to the second display
  display_esp2.clearDisplay();
  display_esp2.setCursor(0,15);      //position for text on display_esp1; just for demo another position
  display_esp2.print("display_two");
  display_esp2.display();            //send changes to display2
}

void loop() {
}
