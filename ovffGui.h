/**
 * ovffGui.h
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

#ifndef OVFFGUI_H
#define OVFFGUI_H

#include <QWidget>
#include "FileMg.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QPushButton;
QT_END_NAMESPACE

class ovffGui: public QWidget {

  Q_OBJECT

  public:
    ovffGui(QWidget* parent = 0, char* sArgv = NULL);

  public slots:
    void TransToggle();
    void ClearText();
    void LoadFromFile();
    void SaveToFile();
    void About();

  private:
    void updateInterface(void);
    char* sourceArgv;
    FileMg::Mode nextMode;
    QPushButton* toOvffButton;
    QPushButton* toChineseButton;
    QPushButton* clearButton;
    QPushButton* loadFromFileButton;
    QPushButton* saveToFileButton;
    QPushButton* aboutButton;
    QTextEdit* textArea;
};

#endif
