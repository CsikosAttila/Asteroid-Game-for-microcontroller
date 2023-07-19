#include "segmentlcd.h"
#include "segmentlcd_individual.h"

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[];

///Also LCD kepernyo teljes torlese ciklussal
void clearLCD(void){
    for(uint8_t p=0; p<SEGMENT_LCD_NUM_OF_LOWER_CHARS; p++){
            lowerCharSegments[p].raw = 0;
            SegmentLCD_LowerSegments(lowerCharSegments);
            }
}
