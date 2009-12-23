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
#include "utils.h"
#include <fstream>
#include <sstream>
using std::ostringstream;

#include <string>
using std::string;
using std::ios;

#include <stdexcept>

FileMg::FileMg(const char* fname, bool md) {
  mode = md;
  string dir = dir_name(fname);
  filename = base_name(fname);
  string outname = dir;
  if(mode == 0)
    outname += "d_" + filename;
  else
    outname += "e_" + filename;
  fin.open(fname);
  if(!fin.is_open())
    throw ios::failure(string("Error opening `") +  string(filename)
        + string("'."));
  fout.open(outname.c_str());
  if(!fout.is_open())
    throw ios::failure(string("Error opening `") +  string(outname)
        + string("'."));
  for(int i = 0; i < 5; i++)
    m[i] = 0;
  mlen = 0;
}

FileMg::FileMg(const FileMg& robj) {
  throw std::runtime_error("Copy of class FileMg is not allowed, file can\
 only be opened once at a time.");
}

FileMg::~FileMg() {
  fin.close();
  fout.close();
}

FileMg& FileMg::operator << (const char* chs) {
  fout << chs;
  if(imode == 2) fout << '\n';
  return (*this);
}

int FileMg::next(void) {
  char c;
  imode = 1;              // reset imode to 1
  string tmp;

  while(tmp.length() == 0) {
    fin.get(c);
    if(fin.eof()) return 0; // exit if end of file

    if(c == '\n') {         // read '\n' first
      imode = 4;
      return 1;
    }
    while(c != ' ' && c != '\n' && !fin.eof()) {
      tmp += c;
      if((c < 'A' || c > 'Z') && c != '.' && c != ',' && c != '\\'
          && c != '[' && c != ']') {
        fout << tmp;
        imode = 3;
        return 1;
      }
      fin.get(c);
    }
  }

  mlen = tmp.length();
  if(c == '\n') imode = 2;
  if(mlen > 5) {
    fout << tmp << c;
    imode = 3;
    return 1;            // not a ovff word, maybe english or something else
  }

  for(int i = 0; i < mlen; i++) 
    switch(tmp[i]) {
      case '.':  m[i] = 56;  break;
      case ',':  m[i] = 55;  break;
      case '\'': m[i] = 27;  break;
      case '[':  m[i] = 45;  break;
      case ']':  m[i] = 46;  break;
      default:   m[i] = tmp[i] - 64;
    }

  make_syntax();
  return 1;
}

void FileMg::make_syntax(void) {
  ostringstream packer;
  packer << "SELECT phrase FROM phrases WHERE ";
  for(int i = 0; i < mlen; i++) {
    packer << "m" << i << "=" << m[i];
    if(i != mlen -1)
      packer << " AND ";
  }
  packer << " ORDER BY id LIMIT 1;";
  query_syntax = packer.str();
}
