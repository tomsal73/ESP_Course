# Funkcijos. Kintamieji. Projektas - Įvedimas per Serial. Kitos Valdymo struktūros.

### Funkcijos ir Procedūros

Privalomos procedūros ESP32 valdymui
```C
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

![image](https://user-images.githubusercontent.com/67558835/181800957-6e2d0bf3-e353-427d-88d4-cec2ccdb61f3.png)

Programuojant pasikartojančius veiksmus naudojamos Procedūros ir Funkcijos

![image](https://user-images.githubusercontent.com/67558835/181801669-32dba330-589d-4041-aa61-81e9d612228e.png)

Norint išsaugoti reikšmę ir ją vėliau panaudoti naudojami kintamieji

```C
// kintamojo sukūrimas. C kalboje svarbu didžiosios ir mažosios raidės
int a;
int b;
int c;

// kintamojo inicializavimas. NEPAMIRŠTI!
a = 10;
b = 3;

//kintamųjų reikšmių perdavimas funkcijai
c = suma (a, b) ;

//funkcijos aprašymas
int suma (int p1, int p2) {
    return p1+p2 ;
}

```
## Užduotis
Parašykite programą, kuri per Serial portą gautų 2 sveikus skaičius, juos susumuotų iškviečiant funkciją _suma_ ir per Serial atspausdintų gautą rezultatą.
Programai reikės:
 - inicializuoti Serial portą naudojant komandas   Serial.begin(9600); ir Serial.setTimeout(10000);
 - aprašyti kintamuosius reikšmės ir rezultatui saugoti
 - gauti įvesties duomenis naudojant komandas kintamasis = Serial.readStringUntil('\n').toInt() ;
 - iškviesti funkciją suma naudojant komandą rezultatas = suma (demuo1, demuo2) ;
 - atspausdinti rezultatą naudojant komandas Serial.print ("Suma: ") ; Serial.println (rezultatas) ; 

### Kitos valdymo struktūros

#### Ciklai - for, while, do...while

![image](https://user-images.githubusercontent.com/67558835/183753210-35127bf2-3961-4f98-b37a-3b6cc84324db.png)

Pvz:
```C
  for (int i = 0; i <= 255; i++) {
    analogWrite(PWMpin, i);
    delay(10);
  }
```

![image](https://user-images.githubusercontent.com/67558835/183755391-1eb0c69a-6688-4d2f-9682-b0b9be63ee89.png)

Pvz:
```C
var = 200;
while (var > 0) {
  // kartojami veiksmai, kol kintamasis var bus didesnis už 0
  // priklausomai nuo pradinės kintamojo reikšmės, ciklas gali būti nevykdomas nei vieno karto
  var--;
}
```

![image](https://user-images.githubusercontent.com/67558835/183755472-6ba92a7f-581d-4fcb-bffe-53b04b634afe.png)

Pvz:
```C
var = 200;
 {
  // kartojami veiksmai, kol kintamasis var bus didesnis už 0
  // kokia bebūtų kitamojo reikšmė, ciklas bus įvykdytas bent vieną kartą.
  var--;
} while (var > 0) ;
```

#### Sąlygos - if, else, else if

![image](https://user-images.githubusercontent.com/67558835/183757533-b969239f-e387-43d6-80a4-41ab9a0a39bd.png)

Pvz:
```C
if (temperature >= 70) {
  // Danger! Shut down the system.
}
else if (temperature >= 60) { // 60 <= temperature < 70
  // Warning! User attention required.
}
else { // temperature < 60
  // Safe! Continue usual tasks.
}
```

#### Atvejai - switch...case


```C
  switch (range) {
    case 0:    // your hand is on the sensor
      Serial.println("dark");
      break;
    case 1:    // your hand is close to the sensor
      Serial.println("dim");
      break;
    case 2:    // your hand is a few inches from the sensor
      Serial.println("medium");
      break;
    case 3:    // your hand is nowhere near the sensor
      Serial.println("bright");
      break;
  }
```


Daugiau informacijos: https://www.arduino.cc/reference/en/
