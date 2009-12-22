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

#include <string>
#include "utils.h"

#ifdef WIN32
  #define SEP "\\"
#else
  #define SEP "/"
#endif


using std::string;

string dir_name(const char* cstr) {
  string tmp(cstr);
  return tmp.substr(0, tmp.find_last_of(SEP) +1);
}

string base_name(const char* cstr) {
  string tmp(cstr);
  return tmp.substr(tmp.find_last_of(SEP) +1, tmp.length());
}
