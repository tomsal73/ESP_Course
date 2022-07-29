# ESP 32 Jungtys


![image](https://user-images.githubusercontent.com/67558835/178195104-90e04b1e-1ec0-42ae-ae38-547738328c7c.png)

**GPIO0**: Kai ši jungtis yra LOW pradinio užkrovimo metu - pereinama prie užkrovimo į nuolatinę atmintį (flash), Bet galima naudoti kaip išvesties (output) jungtį,

**GPIO34-GPIO39 (INPUT)**: gali būti naudojamos kaip bendro pobūdžio įvesties jungtys. Negali būti naudojamos kaip išvesties (output).

**GPIO32-GPIO39 (ADC)**: Šios jungtys gali būti naudojamos kaip ADC - Analoginis konverteris į skaitmeninį. Gali matuoti įtampą jungtyse.

**GPIO0, GPIO2, GPIO4, GPIO12-GPIO15, GPIO27, GPIO32, GPIO33 (TOUCH)**: Šios jungtys tinkamos naudoti lietimui jautrų sensorių.

**GPIO2 (LED)**: Ši jungtis prijungta prie mėlyno LED. Padavus įtampą - užsidega LED.

**GND**: Per šias jungtis galima prijungti negiamą (-) įtampos šaltinį (žemę).

**5V** įtampa prijungta prie USB maitinimo laido. Mikrokompiuterį galima maitinti per šią jungtį, bet tik paduodant 5V įtampą!

**3.3V** mikrokompiuterio veikimui užtenka 3.3 V įtampos. Tokią įtampą galima paduoti per šią jungtį, bet jokiu būdu ne 5V - mikroschema perdegs!



### NUORODOS

>Arduino IDE
>https://www.arduino.cc/en/software
>
>ESP32 plokštės bibliotekos
>http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json
>
>CP2102 USB Valdiklis
>https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
>
>Daugiau apie ESP32
>https://randomnerdtutorials.com/projects-esp32/

---


### Projektas: Mirksintis LED

#### Maketinės plokštės diagrama

![image](https://user-images.githubusercontent.com/67558835/181736844-509025f3-b3bc-4153-aab8-4e9b9dff9855.png)


#### Programa

```C
// Made by Tomas Šalkauskas in 2022
// using examples from https://randomnerdtutorials.com/



// the number of the LED pin
#define ledPin 14  // 14 corresponds to GPIO14

 
void setup(){
   pinMode(ledPin, OUTPUT);
}
 
void loop(){
  // turn LED ON 
  digitalWrite (ledPin, HIGH);
  // delay for 0,5 sec
  delay(500);
  // turn LED off
  digitalWrite (ledPin, LOW);
  // delay for 0,5 sec
  delay(500);
}
```
