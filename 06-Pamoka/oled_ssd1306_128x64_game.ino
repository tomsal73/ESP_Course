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

#define ILG 14 //lentelės ilgis
int kx = 1 ; // kairės lentelės X koordinatė
int ky = SCREEN_HEIGHT/2-ILG/2 ; //// kairės lentelės X koordinatė
int kk = 0 ; // kairės lentelės kryptis: 1 - žemyn, 0 - vietoj, -1 aukštyn

int dx = SCREEN_WIDTH-1 ; // dešinės lentelės Y koordinatė
int dy = SCREEN_HEIGHT/2-ILG/2 ; //// dešinės lentelės Y koordinatė
int dk = 0 ; // dešinės lentelės kryptis: 1 - žemyn, 0 - vietoj, -1 aukštyn

#define ZINGSNIS 2 // kiek tasku pasislenka per viena karta
int r = 5 ; // apksritimo spindulys
double cx = SCREEN_WIDTH/2 ;
double cy = SCREEN_HEIGHT/2 ;
int kamp;
double rad ;
int km1, km2, dm1, dm2 ;

int krez = 0 ;
int drez = 0 ;

void startBall () {
  display.fillCircle(int(cx), int(cy), r, BLACK);
  cx = SCREEN_WIDTH/2 ;
  cy = SCREEN_HEIGHT/2 ;
  do
      kamp = random(360) ;
  while (!((kamp > 0 and kamp <= 45) or (kamp >= 135 and kamp <= 225 and kamp!=180) or (kamp >= 315 and kamp != 360))) ;
  Serial.println(kamp) ;
  display.fillCircle(int(cx), int(cy), r, WHITE);
  display.fillRect (SCREEN_WIDTH/2-10,0,20,10,BLACK) ;
  display.setCursor (SCREEN_WIDTH/2-10,0) ;
  display.println (krez) ;
  display.setCursor (SCREEN_WIDTH/2+3,0) ;
  display.print (drez) ;
  display.display();
  delay(1000); // Pause for 1 seconds  
  display.fillCircle(int(cx), int(cy), r, BLACK);
}

void drawLeft () {
     display.drawLine (kx, ky, kx, ky+ILG, BLACK) ;
     ky += kk ;
     if (ky < 0) ky = 0;
     else if (ky>SCREEN_HEIGHT) ky = SCREEN_HEIGHT ;     
     display.drawLine (kx, ky, kx, ky+ILG, WHITE) ;
}

void drawRight () {
     display.drawLine (dx, dy, dx, dy+ILG, BLACK) ;
     dy += dk ;
     if (dy < 0) dy = 0;
     else if (dy>SCREEN_HEIGHT) dy = SCREEN_HEIGHT ;
     display.drawLine (dx, dy, dx, dy+ILG, WHITE) ;
}

void checkVBorder () {
   if ((int(cy) >= SCREEN_HEIGHT-r-1) or (int(cy) <= r+1)) {
      // atsitrenkė į viršutinį arba apatinį kraštą
      kamp = 360 - kamp ;
   }
}

int checkLPanel () {
   if (int(cx) <= r+2) {
      if ((int(cy) >= ky-r) and (int(cy)<= ky+ILG+r)) {
         // atsitrenkė į kairę lentelę
         kamp = 180 - kamp ;
         return (1) ;
     } else {
        krez++ ;
        startBall () ;
        return (1) ;
     }
   } else {
      return (0) ;
   }
}

int checkRPanel () {
     if (int(cx) >= SCREEN_WIDTH-r-2) {
        if ((int(cy) >= dy-r) and (int(cy)<= dy+ILG+r)) {
            // atsitrenkė į kairę lentelę
            kamp = 180 - kamp ;
            return (1) ;
        } else {
          drez++ ;
          startBall () ;
          return (1) ;
        }  
     } else {
        return (0) ;
     }
}
void drawBall () {
    // valom skritulį
    display.fillCircle(int(cx), int(cy), r, BLACK);

   checkVBorder () ;
   if ( !checkLPanel () ) 
      checkRPanel ();

   //skaičiuojam naujas koordinates
   rad = M_PI/double(180)*double(kamp) ;
   cx += ZINGSNIS*cos(rad) ; 
   cy += ZINGSNIS*sin(rad) ;

   // piešiam skritulį
   display.fillCircle(int(cx), int(cy), r, WHITE);
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  //kamp = random(360) ;
  
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
  display.setTextSize (1) ;
  display.setTextColor(WHITE);
  display.display();
  startBall () ;
}


void loop() {
    // valom skritulį
    display.fillCircle(int(cx), int(cy), r, BLACK);

   // tikrinam ar mygtukai paspausti
   km1 = digitalRead (KM1) ;
   km2 = digitalRead (KM2) ;
   dm1 = digitalRead (DM1) ;
   dm2 = digitalRead (DM2) ;
//   if (km1 == LOW) 
//      display.fillCircle(15, 10, 5, WHITE) ;
//   else 
//     display.fillCircle(15, 10, 5, BLACK) ;
//     
//   if (km2 == LOW) 
//      display.fillCircle(15, SCREEN_HEIGHT-10, 5, WHITE) ;
//   else 
//     display.fillCircle(15, SCREEN_HEIGHT-10, 5, BLACK) ;
//
//   if (dm1 == LOW) 
//      display.fillCircle(SCREEN_WIDTH-15, 10, 5, WHITE) ;
//   else 
//     display.fillCircle(SCREEN_WIDTH-15, 10, 5, BLACK) ;
//   
//   if (dm2 == LOW) 
//      display.fillCircle(SCREEN_WIDTH-15, SCREEN_HEIGHT-10, 5, WHITE) ;
//   else 
//     display.fillCircle(SCREEN_WIDTH-15, SCREEN_HEIGHT-10, 5, BLACK) ;
   if (km1 == LOW) kk = -1; 
   else if (km2 == LOW) kk = 1;
   else kk = 0 ;

   if (dm1 == LOW) dk = -1; 
   else if (dm2 == LOW) dk = 1;
   else dk = 0 ;

   drawLeft () ;
   drawRight () ;
   drawBall () ;
   display.display();
}
