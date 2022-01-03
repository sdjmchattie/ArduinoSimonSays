/*
  led_multi_flash.h - JLed custom effect to flash a fixed number of times.
  Created by Stuart D.J. McHattie, January 03, 2022.
*/

#ifndef led_multi_flash_h
#define led_multi_flash_h

#include <jled.h>

class LedMultiFlash : public jled::BrightnessEvaluator
{
  uint8_t flashCount;
  uint16_t speed;

public:
  explicit LedMultiFlash(uint8_t flashCount, uint16_t speed = 100) : flashCount(flashCount), speed(speed){};
  uint8_t Eval(uint32_t t) const override;
  uint16_t Period() const override;
};

#endif
