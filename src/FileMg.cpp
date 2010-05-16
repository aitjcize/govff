/**
 * FileMg.cpp
 *
 * Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modif y
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
 * Inc., 51 Franklin Street, Fif th Floor, Boston, MA 02110-1301 USA.
 */

#include "FileMg.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
using std::string;

FileMg::FileMg(const FileMg&): in(std::cin), out(std::cout) {
  throw std::runtime_error("Copy of class FileMg is not allowed, file can "
    "only be opened once at a time.");
}

FileMg& FileMg::operator << (const char* chs) {
  out << chs;
  return (*this);
}

FileMg& FileMg::operator << (const char ch) {
  out << ch;
  return (*this);
}

/* @brief    next loader for encode and decode
 * @param    
 * @retval   
 */

int FileMg::next(void) {
  if (mode == DecodeMode)
    return next_decode();
  else
    return next_encode();
}

int FileMg::next_decode(void) {
  const string seperators = " \t\n";
  int mlen,             // text code array length
      m[5] = { 0 };             // text code array
  char c;

  // ----- clear string content to reset status ----- //
  query_syntax.clear();
  query_orig.clear();

  in.get(c);

  // ----- return 0 if reach end of file ----- //
  if (in.eof())
    return 0;

  // ----- if recieve '\n' return without query_syntax ----- //
  if (seperators.find(c, 0) != string::npos) {
    query_orig += c;
    return 1;
  }

  while (seperators.find(c, 0) == string::npos && !in.eof()) {
    query_orig += c;
    if ((toupper(c) < 'A' || toupper(c) > 'Z') && c != '.' && c != ','
        && c != '\'' && c != '[' && c != ']')
      return 1;
    in.get(c);
  }

  mlen = query_orig.length();
  // ----- if mlen > 5, query_orig is not a valid word, return without
  // query_syntax -----
  if (mlen > 5) {
    query_orig += c;
    return 1;
  }

  // ----- if the last character is '\n', put it back to the stream in order
  // to be output at the next query -----
  if (c == '\n') in.putback(c);

  for (int i = 0; i < mlen; i++)
    switch (toupper(query_orig[i])) {
      case '.':  m[i] = 56;  break;
      case ',':  m[i] = 55;  break;
      case '\'': m[i] = 27;  break;
      case '[':  m[i] = 45;  break;
      case ']':  m[i] = 46;  break;
      default:   m[i] = toupper(query_orig[i]) - 'A' + 1;
    }

  make_syntax(m, 5);
  return 1;
}

int FileMg::next_encode(void) {
  const string seperators = " \t\n";
  int phrase[4] = { 0 };      // for a single mbs
  char c;

  // clear string content to reset status
  query_syntax.clear();
  query_orig.clear();

  in.get(c);

  if (in.eof()) return 0;
  if (c < 0)
    in.putback(c);
  else {
    query_orig += c;
    return 1;
  }

  for (int i = 0; i < 3; i++) {
    in.get(c);
    query_orig += c;
    phrase[i] = c;
    if (c > 0)
      return 1;
  }
  make_syntax(phrase, 3);
  return 1;
}

/* @brief    make syntax for sqlite3 query
 * @param    text code array, text code array length
 * @retval   none
 */

void FileMg::make_syntax(int* ptr, int len) {
  std::ostringstream packer;
  if (mode == DecodeMode) {
    packer << "SELECT phrase FROM phrases WHERE ";
    for (int i = 0; i < len; i++) {
      if (ptr[i] != 0)
        packer << "m" << i << "=" << ptr[i];
      else
        packer << "m" << i << " IS NULL";
      if (i != len -1)
        packer << " AND ";
    }
    packer << " ORDER BY -freq LIMIT 1;";
  } else {
    packer << "SELECT m0,m1,m2,m3,m4 FROM phrases WHERE phrase='";
    for (int i = 0; i < len; i++)
      packer << static_cast<char>(ptr[i]);
    packer << "' ORDER BY -freq,category LIMIT 1;";
  }
  query_syntax = packer.str();
}
