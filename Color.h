/*
   FSR Board Firmware - Firmware for PCB doing FSR Sensor tests for
    reprap printers auto bed leveling.
    
    Copyright (C) 2015  Roland "Glatzemann" Rosenkranz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

struct RGB
{
  float r;
  float g;
  float b;
};

struct HSV
{
  float h;
  float s;
  float v;
};

int linearF(float a, float b, float t);

class Color
{
public:
  Color(float r, float g, float b);
  Color(RGB rgb);
  Color(HSV hsv);

  RGB getRGB() { return rgb; }
  HSV getHSV() { return hsv; }

  template<typename F>
  Color interpolate(Color b, float t, F interpolator)
  {
    // 0.0 <= t <= 1.0
    HSV hsvB  = b.getHSV();
    HSV final;

    final.h = interpolator(hsv.h, hsvB.h, t);
    final.s = interpolator(hsv.s, hsvB.s, t);
    final.v = interpolator(hsv.v, hsvB.v, t);

    return Color(final);
  }

private:
  void calcHsv();
  void calcRgb();
  
private:
  RGB rgb;
  HSV hsv;
};

