#pragma once
#include <Arduino.h>
#include <BitPack.h>
#include <GyverIO.h>

#ifndef GSHIFTT_DELAY
#define GSHIFTT_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount, uint8_t cs_pin, uint8_t dt_pin, uint8_t clk_pin>
class GyverShiftT : public BitPackExt {
   public:
    GyverShiftT() : BitPackExt(buffer, chip_amount * 8, true) {
        gio::init(cs_pin, OUTPUT);
        gio::init(dt_pin, mode);
        gio::init(clk_pin, OUTPUT);
        gio::high(cs_pin);
    }

    // обновить состояния пинов
    bool update() {
        if (mode == INPUT) {
            gio::low(cs_pin);
            if (GSHIFTT_DELAY) delayMicroseconds(GSHIFTT_DELAY);
            gio::high(cs_pin);
            _changed = gio::shift::read(dt_pin, clk_pin, MSB_NORMAL, buffer, chip_amount, GSHIFTT_DELAY);
            return _changed;
        } else {
            gio::shift::send_cs(dt_pin, clk_pin, cs_pin, MSB_REVERSE, buffer, chip_amount, GSHIFTT_DELAY);
            return 1;
        }
    }

    // true - было изменение буфера (для режима INPUT). Само сбросится в false
    bool changed() {
        return _changed ? _changed = 0, 1 : 0;
    }

    // доступ к буферу
    uint8_t buffer[chip_amount];

   private:
    bool _changed = 0;
};