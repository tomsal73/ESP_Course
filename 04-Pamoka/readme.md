# Ciklai ir kitos valdymo struktūros. 

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


##Užduotis 4 Mirksintys LED

Tikslas: Parašyti programą, kuri uždegtų po vieną visus 4 LED kas 0,25 sek. Visi 4 dega 0,5 sek. Po to vėl po vieną visi užgęsta ir 1 sek nedega. 
Paskui viskas vėl kartojasi. Programą parašyti 3 variantais naudojant tokias ciklo komandas:
 - for
 - while
 - do ... while

Patarimai
 - LED įvadų inicializavimui naudoti komandą pinMode(ledPin, OUTPUT);
 - LED uždegimui naudoti komandą digitalWrite (ledPin, HIGH), užgesinimui digitalWrite (ledPin, LOW);
 - uždelsimui naudoti komandą delay(x), kur x - uždelsimo laikas milisekundėmis. 1000 = 1 sek.

Schemos pavyzdys:

![image](https://user-images.githubusercontent.com/67558835/191341982-967b1239-ce75-437f-86cd-15f8e61c199d.png)




