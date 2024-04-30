#include <Arduino.h>
#include <GyverShift.h>
// #include <GyverShiftT.h>

// кол-во чипов (по 8 выходов)
#define CHIP_AMOUNT 1

#define CLK_595 12
#define CS_595 14
#define DAT_595 27

GyverShift<OUTPUT, CHIP_AMOUNT> outp(CS_595, DAT_595, CLK_595);
// GyverShiftT<OUTPUT, 1, CS_595, DAT_595, CLK_595> outp;

void setup() {
}

void loop() {
    for (int i = 0; i < CHIP_AMOUNT * 8; i++) {
        outp.clearAll();
        outp[i] = 1;
        outp.update();
        delay(200);
    }
}