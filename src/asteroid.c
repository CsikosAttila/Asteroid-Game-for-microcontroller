#include "em_device.h"
#include "em_chip.h"
#include "em_adc.h"
#include "em_timer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "asteroid.h"
#include "adc.h"
#include "constant.h"

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[];

extern uint16_t segments[];
extern uint16_t asteroidDigits[];
extern uint16_t asteroidSegments[];

///Aszteroidak generalasa
/// Az ADC segitsegevel keszitunk egy random szamot, majd azt a megfelelo ertekekkel maradekosan osztva megkapjuk a kivant indexet.
/// A digitek kivalasztasahoz 6-al osztunk maradekosan,igy a lehetseges eredmenye 0 es 5 kozott. Nekunk az 1-6. digiteket kell hasznalnunk, igy 1-el eltoljuk jobbra az eredmenyt.
/// Az aszteroidaknal az elso 5 digiten 5 lehetseges szegmenst valaszthatunk ki, az utolson pedig 7-et. (az abrabol vettuk ezt)
/// Egy digiten csak egy szegmens lehet aszteroida, igy figyeljuk, hogy ne egyezzen az uj random digit egy korabbival.

void generateAsteroids(void)
{
  for(uint8_t i=0;i<3;i++){
      asteroidDigits[i]=(randomNumber()%6)+1;
      while(i==1 && asteroidDigits[i]==asteroidDigits[i-1]){
         asteroidDigits[i]=(randomNumber()%6)+1;
      }
      while(i==2 && (asteroidDigits[i]==asteroidDigits[i-1] || asteroidDigits[i]==asteroidDigits[i-2]) ){
               asteroidDigits[i]=(randomNumber()%6)+1;
            }
      if(asteroidDigits[i]<6) //ha az elso 5 digiten belul van akk 5 szegmens kozul kap erteket
          {
          asteroidSegments[i]=segments[randomNumber()%5];

          }
        else //ha az utolso digiten belul van akk 7 szegmens kozul kap erteket
          {
            asteroidSegments[i]=segments[randomNumber()%7];
          }
    }
}


///Aszteroidak megjelenitese

void displayAsteroids(void)
{

  for(uint8_t i=0;i<3;i++){
      lowerCharSegments[asteroidDigits[i]].raw|=asteroidSegments[i];
      }
  SegmentLCD_LowerSegments(lowerCharSegments);
}


