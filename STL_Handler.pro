QT += widgets

SOURCES += \
    main.cpp \
    Types/triangle.cpp \
    Types/layer.cpp \
    Types/segment.cpp \
    Process/process.cpp \
    Process/slicer.cpp \
    Process/filereader.cpp \
    Process/gcodegenerator.cpp \
    Types/part.cpp

HEADERS += \
    Types/datatypes.h \
    Types/triangle.h \
    Types/layer.h \
    Types/segment.h \
    Process/process.h \
    Process/slicer.h \
    Process/filereader.h \
    Process/gcodegenerator.h \
    Types/part.h

FORMS += \
    mainwindow.ui
