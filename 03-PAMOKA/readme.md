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
c = susumuok (a, b) ;

//funkcijos aprašymas
int susumuok (int p1, int p2) {
    return p1+p2 ;
}

```
