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

extern uint16_t segment;
extern uint16_t digit;
extern uint8_t updowndirection;


///Kovetkezo szegmens kikeresese balra kanyarodasnal
///Visszafele nem tudunk kanyarodni, ilyenkor fuggelegesen halad tovabb az urhajo

void lookupLeft(void){ // @suppress("No return")
  if (segment==UP){
      if(digit!=6){
     segment=LEFT_DOWN;
      digit++;}
      else
        segment=RIGHT_DOWN;
      updowndirection=0; //felfele nezunk
  }
  else if(segment==MIDDLE){
      if(digit!=6){
     segment=LEFT_UP;
         digit++;
      }
      else
        segment=RIGHT_UP;
      updowndirection=0;//felfele nezunk
  }
  else if(segment==BOTTOM){
      if(digit!=6){
       segment=LEFT_DOWN;
       digit++;
      }
      else
        segment=RIGHT_DOWN;
      updowndirection=0;//felfele nezunk
    }
  else if(segment==LEFT_UP){
      if(updowndirection==0){
       segment=LEFT_DOWN;
      }
      else{
         segment=MIDDLE;
      }
      }
  else if(segment==LEFT_DOWN){
      if(updowndirection==0){
             segment=LEFT_UP;
            }
            else{
               segment=BOTTOM;
            }
    }
  else if(segment==RIGHT_UP){
      if(updowndirection==0){
             segment=RIGHT_DOWN;
            }
            else{ //ez csak akkor lehetseges ha az utolso digiten allok ezert kell uj kor
                newRound(MIDDLE);
            }
    }
  else if(segment==RIGHT_DOWN){
      if(updowndirection==0){
             segment=RIGHT_UP;
            }
            else{ //ez csak akkor lehetseges ha az utolso digiten allok ezert kell uj kor
               newRound(BOTTOM);
            }
    }
}

///Kovetkezo szegmens kikeresese jobbra kanyarodasnal
///Visszafele nem tudunk kanyarodni, ilyenkor fuggolegesen halad tovabb az urhajo

void lookupRight(void){ // @suppress("No return")
  if (segment==UP){
      if(digit!=6){
     segment=LEFT_UP;
     digit++;}
      else
        segment=RIGHT_UP;
      updowndirection=1;//lefele
  }
  else if(segment==MIDDLE){
      if(digit!=6){
     segment=LEFT_DOWN;
     digit++;
      }
      else
        segment=RIGHT_DOWN;
      updowndirection=1; //lefele
  }
  else if(segment==BOTTOM){
      if(digit!=6){
       segment=LEFT_UP;
       digit++;
      }
      else
        segment=RIGHT_UP;
      updowndirection=1; //lefele
    }
  else if(segment==LEFT_UP){
      if(updowndirection==0){
       segment=UP;}
       else
         segment=LEFT_DOWN;
      }
  else if(segment==LEFT_DOWN){
      if(updowndirection==0){
       segment=MIDDLE;
      }
      else
        segment=LEFT_UP;
    }
  else if(segment==RIGHT_UP){
      if(updowndirection==0){
          newRound(UP);}
      else
        segment=RIGHT_DOWN;
    }
  else if(segment==RIGHT_DOWN){
      if(updowndirection==0){
          newRound(MIDDLE);}
      else
        segment=RIGHT_UP;
    }
}

///Kovetkezo szegmens egyenesen haladasnal
///Ha a hajo fuggolegesen felfele vagy lefele elhagyna a palyat, akkor a "tuloldalon" jelenik meg.

void lookupForward(void){
  if (segment==UP){
      if(digit!=6){
      digit++;}
      else{
          newRound(UP);
      }}
  else if(segment==MIDDLE){
      if(digit!=6){
        digit++;}
      else{
          newRound(MIDDLE);
        }}
  else if(segment==BOTTOM){
      if(digit!=6){
            digit++;}
      else{
          newRound(BOTTOM);
          }}
  else if(segment==LEFT_UP){
         segment=LEFT_DOWN;
          }
  else if(segment==LEFT_DOWN){
         segment=LEFT_UP;
          }
  else if(segment==RIGHT_UP){
         segment=RIGHT_DOWN;
          }
  else if(segment==RIGHT_DOWN){
         segment=RIGHT_UP;
          }

}


///A hajo mozgasa, a lenyomott erzekelonek megfeleloen
/// Az iranytol fuggoen mozgatjuk urhajot, aminek a menete a kovetkezo:
/// 1. Taroljuk az LCD aktualis kepet
/// 2. Megkeressuk az iranynak megfelelo kovetkezo szegmenst es oda lepunk
/// 3. Kirajzoljuk az aszteroidakat
/// 4. Megnezzuk, hogy tortent-e utkozes az aszteroidakkal
/// 5. Ha tortent utkozes, a jatek vegeter, egyebkent vegeter a mozgatas

void moving(uint16_t direction){
  switch (direction){
  case 0:
    {
      clearLCD();
      lookupForward();
      lowerCharSegments[digit].raw=segment;
      SegmentLCD_LowerSegments(lowerCharSegments);
      displayAsteroids();
      checkDefeat();
      break;
    }
  case 1:
    {
    clearLCD();
    lookupLeft();
    checkDefeat();
    lowerCharSegments[digit].raw=segment;
    SegmentLCD_LowerSegments(lowerCharSegments);
    displayAsteroids();
    break;
    }
  case 2:
      {
      clearLCD();
      lookupRight();
      checkDefeat();
      lowerCharSegments[digit].raw=segment;
      SegmentLCD_LowerSegments(lowerCharSegments);
      displayAsteroids();
      break;
      }

  }
}

