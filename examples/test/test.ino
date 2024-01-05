#include <Arduino.h>
// читаем hc165 и выводим соответственно на hc595

// 74hc595
#define CLK_595 13
#define CS_595 9
#define DAT_595 11

// 74hc165
#define LAT_165 8
#define CLK_165 13
#define DAT_165 12

#include <GyverShift.h>
#include <GyverShiftSPI.h>

GyverShift<OUTPUT, 2> outp(CS_595, DAT_595, CLK_595);
GyverShift<INPUT, 2> inp(LAT_165, DAT_165, CLK_165);
// GyverShiftSPI<OUTPUT, 2> outp(CS_595);
// GyverShiftSPI<INPUT, 2> inp(LAT_165);

void setup() {
    Serial.begin(115200);
    SPI.begin();
    // outp.write(0, 1);
    // outp.write(1, 1);
    // outp[7] = 1;
    // outp[8] = 1;
    // outp[14] = 1;
    // outp.update();
}

void loop() {
    inp.update();  // читаем

    if (inp.changed()) {
        for (uint16_t i = 0; i < inp.amount(); i++) {
            Serial.print(inp[i]);
            outp[i] = inp[i];  // дублируем
        }
        Serial.println();
        outp.update();  // обновляем выход
    }

    delay(100);  // антидребезг
}