# Įvykių apdorojimas

### Pertraukimai
Norint "pagauti" įvykius, reikia naudoti pertraukimus - Interrupt. Pertraukimas leidžia nutraukti įprastą programos seką bet kurioje vietoje, ir "peršokti" prie nurodytos funkcijos vykdymo. 
Įvykdžius funkciją, programos vykdymas grįžta prie įprastos sekos.

```C

attachInterrupt(digitalPinToInterrupt(GPIO), function, mode);

```
Pertraukimo sukūrimui reikalingi šie parametrai:
 - **digitalPinToInterrupt(GPIO)**. Nurodomas jūgties numeris, pvz. digitalPinToInterrupt(27)
 - **function**. Funkcijos, kuri bus pradėta vykdyti įvykus pertraukimui, pavadinimas. Funkcija turi būti aprašyta iš anksto.
 - **mode**. Nurodo pertraukimo sąlygą:
    - LOW: iššaukiamas pertraukimas kai jungties įtampa yra LOW būsenoje;
    - HIGH: iššaukiamas pertraukimas kai jungties įtampa yra HIGH būsenoje;
    - CHANGE: iššaukiamas pertraukimas kai jungties įtampa pasikeičia iš HIGH į LOW arba atvirkščiai - iš LOW į HIGH;
    - FALLING: iššaukiamas pertraukimas kai jungties įtampa pasikeičia iš HIGH į LOW;
    - RISING: iššaukiamas pertraukimas kai jungties įtampa pasikeičia iš LOW į HIGH;
 
 
 ### Laikmatis
 
 Laiko skaičiavimui milisekundėmis naudojama funkcija millis (), ji grąžina laiką nuo mikrokompiuterio starto milisekundėmis. Paprastai ši funkcija naudojama suskaičiuoti, 
 kiek laiko praėjo tarp įvykių.
 
Pavyzdžio jungimo schema galima rasti čia: *[Mirksintis LED](02-PAMOKA/readme.md)*
```C

/*********
  Šis pavyzdys rodo, kaip galima sukurti mirksintį LED nenaudojant delay() funkcijos ir tokiu būdu nestabdant programos. 
*********/

// Konstanta - kintamasis, kurio reikšmė nesikeičia
const int ledPin =  14;      // LED pajungtas prie 14 jungties

const long interval = 1000;           // LED mirksėjimo dažnumas (milisekundėmis)

// Kintamųjų reikšmės gali keistis  :
int ledState = LOW;             // ledState kitamasi saugos LED būseną. Pradžioje išjungta

// Kintamasis, kuris saugo laiką milisekundėmis turi būti "unsigned long" tipo
// Nes int nepakanka didelėms reikšmėms saugoti
unsigned long previousMillis = 0;        // saugos laiką, kada LED būsena pasikeitė paskutinį kartą


void setup() { 
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // čia galima rašyti komandas kurios bus vykdomos įprasta tvarka

  // kintamasis currentMillis bus naudojamas laiko paskaičiavimui nuo paskutinio LED būsenos pakeitimo
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // išsaugome laiką, kada LED būsena pasikeitė
    previousMillis = currentMillis;

    // jei LED išjugtas - įjungiame, jei įjungtas - išjungiame:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // nustatome įtampą LED jungtyje pagal kitantamojo ledState reikšmę:
    digitalWrite(ledPin, ledState);
  }
}

```

 ### Užduotis
 
 Parašyti programą, naudojant funkcijas millis ir attachInterrupt kuri valdytų LED pagal mygtuko paspaudimus:
  - Jei mygtukas paspaudžiamas - LED įjungiamas
  - Jei mygtukas dar kartą paspaudžiamas - LED išjungiamas
  - Jei mygtukas paspaudžiamas ir palaikomas ilgiau nei 1 sek. - LED pradeda mirksėti
 
 
 Patarimai:
  - Mygtuko paspaudimui bei atleidimui galima panaudoti tokį pertraukimą: attachInterrupt(digitalPinToInterrupt(buttonPin), paspaudimas, CHANGE);
  - Funkcija paspaudimas turi nustatyti, ar mygtukas paspaustas, ar atleistas. Jei mygtukas atleistas, prieš kiek laiko jis buvo paspaustas, funkcijos rezultatas - LED būsena: 1 - Įjungtas, 2 - Išjungtas, 3 - Mirksintis
  - Programos loop cikle, nustatoma įtampa LED jungtyje, pagal LED būsena



