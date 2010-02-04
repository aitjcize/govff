/**
 * ovffGui.cpp
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

#include <QtGui>
#include <string>
#include <sstream>
#include <stdexcept>

#include "ovffGui.h"
#include "FileMg.h"
#include "SQLite_Manage.h"
#include "resource.h"

ovffGui::ovffGui(QWidget* parent)
  : QWidget(parent) {
  QLabel* label = new QLabel(tr("Text:"));
  textArea = new QPlainTextEdit;

  toChineseButton = new QPushButton(tr("To Chinese"));
  toOvffButton = new QPushButton(tr("To OVFF"));
  clearButton = new QPushButton(tr("Clear"));
  loadFromFileButton = new QPushButton(tr("Load"));
  saveAsFileButton = new QPushButton(tr("Save As"));
  aboutButton = new QPushButton(tr("About"));

  // ----- Connect singals and slots -----
  connect(toChineseButton, SIGNAL(clicked()), this, SLOT(ToChinese()));
  connect(toOvffButton, SIGNAL(clicked()), this, SLOT(ToOvff()));
  connect(clearButton, SIGNAL(clicked()), this, SLOT(ClearText()));
  connect(loadFromFileButton, SIGNAL(clicked()), this, SLOT(LoadFromFile()));
  connect(saveAsFileButton, SIGNAL(clicked()), this, SLOT(SaveAsFile()));
  connect(aboutButton, SIGNAL(clicked()), this, SLOT(About()));

  // ----- Manage layout -----
  QHBoxLayout* button_layout = new QHBoxLayout;
  button_layout->addWidget(toChineseButton);
  button_layout->addWidget(toOvffButton);
  button_layout->addWidget(clearButton);
  button_layout->addWidget(loadFromFileButton);
  button_layout->addWidget(saveAsFileButton);
  button_layout->addWidget(aboutButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label);
  mainLayout->addWidget(textArea); 
  mainLayout->addLayout(button_layout);
  setLayout(mainLayout);
  setWindowTitle(tr("Ovff Liu IME Translate Program"));
}

void ovffGui::ToOvff(void) {
  TransToggle(FileMg::EncodeMode);
}

void ovffGui::ToChinese(void) {
  TransToggle(FileMg::DecodeMode);
}

void ovffGui::TransToggle(FileMg::Mode mode) {
  QString inputText = textArea->toPlainText();
  std::string inputText_string = inputText.toStdString();
  std::istringstream gin(inputText_string);
  std::ostringstream gout;

  try {
    SQLiteMg ovff(RESOURCE_PATH "database" SEP "boshiamy_t.db");
    FileMg handle(gin, gout, mode);
    while(handle.next()) 
      ovff.query_and_write(handle);
    textArea->setPlainText(QString().fromStdString(gout.str()));
  } catch(std::exception& ex) {
    QMessageBox::critical(this, tr("Error"), tr(ex.what()));
    QCoreApplication::exit(1);
  }
  textArea->document()->setModified(true);
  UpdateClipboard();
}

void ovffGui::LoadFromFile(void) {
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Load text from file"), "",
      tr("All Files (*)"));
  if(fileName.isEmpty())
    return;

  QFile file(fileName);
  if(!file.open(QIODevice::ReadOnly)) {
    QMessageBox::information(this, tr("Unable to open file"),
        file.errorString());
    return;
  }
  textArea->setPlainText(file.readAll());
}

void ovffGui::SaveAsFile(void) {
  _SaveAsFile();
  textArea->document()->setModified(false);
}

int ovffGui::_SaveAsFile(void) {
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save text to file"), "",
      tr("All Files (*)"));
  if(fileName.isEmpty())
    return true;
  else {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
      return true;
    }
    file.write(textArea->toPlainText().toAscii());
  }
  return false;
}

void ovffGui::ClearText(void) {
  textArea->clear();
  return;
}

void ovffGui::About(void) {
  QMessageBox about(this);
  about.setWindowTitle(tr("About"));
  about.setText(tr("OVFF Liu Input Method Translate Program\n"
        "by AZ (Wei-Ning Huang) <aitjcize@gmail.com>"));
  about.setIconPixmap(QPixmap(":/images/govff.png"));
  about.exec();
  return;
}

void ovffGui::closeEvent(QCloseEvent *event) {
  if(textArea->toPlainText().length() && textArea->document()->isModified()) {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Warning"),
        tr("The text area contains modified text.\n"
          "Do you want to save it?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if(ret == QMessageBox::Save) {
      if(_SaveAsFile() == false)
        event->accept();
      else
        event->ignore();
    }
    else if(ret == QMessageBox::Cancel)
      event->ignore();
    else if(ret == QMessageBox::Discard)
      event->accept();
  }
  else
    event->accept();
  return;
}

void ovffGui::UpdateClipboard(void) {
  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(textArea->toPlainText(), QClipboard::Clipboard);
#ifdef Q_OS_LINUX
  // Linux mouse selection clipboard support
  clipboard->setText(textArea->toPlainText(), QClipboard::Selection);
#endif
}
