/* Ovff_Manage.h

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

#ifndef OVFF_MANAGE_H
#define OVFF_MANAGE_H

#include "FileMg.h"
#include <sqlite3.h>

class Ovff {
  private:
    char* db_name;
    sqlite3 *db;
    char* ErrMsg;

  public:
    Ovff(const char* db_name);
    Ovff(const Ovff& robj);
    ~Ovff();
    void query_and_write(FileMg& in);
    friend int callback(void* fg, int argc, char **argv, char **ColName);
};

#endif
