#include "em_device.h"
#include "em_chip.h"
#include "em_adc.h"
#include "em_timer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#include "asteroid.h"
#include "adc.h"
#include "constant.h"
#include "lcd.h"
#include "tmr.h"

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[];

extern uint16_t segment;
extern uint16_t digit;
extern uint16_t counter;
extern uint16_t asteroidDigits[];
extern uint16_t asteroidSegments[];

///Jatek inicializalasa
/// Kezdo szegmenst kozepre allitjuk, legenraljuk az aszteroidakat es megjelenitjuk oket, majd varakozunk egy keveset, hogy a jatekos megismerhesse a palyat.

void initialize(void){
  segment=MIDDLE;
  lowerCharSegments[0].raw = MIDDLE;
  SegmentLCD_LowerSegments(lowerCharSegments);
  generateAsteroids();
  displayAsteroids();
  SegmentLCD_Number(counter);
  delay();
}


///utkozes vizsgalata, ebben az esetben a jatek veget er.
/// Ha utkozes tortent, azt az egy szegmens mutatjuk csak, aminek neki utkoztunk
/// Elkezdjuk villogtatni a decimalis pontokat, a jatek vegtelen ciklusba fut, resettel indithato ujra.

void checkDefeat(void){
  for(uint8_t i=0;i<3;i++){
      if(digit==asteroidDigits[i] && segment==asteroidSegments[i]){
          clearLCD();
          lowerCharSegments[digit].raw=segment;
          SegmentLCD_LowerSegments(lowerCharSegments);
          while(1){
              SegmentLCD_Symbol(LCD_SYMBOL_DP2,1);
              SegmentLCD_Symbol(LCD_SYMBOL_DP3,1);
              SegmentLCD_Symbol(LCD_SYMBOL_DP4,1);
              SegmentLCD_Symbol(LCD_SYMBOL_DP5,1);
              SegmentLCD_Symbol(LCD_SYMBOL_DP6,1);
              delay();
              SegmentLCD_Symbol(LCD_SYMBOL_DP2,0);
              SegmentLCD_Symbol(LCD_SYMBOL_DP3,0);
              SegmentLCD_Symbol(LCD_SYMBOL_DP4,0);
              SegmentLCD_Symbol(LCD_SYMBOL_DP5,0);
              SegmentLCD_Symbol(LCD_SYMBOL_DP6,0);
              delay();

          }
      }
  }
}


///uj kor inditasa, ha a hajo vegigert a palyan
///A kor inditasanak idejere a TIMER0-t kikapcsoljuk.
/// A pontszamot noveljuk, az urhajot a megfelelo helyre allitjuk, uj aszteroidakat generalunk es megjelenitjuk oket.
/// Amint vegeztunk az inicializalassal, varunk kicsit, hogy a jatekosnak legyen ideje megismerni az akadalyokat.
/// Reseteljuk a TIMER0 aktualis erteket, majd csokkentjuk a felso korlatjat 5%-al, ez utan ujrainditjuk a Timert.

void newRound(uint16_t newSegment){
    TIMER0->CMD = 0;
    counter++;
    digit=0;
    segment=newSegment;
    lowerCharSegments[digit].raw=segment;
    SegmentLCD_LowerSegments(lowerCharSegments);
    generateAsteroids();
    displayAsteroids();
    SegmentLCD_Number(counter);
    delay();
    TIMER0->CNT=0;
    TIMER0->TOP=TIMER0->TOP*0.95;
    TIMER0->CMD = 1;
}

