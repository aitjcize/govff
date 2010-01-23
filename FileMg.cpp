/* FileMg.cpp

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

#include "FileMg.h"
#include "utils.h"
#include <iostream>
#include <sstream>
using std::ostringstream;

#include <string>
using std::string;
using std::ios;

#include <stdexcept>

FileMg::FileMg(std::istream& _in, std::ostream& _out, bool md):
  in(_in), out(_out) {
  mode = md;
  for(int i = 0; i < 5; i++)
    m[i] = 0;
  mlen = 0;
}

FileMg::FileMg(const FileMg& robj): in(std::cin), out(std::cout) {
  throw std::runtime_error("Copy of class FileMg is not allowed, file can\
 only be opened once at a time.");
}

FileMg& FileMg::operator << (const char* chs) {
  out << chs;
  return (*this);
}

int FileMg::next(void) {
  char c;
  query_syntax.clear();
  query_orig.clear();

  in.get(c);

  // ----- return 0 if reach end of file -----
  if(in.eof()) {
    query_orig += c;
    return 0; 
  }
  // ----- if recieve '\n' return without query_syntax -----
  if(c == '\n' || c == ' ') {
    query_orig += c;
    return 1;
  }

  while(c != ' ' && c != '\n' && !in.eof()) {
    query_orig += c;
    if((toupper(c) < 'A' || toupper(c) > 'Z') && c != '.' && c != ','
        && c != '\\' && c != '[' && c != ']')
      return 1;
    in.get(c);
  }

  mlen = query_orig.length();
  // ----- if the last character is '\n', put it back to the stream in order
  // to be output at the next query -----
  if(c == '\n') in.putback(c);

  // ----- if mlen > 5, query_orig is not a valid word, return without
  // query_syntax -----
  if(mlen > 5)
    return 1;

  for(int i = 0; i < mlen; i++) 
    switch(toupper(query_orig[i])) {
      case '.':  m[i] = 56;  break;
      case ',':  m[i] = 55;  break;
      case '\'': m[i] = 27;  break;
      case '[':  m[i] = 45;  break;
      case ']':  m[i] = 46;  break;
      default:   m[i] = toupper(query_orig[i]) - 'A' + 1;
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
