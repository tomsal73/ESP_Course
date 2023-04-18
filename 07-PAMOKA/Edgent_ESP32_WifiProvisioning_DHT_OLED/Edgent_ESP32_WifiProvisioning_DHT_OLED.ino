/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPLglVEp4km"
#define BLYNK_TEMPLATE_NAME "DHT"
//#define BLYNK_AUTH_TOKEN "ezxp4E-5AcbJn71AHAraiCq4eEbj82h4"
//#define BLYNK_WIFI_SSID "peteliskiu24"
//#define BLYNK_WIFI_PASS "pass"


#define BLYNK_FIRMWARE_VERSION        "0.1.4"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< get adddress using I2C scanner
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <DHTesp.h>
#define DHTPIN 25     // Sensoriaus jungtis
DHTesp dht;
  float h =  -1; // kintamasis dregnumui
  float t =  -1; // kintamasis tempraturai

void updateOled() {

  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);
  
  display.setCursor (0,0) ;
  display.print ('v') ;
  display.print (BLYNK_FIRMWARE_VERSION) ;
    
  display.setTextSize(2);             // Draw 2X-scale text
  
  display.setCursor (1,15) ;
  display.print (h) ;
  display.print (" %") ;
  
  display.setCursor (1,35) ;
  display.print (t) ;
  // print degree symbols ( ° )
  display.drawCircle(70, 35, 2, WHITE);
  display.setCursor(74,35);
  display.print("C");
  
  display.display(); 
}

// This function creates the timer object. It's part of Blynk library
BlynkTimer timer;


void myTimer() {
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  h = dht.getHumidity();
  t = dht.getTemperature();

	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return ;
	}
  Blynk.virtualWrite(V1, h);  
  Blynk.virtualWrite(V2, t);
  updateOled() ;
}  

void setup()
{
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 seconds
  

  dht.setup(DHTPIN, DHTesp::DHT11);

  BlynkEdgent.begin();
  // Setting interval to send data to Blynk Cloud to 2000ms.
  // It means that data will be sent every 2 seconds
  timer.setInterval(2000L, myTimer);  
}

void loop() {
  BlynkEdgent.run();

  // runs BlynkTimer
  timer.run();
}

