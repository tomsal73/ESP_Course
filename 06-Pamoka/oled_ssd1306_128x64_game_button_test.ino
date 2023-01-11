#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)
// On ESP32 Node MCU:   21(SDA),  22(SCL), ...
// On ESP8266 Node MCU:   4(SDA),  5(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< get adddress using I2C scanner
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define KM1 14
#define KM2 27
#define DM1 26
#define DM2 25

#define R 5    // apksritimo spindulys
#define GAP 10 // atstumas nuo krašto

int km1, km2, dm1, dm2 ;

void setup() {
  pinMode (KM1, INPUT_PULLUP) ;
  pinMode (DM1, INPUT_PULLUP) ;
  pinMode (KM2, INPUT_PULLUP) ;
  pinMode (DM2, INPUT_PULLUP) ;
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 seconds
  display.clearDisplay();
  display.display();
}

void loop() {
   // tikrinam ar mygtukai paspausti
   km1 = digitalRead (KM1) ;
   km2 = digitalRead (KM2) ;
   dm1 = digitalRead (DM1) ;
   dm2 = digitalRead (DM2) ;
   if (km1 == LOW) 
     display.fillCircle(GAP, GAP, R, WHITE) ;
   else 
     display.fillCircle(GAP, GAP, R, BLACK) ;
     
   if (km2 == LOW) 
     display.fillCircle(GAP, SCREEN_HEIGHT-GAP, R, WHITE) ;
   else 
     display.fillCircle(GAP, SCREEN_HEIGHT-GAP, R, BLACK) ;

   if (dm1 == LOW) 
     display.fillCircle(SCREEN_WIDTH-GAP, GAP, R, WHITE) ;
   else 
     display.fillCircle(SCREEN_WIDTH-GAP, GAP, R, BLACK) ;
   
   if (dm2 == LOW) 
     display.fillCircle(SCREEN_WIDTH-GAP, SCREEN_HEIGHT-GAP, R, WHITE) ;
   else 
     display.fillCircle(SCREEN_WIDTH-GAP, SCREEN_HEIGHT-GAP, R, BLACK) ;

   display.display();  
}
