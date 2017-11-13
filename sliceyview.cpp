#include "sliceyview.h"

SliceyView::SliceyView(QWidget* parent){
    //QGLWidget(parent);
    qglClearColor(Qt::darkGray); // ou avec glClearColor
    glEnable(GL_DEPTH_TEST);
}

SliceyView::~SliceyView() {
   // ~QGLWidget();
};

void SliceyView::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   //gluLookAt(0.0, 0.0, -distance,    0.0, 0.0, 0.0,    0.0, 1.0, 0.0);

    glRotatef(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // On affiche un simple repère
    glBegin(GL_LINES);
        glColor3d(1,0,0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3d(0,0,1);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        glColor3d(0,1,0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}
