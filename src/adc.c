#include "em_device.h"
#include "em_chip.h"
#include "em_adc.h"





///Randomszamgeneralas, az ADC bemenetere mintavetelezunk egy pillatnyi erteket, majd ezt visszaadjuk

uint16_t randomNumber(void)
{
  uint16_t adc_result=0; //belso valtozo ami a random szam lesz
  ADC0->CMD = 0x1;                      //Elinditjuk a mintavetelezest
    while(!(ADC0->STATUS & (1 << 16))); //Megvarjuk, hogy stabilizalodjon az eredmeny
    adc_result = ADC0->SINGLEDATA;      //Kiolvassuk az eredmenyt
    return adc_result;
  }

