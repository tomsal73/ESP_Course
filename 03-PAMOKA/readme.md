# Funkcijos. Kintamieji. Projektas - Įvedimas per Serial. 

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
### Užduotis
>
> Parašykite programą, kuri per Serial portą gautų 2 sveikus skaičius, juos susumuotų iškviečiant funkciją _suma_ ir per Serial atspausdintų gautą rezultatą.
> Programai reikės:
>  - inicializuoti Serial portą naudojant komandas   Serial.begin(9600); ir Serial.setTimeout(10000);
>  - aprašyti kintamuosius reikšmės ir rezultatui saugoti
>  - gauti įvesties duomenis naudojant komandas kintamasis = Serial.readStringUntil('\n').toInt() ;
>  - iškviesti funkciją suma naudojant komandą rezultatas = suma (demuo1, demuo2) ;
>  - atspausdinti rezultatą naudojant komandas Serial.print ("Suma: ") ; Serial.println (rezultatas) ; 
>  
> PAVYZDYS
> 
> ![image](https://user-images.githubusercontent.com/67558835/191327811-53d00eb8-9302-4803-b9c4-77ae4cf9932c.png)
>
 
