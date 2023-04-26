
// Uncomment your board, or configure a custom board in Settings.h
#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


// Define the service and characteristic UUIDs
#define SERVICE_UUID        "181A" // Environmental Sensing Service
#define TEMP_CHAR_UUID      "2A6E" // Temperature Characteristic
#define HUMID_CHAR_UUID     "2A6F" // Humidity Characteristic

// Define the Generic Access Service and Device Name UUIDs
#define GENERIC_ACCESS_UUID "1800" // Generic Access Service
#define DEVICE_NAME_UUID    "2A00" // Device Name Characteristic

#define DESCRIPTOR_UUID 0x2903 //

  // Temperature Characteristic and Descriptor
  //BLECharacteristic dhtTemperatureCelsiusCharacteristics("cba1d466-344c-4be3-ab3f-189f80dd7518", BLECharacteristic::PROPERTY_NOTIFY);
  BLECharacteristic dhtTemperatureCelsiusCharacteristics(TEMP_CHAR_UUID, BLECharacteristic::PROPERTY_NOTIFY);
  BLEDescriptor dhtTemperatureCelsiusDescriptor(BLEUUID((uint16_t)DESCRIPTOR_UUID));

  // Humidity Characteristic and Descriptor
  BLECharacteristic dhtHumidityCharacteristics(HUMID_CHAR_UUID, BLECharacteristic::PROPERTY_NOTIFY);
  BLEDescriptor dhtHumidityDescriptor(BLEUUID((uint16_t)DESCRIPTOR_UUID));

// Create a BLE characteristic for device name
BLECharacteristic *pDeviceNameCharacteristic = NULL;

bool deviceConnected = false; //BLE Connection status

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
  display.print ("BLE Connection: ") ;
  if ( deviceConnected ) {
      display.print ("on") ;
  }    
  else  {
      display.print ("off");
  }    
  
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


void getTemp() {
  // This function describes what will happen with each timer tick
  // e.g. writing sensor value to datastream V5
  h = dht.getHumidity();
  t = dht.getTemperature();

	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return ;
	}

  updateOled() ;
}  


//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

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

  // Create the BLE Device
  BLEDevice::init("ESP32 DHT Sensor");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *dhtService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics and Create a BLE Descriptor
  // Temperature
  dhtService->addCharacteristic(&dhtTemperatureCelsiusCharacteristics);
  dhtTemperatureCelsiusDescriptor.setValue("BDHTME temperature Celsius");
  dhtTemperatureCelsiusCharacteristics.addDescriptor(&dhtTemperatureCelsiusDescriptor);

  // Humidity
  dhtService->addCharacteristic(&dhtHumidityCharacteristics);
  dhtHumidityDescriptor.setValue("DHT humidity");
  dhtHumidityCharacteristics.addDescriptor(&dhtHumidityDescriptor);
  
  // Start the service
  dhtService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

}

void loop() {
  getTemp() ;

  Serial.print ("temp: ") ;Serial.println (t) ;
  Serial.print ("hum: ") ;Serial.println (h) ;
  Serial.println ("-----------------------------") ;

  // Update the characteristics with the new values
  //pTempCharacteristic->setValue("temperatura");
  //pHumidCharacteristic->setValue("dregnumas");

  static char temperatureCTemp[6];
  dtostrf(t, 6, 2, temperatureCTemp);
  dhtTemperatureCelsiusCharacteristics.setValue(temperatureCTemp);

  static char humidityTemp[6];
  dtostrf(h, 6, 2, humidityTemp);
  dhtHumidityCharacteristics.setValue(humidityTemp);


  // Notify the client about the new values
  dhtTemperatureCelsiusCharacteristics.notify();
  dhtHumidityCharacteristics.notify();

  // Wait for the update interval
  delay(1000);

}

