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
#include "Types/triangle.h"


Logo::Logo()
  : m_count(0)
{
  m_data.resize(200000 * 6);

  grid_x_start_index = vertexCount();
  for(int i = -10; i <= 10; i++)
  {
    d_line(QVector3D(i,-10,0),QVector3D(i,10,0)); // the x lines
  }
  grid_x_end_index = vertexCount();
  grid_y_start_index = vertexCount();
  for(int i = -10; i <= 10; i++)
  {
    d_line(QVector3D(-10,i,0),QVector3D(10,i,0)); // the x lines
  }
  grid_y_end_index = vertexCount();
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

void Logo::d_line(const QVector3D p1, const QVector3D p2)
{
  QVector3D n = QVector3D::normal(p2-p1, p2-p1);
  add(p1,n);
  add(p2,n);
  n = QVector3D::normal(p1-p2, p1-p2);
  add(p1,n);
  add(p2,n);
}
void Logo::d_triangle(const QVector3D p1,
                    const QVector3D p2,
                    const QVector3D p3) {
  QVector3D n = QVector3D::normal(p3-p1, p2-p1);

  add(p1, n);
  add(p3, n);
  add(p2, n);

  add(p1, n);
  add(p2, n);
  add(p3, n);

  n = QVector3D::normal(p1-p3, p2-p1);
  add(p1, n);
  add(p3, n);
  add(p2, n);

  add(p1, n);
  add(p2, n);
  add(p3, n);
}

void Logo::tetra(const QVector3D p1,
                 const QVector3D p2,
                 const QVector3D p3,
                 const QVector3D p4)
{
  d_triangle(p1, p2, p3);
  d_triangle(p1, p2, p4);
  d_triangle(p1, p3, p4);
  d_triangle(p2, p3, p4);
}

void Logo::displayPart(part Part)
{
  m_count = grid_y_end_index * 6;
  std::vector<triangle> triangles = Part.getTriangles();
  part1_start_index = vertexCount();

  std::cout << "Nb of triangles" << triangles.size() << std::endl;
  for(unsigned int i = 0; i < triangles.size(); i++)
  {
    d_triangle(triangles[i].p1.to3dVector(),triangles[i].p2.to3dVector(),triangles[i].p3.to3dVector());
  }
  part1_end_index = vertexCount();
  std::cout << "Part from:" << part1_start_index << "to: " << part1_end_index << " Total of " << (part1_end_index - part1_start_index)/6 << " triangles." << std::endl;
}

void Logo::diplayLayers(part Part)
{
  m_count = grid_y_end_index * 6;
  part1_start_index = vertexCount();
  std::vector<layer> layers = Part.getLayers();

  for(unsigned int i = 0; i < layers.size(); i ++) {
    for(unsigned int j = 0; j < layers[i].contours.size(); j++) {
      d_line(layers[i].contours[j].p1.to3dVector(), layers[i].contours[j].p2.to3dVector());
    }
  }
  part1_end_index = vertexCount();
}
