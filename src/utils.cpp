/**
 * utils.cpp
 *
 * Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "utils.h"

#include <string>
#include <stdexcept>
#include <cstdio>

#include <uchardet/uchardet.h>

using std::string;

bool fileIsBig5(const char* filename) {
  char buf[4096];
  size_t len = 0;
  int res = 0;
  FILE* fp = fopen(filename, "rb");

  if (fp == NULL)
    throw std::runtime_error(string("can't open `") + filename + "'.");

  uchardet_t det = uchardet_new();

  do {
    len = fread(buf, 1, sizeof(buf), fp);
    res = uchardet_handle_data(det, buf, len);
  } while ((res == 0) && (feof(fp) == 0));

  uchardet_data_end(det);

  const char* charset = uchardet_get_charset(det);
  bool result = (string(charset) == "Big5");
  uchardet_delete(det);

  fclose(fp);

  return result;
}
