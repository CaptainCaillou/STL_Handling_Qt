#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>
#include <QTimer>
#include <iostream>

class process : public QThread
{
  Q_OBJECT
private:
  bool isRunning;
protected:
  int state;
  virtual void run();
};

#endif // PROCESS_H
