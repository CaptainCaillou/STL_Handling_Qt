QT += widgets

SOURCES += \
    main.cpp \
    FileHandling/stlfileobject.cpp \
    Types/triangle.cpp \
    Types/layer.cpp \
    Types/segment.cpp \
    Printer/printer.cpp \
    mainwindow.cpp

HEADERS += \
    stlfileobject.h \
    Types/datatypes.h \
    Types/triangle.h \
    Types/layer.h \
    Types/segment.h \
    Printer/printer.h \
    mainwindow.h

FORMS += \
    mainwindowbak.ui \
    mainwindow.ui
