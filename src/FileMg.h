/**
 * FileMg.h
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
    int next_decode(void);
    int next_encode(void);

  public:
    FileMg(istream& _in = std::cin, ostream& _out = std::cout,
        Mode md = EncodeMode): mode(md), in(_in), out(_out) {}
    FileMg(const FileMg& robj);
    FileMg& operator << (const char* chs);
    FileMg& operator << (const char ch);
    int next(void);
    Mode getMode(void) { return mode; }
    string& r_query_syntax(void) { return query_syntax; }
    string& r_query_orig(void) { return query_orig; }
};

#endif
