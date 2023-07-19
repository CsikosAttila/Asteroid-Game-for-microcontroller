#include "em_device.h"
#include "em_chip.h"
#include "em_adc.h"
#include "em_timer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#include "asteroid.h"
#include "adc.h"
#include "constant.h"
#include "moving.h"
#include "gameMechanics.h"
#include "lcd.h"

#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_assert.h"
#include "em_acmp.h"
#include "em_core.h"
#include "em_assert.h"
#include "em_lesense.h"
#include "em_rtc.h"
#include "em_vcmp.h"

#include "bsp_trace.h"
#include "caplesense.h"
#include "vddcheck.h"

extern uint16_t counter;
extern int32_t sliderPos;

///Egyszeru varakozas

void delay() {
   for(uint32_t d=0;d<=500000;d++){}
}

///TIMER0 megszakitas fuggvenye, amennyiben a szamlalo erteke eleri a megadott erteket, megvizsgaljuk a gombok aktualis allapotat.  /////// IDE KELL A TOUCH SLIDER VIZSGALAT!!!!
/// A gomboktol fuggoen kanyarodhatunk balra vagy jobbra, vagy ha nincs megnynomva gomb, tovabbhaladunk egyenesen.
/// A haladas vegen a TIMER0 interruptjat ujra engedelyezzuk.
///
void TIMER0_IRQHandler(void) {

	//CAPLESENSE_Sleep();  // ennek lemernie a jo slider erteket

	//EZ KELLENE H JO LEGYEN DE vmi baja van az em_emu.c nek
	// ha a CAPLESENSE_Sleep() re ra F3 zol
	// es azon belul EMU_EnterEM2(true); erre is ra F3 zol
	// ha legorgetsz vmi hibaja van a _WFI() nek ami nem tom mi es nem ertem miert rossz ha az beepitett cucc


	sliderPos=CAPLESENSE_getSliderPosition(); //ennek meg megadnia kene az ertket 0- 48 kozott
 //a hiba itt van mivel vmit elszamol a CAPLESENSE_getSliderPosition() fugveny
	//legalabb is ugy tunik
	// full random elfordul akkor is ha hozza sem ertunk

	if(0 <= sliderPos && 20 >= sliderPos)
	{
		moving(left);
	}
	else if(28 <= sliderPos && 48 >= sliderPos)
	{
		moving(right);
	}
	else
	{
		moving(forward);
	}

                            //Clear overflow flag
 /* if(!(GPIO->P[BUTTON_PORT].DIN & (1 << PB0)))
            {
              moving(left);
          }
          else if(!(GPIO->P[BUTTON_PORT].DIN & (1 << PB1))){
              moving(right);
          }
          else{
          moving(forward);
          }*/

  SegmentLCD_Number(counter);
  TIMER0->IFC = 1; // torli a flag bitet
  //sliderPos = -1;
}
