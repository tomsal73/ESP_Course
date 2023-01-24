# Jutiklių naudojimas. Projektas - temperatūros ir drėgmės matavimas.

Naudojamas sensorius: **DHT11**

## Jungimo schema
![image](https://user-images.githubusercontent.com/67558835/214383782-d17b17c1-1f61-4f98-bc7c-3e1e8bc99f9b.png)


## Papildomos bibliotekos

Naudojama biblioteka: DHT Sensor library for ESPx

## Programai reikalinga informacija

### Definitions dalis

```C
#include <DHTesp.h>

#define DHTPIN 25     // Sensoriaus jungtis
#define EIL1 1  // Pirmos eilutės Y koordinatė
#define EIL2 21 // Antros eilutės Y koordinatė
#define EIL3 41 // Trečios eilutės Y koordinatė

DHTesp dht;
/** Comfort profile */
ComfortState cf;

```

### Setup dalis

```C
dht.setup(DHTPIN, DHTesp::DHT11);
```

### Loop dalis
```C
float h = dht.getHumidity();
float t = dht.getTemperature();

	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return ;
	}
  
float cr = dht.getComfortRatio(cf, t, h);

  String comfortStatus;
  switch(cf) {
    case Comfort_OK:
      comfortStatus = "Liuks";
      break;
    case Comfort_TooHot:
      comfortStatus = "Karsta";
      break;
    case Comfort_TooCold:
      comfortStatus = "Salta";
      break;
    case Comfort_TooDry:
      comfortStatus = "Sausa";
      break;
    case Comfort_TooHumid:
      comfortStatus = "Dregna";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "Karsta Dregna";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "Karsta Sausa";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = "Salta Dregna";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = "Salta Sausa";
      break;
    default:
      comfortStatus = "Neaisku:";
      break;
  };

  display.clearDisplay();
  
  display.setCursor (1,EIL1) ;
  display.print (h) ;
  display.print (" %") ;
  
  display.setCursor (1,EIL2) ;
  display.print (t) ;
  // print degree symbols ( ° )
  display.drawCircle(70, EIL2, 2, WHITE);
  display.setCursor(74,EIL2);
  display.print("C");
  
  display.setCursor(1,EIL3);
  display.print(comfortStatus);

  display.display(); 
  
  delay(1000);
```
