/**
 * ovff.cpp
 *
 * Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2 as published by the Free Software Foundation.
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
#include "SQLite_Manage.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#ifdef __linux__
  #include <errno.h>
#endif

#define VERSION "1.6.2"
#define DB_NAME "boshiamy_t.db"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

// ----- global flags ----- //
bool f_inputfile = false;
bool f_outputfile = false;

int main(int argc, char *argv[])
{
  FileMg::Mode mode = FileMg::DecodeMode;
  char *pInfile = 0, *pOutfile = 0;
  std::ostream* postream = &cout;
  std::istream* pistream = &cin;
  std::ifstream infile;
  std::ofstream outfile;

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '-' && strlen(argv[i]) == 2)
      switch(argv[i][1]) {
        case 'e':
          mode = FileMg::EncodeMode;
          break;
        case 'v':
          cout << "Ovff 嘸蝦米翻譯程式 Ver. " << VERSION << endl;
          cout << "Copyright (C) 2009 Aitjcize (Wei-Ning Huang)\n\
License GPLv2 <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\n\
Written by Aitjcize (Wei-Ning Huang)." << endl;
          exit(0);
        case 'h':
          cout << "usage: ovff [-e] [-i pInfile] [-o pOutfile]\n\
       ovff [-v] [-h]\n\n\
        -e      Encode mode, default mode is decode mode.\n\
        -i      Specify source filename, default is stdin\n\
        -o      Specify destination filename, default is stdout\n\
        -v      Show version info\n\
        -h      Show this help list\n\n\
Note: You can also pipe the data through ovff, for example:\n\
  ovff -i pInfile -o pOutfile\n\
can be written as:\n\
  ovff < pInfile > pOutfile\n\n\
Please report bugs to Aitjcize <aitjcize@gmail.com>" << endl;
          exit(0);
        case 'i':
          if(i == argc -1) {
            cerr << "error: option without a value: `" << argv[i] << "'."
              << endl;
            exit(1);
          }
          pInfile = argv[++i];
          f_inputfile = true;
          break;
        case 'o':
          if(i == argc -1) {
            cerr << "error: option without a value: `" << argv[i] << "'."
              << endl;
            exit(1);
          }
          pOutfile = argv[++i];
          f_outputfile = true;
          break;
        default:
          cerr << "Unknown option `" << argv[i] << "'." << endl;
          exit(1);
      }
    else {
      cerr << "Unknown option `" << argv[i] << "'." << endl;
      exit(1);
    }
  }

  // ----- check if the input and output file are the same ----- //
  if(f_inputfile && f_outputfile && strcmp(pInfile, pOutfile) == 0) {
    cerr << "Input filname should difference from the output filename." << endl;
    exit(1);
  }

  // ----- open output file stream ----- //
  if(f_inputfile) {
    infile.open(pInfile);
    pistream = &infile;
  }

  // ----- open input file stream ----- //
  if(f_outputfile) {
    outfile.open(pOutfile);
    postream = &outfile;
  }

  if(!infile) {
    cerr << "Failed to open `" << pInfile << "'." << endl;
#ifdef __linux__
    perror("");
#endif
    exit(1);
  }
  if(!outfile) {
    cerr << "Failed to open `" << pOutfile << "'." << endl;
#ifdef __linux__
    perror("");
#endif
    exit(1);
  }

  // ----- main loop ----- //
  try {
    SQLiteMg ovff(DB_NAME, argv[0]);
    FileMg handle(*pistream, *postream, mode);
    while(handle.next())
      ovff.query_and_write(handle);
  }
  catch(std::exception& ex) {
    cout << "Ovff: " << ex.what() << endl;
  }
  return 0;
}
