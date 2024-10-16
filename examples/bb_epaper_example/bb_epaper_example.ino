//
// Getting_started with the bb_epaper library (https://github.com/bitbank2/bb_epaper)
// Written by Larry Bank, October 16, 2024
// bitbank@pobox.com
//
// This sketch will demonstrate how to use various features of the bb_epaper
// library including working with compressed fonts and graphics
//
// To build this in Arduino, select ESP32S3 Dev Module as the target system
// and clone the bb_epaper library into the Arduino/libraries folder
//
#include <bb_epaper.h>
#include "bart_37x80.h" // G5 compressed image created with the bb_epaper imagecompress tool
#include "Roboto_Black_20.h" // G5 compressed font created with bb_epaper fonfconvert tool

BBEPAPER bbep(EPD102_80x128);
// Pinout for the LilyGo mini-epaper S3
#define PIN_BUSY 10
#define PIN_RST 11
#define PIN_DC 12
#define PIN_CS 13
#define PIN_SCK 14
#define PIN_MOSI 15

void setup()
{
  // The class is instantiated with the e-paper panel type, but we still need to tell
  // the library how it's connected to the MCU
  bbep.initIO(PIN_DC, PIN_RST, PIN_BUSY, PIN_CS, PIN_MOSI, PIN_SCK, 4000000);
  // A backing buffer isn't required to draw text and graphics on e-paper displays
  // but it does allow more functionality and drawing objects on top of each other
  bbep.allocBuffer(); // have the library allocate and manage a backing buffer
  bbep.setRotation(90); // The native panel size is 80 wide by 128 tall, rotate it to landscape
  bbep.fillScreen(BBEP_WHITE); // clear the memory to white to begin
  // Decompress and draw the compressed Bart bitmap at the right edge of the display
  bbep.loadG5Image(bart_37x80, bbep.width() - 37, 0, BBEP_WHITE, BBEP_BLACK);
  bbep.setFont(Roboto_Black_20);
  //bbep.setFont(FONT_12x16);
  bbep.setCursor(0,24);
  bbep.setTextColor(BBEP_BLACK);
  bbep.println("Hello");
  bbep.println("Bart");
  // When using a back buffer, we need to explicitly tell bb_epaper to write the memory
  // buffer to the e-paper's memory. There are 2 planes (0 & 1) which server different
  // purposes depending on the update mode
  bbep.writePlane(); // by default, the buffer is written to both memory planes
  bbep.refresh(REFRESH_FULL); // do a full (flashing) update
  bbep.wait(); // wait for the operation to complete
  bbep.sleep(DEEP_SLEEP); // put the panel to sleep to extend its life and save power
} /* setup() */

void loop()
{
} /* loop() */
