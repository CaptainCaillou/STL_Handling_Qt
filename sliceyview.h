#ifndef SLICEYVIEW_H
#define SLICEYVIEW_H

#include <QWidget>
#include "QTGui/QOpenGLFunctions"
#include "QTGui/QOpenGLContext"
#include "QTGui/QPainter"
#include <QGLWidget>

class SliceyView : public QGLWidget
{
    Q_OBJECT
public:
    SliceyView(QWidget* parent = 0);
    ~SliceyView();

   // void initializeGL();
protected:
    void paintGL();
    //void resizeGL();

private :
    float distance = -5.0;
    float xRot = 0;
    float yRot = 0;
    float zRot = 0;
    QOpenGLFunctions *f;
};

#endif // SLICEYVIEW_H
