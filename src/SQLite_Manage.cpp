/**
 * SQLite_Manage.h
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

#include "SQLite_Manage.h"
#include "FileMg.h"
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cstdlib>      // for atoi()

using std::string;

int callback(void* fg, int argc, char **argv, char**) {
  FileMg* file = static_cast<FileMg*>(fg);
  if(file->getMode() == FileMg::DecodeMode)
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
  file->r_query_orig().clear();
  return 0;
}

SQLiteMg::SQLiteMg(const char* db_path) {
  int rc = sqlite3_open_v2(db_path, &db, SQLITE_OPEN_READONLY, NULL);
  if(rc) {
    string msg = string("Can't find db - `") + db_path + "'.";
    sqlite3_close(db);
    throw std::runtime_error(msg.c_str());
  }
}

SQLiteMg::SQLiteMg(const SQLiteMg&) {
  throw std::runtime_error("Copy of class SQLiteMg is not allowed, database can\
 only be opened once at a time.");
}

SQLiteMg::~SQLiteMg() {
  sqlite3_close(db);
}

void SQLiteMg::query_and_write(FileMg& in) {
  // ----- if query syntax not set, the word is invalid, output the original
  // text then return -----
  if(in.r_query_syntax().length() == 0) {
    in << in.r_query_orig().c_str();
    return;
  }
  int rc = sqlite3_exec(db, in.r_query_syntax().c_str(), callback, &in,&ErrMsg);
  if(rc != SQLITE_OK) {
    string msg = "SQLiteMg: SQL error: " + string(ErrMsg);
    sqlite3_free(ErrMsg);
    throw std::runtime_error(msg.c_str());
  }
  // ----- if r_query_orig() is not cleared means callback was not called,
  // output original word then exit -----
  if(in.r_query_orig().length() != 0)
    in << in.r_query_orig().c_str() << ' ';
}
