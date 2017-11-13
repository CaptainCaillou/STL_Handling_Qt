#ifndef PART3D_H
#define PART3D_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class part3d
{
public:
  part3d();
  const GLfloat *constData() { return m_data.constData(); }
  int count() { return m_count; }
  int vertexCount() { return m_count / 6; }

private:
  QVector<GLfloat> m_data; // all the points
  int m_count; // nb of points

private:
  void add_3d_seg(const QVector3D &v, const QVector3D &n);
};
#endif // PART3D_H
