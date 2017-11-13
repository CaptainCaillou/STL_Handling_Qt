#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>
#include <QFuture>

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <windows.h>

#include "Process/filereader.h"
#include "Types/datatypes.h"
#include "Types/segment.h"
#include "Types/layer.h"
#include "Printer/printer.h"

#include "Types/part.h"

#include "Process/slicer.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow ui;
  ui.show();

  return app.exec();
}
