QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HybridMenubar/customeffectedmenu.cpp \
    HybridMenubar/custommenubarextension.cpp \
    HybridMenubar/flatbutton.cpp \
    HybridMenubar/hybridmenubar.cpp \
    HybridMenubar/menuactionproxystyle.cpp \
    HybridMenubar/menubarwidget.cpp \
    HybridMenubar/titlepartwidget.cpp \
    HybridMenubar/titlerightbuttons.cpp \
    ResizableLayout/horizontallinehandle.cpp \
    ResizableLayout/linehandle.cpp \
    ResizableLayout/resizableqhboxlayout.cpp \
    ResizableLayout/resizableqvboxlayout.cpp \
    ResizableLayout/verticallinehandle.cpp \
    SideMenubar/sidemenubar.cpp \
    SideMenubar/sidemenubarbutton.cpp \
    SideMenubar/sidemenuplane.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    HybridMenubar/customeffectedmenu.h \
    HybridMenubar/custommenubarextension.h \
    HybridMenubar/flatbutton.h \
    HybridMenubar/hybridmenubar.h \
    HybridMenubar/menuactionproxystyle.h \
    HybridMenubar/menubarwidget.h \
    HybridMenubar/titlepartwidget.h \
    HybridMenubar/titlerightbuttons.h \
    ResizableLayout/horizontallinehandle.h \
    ResizableLayout/linehandle.h \
    ResizableLayout/resizableqhboxlayout.h \
    ResizableLayout/resizableqvboxlayout.h \
    ResizableLayout/verticallinehandle.h \
    SideMenubar/sidemenubar.h \
    SideMenubar/sidemenubarbutton.h \
    SideMenubar/sidemenuplane.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

LIBS += \
    -ldwmapi

RC_ICONS = icons/vscode_icon.ico
