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
private:
  QString fileUrl;
  FILE* file;
 // std::vector<toolPath> paths;

public:
  GCodeGenerator();
  void run() override;
  void setFileUrl(QString fileUrl);

private:
  void optimize(); //TODO: Implement this function

};

#endif // GCODEGENERATOR_H
