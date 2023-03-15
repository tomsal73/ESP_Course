# Wifi komunikacija

## Užduotis

Užsiregistruoti viešoje Orų duomenų basėje - OpenWeather. Prisijungti prie Wifi tinklo, gauti informaciją apie oro sąlygas Vilniuje (arba kitame mieste) ir atvaizduoti gautus duomenis ekranėlyje.

## Ko tam reikės

 - Registracija OpenWeather tinkalpyje: *https://home.openweathermap.org/users/sign_in*
 - Sesijos rakto generavimas: *https://home.openweathermap.org/api_keys*
 - Papildomų Arduino bibliotekų diegimas: 
     - Arduino_JSON - JSON failų apdorojimui
     - U8g2_for_Adafruit_GFX - lietuviškų raidžių rašymui ekranėlyje
 - Užklausos OpenWeather API sugeneravimas
     - Užklausos formatas: http://api.openweathermap.org/data/2.5/weather?q=<miestas\>,\<šalis\>&APPID=\<raktas\>&lang=\<kalba\>&units=\<vienetai\>, kur 
         - \<miestas\> - tekstas, pvz. Vilnius arba Klaipėda
         - \<šalis\> - šalies kodas: LT
         - \<raktas\> - jūsų asmeninis API sesijos raktas
         - \<kalba\> - lt arba en
         - \<vienetai\> - metric, jeigu norim matyti temperatūrą Celsijaus laispniais
     - paruoštos užklausos pavyzdys: http://api.openweathermap.org/data/2.5/weather?q=Vilnius,LT&APPID=9ea5a3cd53f1dbc196176454eeb56679&lang=lt&units=metric
     - daugiau informacijos apie užklausų formatus: https://openweathermap.org/api
  - Pavyzdys, kaip atrodo atsakymas iš OpenWeather JSON formatu
  ``` JSON
  {
  "coord": {
    "lon": 25.2798,
    "lat": 54.6892
  },
  "weather": [
    {
      "id": 802,
      "main": "Clouds",
      "description": "mažai debesuota",
      "icon": "03n"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 7.49,
    "feels_like": 4.39,
    "temp_min": 7.49,
    "temp_max": 7.62,
    "pressure": 995,
    "humidity": 87
  },
  "visibility": 10000,
  "wind": {
    "speed": 5.14,
    "deg": 180
  },
  "clouds": {
    "all": 40
  },
  "dt": 1678829102,
  "sys": {
    "type": 1,
    "id": 1883,
    "country": "LT",
    "sunrise": 1678768661,
    "sunset": 1678810734
  },
  "timezone": 7200,
  "id": 593116,
  "name": "Vilnius",
  "cod": 200
}
  ```

## Programos veikimo principas

 - setup dalis
     - Inicializuojam Ekraną, Wifi ir laikmatį
     - Jungiamės prie Wifi
 - loop dalis
     - Tikrinam ar jau laikas siųsti užklausą į OpenWeather ``` (if ((millis() - lastTime) > timerDelay)) { ```
     - Siunčiam užklausą ``` jsonBuffer = httpGETRequest(serverPath.c_str()); ```
     - Apdorojam gautą JSON failą ```  JSONVar myObject = JSON.parse(jsonBuffer); ```
     - Įrašom duomenis iš gauto atsakymo į kintamuosius
       ```C       strcpy (tmp, myObject["name"]) ;
                  strcpy (tmp, myObject["weather"][0]["description"]) ;
                  temp1 = myObject["main"]["temp"];
                  temp2 = myObject["main"]["feels_like"]; 
       ```
     - Atvaizduojam duomenis ekranėlyje
       ```C
                  wStatusL2 = String(tmp) ;
                  Print2(wStatusL2); 
                  
                  wStatusL3 = oras + "\r\nTemp: "+ temp1+ "; Jausmas: "+temp2 ;
                  Print3(wStatusL3) ;
       ```
