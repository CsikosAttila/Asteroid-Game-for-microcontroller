#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"

#include "bsp_trace.h"
#include "caplesense.h"
#include "vddcheck.h"

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


uint16_t segments[7]={MIDDLE,UP,BOTTOM,LEFT_UP,LEFT_DOWN,RIGHT_UP,RIGHT_DOWN};  //Tomb a lehetseges szegmensek tarolasara
volatile uint16_t segment=MIDDLE;                                               //eppen megjelenitett szegmens ertek(urhajo)
volatile uint16_t digit=0;                                                      //aktualis megjenitendo digit erteke (ahol a szegmenst meg kell jeleniteni)
volatile uint8_t  updowndirection=0;                                            //Fuggoleges iranyt jelzo ertek 0=felfele, 1=lefele
volatile uint16_t counter=0;                                                    //Sikeresen teljesitett korok szama
volatile uint16_t asteroidDigits[3]={0,0,0};                                    //Aszteroidak digitei
volatile uint16_t asteroidSegments[3]={0,0,0};                                  //aszteroidak deigiteinek szegmensei
volatile int32_t sliderPos=-1;  													//slider poziciot alabol -1 re rakjuk h ne menjen semerre


SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS];
SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  //Engedelyezzuk az orajelet a GPIO-nak (13. bit), az ADC-nek (16. bit)es a TIMER0-nak (5. bit)
  CMU->HFPERCLKEN0 = (1 << 16) | (1 << 13) | (1 << 5);

  ///Konfiguraljuk az ADC0-t
  ///1. A felmelegedesi idot 24 orajelciklusra allitjuk (16. bitte kezdve), a prescalert pedig 1-re allitjuk (8. bit)
  ///2. Konfigurajuk az egyszeri mintavetelezest, a referencia feszultsegnek VDD-t vesszuk (16. bit), a mintat pedig a 6-os csatornara vesszuk
  ///3. Tiltjuk az ADC0 interruptjat
   ADC0->CTRL = (24 << 16) | (1 << 8);
   ADC0->SINGLECTRL = (2 << 16) | (6 << 8);
   ADC0->IEN = 0x0;


   TIMER0->CTRL=(8<<24); //256-al osztjuk az orajelet
   TIMER0->TOP = 120000;  //a szamlalo felso erteket 30000 allitjuk
   TIMER0->IEN = 1;      //engedelyezzuk a megszakitast

   ///E HELYETT TOUCH INICIALIZALAS///
   //GPIO->P[BUTTON_PORT].MODEH = (2 << 4) | (2 << 8);    // Configure PB0 and PB1 as inputs
   //GPIO->P[BUTTON_PORT].DOUT = (1 << PB1) | (1 << PB0);
 // talan
   CMU_ClockEnable(cmuClock_GPIO, true);
   CAPLESENSE_Init(false);

   // int sliderPos;
   //sliderPos = CAPLESENSE_getSliderPosition();

   SegmentLCD_Init(false);


   NVIC_EnableIRQ(TIMER0_IRQn); //Interrupt contoller


   initialize(); //Inicializáljuk a játékot

   TIMER0->CMD = 0x1; //Elindítjuk a TIMER0-t

  /* Infinite loop */
  while (1) {
  }
}
