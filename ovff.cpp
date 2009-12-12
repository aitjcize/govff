/* ovff.cpp

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

#define VERSION "1.4.1"

#include "FileMg.h"
#include "SQLite_Manage.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  if(argc != 2) {
    cout << "usage: ovff [file]" << endl;
    cout << "       ovff -v" << endl;
    exit(1);
  }

  if(!strcmp(argv[1], "-v")) {
    cout << "Ovff 嘸蝦米翻譯程式 Ver. " << VERSION << endl;
    cout << "Copyright (C) 2009 Aitjcize (Wei-Ning Huang)\n\
License GPLv2 <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
\n\
Written by Aitjcize (Wei-Ning Huang)." << endl;
    exit(0);
  }
  try {
    SQLiteMg ovff("boshiamy_t.db", argv[0]);
    FileMg handle(argv[1], 0);
    while(handle.next())
      ovff.query_and_write(handle);
    cout << "Ok!" << endl;
  }
  catch(std::exception& ex) {
    cout << "Ovff: " << ex.what() << endl;
  }
  return 0;
}
