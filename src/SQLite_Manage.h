/**
 * SQLite_Manage.cpp
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

#ifndef OVFF_MANAGE_H
#define OVFF_MANAGE_H

#include "FileMg.h"
#include <sqlite3.h>

class SQLiteMg {
  private:
    sqlite3 *db;
    char* ErrMsg;
    bool query_success;

  public:
    SQLiteMg(const char* db_path);
    SQLiteMg(const SQLiteMg& robj);
    ~SQLiteMg();
    void query_and_write(FileMg& in);
};

#endif
