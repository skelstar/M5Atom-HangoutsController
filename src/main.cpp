
#ifdef DEBUG_SERIAL
#define DEBUG_OUT Serial
#endif
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <rom/rtc.h> // for reset reason

#define SOFT_SPI_MOSI_PIN 21 // Blue
#define SOFT_SPI_MISO_PIN 25 // Orange
#define SOFT_SPI_SCK_PIN 33  // Yellow

#define NRF_CE 22 // green
#define NRF_CS 23 // white

#include <NRF24L01Lib.h>
#include <RF24Network.h>

NRF24L01Lib nrf24;

RF24 radio(NRF_CE, NRF_CS);
RF24Network network(radio);

//-----------------------------------------

// #include "M5Atom.h"

// extern const unsigned char AtomImageData[375 + 2];

// uint8_t DisBuff[2 + 5 * 5 * 3];

// void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
// {
//   DisBuff[0] = 0x05;
//   DisBuff[1] = 0x05;
//   for (int i = 0; i < 25; i++)
//   {
//     DisBuff[2 + i * 3 + 0] = Rdata;
//     DisBuff[2 + i * 3 + 1] = Gdata;
//     DisBuff[2 + i * 3 + 2] = Bdata;
//   }
// }

void setup()
{
  // M5.begin(true, false, true);
  // delay(10);
  // setBuff(0xff, 0x00, 0x00);
  // M5.dis.displaybuff(DisBuff);

  DEBUG("Starting");

  nrf24.begin(&radio, &network, 1, NULL);
}

uint8_t FSM = 0;

void loop()
{
  // if (M5.Btn.wasPressed())
  // {

  //   switch (FSM)
  //   {
  //   case 0:
  //     setBuff(0xff, 0xff, 0xff);
  //     break;
  //   case 1:
  //     setBuff(0x00, 0xff, 0x00);
  //     break;
  //   case 2:
  //     setBuff(0x00, 0x00, 0xff);
  //     break;
  //   case 3:
  //     setBuff(0xff, 0x00, 0x00);
  //     break;
  //   default:
  //     break;
  //   }
  //   M5.dis.displaybuff(DisBuff);

  //   FSM++;
  //   if (FSM >= 4)
  //   {
  //     FSM = 0;
  //   }
  // }

  delay(50);
  // M5.update();
}