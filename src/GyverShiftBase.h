#pragma once
#include <Arduino.h>
#include <BitPack.h>

template <uint8_t mode, uint16_t chip_amount>
class GyverShiftBase : public BitPackExt {
   public:
    static_assert(mode == INPUT || mode == OUTPUT, "mode must be INPUT or OUTPUT");
    static_assert(chip_amount > 0 && chip_amount <= 8191, "chip_amount must be 1..8191");

    GyverShiftBase() {
        setBuffer(buffer, chip_amount * 8);
    }

    GyverShiftBase(const GyverShiftBase& other) {
        setBuffer(buffer, chip_amount * 8, false);
        *this = other;
    }

    GyverShiftBase& operator=(const GyverShiftBase& other) {
        if (this == &other) return *this;
        other.copyTo(*this);
        _changed = other._changed;
        return *this;
    }

    // true - было изменение буфера (для режима INPUT). Само сбросится в false
    bool changed() {
        return _changed ? _changed = 0, 1 : 0;
    }

    // доступ к буферу
    uint8_t buffer[chip_amount];

   protected:
    bool updateChanged(bool changed) {
        _changed |= changed;
        return changed;
    }

   private:
    bool _changed = 0;
};
