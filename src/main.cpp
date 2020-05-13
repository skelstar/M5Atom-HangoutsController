#ifdef DEBUG_SERIAL
#define DEBUG_OUT Serial
#endif
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>

//--------------------------------------------

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

float accX = 0, accY = 0, accZ = 0;
float lastX = 0, lastY = 0, lastZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
bool IMU6886Flag = false;

//---------------------------------------------------------------

#include <BleKeyboard.h>

// // https://github.com/T-vK/ESP32-BLE-Keyboard
// // https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/

BleKeyboard bleKeyboard("M5Atom Hangouts Ctrlr");

void sendFindMeetingTab()
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('j');
  delay(100);
  bleKeyboard.releaseAll();
}

void sendMicHotKey()
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press('d');
  delay(100);
  bleKeyboard.releaseAll();
}

//---------------------------------------------------------------

#include <MPU6886.h>

MPU6886 mpu;

//---------------------------------------------------------------
#define DOUBLECLICK_MS 300
#define LONGCLICK_MS 1000

#include <Button2.h>

Button2 button(39);

bool micOn = false;

//---------------------------------------------------------------

void toggleMic(Button2 &btn)
{
  sendFindMeetingTab();
  delay(100);
  sendMicHotKey();
  // setLeds(micOn ? CRGB::Red : CRGB::Green);
  micOn = !micOn;
}

void sendPlusOne(Button2 &btn)
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press('k');
  delay(100);
  bleKeyboard.releaseAll();

  DEBUG("+1 sent");
}

void sendWakeKey()
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  delay(50);
  bleKeyboard.releaseAll();
  DEBUG("sent wake key");
}

bool imuHasMoved()
{
  lastX = accX;
  lastY = accY;
  lastZ = accZ;
  mpu.getAccelData(&accX, &accY, &accZ);

#define MOTION_THRESHOLD 0.3

  bool _moved = abs(lastX - accX) > MOTION_THRESHOLD ||
                abs(lastY - accY) > MOTION_THRESHOLD ||
                abs(lastZ - accZ) > MOTION_THRESHOLD;
  if (_moved)
  {
    Serial.printf("motion\n");
  }

  lastX = accX;
  lastY = accY;
  lastZ = accZ;

  return _moved;
}

//---------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  DEBUG("Ready");

  // button.setReleasedHandler(toggleMic);
  button.setDoubleClickHandler(sendPlusOne);
  button.setTapHandler(toggleMic);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  FastLED.setBrightness(30);
  setLeds(CRGB::Blue);

  bleKeyboard.begin();

  mpu.Init();
}
//---------------------------------------------------------------

bool connected = false;
elapsedMillis sinceReadImu, sinceSentWakeKey;
#define READ_IMU_PERIOD 200
#define SECONDS 1000
#define MINUTES SECONDS * 60
#define SEND_WAKE_KEY_PERIOD 4 * MINUTES
bool moved;

void loop()
{
  if (sinceReadImu > READ_IMU_PERIOD && connected)
  {
    sinceReadImu = 0;

    moved = moved || imuHasMoved();
  }

  if (moved && sinceSentWakeKey > SEND_WAKE_KEY_PERIOD)
  {
    sinceSentWakeKey = 0;
    if (moved && connected)
    {
      sendWakeKey();
      moved = false;
    }
  }

  if (!connected && bleKeyboard.isConnected())
  {
    connected = true;
    setLeds(CRGB::Green);
    DEBUG("Connected!");
  }
  else if (connected && !bleKeyboard.isConnected())
  {
    setLeds(CRGB::Blue);
    connected = false;
    DEBUG("Disconnected!");
  }

  button.loop();

  vTaskDelay(10);
}
//------------------------------------------------------------------