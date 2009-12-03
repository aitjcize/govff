/* Ovff_Manage.cpp

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

#include "Ovff_Manage.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

using std::string;

int callback(void* fg, int argc, char **argv, char **ColName) {
  *static_cast<FileMg*>(fg) << (argv[0]);
  return 0;
}

Ovff::Ovff(const char* d_name) {
  db_name = new char[strlen(d_name) +1];
  strcpy(db_name, d_name);
  int rc = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READONLY, NULL);
  if(rc) {
    string msg = "Ovff: can't open db - `" + string(db_name) + "'.";
    sqlite3_close(db);
    throw std::runtime_error(msg.c_str());
  }
}

Ovff::Ovff(const Ovff& robj) {
  db_name = new char[strlen(robj.db_name) +1];
  strcpy(db_name, robj.db_name);
  int rc = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READONLY, NULL);
  if(rc) {
    string msg = "Ovff: can't open db - `" + string(db_name) + "'.";
    sqlite3_close(db);
    throw std::runtime_error(msg.c_str());
  }
}

Ovff::~Ovff() {
  delete db_name;
  sqlite3_close(db);
}

void Ovff::query_and_write(FileMg& in) {
  if(in.imode == 3) return;
  if(in.imode == 4) {
    in << "\n";
    return;
  }
  int rc = sqlite3_exec(db, in.query_syntax.c_str(), callback, &in, &ErrMsg);
  if(rc != SQLITE_OK) {
    string msg = "Ovff: SQL error: " + string(ErrMsg);
    sqlite3_free(ErrMsg);
    throw std::runtime_error(msg.c_str());
  }
}
