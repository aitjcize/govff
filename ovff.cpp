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

#include "FileMg.h"
#include "Ovff_Manage.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  if(argc == 1) {
    cout << "usage: ovff [file]" << endl;
    exit(1);
  }
  FileMg handle(argv[1], 0);
  Ovff ovff("boshiamy_t.db");
  while(handle.next())
    ovff.query_and_write(handle);
  cout << "Ok!" << endl;
  return 0;
}
