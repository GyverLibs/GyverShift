#pragma once
#include <Arduino.h>
#include <GyverIO.h>
#include <SPI.h>

#include "GyverShiftBase.h"

#ifndef GSHIFTSPI_DELAY
#define GSHIFTSPI_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount, uint32_t spi_clock = 4000000ul>
class GyverShiftSPI : public GyverShiftBase<mode, chip_amount> {
   public:
    static_assert(spi_clock > 0, "spi_clock must be greater than 0");

    GyverShiftSPI(uint8_t CS) : _cs(CS) {
        gio::init(_cs, OUTPUT);
        gio::high(_cs);
    }

    // обновить состояния пинов
    bool update() {
        if (mode == INPUT) {
            bool changed = false;
            gio::low(_cs);
            if (GSHIFTSPI_DELAY) delayMicroseconds(GSHIFTSPI_DELAY);
            gio::high(_cs);
            SPI.beginTransaction(SPISettings(spi_clock, MSBFIRST, SPI_MODE0));
            uint8_t msb = gio::read(MISO);

            for (uint16_t i = 0; i < chip_amount; i++) {
                uint8_t b = SPI.transfer(0);
                uint8_t n = (msb << 7) | (b >> 1);
                if (this->buffer[i] != n) {
                    this->buffer[i] = n;
                    changed = true;
                }
                msb = b & 1;
            }

            SPI.endTransaction();
            return this->updateChanged(changed);
        } else {
            gio::low(_cs);
            SPI.beginTransaction(SPISettings(spi_clock, MSBFIRST, SPI_MODE0));
            for (int16_t i = chip_amount - 1; i >= 0; i--) SPI.transfer(this->buffer[i]);
            SPI.endTransaction();
            gio::high(_cs);
            return 1;
        }
    }

   private:
    uint8_t _cs;
};
