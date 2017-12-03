#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>
#include <QTimer>
#include <iostream>
#include "Types/part.h"

class process : public QThread
{
  Q_OBJECT
private:
  bool isRunning;
protected:
  part Part;
  int state;
  virtual void run();
public:
  int getState();
  void setPart(part Part);
  part getPart(void);

};

#endif // PROCESS_H
