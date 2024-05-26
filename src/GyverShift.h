#pragma once
#include <Arduino.h>
#include <BitPack.h>
#include <gio/gio.h>
#include <utils/shift.h>

#ifndef GSHIFT_DELAY
#define GSHIFT_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount>
class GyverShift : public BitPackExt {
   public:
    GyverShift(uint8_t CS, uint8_t DT, uint8_t CLK) : BitPackExt(buffer, chip_amount * 8, true) {
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
            _changed = gio::shift::read(_dt, _clk, MSB_NORMAL, buffer, chip_amount, GSHIFT_DELAY);
            return _changed;
        } else {
            gio::shift::send_cs(_dt, _clk, _cs, MSB_REVERSE, buffer, chip_amount, GSHIFT_DELAY);
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
    uint8_t _cs, _dt, _clk;
    bool _changed = 0;
};