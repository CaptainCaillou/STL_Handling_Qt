#ifndef GCODEGENERATOR_H
#define GCODEGENERATOR_H

#include <QThread>
#include <QTimer>
#include "process.h"
#include "Types/part.h"
#include "Types/layer.h"
#include "Types/segment.h"
#include "Types/toolpath.h"

class GCodeGenerator : public process
{

public:
  GCodeGenerator();
  void run() override;
  int  getState(void);

public:
  void setPart(part Part);
  void setFileUrl(QString fileUrl);
  std::vector<triangle> writeFile(QString text);

private:
  void optimize();

  QString fileUrl;
  part Part;
  FILE* file;
  std::vector<segment> layers;
  std::vector<toolPath> trajets;
  int state;
};

#endif // GCODEGENERATOR_H
