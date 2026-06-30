#pragma once
#include <Arduino.h>
#include <GyverIO.h>

#include "GyverShiftBase.h"

#ifndef GSHIFTT_DELAY
#define GSHIFTT_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount, uint8_t cs_pin, uint8_t dt_pin, uint8_t clk_pin>
class GyverShiftT : public GyverShiftBase<mode, chip_amount> {
   public:
    GyverShiftT() {
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
            bool changed = gio::shift::read(dt_pin, clk_pin, MSB_NORMAL, this->buffer, chip_amount, GSHIFTT_DELAY);
            return this->updateChanged(changed);
        } else {
            gio::shift::send_cs(dt_pin, clk_pin, cs_pin, MSB_REVERSE, this->buffer, chip_amount, GSHIFTT_DELAY);
            return 1;
        }
    }

};
