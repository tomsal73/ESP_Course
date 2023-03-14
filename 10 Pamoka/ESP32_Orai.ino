/*
  Thanks to for this example
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-open-weather-map-thingspeak-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define TEXT1_HEIGHT 13 // Heigt of text size 1 row

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
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

//------------------------------------------------------------------
// HTTP reikalingi nuistatymai
const char* ssid = "iPhone_Salkus";
const char* password = "1234567890";

// Your Domain name with URL path or IP address with path
//String openWeatherMapApiKey = "REPLACE_WITH_YOUR_OPEN_WEATHER_MAP_API_KEY";
// Example:
String openWeatherMapApiKey = "9ea5a3cd53f1dbc196176454eeb56679";

// Replace with your country code and city
String city = "Šiauliai";
String countryCode = "LT";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

String  wStatusL1;
String  wStatusL2;
String  wStatusL3 ;
String  oras ; 
int temp1 ;
int temp2 ;
//------------------------------------------------------------------


//------------------------------------------------------------------
// Displėjaus valdymo funkcijos

void Print1 (String pTxt) {
    //display.fillRect (0,0,SCREEN_WIDTH,TEXT1_HEIGHT*2-1, BLACK) ;
    u8g2_for_adafruit_gfx.setForegroundColor(WHITE);
    u8g2_for_adafruit_gfx.setBackgroundColor(BLACK);
    u8g2_for_adafruit_gfx.setCursor (0, TEXT1_HEIGHT) ;
    u8g2_for_adafruit_gfx.print (pTxt) ;
    //display.setCursor (0,0) ;
    //display.setTextColor(WHITE);
    //display.print (pTxt) ;
    display.display();
}

void Print2 (String pTxt) {
    display.drawRoundRect (0,TEXT1_HEIGHT*2,SCREEN_WIDTH,TEXT1_HEIGHT, 3, WHITE) ;
    u8g2_for_adafruit_gfx.setForegroundColor(WHITE);
    u8g2_for_adafruit_gfx.setBackgroundColor(BLACK);
    u8g2_for_adafruit_gfx.setCursor (1,TEXT1_HEIGHT*3-2) ;
    u8g2_for_adafruit_gfx.print (pTxt) ;
    //display.setCursor (1,TEXT1_HIGHT*3) ;
    //display.setTextColor(BLACK);
    //display.print(pTxt);
    display.display();
}

void Print3 (String pTxt) {
    u8g2_for_adafruit_gfx.setForegroundColor(WHITE);
    u8g2_for_adafruit_gfx.setBackgroundColor(BLACK);
    u8g2_for_adafruit_gfx.setCursor (0,TEXT1_HEIGHT*4-1) ;
    u8g2_for_adafruit_gfx.print(pTxt);
    //display.fillRect (0,TEXT1_HIGHT*5,SCREEN_WIDTH,TEXT1_HIGHT*3, BLACK) ;
    //display.setCursor (0,TEXT1_HIGHT*5) ;
    //display.setTextColor(WHITE);
    //display.print(pTxt);
    display.display();
}

//-------------------------------------------------------------------


void setup() {
  Serial.begin(115200);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  u8g2_for_adafruit_gfx.begin(display);                 // connect u8g2 procedures to Adafruit GFX
  u8g2_for_adafruit_gfx.setFontMode(0);
  display.display();
  delay(1000);  
  display.clearDisplay();
  //u8g2_for_adafruit_gfx.setFont(u8g2_font_7x13_te);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_t0_11_te );
  
  display.setTextSize (1) ;

  wStatusL2 = "Jungiamės" ;
  WiFi.begin(ssid, password);
  Print1(wStatusL2);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    wStatusL2+= "." ;
    Print1(wStatusL2);
  }
  wStatusL2 = "Prisijungėm    " ;
  Print1(wStatusL2);
  delay(2000);
}

void loop() {
// Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey + "&lang=lt&units=metric";
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        wStatusL2 = "Parsing input failed!";
        Print2(wStatusL2);
        return;
      } 

      char tmp[128] ;
      strcpy (tmp, myObject["name"]) ;
      wStatusL2 = String(tmp) ;
      Print2(wStatusL2);
        
      //oras = JSON.stringify(myObject["weather"][0]["description"]) ;
      strcpy (tmp, myObject["weather"][0]["description"]) ;
      oras = String(tmp) ;
      temp1 = myObject["main"]["temp"];
      temp2 = myObject["main"]["feels_like"];
      wStatusL3 = oras + "\r\nTemp: "+ temp1+ "; Jausmas: "+temp2 ;
      Print3(wStatusL3) ;
    }
    else {
      wStatusL1 = "WiFi Disconnected";
      Print1(wStatusL1) ;
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
