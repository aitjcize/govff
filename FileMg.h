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

using std::string;
using std::ifstream;
using std::ofstream;

class FileMg {
  private:
    string filename;
    bool mode;                // 0: decode, 1: encode
    string query_syntax;      // set by the `next' function
    ifstream fin;
    ofstream fout;
    int m[5];
    int mlen;
    int imode;
    // imode:
    //  1: normal, single word
    //  2: single word with a nextline character
    //  3: not a ovff word, maybe english or something else,
    //     return without query
    //  4: empty, print newline charactor

    // private member functions;
    void initialize(const char* fname, bool md);
    void make_syntax(void);
    friend class Ovff;

  public:
    FileMg(const char* fname, bool md);
    FileMg(const FileMg& robj);
    ~FileMg();
    FileMg& operator << (const char* chs);
    int next(void);
};

#endif
