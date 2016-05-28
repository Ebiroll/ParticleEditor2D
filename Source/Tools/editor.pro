DEFINES += "LINUX"
DEFINES += "VSG_USE_NATIVE_STL"
OSFLAG=linux
CONFIG += release

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += include
INCLUDEPATH += ../../assimp/include/
INCLUDEPATH += ../../glm/
INCLUDEPATH += ../../soil/
INCLUDEPATH += ../../
#INCLUDEPATH += S:\work\glew-1.12.0\include
INCLUDEPATH += ../glew/include
INCLUDEPATH += /home/olas/work/si_vis/glfw/include
INCLUDEPATH += /home/olas/work/si_vis/glew/include


SOURCES +=  ParticleEditor2D/ColorVarianceEditor.cpp \
   ParticleEditor2D/EmitterAttributeEditor.cpp \
   ParticleEditor2D/FloatEditor.cpp \
   ParticleEditor2D/IntEditor.cpp \
   ParticleEditor2D/Main.cpp \
   ParticleEditor2D/MainWindow.cpp \
   ParticleEditor2D/ParticleAttributeEditor.cpp \
   ParticleEditor2D/ParticleEditor.cpp \
   ParticleEditor2D/ParticleEffectEditor.cpp \
   ParticleEditor2D/ScrollAreaWidget.cpp \
   ParticleEditor2D/ValueVarianceEditor.cpp \
   ParticleEditor2D/Vector2Editor.cpp \
    particle_fx_manager.cpp \
    rt_particles.cpp \
    rt_gl.cpp \
    glwidget.cpp


HEADERS += ParticleEditor2D/ColorVarianceEditor.h \
ParticleEditor2D/EmitterAttributeEditor.h \
ParticleEditor2D/FloatEditor.h \
ParticleEditor2D/IntEditor.h \
ParticleEditor2D/MainWindow.h \
ParticleEditor2D/ParticleAttributeEditor.h \
ParticleEditor2D/ParticleEditor.h \
ParticleEditor2D/ParticleEffectEditor.h \
ParticleEditor2D/ScrollAreaWidget.h \
ParticleEditor2D/ValueVarianceEditor.h \
ParticleEditor2D/Vector2Editor.h \
    particle_fx.h \
    particle_fx_manager.h \
    rt_core.h \
    glwidget.h


RESOURCES     = ParticleEditor2D/Resources.qrc

RESOURCES     += ParticleEditor2D/style.qrc

RESOURCES     += textures.qrc

!win32 {
#SOURCES += ../engine/src/engine/sysglx.cpp
}

win32 {
#SOURCES += ../engine/src/engine/syswgl.cpp
}





!win32 {
#SOURCES += ../engine/src/core/core_posix.cpp
}

win32 {

#SOURCES += ../engine/src/core/core_win32.cpp

#HEADERS += ../engine/src/core/time.h\
#    ../engine/src/core/math.h

}

win32 {
QMAKE_CXXFLAGS += -m32 -msse -mwindows
DEFINES -= UNICODE
LIBS += -LS:\work\glew-1.12.0\lib\ -lglew32
QT += opengl
LIBS  += -lopengl32 -lgdi32
#LIBS += -L../engine/lib -lglew32
LIBS += S:\QT\Tools\mingw491_32\i686-w64-mingw32\lib\libws2_32.a
#LIBS += S:\work\glew-1.12.0\lib\libglew32.a
QMAKE_CXXFLAGS += -m32 -msse
}

!win32 {
LIBS += -L/usr/lib64 -lGL
LIBS += -L/usr/lib64 -lGLU -lX11 -lm -lpthread
LIBS += -L/usr/lib64 -lXmu
LIBS += -lX11
LIBS += -static-libstdc++
}

TARGET = si_editor
CONFIG += qt
QT += network
QT += opengl

QMAKE_CXXFLAGS += -fpermissive -std=c++0x
# -std=c++11
#QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wno-long-long

#DESTDIR = ./release
OBJECTS_DIR = ./build/.obj
MOC_DIR = ./build/.moc
RCC_DIR = ./build/.rcc
UI_DIR = ./build/.ui




