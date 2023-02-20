#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_now.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define TEXT1_HIGHT 8 // Heigt of text size 1 row

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


#define SENSORPIN 25     // Sensoriaus jungtis, pakeiskite skaičių, jei naudojate kitą jungtį
#define EIL1 1  // Pirmos eilutės Y koordinatė

char statusTxt[64] ;
char status2Txt[64] ;
int siuntSk = 0 ; // išsiųstų žinučių skaičius
int gautSk = 0 ; // gautų žinučių skaičius

//------------------------------------------------------------------
// Displėjaus valdymo funkcijos

void Print1 (const char pTxt[]) {
    display.fillRect (0,0,SCREEN_WIDTH,TEXT1_HIGHT*2, BLACK) ;
    display.setCursor (0,0) ;
    display.setTextColor(WHITE);
    display.print (pTxt) ;
    display.display();
}

void Print2 (const char pTxt[]) {
    display.fillRect (0,TEXT1_HIGHT*3,SCREEN_WIDTH,TEXT1_HIGHT, WHITE) ;
    display.setCursor (1,TEXT1_HIGHT*3) ;
    display.setTextColor(BLACK);
    display.print(pTxt);
    display.display();
}

void Print3 (const char pTxt[]) {
    display.fillRect (0,TEXT1_HIGHT*5,SCREEN_WIDTH,TEXT1_HIGHT*2, BLACK) ;
    display.setCursor (0,TEXT1_HIGHT*5) ;
    display.setTextColor(WHITE);
    display.print(pTxt);
    display.display();
}

//-------------------------------------------------------------------

//------------------------------------------------------------------
// ESP NOW reikalingi nustatymai

// Pakeiskite kintamojo vardą ir gavėjo MAC Adresą
uint8_t addrVardas[] = {0x30, 0xC6, 0xF7, 0x0E, 0x25, 0xDC};

// Structure duomenims siųsti
// Gavėjo pusėje struktūra turi būti tokia pati
typedef struct struct_message {
  char vardas[32];
  char txt[60];
  int skaicius;
} struct_message;

// kintamasis myData, kuriame bus siunčiamas pranešimas
struct_message myData;

// kintamasis myData, kuriame bus gautas pranešimas
struct_message receivedData;

// kintamasis, zymintis, jog reikia atvaizduoti gautą pranešimą
bool dataRecived = false ;

// informacija apie gavėją
esp_now_peer_info_t peerInfo;

// callback funkcija kviečiama sėkmingai išsiuntus duomenis
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
   strcpy(status2Txt, status == ESP_NOW_SEND_SUCCESS ? "Pavyko :)" : "Siuntimas nepavyko");
}

// Callback funkcija kviečiama gavus pranešimą
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  dataRecived = true ;
  gautSk++ ;
}
//------------------------------------------------------------------



void setup() {
  Serial.begin(115200);
  pinMode (SENSORPIN, INPUT) ;

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(1000);  
  display.clearDisplay();
  display.setTextSize (1) ;

  display.display();
  
  // Wifi nustatomas į rėžimą: Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  // Inicializuojam ESP-NOW komunikaciją
  if (esp_now_init() == ESP_OK) {
     // inicializuoti pavyko
     Print1("ESP NOW Inicializuota");
     // Registruojam funkciją kuri bus iškviesta, išsiuntus duomenis
     esp_now_register_send_cb(OnDataSent);

     // Registruojam funkciją kuri bus iškviesta, gavus naują duomenų pranešimą
     esp_now_register_recv_cb(OnDataRecv);
  
     // Registruojam gavėjo adresą
     memcpy(peerInfo.peer_addr, addrVardas, 6);
     peerInfo.channel = 0;  
     peerInfo.encrypt = false;
     
     // Pridedam prie ESP gavėjų
     if (esp_now_add_peer(&peerInfo) == ESP_OK){
        Print1("Gavejas pridetas");
     }  else {
        Print1("Gavejo prideti nepavyko !");
     }
  } else {
     Print1("Klaida inicializuojant ESP-NOW !");
  }
  
  delay(2000);
}

void loop() {
  display.clearDisplay();

  
  // Nustatom siunčiamų duomenų reikšmes
  // Vardą pakeiskite į savo vardą
  strcpy(myData.vardas, "Tomas");
  strcpy(myData.txt, digitalRead (SENSORPIN) == LOW ? "Sviesu" : "Tamsu") ;

  // Siunčiam pranešimą per ESP-NOW
  esp_err_t result = esp_now_send(addrVardas, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    siuntSk++ ;
    sprintf (statusTxt, "Nusiusta: '%s' \r\nViso: %d", myData.txt, siuntSk) ; 
   }
  else {
    sprintf (statusTxt, "Siuntimo klaidai: %d", result) ; 
  }
  Print1(statusTxt);
  Print2(status2Txt);

  if (dataRecived) {
     sprintf (statusTxt, "Gauta: %d \r\n nuo: '%s' \r\n%s", gautSk, receivedData.vardas, receivedData.txt) ; 
     Print3(statusTxt);
     dataRecived = false ;
  }
  
  delay(3000);
}
