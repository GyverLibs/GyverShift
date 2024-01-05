This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyvershift
Library for convenient work with shift registers, increasing the number of ARDUINO Pino
- To the exit - 74hc595
- Input - 74hc165
- buffering of meanings beaten in the buffer
- Fast Bit-Bang data transfer based on Gyverio- ten times faster than standard Shift functions
- Work through hardware SPI
- Convenient appeal to pins as an array

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [connection] (#wiring)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id="wiring"> </a>

## connection
## 74hc595
! [595] (DOC/HC595.png)

## 74hc165
! [165] (doc/hc165.png)

> Note: the pin should either be tightened or have a single -digit signal Low/High

<a id="usage"> </a>
## Usage

## H initialization
`` `CPP
// bit-bang (any pins)
Gyvershift <output, number of chips> reg (CS, DAT, CLK);// Exit (hc595)
Gyvershift <input, number of chips> reg (CS, DAT, CLK);// Entrance (hc165)

// Hardware SPI
Gyvershiftspi <output, number of chips, clock = 4000000> reg (CS);// Exit (hc595)
Gyvershiftspi <input, number of chips, clock = 4000000> reg (CS);// Entrance (hc165)

// Output: Dat-> Mosi
// Input: Dat-> Miso
`` `

> Note: for the `Input` mode (74hc165) ** Hardware SPI ** works incorrectly due to the features of the chip - does not read the last (D7) entrance!

### description of the class
`` `CPP
// update the states of Pinov
Bool update ();

// True - there was a change in the buffer (for Input mode).Will drop in FALSE itself
Bool Changed ();

// access to the buffer
uint8_t buffer [];

// inherited from Bitpack
VOID set (uint16_t num);// install
VOID Clear (uint16_t num);// reset
VOID TOGGLE (UINT16_T NUM);// switch
VOID Write (Uint16_T Num, Bool State);// Record
Bool Read (uint16_t num);// Read
VOID setall ();// install everything
VOID CLEARALL ();// throw everything
uint16_t amount ();// Number of Pinins
uint16_t size ();// size in bytes
`` `

### reading
The library inherits [bitpack] (https://github.com/gyverlibs/bitpack) - access to the buffer as an array and other tools.The buffer is beaten and packed in bytes, the chip just has 8 entrances-exits.To update the state of outputs and reading inputs, `update ()` must be called.
`` `CPP
// output
reg [0] = 1;// Turn on PIN 1
reg [1] = 0;// Turn off PIN 1
reg.write (2, 1);// Turn on PIN 2
reg.Set (3);// Turn on PIN 3
reg.clear (4);// Turn off PIN 4
//reg.setall ();// enable all
reg.update ();// update the states of Pinov


// Input
reg.update ();// Read pins
// Get from the buffer in any way
Serial.println (reg [0]);
Serial.println (reg.read (1));
Bool p2 = reg [2];
Bool p3 = reg.read (3);
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!

`` `CPP
#include <gyvershift.h>
// 74hc595
#define clk_595 13
#define cs_595 9
#define Dat_595 11

Gyvershift <output, 2> outp (CS_595, Dat_595, CLK_595);
VOID setup () {
    outp.write (0, 1);
    outp.write (1, 1);
    outp [7] = 1;
    OUTP [8] = 1;
    outp [14] = 1;
    outp.update ();
}
`` `

<a id="versions"> </a>

## versions
- V1.0

<a id="install"> </a>
## Installation
- Libraries are required for work [bitpack] (https://github.com/gyverlibs/Bitpack) and [gyverio] (https://github.com/gyverlibs/gyverio)
- The library can be found by the name ** gyvershift ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyvershift/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code