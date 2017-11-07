#ifndef PROCESS_H
#define PROCESS_H


class process
{
private:
  bool isRunning;
  int state;

public:
  int  getState();
  void kill();

public:
  process();
};

#endif // PROCESS_H
