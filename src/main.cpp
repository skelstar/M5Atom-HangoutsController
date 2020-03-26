#ifdef DEBUG_SERIAL
#define DEBUG_OUT Serial
#endif
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>
#include <Button2.h>

//---------------------------------------------------------------

// #include <BleKeyboard.h>

// // https://github.com/T-vK/ESP32-BLE-Keyboard
// // https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/

// BleKeyboard bleKeyboard("M5Atom Hangouts Controller");

//---------------------------------------------------------------

Button2 button(39);

void onButtonPress(Button2 &btn)
{
  DEBUG("onPress");
  // bleKeyboard.press(KEY_LEFT_CTRL);
  // bleKeyboard.press('d');
  // delay(100);
  // bleKeyboard.releaseAll();
}

void onButtonRelease(Button2 &btn)
{
  DEBUG("onRelease");
  // bleKeyboard.press(KEY_LEFT_CTRL);
  // bleKeyboard.press('d');
  // delay(100);
  // bleKeyboard.releaseAll();
}

//---------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("Ready");

  button.setPressedHandler(onButtonPress);
  button.setReleasedHandler(onButtonRelease);

  // bleKeyboard.begin();
}
//---------------------------------------------------------------

void loop()
{
  // if (bleKeyboard.isConnected())
  // {
  // }

  button.loop();

  vTaskDelay(10);
}
//------------------------------------------------------------------