# #####################################################################
# Automatically generated by qmake (2.01a) Fri Jan 8 19:17:22 2010
# #####################################################################
TEMPLATE = app
TARGET = 
INCLUDEPATH += . \
    src \
    src/preferences
DESTDIR = bin
UI_DIR = build
UIC_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build

QMAKE_CXXFLAGS += -fno-show-column
QT += network
QT += sql

# Input
HEADERS += src/core/dbfredactor.h \
    src/dbfredactordelegate.h \
    src/dbfredactormainwindow.h \
    src/core/dbfredactormodel.h \
    src/dbfredactorpage.h \
    src/core/dbfredactorsortfilterproxymodel.h \
    src/filterdelegate.h \
    src/dialogs/filterdialog.h \
    src/dialogs/sortdialog.h \
    src/translationmanager.h \
    src/preferences/abstractpreferencespage.h \
    src/preferences/displaypreferences.h \
    src/preferences/globalpreferences.h \
    src/preferences/preferencesdialog.h \
    src/widgets/qtcolorbutton.h \
    src/widgets/qtfontbutton.h \
    src/dialogs/aboutdialog.h \
    src/3dparty/qtsingleapplication/src/qtlocalpeer.h \
    src/3dparty/qtsingleapplication/src/qtlockedfile.h \
    src/3dparty/qtsingleapplication/src/QtSingleApplication \
    src/3dparty/qtsingleapplication/src/qtsingleapplication.h \
    src/3dparty/qtsingleapplication/src/qtsinglecoreapplication.h \
    src/preferences/languagepreferences.h \
    src/dialogs/convertToSQLdialog.h \
    src/core/dbconfig.h \
    src/core/mysql_worker.h \
    src/core/dbf-thread.h \
    src/dialogs/stopProcessDialog.h
SOURCES += src/core/dbfredactor.cpp \
    src/dbfredactordelegate.cpp \
    src/dbfredactormainwindow.cpp \
    src/core/dbfredactormodel.cpp \
    src/core/dbfredactorsortfilterproxymodel.cpp \
    src/dialogs/filterdialog.cpp \
    src/main.cpp \
    src/dialogs/sortdialog.cpp \
    src/translationmanager.cpp \
    src/preferences/displaypreferences.cpp \
    src/preferences/globalpreferences.cpp \
    src/preferences/preferencesdialog.cpp \
    src/widgets/qtcolorbutton.cpp \
    src/widgets/qtfontbutton.cpp \
    src/dialogs/aboutdialog.cpp \
    src/3dparty/qtsingleapplication/src/qtlocalpeer.cpp \
    src/3dparty/qtsingleapplication/src/qtlockedfile_unix.cpp \
    src/3dparty/qtsingleapplication/src/qtlockedfile_win.cpp \
    src/3dparty/qtsingleapplication/src/qtlockedfile.cpp \
    src/3dparty/qtsingleapplication/src/qtsingleapplication.cpp \
    src/3dparty/qtsingleapplication/src/qtsinglecoreapplication.cpp \
    src/preferences/languagepreferences.cpp \
    src/dialogs/convertToSQLdialog.cpp \
    src/dialogs/stopProcessDialog.cpp
RESOURCES += resource.qrc
TRANSLATIONS += share/translations/qdbfredactor_ru.ts

OTHER_FILES += \
    src/3dparty/qtsingleapplication/src/qtsingleapplication.pri \
    src/3dparty/qtsingleapplication/src/qtsinglecoreapplication.pri
