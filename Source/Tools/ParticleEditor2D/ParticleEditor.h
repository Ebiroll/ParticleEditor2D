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

#include <QString>
//#include "Object.h"
//#include "Ptr.h"
#include <QApplication>

namespace Urho3D
{

class Camera;
class Context;
class Engine;
class MainWindow;
class Node;
class ParticleEffect2D;
class ParticleEmitter2D;
class Scene;

/// Particle editor class.
class ParticleEditor : public QApplication
{
    Q_OBJECT
    //OBJECT(ParticleEditor)
    //URHO3D_OBJECT(ParticleEditor, Object);
private:
    QString fileName_;
public:
    /// Construct.
    ParticleEditor(int argc, char** argv);
    /// Destruct.
    virtual ~ParticleEditor();

    /// Run.
    int Run();

    void New();
    void Open(const QString& fileName);
    void Save(const QString& fileName);

    const QString& GetFileName() const { return fileName_; }

    /// Return editor pointer.
    static ParticleEditor* Get();

private slots:
    // Timeout handler.
    void OnTimeout();

private:
    /// Create scene.

    /// Editor main window.
    MainWindow* mainWindow_;
};

}
