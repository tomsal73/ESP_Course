/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP32 chip.
 *
 * You need to install this for ESP32 development:
 *   https://github.com/espressif/arduino-esp32
 *
 * Please be sure to select the right ESP32 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/
#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"

#define BLYNK_PRINT Serial  // Comment this out to disable prints and save space
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WifiID";
char pass[] = "WifiPass";

#define LEDPIN 25

// This function creates the timer object. It's part of Blynk library
BlynkTimer timer;

int timeOn = 0;

void myTimer() {
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  timeOn++;
  //Serial.println (timeOn) ;
  Blynk.virtualWrite(V2, timeOn);
}

BLYNK_WRITE(V0)  // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1) {
    // execute this code if the switch widget is now ON
    //Serial.println ("ON") ;
    digitalWrite(LEDPIN, HIGH);  // Set digital pin 2 HIGH
  } else {
    // execute this code if the switch widget is now OFF
    //Serial.println ("OFF") ;
    digitalWrite(LEDPIN, LOW);  // Set digital pin 2 LOW
  }
}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  // Setting interval to send data to Blynk Cloud to 1000ms.
  // It means that data will be sent every second
  timer.setInterval(1000L, myTimer);
}

void loop() {
  // run Blynk command processor
  Blynk.run();

  // runs BlynkTimer
  timer.run();
}
