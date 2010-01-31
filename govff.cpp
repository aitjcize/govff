/**
 * govff.cpp - Graphical interface for ovff
 *
 * Copyright (C) 2010 -  Wei-Ning Huang (AZ) <aitjcize@gmail.com>
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

#include <QtGui>
#include "ovffGui.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  ovffGui *govff = new ovffGui(0, argv[0]);
  govff->resize(640, 480);
  govff->show();
  return app.exec();
}
