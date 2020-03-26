#ifdef DEBUG_SERIAL
#define DEBUG_OUT Serial
#endif
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>

#include <FastLED.h>

#define NUM_LEDS 25
#define LED_PIN 27

CRGB leds[NUM_LEDS];

void setLeds(CRGB colour)
{
  for (int num = 0; num < NUM_LEDS; num++)
  {
    leds[num] = colour;
  }
  FastLED.show();
}

//---------------------------------------------------------------

#include <BleKeyboard.h>

// // https://github.com/T-vK/ESP32-BLE-Keyboard
// // https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/

BleKeyboard bleKeyboard("M5Atom Hangouts Ctrlr");

//---------------------------------------------------------------

#include <Button2.h>

Button2 button(39);

void onButtonPress(Button2 &btn)
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('d');
  delay(100);
  bleKeyboard.releaseAll();
  setLeds(CRGB::Green);
}

void onButtonRelease(Button2 &btn)
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('d');
  delay(100);
  bleKeyboard.releaseAll();
  setLeds(CRGB::Red);
}

//---------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("Ready");

  button.setPressedHandler(onButtonPress);
  button.setReleasedHandler(onButtonRelease);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  setLeds(CRGB::Blue);
  FastLED.setBrightness(100);

  bleKeyboard.begin();
}
//---------------------------------------------------------------

bool connected = false;

void loop()
{
  if (!connected && bleKeyboard.isConnected())
  {
    connected = true;
    setLeds(CRGB::Red);
    DEBUG("Connected!");
  }
  else if (connected && !bleKeyboard.isConnected())
  {
    setLeds(CRGB::Blue);
    connected = false;
    DEBUG("Disconnected!");
  }

  if (connected)
  {
    button.loop();
  }

  vTaskDelay(10);
}
//------------------------------------------------------------------