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

#define KM 27
#define DM 25
#define ZINGSNIS 2 // kiek tasku pasislenka per viena karta
int r = 5 ; // apksritimo spindulys
double cx = SCREEN_WIDTH/2 ;
double cy = SCREEN_HEIGHT/2 ;
int kamp;
double rad ;
int kmm, dmm ;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  kamp = random(360) ;
  pinMode (KM, INPUT_PULLUP) ;
  pinMode (DM, INPUT_PULLUP) ;
  
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
  display.drawRect(0, 0, SCREEN_WIDTH-0, SCREEN_HEIGHT-0, WHITE);
  display.display();
}


void loop() {
    // valom skritulį
    display.fillCircle(int(cx), int(cy), r, BLACK);

   // tikrinam ar mygtukai paspausti
   kmm = digitalRead (KM) ;
   dmm = digitalRead (DM) ;
   if (kmm == LOW) r-- ;
   if (dmm == LOW) r++ ;
    
   // tikrinam ar atsitrenkė

   
   //skaičiuojam naujas koordinates
   rad = M_PI/double(180)*double(kamp) ;
   cx += ZINGSNIS*cos(rad) ; 
   cy += ZINGSNIS*sin(rad) ;

   // piešiam skritulį
   display.fillCircle(int(cx), int(cy), r, WHITE); 
   display.display();
   //delay (5) ;

}
