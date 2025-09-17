#pragma once
#include <Arduino.h>
#include <BitPack.h>
#include <GyverIO.h>
#include <SPI.h>

#ifndef GSHIFTSPI_DELAY
#define GSHIFTSPI_DELAY 0
#endif

template <uint8_t mode, uint16_t chip_amount, uint32_t spi_clock = 4000000ul>
class GyverShiftSPI : public BitPackExt {
   public:
    GyverShiftSPI(uint8_t CS) : BitPackExt(buffer, chip_amount * 8, true), _cs(CS) {
        gio::init(_cs, OUTPUT);
        gio::high(_cs);
    }

    // обновить состояния пинов
    bool update() {
        if (mode == INPUT) {
            _changed = 0;
            gio::low(_cs);
            if (GSHIFTSPI_DELAY) delayMicroseconds(GSHIFTSPI_DELAY);
            gio::high(_cs);
            SPI.beginTransaction(SPISettings(spi_clock, MSBFIRST, SPI_MODE0));
            uint8_t msb = gio::read(MISO);

            for (uint16_t i = 0; i < chip_amount; i++) {
                uint8_t b = SPI.transfer(0);
                uint8_t n = (msb << 7) | (b >> 1);
                if (buffer[i] != n) {
                    buffer[i] = n;
                    _changed = 1;
                }
                msb = b & 1;
            }

            SPI.endTransaction();
            return _changed;
        } else {
            gio::low(_cs);
            SPI.beginTransaction(SPISettings(spi_clock, MSBFIRST, SPI_MODE0));
            for (int16_t i = chip_amount - 1; i >= 0; i--) SPI.transfer(buffer[i]);
            SPI.endTransaction();
            gio::high(_cs);
            return 1;
        }
    }

    // true - было изменение буфера (для режима INPUT). Само сбросится в false
    bool changed() {
        return _changed ? _changed = 0, 1 : 0;
    }

    // буфер
    uint8_t buffer[chip_amount];

   private:
    uint8_t _cs;
    bool _changed = 0;
};
