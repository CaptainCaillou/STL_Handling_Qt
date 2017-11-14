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
  void add_3d_seg(const QVector3D &v, const QVector3D &n);
  void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
  void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
  QVector<GLfloat> m_data; // all the points

private:
  int m_count; // nb of points

private:
};
#endif // PART3D_H
