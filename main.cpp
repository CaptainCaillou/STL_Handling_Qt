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
  int state = 0;

  //first load the part
  fileReader* FileReader = new fileReader;
  //FileReader->setPart(part_1);
  //FileReader->setFileUrl("../STL_Handler/TestFiles/cubehole.STL");
  //FileReader->start();
  //for(int i = 0; !FileReader->isFinished() ; i++)
  //{
  //  state =  FileReader->getState();
   // if (state != -1)
   //   std::cout << "Reading in progress : " << state << std::endl;
   // Sleep(1);
 // }

  //free the memory
  delete FileReader;

  return app.exec();
}
