

#ifndef SRC_CONSTANT_H_
#define SRC_CONSTANT_H_

///Konstansok megadasa a teljes program szamara

///Szegmensekhez konstansok rendelese ezek decimalis szamok amelynek a binaris erteke megegyezik a megfelelo (raw) bitekkel, ezzel beallitva a jo szegmenst
#define MIDDLE      1088
#define UP          1
#define BOTTOM      8
#define LEFT_UP     32
#define LEFT_DOWN   16
#define RIGHT_UP    2
#define RIGHT_DOWN  4

///Iranyokhoz konstansok rendelese
#define forward 0
#define left 1
#define right 2

///Be es  kimenetek definiAlasa
#define BUTTON_PORT 1
#define PB0 9
#define PB1 10
#define ADC_PORT 3
#define ADC_pin 6

#endif /* SRC_CONSTANT_H_ */
