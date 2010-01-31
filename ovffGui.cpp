/**
 * ovffGui.cpp
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
#include <QTextCodec>
#include <QCoreApplication>
#include <string>
#include <sstream>
#include <stdexcept>

#include "ovffGui.h"
#include "FileMg.h"
#include "SQLite_Manage.h"

#define DB_NAME "boshiamy_t.db"

ovffGui::ovffGui(QWidget* parent, char* sArgv)
  : QWidget(parent), sourceArgv(sArgv), nextMode(FileMg::DecodeMode) {
  QLabel* label = new QLabel(tr("Text:"));
  textArea = new QTextEdit;

  toOvffButton = new QPushButton(tr("To OVFF"));
  toOvffButton->hide();
  toChineseButton = new QPushButton(tr("To Chinese"));
  toChineseButton->show();
  clearButton = new QPushButton(tr("Clear"));
  clearButton->show();
  loadFromFileButton = new QPushButton(tr("Load"));
  loadFromFileButton->show();
  saveToFileButton = new QPushButton(tr("Save"));
  saveToFileButton->show();
  aboutButton = new QPushButton(tr("About"));
  aboutButton->show();

  // ----- Connect singals and slots -----
  connect(toOvffButton, SIGNAL(clicked()), this, SLOT(TransToggle()));
  connect(toChineseButton, SIGNAL(clicked()), this, SLOT(TransToggle()));
  connect(clearButton, SIGNAL(clicked()), this, SLOT(ClearText()));
  connect(loadFromFileButton, SIGNAL(clicked()), this, SLOT(LoadFromFile()));
  connect(saveToFileButton, SIGNAL(clicked()), this, SLOT(SaveToFile()));
  connect(aboutButton, SIGNAL(clicked()), this, SLOT(About()));

  // ----- Manage layout -----
  QHBoxLayout* button_layout = new QHBoxLayout;
  button_layout->addWidget(toOvffButton);
  button_layout->addWidget(toChineseButton);
  button_layout->addWidget(clearButton);
  button_layout->addWidget(loadFromFileButton);
  button_layout->addWidget(saveToFileButton);
  button_layout->addWidget(aboutButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label);
  mainLayout->addWidget(textArea); 
  mainLayout->addLayout(button_layout);
  setLayout(mainLayout);
  setWindowTitle(tr("Ovff Liu IME Translate Program"));
}

void ovffGui::TransToggle(void) {
  QString inputText = textArea->toPlainText();
  std::string inputText_string = inputText.toStdString();
  std::istringstream gin(inputText_string);
  std::ostringstream gout;

  try {
    SQLiteMg ovff(DB_NAME, sourceArgv);
    FileMg handle(gin, gout, nextMode);
    while(handle.next()) 
      ovff.query_and_write(handle);
    textArea->setText(QString().fromStdString(gout.str()));
  } catch(std::exception& ex) {
    QMessageBox::critical(this, tr("Error"), tr(ex.what()));
    QCoreApplication::exit(1);
  }

  // Toggle next Mode
  if(nextMode == FileMg::DecodeMode)
    nextMode = FileMg::EncodeMode;
  else
    nextMode = FileMg::DecodeMode;
  updateInterface();
}

void ovffGui::LoadFromFile(void) {
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Load text from file"), "",
      tr("All Files (*)"));
  if(fileName.isEmpty())
    return;
  else {
    QString fileText;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
      return;
    }
    fileText = file.readAll();
    textArea->setText(fileText);
  }
}

void ovffGui::SaveToFile(void) {
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save text to file"), "",
      tr("All Files (*)"));
  if(fileName.isEmpty())
    return;
  else {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
      return;
    }
    file.write(textArea->toPlainText().toAscii());
  }
}

void ovffGui::ClearText(void) {
  textArea->clear();
  return;
}

void ovffGui::About(void) {
  QMessageBox::about(this, tr("About"), tr("OVFF Liu Input Method \
Translate Program\nby AZ (Wei-Ning Huang) <aitjcize@gmail.com>"));
  return;
}

void ovffGui::updateInterface(void) {
  if(nextMode == FileMg::DecodeMode) {
    toOvffButton->hide();
    toChineseButton->show();
  }
  else {
    toOvffButton->show();
    toChineseButton->hide();
  }
}
