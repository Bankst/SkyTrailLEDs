#include "FastLED.h"
#include "TeensyThreads.h"

#define NUM_LEDS 200
#define MAX_BRIGHTNESS 255
#define FRAMES_PER_SECOND 240

CRGB leds[NUM_LEDS];

void setup() {
  LEDS.addLeds<WS2811, 0, BRG>(leds, NUM_LEDS);
  LEDS.addLeds<WS2811, 1, BRG>(leds, NUM_LEDS);
  LEDS.addLeds<WS2811, 2, BRG>(leds, NUM_LEDS);
  LEDS.addLeds<WS2811, 23, BRG>(leds, NUM_LEDS);
  LEDS.addLeds<WS2811, 22, BRG>(leds, NUM_LEDS);
  LEDS.addLeds<WS2811, 21, BRG>(leds, NUM_LEDS);
  LEDS.setBrightness(MAX_BRIGHTNESS);

  pinMode(LED_BUILTIN, OUTPUT);
  threads.addThread(statusThread);
}

const int blinkDelay = 60;

void statusThread() {
  while(1) {
    digitalWrite(LED_BUILTIN, HIGH);
    threads.delay(blinkDelay);
    digitalWrite(LED_BUILTIN, LOW);
    threads.delay(blinkDelay);
    digitalWrite(LED_BUILTIN, HIGH);
    threads.delay(blinkDelay);
    digitalWrite(LED_BUILTIN, LOW);
    threads.delay(1000);
    threads.yield();
  }
}

void loop() {
  palettetest(leds, NUM_LEDS, RainbowStripeColors_p);
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

// Alternate rendering function just scrolls the current palette across the defined LED strip.
void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette)
{
  static uint8_t startindex = 0;
  startindex -= 10;
  fill_palette( ledarray, numleds, startindex, (256 / (NUM_LEDS/6)) + 1, gCurrentPalette, 255, LINEARBLEND);
}
