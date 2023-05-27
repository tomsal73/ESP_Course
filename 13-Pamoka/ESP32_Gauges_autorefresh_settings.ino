/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-web-server-gauges/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  Modified by Tomas Šalkauskas 2023
*********/

// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Visas HTML puslapio tekstas priskiriams kintamajam 
// const char index_html[]
#include "html_body.h"
const char* PARAM_INPUT_STATE = "state";
const char* PARAM_INPUT_VAL = "value";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< get adddress using I2C scanner
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <DHTesp.h>
#define DHTPIN 25     // Sensoriaus jungtis
#define DHTTYPE    DHT11
DHTesp dht;
  float h =  -1; // kintamasis dregnumui
  float t =  -1; // kintamasis tempraturai


 #define HUMPIN 13 // Laistymo įrenginys

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

// Replace with your network credentials
const char* ssid = ""; //"REPLACE_WITH_YOUR_SSID";
const char* password = ""; //"REPLACE_WITH_YOUR_PASSWORD";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDHTTemperature() {
  //t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}


String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}


void updateOled() {

  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);
  
  display.setCursor (0,0) ;
  display.print ("IP: ") ;
  display.print(WiFi.localIP()) ;
  //if (WiFi.status() != WL_CONNECTED) {
  //    display.print ("be rysio") ;
  //}    
  //else  {
  //    display.print ("Wifi yra");
  //}    
  
  display.setTextSize(2);             // Draw 2X-scale text
  
  display.setCursor (1,20) ;
  display.print (h) ;
  display.print (" %") ;
  
  display.setCursor (1,40) ;
  display.print (t) ;
  // print degree symbols ( ° )
  display.drawCircle(70, 40, 2, WHITE);
  display.setCursor(74,40);
  display.print("C");
  
  display.display(); 
}

// riba, žemiau kurios įjungiamas prietaisas
int humidityThreshold = 40 ;

void setHumidityThreshold(int newTreshold) {
  // nustatoma nauja dregnumo riba
  char buffer[100];
  sprintf(buffer, "Current threshold: %d; new threshold: %d", humidityThreshold,  newTreshold);
  Serial.println (buffer) ;
  if ((newTreshold > -1) && (humidityThreshold != newTreshold)) {
      humidityThreshold = newTreshold ;
  }
}

void manageDevices() {
  // irengniai įjungiami arba isjugniami pagal davikliu parodymus
  if (h < humidityThreshold) {
    digitalWrite(HUMPIN, HIGH);
  } else {
    digitalWrite(HUMPIN, LOW);
  }
}

void getTemp() {
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  h = dht.getHumidity();
  t = dht.getTemperature();

	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		//return ;
	}

  updateOled() ;
}  

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    updateOled() ;
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "HumidityThreshold"){
    return String(humidityThreshold);
  }

  return String();
}

void setup() {
  Serial.begin(115200);
  pinMode (HUMPIN , OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 seconds

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  dht.setup(DHTPIN, DHTesp::DHTTYPE);

  initWiFi();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  server.on("/hum_slider", HTTP_GET, [](AsyncWebServerRequest *request){
    String inputMessage1;
    if (request->hasParam(PARAM_INPUT_VAL)) {
      inputMessage1 = request->getParam(PARAM_INPUT_VAL)->value();
      if (inputMessage1 != "-1") {
        setHumidityThreshold(inputMessage1.toInt()) ;
      }  
      request->send_P(200, "text/plain", String(humidityThreshold).c_str());
    }
  });


  // Start server
  server.begin();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    getTemp() ;
    manageDevices() ;
    lastTime = millis();
  }
 
}