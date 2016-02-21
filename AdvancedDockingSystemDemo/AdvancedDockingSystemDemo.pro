TARGET = AdvancedDockingSystemDemo

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += $$PWD/src

greaterThan(QT_MAJOR_VERSION, 4): DEFINES += ADS_NAMESPACE_ENABLED

windows {
	# MinGW
	*-g++* {
		QMAKE_CXXFLAGS += -std=c++11
	}
	# MSVC
	*-msvc* {
	}
}

SOURCES += \
	src/main.cpp \
	src/mainwindow.cpp \
	src/icontitlewidget.cpp

HEADERS += \
	src/mainwindow.h \
	src/icontitlewidget.h

FORMS += \
	src/mainwindow.ui


# Dependency: AdvancedDockingSystem
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/release/ -lAdvancedDockingSystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/debug/ -lAdvancedDockingSystem
else:unix: LIBS += -L$$OUT_PWD/../AdvancedDockingSystem/ -lAdvancedDockingSystem

INCLUDEPATH += $$PWD/../AdvancedDockingSystem/include
DEPENDPATH += $$PWD/../AdvancedDockingSystem/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/libAdvancedDockingSystem.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/libAdvancedDockingSystem.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/release/AdvancedDockingSystem.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/debug/AdvancedDockingSystem.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../AdvancedDockingSystem/libAdvancedDockingSystem.a

# Dependency: LayoutManager
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LayoutManager/release/ -lLayoutManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LayoutManager/debug/ -lLayoutManager
else:unix: LIBS += -L$$OUT_PWD/../LayoutManager/ -lLayoutManager

INCLUDEPATH += $$PWD/../LayoutManager
DEPENDPATH += $$PWD/../LayoutManager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LayoutManager/release/libLayoutManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LayoutManager/debug/libLayoutManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LayoutManager/release/LayoutManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LayoutManager/debug/LayoutManager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../LayoutManager/libLayoutManager.a
