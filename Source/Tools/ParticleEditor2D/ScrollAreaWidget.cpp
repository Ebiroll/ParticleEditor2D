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

#include "ScrollAreaWidget.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Urho3D
{

ScrollAreaWidget::ScrollAreaWidget()
{
    setMinimumWidth(320);
    setWidgetResizable(true);

    QWidget* widget = new QWidget();
    setWidget(widget);

    vBoxLayout_ = new QVBoxLayout();
    widget->setLayout(vBoxLayout_);
}

ScrollAreaWidget::~ScrollAreaWidget()
{
}

QHBoxLayout* ScrollAreaWidget::AddHBoxLayout()
{
	QHBoxLayout* hBoxLayout = new QHBoxLayout();
	vBoxLayout_->addLayout(hBoxLayout);

    hBoxLayout->setContentsMargins(0, 0, 0, 0);
	return hBoxLayout;
}

void ScrollAreaWidget::AddLineShape()
{
    QFrame* frame = new QFrame();
    vBoxLayout_->addSpacing(4);
    vBoxLayout_->addWidget(frame);
    vBoxLayout_->addSpacing(4);

    frame->setFrameShape(QFrame::HLine);
}

}