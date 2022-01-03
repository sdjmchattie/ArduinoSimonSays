/*
  led_multi_flash.cpp - JLed custom effect to flash a fixed number of times.
  Created by Stuart D.J. McHattie, January 03, 2022.
*/

#include "led_multi_flash.h"

uint8_t LedMultiFlash::Eval(uint32_t t) const
{
  if (t == Period())
  {
    return 0;
  }

  return 255 * (1 - (t / speed) % 2);
}

uint16_t LedMultiFlash::Period() const
{
  return (flashCount * 2 - 1) * speed;
}
