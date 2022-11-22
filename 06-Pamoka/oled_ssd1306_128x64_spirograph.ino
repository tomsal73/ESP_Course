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

void spirograph(int *x, int *y, int l, int r1, int r2, int zingsnis) 
{
    const int N = 720 ;
    int ratas = (zingsnis/N)+1 ;
    int z = zingsnis - (ratas-1)*N + 1;
    double dt = ratas * 2.f * M_PI / N ;
    double t = dt*z, R = 20.f;
    double k = float(r1) / float(r2) ;
    const double k1 = 1.f - k;

    *x =  R * (k1 * cos(t) + l * k * cos(k1 * t / k));
    *y =  R * (k1 * sin(t) - l * k * sin(k1 * t / k));
}

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

  display.clearDisplay();
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(25, 25);
  display.println("Veikia!");
  display.drawRoundRect(20, 21, 90, 22, 2, WHITE);
  display.display();
  delay (2000) ;
  //display.startscrollleft(0x00, 0x0F) ;
  //delay (8000) ;
  //display.stopscroll();
  display.clearDisplay();
  
}

int z = 0;
int x; 
int y;
void loop() {
  // Parametrai:
  //  - skylutes atstumas nuo krašto
  //  - vidinio apskritimo skersmuo
  //  - išorinio apskritimo skersmuo
  //  - žingsnio numeris
  spirograph(&x, &y, 5, 3, 33, z) ;
  Serial.printf("z=%d; x=%d; y=%d;", z, x, y) ;
  Serial.println ("") ;
    display.drawPixel(SCREEN_WIDTH/2+x, SCREEN_HEIGHT/2+y, WHITE);
    display.display();
  //delay (5) ;
  z++ ;
}
