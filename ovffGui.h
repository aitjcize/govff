/**
 * ovffGui.h
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

#ifndef OVFFGUI_H
#define OVFFGUI_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "FileMg.h"

class ovffGui: public QWidget {

  Q_OBJECT

  public:
    ovffGui(QWidget* parent = 0, char* sArgv = NULL);

  public slots:
    void ToOvff();
    void ToChinese();
    void ClearText();
    void LoadFromFile();
    void SaveToFile();
    void About();

  protected:
    // Reimplement of QWidget::closeEvent()
    virtual void closeEvent(QCloseEvent *event);

  private:
    void TransToggle(FileMg::Mode mode = FileMg::DecodeMode);
    int _SaveToFile();

    char* sourceArgv;
    QPushButton* toOvffButton;
    QPushButton* toChineseButton;
    QPushButton* clearButton;
    QPushButton* loadFromFileButton;
    QPushButton* saveToFileButton;
    QPushButton* aboutButton;
    QTextEdit* textArea;
};

#endif
