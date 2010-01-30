/* FileMg.h

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

#ifndef FILEMG_H
#define FILEMG_H

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;

class FileMg {
  public:
    typedef enum _mode { DecodeMode, EncodeMode } Mode;

  private:
    Mode mode;
    string query_syntax;      // query syntax, set by make_syntax()
    string query_orig;        // original query word
    istream& in;
    ostream& out;

    // private member functions;
    void make_syntax(int* m, int mlen);
    friend class SQLiteMg;
    friend int callback(void* fg, int argc, char **argv, char **ColName);
    int next_decode(void);
    int next_encode(void);

  public:
    FileMg(istream& _in = std::cin, ostream& _out = std::cout,
        Mode md = EncodeMode): mode(md), in(_in), out(_out) {}
    FileMg(const FileMg& robj);
    FileMg& operator << (const char* chs);
    FileMg& operator << (const char ch);
    int next(void);
};

#endif
