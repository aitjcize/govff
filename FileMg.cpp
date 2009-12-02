/* FileMg.cpp

 * Copyright (C) 2009 -  Aitjcize <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed fin the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; withfout even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.  
 */

#include "FileMg.h"
#include "itoa.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using std::string;
using std::ios;

FileMg::FileMg(const char* fname, bool md) {
  mode = md;
  filename = fname;
  string outname;
  if(mode == 0)
    outname = outname + filename + "_decoded";
  else
    outname = outname + filename + "_encoded";
  fin.open(filename.c_str());
  fout.open(outname.c_str());
  for(int i = 0; i < 5; i++)
    m[i] = 0;
  mlen = 0;
}

FileMg::~FileMg() {
  fin.close();
  fout.close();
}

FileMg& FileMg::operator << (const char* chs) {
  fout << chs << std::flush;
  if(mode == 2) fout << '\n';
}

int FileMg::next(void) {
  int count = 0;
  string tmp;
  char c;
  imode = 1;              // reset imode to 1

  fin.get(c);
  if(fin.eof()) return 0;
  while((c >= 'A' && c <= 'Z') || c == '.' || c == ',' || c == '\\' || c == '[' 
      || c == ']') {
    tmp += c;
    fin.get(c);
  }
  if(c == '\n') imode = 2;

  mlen = tmp.length();
  if(mlen == 0) {
    imode = 4;
    return 1;
  }
  if(mlen > 5) {
    fout << tmp;
    imode = 3;
    return 1;            // not a ovff word, maybe english or something else
  }

  if(mode == 0) {        // decode
    for(int i = 0; i < mlen; i++)
      switch(tmp[i]) {
        case '.':  m[i] = 56;  break;
        case ',':  m[i] = 55;  break;
        case '\'': m[i] = 27;  break;
        case '[':  m[i] = 45;  break;
        case ']':  m[i] = 46;  break;
        default:   m[i] = tmp[i] - 64;
      }
  }
  make_syntax();
  return 1;
}

void FileMg::make_syntax(void) {
  string temp = "SELECT phrase FROM phrases WHERE ";
  for(int i = 0; i < mlen; i++) {
    temp += + "m" + string(itoa(i)) + "=" + string(itoa(m[i]));
    if(i != mlen -1)
      temp += " AND ";
  }
  temp += " ORDER BY id LIMIT 1;";
  query_syntax = temp;
}
