#include "part3d.h"

part3d::part3d()
        : m_count(0)
{
  //we set the maximum number of segments
  m_data.resize(2500 * 6);

}

void part3d::add_3d_seg(const QVector3D &v, const QVector3D &n)
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

void part3d::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add_3d_seg(QVector3D(x1, y1, -0.05f), n);
    add_3d_seg(QVector3D(x4, y4, -0.05f), n);
    add_3d_seg(QVector3D(x2, y2, -0.05f), n);

    add_3d_seg(QVector3D(x3, y3, -0.05f), n);
    add_3d_seg(QVector3D(x2, y2, -0.05f), n);
    add_3d_seg(QVector3D(x4, y4, -0.05f), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add_3d_seg(QVector3D(x4, y4, 0.05f), n);
    add_3d_seg(QVector3D(x1, y1, 0.05f), n);
    add_3d_seg(QVector3D(x2, y2, 0.05f), n);

    add_3d_seg(QVector3D(x2, y2, 0.05f), n);
    add_3d_seg(QVector3D(x3, y3, 0.05f), n);
    add_3d_seg(QVector3D(x4, y4, 0.05f), n);
}

void part3d::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add_3d_seg(QVector3D(x1, y1, +0.05f), n);
    add_3d_seg(QVector3D(x1, y1, -0.05f), n);
    add_3d_seg(QVector3D(x2, y2, +0.05f), n);

    add_3d_seg(QVector3D(x2, y2, -0.05f), n);
    add_3d_seg(QVector3D(x2, y2, +0.05f), n);
    add_3d_seg(QVector3D(x1, y1, -0.05f), n);
}
