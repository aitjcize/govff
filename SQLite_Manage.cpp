/* SQLite_Manage.cpp

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

#include "SQLite_Manage.h"
#include "FileMg.h"
#include "utils.h"
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int callback(void* fg, int argc, char **argv, char **ColName) {
  *static_cast<FileMg*>(fg) << (argv[0]);
  return 0;
}

SQLiteMg::SQLiteMg(const char* d_name, char* argv) {
  db_name = new char[strlen(d_name) +1];
  strcpy(db_name, d_name);
  string db_path(argv);
  db_path = dir_name(db_path.c_str()) + db_name;
  int rc = sqlite3_open_v2(db_path.c_str(), &db, SQLITE_OPEN_READONLY, NULL);

#ifndef WIN32 // linux only
  if(rc) {
    cout << "Can't open db - `" + db_path + "'." << endl;
    db_path = string("/usr/share/ovff/") + db_name;
    cout << "Trying " << db_path << "..." << endl;
    sqlite3_close(db);
    rc = sqlite3_open_v2(db_path.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
  }
#endif

  if(rc) {
    string msg = "Can't open db - `" + db_path + "'.";
    sqlite3_close(db);
    throw std::runtime_error(msg.c_str());
  }
}

SQLiteMg::SQLiteMg(const SQLiteMg& robj) {
  throw std::runtime_error("Copy of class SQLiteMg is not allowed, database can\
 only be opened once at a time.");
}

SQLiteMg::~SQLiteMg() {
  delete db_name;
  sqlite3_close(db);
}

void SQLiteMg::query_and_write(FileMg& in) {
  if(in.imode == 3) return;
  if(in.imode == 4) {
    in << "\n";
    return;
  }
  int rc = sqlite3_exec(db, in.query_syntax.c_str(), callback, &in, &ErrMsg);
  if(rc != SQLITE_OK) {
    string msg = "SQLiteMg: SQL error: " + string(ErrMsg);
    sqlite3_free(ErrMsg);
    throw std::runtime_error(msg.c_str());
  }
}
