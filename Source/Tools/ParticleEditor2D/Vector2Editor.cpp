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

#include "FloatEditor.h"
#include "Vector2Editor.h"
#include <QGroupBox>

namespace Urho3D
{
    
Vector2Editor::Vector2Editor(const QString& text) :
    QGroupBox(text)
{
    QVBoxLayout* vBoxLayout = new QVBoxLayout();
    setLayout(vBoxLayout);

    xEditor_ = new FloatEditor("X", false);
    vBoxLayout->addLayout(xEditor_);
    connect(xEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));

    yEditor_ = new FloatEditor("Y", false);
    vBoxLayout->addLayout(yEditor_);
    connect(yEditor_, SIGNAL(valueChanged(float)), this, SLOT(editorValueChanged()));
}

Vector2Editor::~Vector2Editor()
{
    delete xEditor_;
    delete yEditor_;
}


void Vector2Editor::setValue(const float value[2])
{
    xEditor_->setValue(value[0]);
    yEditor_->setValue(value[1]);
}

std::vector<float> Vector2Editor::value() const
{
    std::vector<float> ret;
    ret.push_back(xEditor_->value());
    ret.push_back( yEditor_->value());

    return ret;
}

void Vector2Editor::setRange(const float  min[2], const float  max[2])
{
    xEditor_->setRange(min[0], max[0]);
    yEditor_->setRange(min[1], max[1]);
}

void Vector2Editor::editorValueChanged()
{
    emit valueChanged(value());
}

}
