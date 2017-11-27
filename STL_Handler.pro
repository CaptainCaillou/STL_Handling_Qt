QT += widgets \
    opengl

@DEFINES += CORE_LIBRARY@

SOURCES += \
    main.cpp \
    Types/triangle.cpp \
    Types/layer.cpp \
    Types/segment.cpp \
    Process/process.cpp \
    Process/slicer.cpp \
    Process/filereader.cpp \
    Process/gcodegenerator.cpp \
    Types/part.cpp \
    mainwindow.cpp \
    Vue3D/glwidget.cpp\
    Vue3D/logo.cpp \
    Types/point.cpp

HEADERS += \
    Types/datatypes.h \
    Types/triangle.h \
    Types/layer.h \
    Types/segment.h \
    Process/process.h \
    Process/slicer.h \
    Process/filereader.h \
    Process/gcodegenerator.h \
    Types/part.h \
    mainwindow.h \
    Vue3D/glwidget.h\
    Vue3D/logo.h \
    Types/point.h

FORMS += \
    mainwindowbak.ui \
    mainwindow.ui

LIBS += -lOpengl32
