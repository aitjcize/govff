/* itoa.cpp 

 * Copyright (C) 2009 -  Aitjcize <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.  
 */

#include "itoa.h"
#include <cmath>

char* itoa(int num)
{
  static char cha[64];
  if(num == 0) {
    cha[0] = '0';
    cha[1] = 0;
    return cha;
  }
  int tmp = 0;
  tmp = (num < 0)? -num: num;
  int digits = 0;
  while(static_cast<int>(num / pow(10, digits)))
    digits++;
  for(int i = 0; i < digits; i++)
  {
    cha[digits -i -(num > 0)] = tmp % 10 +'0';
    tmp /= 10;
  }
  if(num < 0) cha[0] = '-';
  cha[digits +(num < 0)] = '\0';
  return cha;
}


