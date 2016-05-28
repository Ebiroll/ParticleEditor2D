//
// Copyright (c) 2014 the ParticleEditor2D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <QFile>
#include <QTimer>

#include "ParticleEditor.h"
#include "MainWindow.h"
#include <X11/Xlib.h>
#include <Qt/qx11info_x11.h>

namespace Urho3D
{

ParticleEditor::ParticleEditor(int argc, char** argv) :
    QApplication(argc, argv),
    mainWindow_(new MainWindow(this))
{
}

ParticleEditor::~ParticleEditor()
{
    delete mainWindow_;
}

int ParticleEditor::Run()
{
    mainWindow_->CreateWidgets();

    //New();

    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimeout()));
    timer.start(16);


    return QApplication::exec();
}

void ParticleEditor::New()
{
    Open("Urho2D/fire.pex");

    fileName_.clear();
}

void ParticleEditor::Open(const QString& fileName)
{

    mainWindow_->UpdateWidget();
}

void ParticleEditor::Save(const QString& fileName)
{

    fileName_ = fileName;
}

void ParticleEditor::setGLWidget(GLWidget* widget)
{
  qDebug() << "setGLWidget";

  glWidget_=widget;
}


void ParticleEditor::OnTimeout()
{

    if (glWidget_!=NULL) {
        //qDebug() << "Timeout\n";
        glWidget_->updateFrame();
    }
    else
    {
        qDebug() << "Null\n";
    }
    //if (engine_ && !engine_->IsExiting())
    //    engine_->RunFrame();
}


ParticleEditor* ParticleEditor::Get()
{
    return qobject_cast<ParticleEditor*>(qApp);
}

}
