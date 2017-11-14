#include "part3d.h"

part3d::part3d()
        : m_count(0)
      {
        m_data.resize(2500 * 6);

        const QVector3D p11(+0.0f, +0.0f, +0.0f);
        const QVector3D p21(+0.1f, +0.1f, +0.1f);
        const QVector3D p31(+0.1f, +0.0f, +0.0f);
        const QVector3D p41(+0.0f, +0.1f, +0.0f);

        triangle(p11, p21, p31);
        //tetra(p1,p2,p3,p4);

        /*
        triangle(x1, y1, z1, x2, y2, z2, x4, y4, z4);
        triangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);
        triangle(x2, y2, z2, x3, y3, z3, x4, y4, z4);
        */
      }

void part3d::add(const QVector3D &v, const QVector3D &n)
{
  GLfloat *p = m_data.data() + m_count;
  *p++ = v.x();
  *p++ = v.y();
  *p++ = v.z();
  *p++ = n.x();
  *p++ = n.y();
  *p++ = n.z();
  m_count += 6;
}

void part3d::quad(GLfloat x1, GLfloat y1, GLfloat z1,
                GLfloat x2, GLfloat y2, GLfloat z2,
                GLfloat x3, GLfloat y3, GLfloat z3,
                GLfloat x4, GLfloat y4, GLfloat z4)
{
  QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, z4 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

  add(QVector3D(x1, y1, z1), n);
  add(QVector3D(x4, y4, z4), n);
  add(QVector3D(x2, y2, z2), n);

  add(QVector3D(x3, y3, z3), n);
  add(QVector3D(x2, y2, z2), n);
  add(QVector3D(x4, y4, z4), n);

  n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

  add(QVector3D(x4, y4, z4), n);
  add(QVector3D(x1, y1, z1), n);
  add(QVector3D(x2, y2, z2), n);

  add(QVector3D(x2, y2, z2), n);
  add(QVector3D(x3, y3, z3), n);
  add(QVector3D(x4, y4, z4), n);
}

void part3d::triangle(const QVector3D p1,
                    const QVector3D p2,
                    const QVector3D p3) {
  QVector3D n = QVector3D::normal(p3-p1, p2-p1);

  add(p1, n);
  add(p3, n);
  add(p2, n);

  add(p3, n);
  add(p2, n);
  add(p1, n);


  n = QVector3D::normal(p1-p3, p2-p1);

  add(p3, n);
  add(p1, n);
  add(p2, n);

  add(p2, n);
  add(p3, n);
  add(p1, n);
}
/*
void Logo::triangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, z4 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x4, y4, z4), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);
}
*/
void part3d::tetra(const QVector3D p1,
                 const QVector3D p2,
                 const QVector3D p3,
                 const QVector3D p4)
{
  triangle(p1, p2, p3);
  triangle(p1, p2, p4);
  triangle(p1, p3, p4);
  triangle(p2, p3, p4);
}
