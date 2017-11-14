/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "logo.h"
#include <qmath.h>
#include <iostream>
#include "Types/datatypes.h"
Logo::Logo()
  : m_count(0)
{
  m_data.resize(2500 * 6);
  /*
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    for(int i = 0; i < 12; i+=9)
    {
      QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(g_vertex_buffer_data[i],g_vertex_buffer_data[i+1], g_vertex_buffer_data[i+2]));
      add(QVector3D(g_vertex_buffer_data[i],g_vertex_buffer_data[i+1], g_vertex_buffer_data[i+2]), n);
      m_count += 3;
    }
*

    const QVector3D v1(+0.06f,-0.14f,+0.14f);
    const QVector3D v2(+0.02f,-0.10f,-0.14f);
    const QVector3D v3(-0.02f,+0.2f,-0.05f);
    QVector3D n = QVector3D::normal(v1, v2);
    add(v3, n);
*/

  const QVector3D p1(+0.0f, +0.0f, +0.0f);
  const QVector3D p2(+0.1f, +0.1f, -0.5f);
  const QVector3D p3(+0.1f, +0.0f, -0.1f);
  const QVector3D p4(+0.0f, +0.1f, +0.0f);

  //triangle(p1, p2, p3);
  tetra(p1,p2,p3,p4);

  /*
  triangle(x1, y1, z1, x2, y2, z2, x4, y4, z4);
  triangle(x1, y1, z1, x3, y3, z3, x4, y4, z4);
  triangle(x2, y2, z2, x3, y3, z3, x4, y4, z4);
  */
}

void Logo::add(const QVector3D &v, const QVector3D &n)
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

void Logo::quad(GLfloat x1, GLfloat y1, GLfloat z1,
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

void Logo::triangle(const QVector3D p1,
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
void Logo::tetra(const QVector3D p1,
                 const QVector3D p2,
                 const QVector3D p3,
                 const QVector3D p4)
{
  triangle(p1, p2, p3);
  triangle(p1, p2, p4);
  triangle(p1, p3, p4);
  triangle(p2, p3, p4);
}
