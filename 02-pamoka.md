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



**Projektas su 1 LED**:

![image](https://user-images.githubusercontent.com/67558835/181628430-5366b0d4-f7d7-4f1c-9800-049cf346d553.png)

