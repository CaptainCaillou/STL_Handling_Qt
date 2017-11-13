#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>
#include <QTimer>
#include <iostream>

class process : public QThread
{
  Q_OBJECT
  virtual void run();
private:
  bool isRunning;
protected:
  int state;
};

#endif // PROCESS_H
