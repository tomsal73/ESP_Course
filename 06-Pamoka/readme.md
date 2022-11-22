# OLED ekrano naudojimas

## Jungimo schema

![image](https://user-images.githubusercontent.com/67558835/201977398-d2e9e3e4-4a8e-4862-809d-188b784b79ae.png)


## Papildomos bibliotekos

Per "Library Manager" reikia instaliuoti 2 papildomas bibliotekas.


![image](https://user-images.githubusercontent.com/67558835/201976850-61dce12d-4ff4-4190-afca-ff4436d2a8d6.png)

 *[Adafruit_SSD1306](https://github.com/adafruit/Adafruit-GFX-Library)* :
 
![image](https://user-images.githubusercontent.com/67558835/201976416-d541b1cb-36a4-4659-a265-a0ed8c98c493.png)

*[Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)* :

![image](https://user-images.githubusercontent.com/67558835/201976685-683f0882-fc26-416a-8841-25ca389baad2.png)

## Reikalingi nustatymai

Įtraukiame bibliotekų naudojimą:

```C
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

Nustatome OLED reikalingus parametrus:

```C
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)
// On ESP32 Node MCU:   21(SDA),  22(SCL), ...
// On ESP8266 Node MCU:   4(SDA),  5(SCL), ...

#define SCREEN_WIDTH 128 // Pikselių skaičius į plotį (iš kairės į dešinę)
#define SCREEN_HEIGHT 64 // Pikselių skaičių į aukštį (iš viršaus žemyn)

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< get adddress using I2C scanner
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
```

Setup () dalyje inicializuojame ekraną:

```C
void setup() {
  ...

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 seconds
  
  ...
  
 }
```

Naudosime tokias ekranos valdymo funkcijas:

```C
  // Išvalo visą ekraną
  display.clearDisplay();
  
  // Atvaizduoja ekrano buferio turinį
  // šią komandą PRIVALOMA iškviesti kiekvieną kartą kai ekrane kažkas pakeičiama
  display.display();
  
  // PAPRASTAS TEKSTAS
  // Nustato teksto dydį. 1 - mažas, 2 - didelis
  display.setTextSize(1);      
  
  // Nustato teksto spalvą: WHITE - baltas, BLACK - juodas. tokiu atveju fonas turi būti baltas
  display.setTextColor(WHITE); 
  
  // Nustato vietą nuo kur bus pradėtas rašyti tekstas (x, y). 0,0 - kairysis viršutinis kampas
  display.setCursor(0, 0);     
  
  // nuo nustatytos vietos, naudojant nustatytą spalvą užrašo tekstą
  display.println("Hello, world!"); // tekstas tarp kabučių
  display.println(kintamasis); // kintamojo turinys
  
  // SLENKANTIS TEKSTAS
  // pradeda slinkti iš kairės į dešinę
  startscrollright(0x00, 0x0F) ;
  
  // pradeda slinkti iš dešinės į kairę
  startscrollleft(0x00, 0x0F); 
  
  // sustabdo teksto slinkimą
  display.stopscroll();
  
  // apkeičia ekrano spalvas: jei nurodyta 'true' - juoda tampa balta, o balta - juoda, jei nurodyta 'false' - atstatomos ankstesnės spalvos
  display.invertDisplay(true);
  
  // GRAFIKA
  // Uždega vieną pikselį: 10-as nuo kairės, ir 10-as nuo viršaus
  display.drawPixel(10, 10, WHITE);
  
  // brėžia liniją pagal nurodytas koordinates ir spalvą:   drawLine(x1, y1, x2, y2, color)
  display.drawLine(0, 0, 127, 20, WHITE);
  
  // brėžia keturkampį pagal nurodytą kampo koordinatę ir dydį: drawRect(x, y, width, height, color)
  display.drawRect(10, 10, 50, 30, WHITE);
  
  // brėžia užpildytą keturkampį pagal nurodytą kampo koordinatę ir dydį: fillRect(x, y, width, height, color)
  display.fillRect(10, 10, 50, 30, WHITE);
  
  // brėžia užapvalintą keturkampį pagal nurodytą kampo koordinatę ir dydį. angle - užapvalinimo dydis: drawRoundRect(x, y, width, height, angle, color)
  display.drawRoundRect(10, 10, 30, 50, 2, WHITE);
  
  // brėžia užpildytą užapvalintą keturkampį pagal nurodytą kampo koordinatę ir dydį. angle - užapvalinimo dydis: fillRoundRect(x, y, width, height, angle, color)
  display.fillRoundRect(10, 10, 30, 50, 2, WHITE);
  
  //brėžia apksritimą su nurodytomis centro koordinatėmis ir nurodyto dydžio: drawCircle(x, y, radius, color)
  display.drawCircle(64, 32, 10, WHITE);
  
  //brėžia skritulį su nurodytomis centro koordinatėmis ir nurodyto dydžio: fillCircle(x, y, radius, color)
  display.fillCircle(64, 32, 10, WHITE);
  
  //brežia trikampį per nurodytas koordinates: drawTriangle(x1, y1, x2, y2, x3, y3, color)
  display.drawTriangle(10, 10, 55, 20, 5, 40, WHITE);
  
  //brežia užpildytą trikampį per nurodytas koordinates: fillTriangle(x1, y1, x2, y2, x3, y3, color)
  display.fillTriangle(10, 10, 55, 20, 5, 40, WHITE);
```

Naudokite kaip pavyzdį *[oled_ssd1306_128x64_test.ino](oled_ssd1306_128x64_test.ino)*, kurioje galėsite pridėti daugiau ekrano valdymo funkcijų.

Sudėtingesnis pavyzdys - spirografas https://nathanfriend.io/inspiral-web/. 
ESP32 programa: *[oled_ssd1306_128x64_spirograph.ino](oled_ssd1306_128x64_spirograph.ino)* 
