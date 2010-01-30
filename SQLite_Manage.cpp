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
#include <cstdlib>      // for atoi()

using std::string;

int callback(void* fg, int argc, char **argv, char **ColName) {
  FileMg* file = static_cast<FileMg*>(fg);
  if(file->mode == 0)
    *file << (argv[0]);
  else {
    for(int i = 0; i < argc; i++)
      if(argv[i] != NULL) {
        char c = static_cast<char>(atoi(argv[i]));
        switch(c) {
          case 56: c = '.';  break;
          case 55: c = ',';  break;
          case 27: c = '\''; break;
          case 45: c = '[';  break;
          case 46: c = ']';  break;
          default: c = c -1 + 'A';
        }
        *file << c;
      }
    *file << ' ';
  }
  // ----- clear string to mark as proccessed ----- //
  file->query_orig.clear();
  return 0;
}

SQLiteMg::SQLiteMg(const char* d_name, char* argv) {
  db_name = new char[strlen(d_name) +1];
  strcpy(db_name, d_name);
  string db_path(argv);
  db_path = dir_name(db_path.c_str()) + db_name;
  int rc = sqlite3_open_v2(db_path.c_str(), &db, SQLITE_OPEN_READONLY, NULL);

#ifdef __linux__
  if(rc) {
    db_path = string("/usr/share/ovff/") + db_name;
    sqlite3_close(db);
    rc = sqlite3_open_v2(db_path.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
  }
#endif

  if(rc) {
    string msg = string("Can't find db - `") + d_name + "'.";
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
  // ----- if query syntax not set, the word is invalid, output the original
  // text then return -----
  if(in.query_syntax.length() == 0) {
    in << in.query_orig.c_str();
    return;
  }
  int rc = sqlite3_exec(db, in.query_syntax.c_str(), callback, &in, &ErrMsg);
  if(rc != SQLITE_OK) {
    string msg = "SQLiteMg: SQL error: " + string(ErrMsg);
    sqlite3_free(ErrMsg);
    throw std::runtime_error(msg.c_str());
  }
  // ----- if query_orig is not cleared menas callback is not called, output
  // original word then exit -----
  if(in.query_orig.length() != 0)
    in << in.query_orig.c_str() << ' ';
}
