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


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  part part_1;

  int state = 0;

  //first load the part
  fileReader* FileReader = new fileReader;
  FileReader->setPart(part_1);
  FileReader->setFileUrl("../STL_Handler/TestFiles/cubehole.STL");
  FileReader->start();
  for(int i = 0; !FileReader->isFinished() ; i++)
  {
    state =  FileReader->getState();
    if (state != -1)
      std::cout << "Reading in progress : " << state << std::endl;
    Sleep(1);
  }
  part_1 = FileReader->getPart();

  //free the memory
  delete FileReader;

  //slicing part
  Slicer* slicer = new Slicer;
  slicer->setPart(part_1);
  slicer->setSlicerWidth(0.0002);
  //then slice the part
  slicer->start();
  for(int i = 0; !slicer->isFinished() ; i++)
  {
    state =  slicer->getState();
    if (state != -1)
      std::cout << "Slice in progress : " << state << std::endl;
    Sleep(125);
  }

  //just for safety, but we normally don't need to wait
  slicer->wait();
  std::cout << "Slice finished" << std::endl;

  //then we copy the part sliced to our main part
  part_1 = slicer->getPart();

  //we free the memory
  delete slicer;

  return app.exec();
}
