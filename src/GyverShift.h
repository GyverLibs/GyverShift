#pragma once
#include <Arduino.h>
#include <GyverIO.h>

#include "GyverShiftBase.h"

#ifndef GSHIFT_DELAY
#define GSHIFT_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount>
class GyverShift : public GyverShiftBase<mode, chip_amount> {
   public:
    GyverShift(uint8_t CS, uint8_t DT, uint8_t CLK) {
        _cs = CS;
        _dt = DT;
        _clk = CLK;
        gio::init(_cs, OUTPUT);
        gio::init(_dt, mode);
        gio::init(_clk, OUTPUT);
        gio::high(_cs);
    }

    // обновить состояния пинов
    bool update() {
        if (mode == INPUT) {
            gio::low(_cs);
            if (GSHIFT_DELAY) delayMicroseconds(GSHIFT_DELAY);
            gio::high(_cs);
            bool changed = gio::shift::read(_dt, _clk, MSB_NORMAL, this->buffer, chip_amount, GSHIFT_DELAY);
            return this->updateChanged(changed);
        } else {
            gio::shift::send_cs(_dt, _clk, _cs, MSB_REVERSE, this->buffer, chip_amount, GSHIFT_DELAY);
            return 1;
        }
    }

   private:
    uint8_t _cs, _dt, _clk;
};
