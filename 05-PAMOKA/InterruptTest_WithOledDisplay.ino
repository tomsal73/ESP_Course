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

#define R_BUTTON_PIN 25
#define LED_PIN 26
#define L_BUTTON_PIN 27

long currentTime, lastCheckTime ; 
long interval = 250 ; // Button check frequency
int interruptMode = 0;
String interruptModeNames [] = {"LOW", "HIGH", "CHANGE", "FALLING", "RISING"} ;
int interruptModes [] = {LOW, HIGH, CHANGE, FALLING, RISING} ;
int ledStatus = 0 ;
//LOW: to trigger the interrupt whenever the pin is LOW;
//HIGH: to trigger the interrupt whenever the pin is HIGH;
//CHANGE: to trigger the interrupt whenever the pin changes value – for example from HIGH to LOW or LOW to HIGH;
//FALLING: for when the pin goes from HIGH to LOW;
//RISING: to trigger when the pin goes from LOW to HIGH.

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 seconds
  printMode ("Interrupt TEST") ;
  delay(1000); // Pause for 1 seconds
  
  // setup pin modes
  pinMode (L_BUTTON_PIN, INPUT_PULLUP) ;
  pinMode (R_BUTTON_PIN, INPUT_PULLUP) ;
  pinMode (LED_PIN, OUTPUT) ;
  
  //start time counter
  currentTime = millis() ;
  lastCheckTime = millis() ;
}

void printMode(String modeStr) {
  display.clearDisplay();
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(modeStr.c_str());
  display.display();
}

void processLed () {
  if (ledStatus == 0) {
     digitalWrite (LED_PIN, LOW) ;
  } else if (ledStatus == 1) {
     digitalWrite (LED_PIN, HIGH) ;
  } else {
    // reserved for blinking led
  }
}

void IRAM_ATTR rButtonPressed() {
  Serial.print("rButtonPressed!!! ");
  ledStatus = 1 - ledStatus ;
  Serial.print(interruptModeNames[interruptMode]);
  Serial.print(". LED status:");
  Serial.println(ledStatus);  
}

void loop() {
  currentTime = millis() ;
  if (currentTime - lastCheckTime >= interval) {
    // check if left button pressed
    lastCheckTime = currentTime ;
    int lbuttonState = digitalRead (L_BUTTON_PIN) ;
    //Serial.println (lbuttonState) ;
    if (lbuttonState == LOW) {
      interruptMode++ ;
    }
    if (interruptMode >= 5) {
      interruptMode = 0 ;
    }

    printMode(interruptModeNames[interruptMode]) ;
    digitalWrite(LED_PIN, LOW);
    attachInterrupt(digitalPinToInterrupt(R_BUTTON_PIN), rButtonPressed, interruptModes[interruptMode]);
  }
  processLed () ;
}
