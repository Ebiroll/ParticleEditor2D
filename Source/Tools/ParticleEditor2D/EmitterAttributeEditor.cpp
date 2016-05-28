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

#include "particle_fx.h"

#include <qobject.h>

//#include "Context.h"
//#include "CoreEvents.h"
#include "EmitterAttributeEditor.h"
#include "FloatEditor.h"
#include "IntEditor.h"
//#include "Sprite2D.h"
//#include "ParticleEffect2D.h"
//#include "ParticleEmitter2D.h"
//#include "ResourceCache.h"
//#include "Texture2D.h"
#include "ValueVarianceEditor.h"
#include "Vector2Editor.h"
#include <QApplication>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Urho3D
{
EmitterAttributeEditor::EmitterAttributeEditor() :
    //ParticleEffectEditor(context),
    maxParticlesChanged_(false)
{
    CreateMaxParticlesEditor();
    Createx_angleVarianceEditor();
    Createy_angleVarianceEditor();
    Create_Speed_VarianceEditor();

    vBoxLayout_->addSpacing(8);

    CreateTextureEditor();
    CreateBlendModeEditor();

    vBoxLayout_->addSpacing(8);

    CreateEmitterTypeEditor();

    vBoxLayout_->addSpacing(8);

    angleEditor_ = CreateValueVarianceEditor(tr("Angle"), 0.0f, 360.0f);

    CreateGravityTypeEditor();
    CreateRadialTypeEditor();

    vBoxLayout_->addStretch(1);

    //SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(EmitterAttributeEditor, HandlePostUpdate));
}

EmitterAttributeEditor::~EmitterAttributeEditor()
{
}

void EmitterAttributeEditor::HandleMaxParticlesEditorValueChanged(int value)
{
    if (updatingWidget_)
        return;

    maxParticlesChanged_ = true;
}

void EmitterAttributeEditor::HandleXAngleValueChanged(float value,float spread)
{
    if (updatingWidget_)
        return;

    //GetEffect()->SetDuration(value);
}

void EmitterAttributeEditor::HandleYAngleValueChanged(float value,float spread)
{
    if (updatingWidget_)
        return;

    //GetEffect()->SetDuration(value);
}

void EmitterAttributeEditor::HandleSpeedValueChanged(float value,float spread)
{
    if (updatingWidget_)
        return;

    //GetEffect()->SetDuration(value);
}


void EmitterAttributeEditor::HandleTexturePushButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(0, tr("Texture"), "./Data/Urho2D/", "*.dds;*.png;*.jpg;*.bmp;*.tga;*.ktx;*.pvr");
    if (fileName.isEmpty())
        return;

    static QString dataPath = qApp->applicationDirPath() + "/Data/";
    if (fileName.left(dataPath.length()) != dataPath)
        return;

    fileName = fileName.right(fileName.length() - dataPath.length());

    //ResourceCache* cache = GetSubsystem<ResourceCache>();
    //Sprite2D* sprite = cache->GetResource<Sprite2D>(fileName.toLatin1().data());
    //if (!sprite)
    //    return;

    textureEditor_->setText(fileName);

    //GetEffect()->SetSprite(sprite);
    //GetEmitter()->SetSprite(sprite);
}

void EmitterAttributeEditor::HandleBlendModeEditorChanged(int index)
{
    if (updatingWidget_)
        return;

    //GetEffect()->SetBlendMode((BlendMode)index);
    //GetEmitter()->SetBlendMode((BlendMode)index);
}

void EmitterAttributeEditor::HandleEmitterTypeEditorChanged(int index)
{
    uint16_t emitterType = index;
    ShowGravityTypeEditor(emitterType == vis::EMITTER_TYPE_BOX);
    ShowRadialTypeEditor(emitterType != vis::EMITTER_TYPE_BOX);

    if (updatingWidget_)
        return;

    //GetEffect()->SetEmitterType(emitterType);
}

#if 0
void EmitterAttributeEditor::HandleSourcePositionVarianceEditorValueChanged(const Vector2& value)
{
    if (updatingWidget_)
        return;

    //GetEffect()->SetSourcePositionVariance(value);
}

void EmitterAttributeEditor::HandleGravityEditorValueChanged(const Vector2& value)
{
    if (updatingWidget_)
        return;

    GetEffect()->SetGravity(value);
}
#endif
void EmitterAttributeEditor::HandleValueVarianceEditorValueChanged(float average, float variance)
{
    if (updatingWidget_)
        return;
#if 0
    QObject* s = sender();
    //ParticleEffect2D* effect = GetEffect();

    if (s == speedEditor_)
    {
        effect->SetSpeed(speedEditor_->value());
        effect->SetSpeedVariance(speedEditor_->variance());
    }
    else if (s == angleEditor_)
    {
        effect->SetAngle(angleEditor_->value());
        effect->SetAngleVariance(angleEditor_->variance());
    }
    else if (s == radialAccelerationEditor_)
    {
        effect->SetRadialAcceleration(radialAccelerationEditor_->value());
        effect->SetRadialAccelVariance(radialAccelerationEditor_->variance());

    }
    else if (s == tangentialAccelerationEditor_)
    {
        effect->SetTangentialAcceleration(tangentialAccelerationEditor_->value());
        effect->SetTangentialAccelVariance(tangentialAccelerationEditor_->variance());
    }
    else if (s == maxRadiusEditor_)
    {
        effect->SetMaxRadius(maxRadiusEditor_->value());
        effect->SetMaxRadiusVariance(maxRadiusEditor_->variance());

    }
    else if (s == minRadiusEditor_)
    {
        effect->SetMinRadius(minRadiusEditor_->value());
        effect->SetMinRadiusVariance(minRadiusEditor_->variance());
    }
    else if (s == rotatePerSecondEditor_)
    {
        effect->SetRotatePerSecond(rotatePerSecondEditor_->value());
        effect->SetRotatePerSecondVariance(rotatePerSecondEditor_->variance());
    }
#endif
}

void EmitterAttributeEditor::HandleUpdateWidget()
{
#if 0
    ParticleEffect2D* effect_ = GetEffect();

    maxParticlesEditor_->setValue(effect_->GetMaxParticles());
    durationEditor_->setValue(effect_->GetDuration());

    //Sprite2D* sprite = effect_->GetSprite();
    //textureEditor_->setText(sprite ? sprite->GetName().CString() : "");

    blendModeEditor_->setCurrentIndex((int)effect_->GetBlendMode());
    
    emitterTypeEditor_->setCurrentIndex((int)effect_->GetEmitterType());

    sourcePositionVarianceEditor_->setValue(effect_->GetSourcePositionVariance());
    speedEditor_->setValue(effect_->GetSpeed(), effect_->GetSpeedVariance());
    angleEditor_->setValue(effect_->GetAngle(), effect_->GetAngleVariance());
    gravityEditor_->setValue(effect_->GetGravity());

    radialAccelerationEditor_->setValue(effect_->GetRadialAcceleration(), effect_->GetRadialAccelVariance());
    tangentialAccelerationEditor_->setValue(effect_->GetTangentialAcceleration(), effect_->GetTangentialAccelVariance());

    maxRadiusEditor_->setValue(effect_->GetMaxRadius(), effect_->GetMaxRadiusVariance());
    minRadiusEditor_->setValue(effect_->GetMinRadius(), effect_->GetMinRadiusVariance());
    rotatePerSecondEditor_->setValue(effect_->GetRotatePerSecond(), effect_->GetRotatePerSecondVariance());
#endif
}

void EmitterAttributeEditor::CreateMaxParticlesEditor()
{
    maxParticlesEditor_ = new IntEditor(tr("max_particles"));
    vBoxLayout_->addLayout(maxParticlesEditor_);
    
    maxParticlesEditor_->setRange(1, 2048);    
    connect(maxParticlesEditor_, SIGNAL(valueChanged(int)), this, SLOT(HandleMaxParticlesEditorValueChanged(int)));
}

void EmitterAttributeEditor::Createx_angleVarianceEditor()
{
    x_angleVarianceEditor_=new ValueVarianceEditor(tr("x_angle"));
    x_angleVarianceEditor_->setValue(0.0f,3.14f);
    x_angleVarianceEditor_->setRange(-3.14f,3.14f);

    vBoxLayout_->addWidget(x_angleVarianceEditor_);
    
    //durationEditor_->setRange(-1.0f, 100.0f);
    connect(x_angleVarianceEditor_, SIGNAL(valueChanged(float,float)), this, SLOT(HandleXAngleValueChanged(float,float)));
}

void EmitterAttributeEditor::Createy_angleVarianceEditor()
{
    y_angleVarianceEditor_=new ValueVarianceEditor(tr("y_angle"));
    y_angleVarianceEditor_->setValue(0.0f,3.14f);
    y_angleVarianceEditor_->setRange(-3.14f,3.14f);

    vBoxLayout_->addWidget(y_angleVarianceEditor_);

    //durationEditor_->setRange(-1.0f, 100.0f);
    connect(y_angleVarianceEditor_, SIGNAL(valueChanged(float,float)), this, SLOT(HandleYAngleValueChanged(float,float)));
}

void EmitterAttributeEditor::Create_Speed_VarianceEditor()
{
    speed_VarianceEditor_=new ValueVarianceEditor(tr("speed"));
    speed_VarianceEditor_->setValue(0.0f,0.4f);
    speed_VarianceEditor_->setRange(0.0f,100.0f);

    vBoxLayout_->addWidget(speed_VarianceEditor_);

    //durationEditor_->setRange(-1.0f, 100.0f);
    connect(speed_VarianceEditor_, SIGNAL(valueChanged(float,float)), this, SLOT(HandleSpeedValueChanged(float,float)));

}


void EmitterAttributeEditor::CreateTextureEditor()
{
    QHBoxLayout* hBoxLayout = AddHBoxLayout();
    hBoxLayout->addWidget(new QLabel(tr("Texture")));

    textureEditor_ = new QLineEdit();
    hBoxLayout->addWidget(textureEditor_, 1);

    textureEditor_->setReadOnly(true);

    QPushButton* texturePushButton = new QPushButton("...");
    hBoxLayout->addWidget(texturePushButton);

    texturePushButton->setFixedWidth(32);
    connect(texturePushButton, SIGNAL(clicked(bool)), this, SLOT(HandleTexturePushButtonClicked()));
}

void EmitterAttributeEditor::CreateBlendModeEditor()
{
    QHBoxLayout* hBoxLayout = AddHBoxLayout();

    hBoxLayout->addWidget(new QLabel(tr("Blend Mode")));

    blendModeEditor_ = new QComboBox();
    hBoxLayout->addWidget(blendModeEditor_, 1);

    const char* blendModeNames[] =
    {
        "replace",
        "add",
        "multiply",
        "alpha",
        "addalpha",
        "premulalpha",
        "invdestalpha",
        "subtract",
        "subtractalpha",
        0
    };

    //for (unsigned i = 0; i < MAX_BLENDMODES; ++i)
    //    blendModeEditor_->addItem(blendModeNames[i], i);

    connect(blendModeEditor_,SIGNAL(currentIndexChanged(int)),this,SLOT(HandleBlendModeEditorChanged(int)));
}

void EmitterAttributeEditor::CreateEmitterTypeEditor()
{
    emitterTypeEditor_ = new QComboBox();
    vBoxLayout_->addWidget(emitterTypeEditor_, 1);

    emitterTypeEditor_->addItem(tr("BOX Emitter Type"));
    emitterTypeEditor_->addItem(tr("Sphere Emitter Type"));
    emitterTypeEditor_->addItem(tr("Cube Emitter Type"));
    emitterTypeEditor_->setCurrentIndex(-1);

    connect(emitterTypeEditor_, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleEmitterTypeEditorChanged(int)));
}

void EmitterAttributeEditor::CreateGravityTypeEditor()
{
    sourcePositionVarianceEditor_ = new Vector2Editor(tr("SourcePositionVariance"));
    vBoxLayout_->addWidget(sourcePositionVarianceEditor_);
    
    //sourcePositionVarianceEditor_->setRange(Vector2::ZERO, Vector2::ONE * 1000.0f);
    connect(sourcePositionVarianceEditor_, SIGNAL(valueChanged(const Vector2&)), this, SLOT(HandleSourcePositionVarianceEditorValueChanged(const Vector2&)));

    speedEditor_ = CreateValueVarianceEditor(tr("Speed"), 0.0f, 2000.0f);

    gravityEditor_ = new Vector2Editor(tr("Gravity"));
    vBoxLayout_->addWidget(gravityEditor_);

    //gravityEditor_->setRange(Vector2::ONE * -3000.0f, Vector2::ONE * 3000.0f);
    connect(gravityEditor_, SIGNAL(valueChanged(const Vector2&)), this, SLOT(HandleGravityEditorValueChanged(const Vector2&)));

    radialAccelerationEditor_ = CreateValueVarianceEditor(tr("Radial Acceleration"), -10000.0f, 10000.0f);
    tangentialAccelerationEditor_ = CreateValueVarianceEditor(tr("Tangential AccelVariance"), -50000.0f, 50000.0f);
}

void EmitterAttributeEditor::CreateRadialTypeEditor()
{
    maxRadiusEditor_ = CreateValueVarianceEditor(tr("MaxRadius"), 0.0f, 1000.0f);
    minRadiusEditor_ = CreateValueVarianceEditor(tr("MinRadius"), 0.0f, 1000.0f);

    const float s = 2.0f;
    rotatePerSecondEditor_ = CreateValueVarianceEditor(tr("RotatePerSecond"), -360.0f * s, 360.0f * s);
}

void EmitterAttributeEditor::ShowGravityTypeEditor(bool visible)
{
    sourcePositionVarianceEditor_->setVisible(visible);
    speedEditor_->setVisible(visible);

    gravityEditor_->setVisible(visible);    
    radialAccelerationEditor_->setVisible(visible);
    tangentialAccelerationEditor_->setVisible(visible);
}

void EmitterAttributeEditor::ShowRadialTypeEditor(bool visible)
{
    maxRadiusEditor_->setVisible(visible);
    minRadiusEditor_->setVisible(visible);
    rotatePerSecondEditor_->setVisible(visible);
}

ValueVarianceEditor* EmitterAttributeEditor::CreateValueVarianceEditor(const QString& name, float min, float max)
{
    ValueVarianceEditor* editor = new ValueVarianceEditor(name);
    vBoxLayout_->addWidget(editor);
    
    editor->setRange(min, max);    
    connect(editor, SIGNAL(valueChanged(float, float)), this, SLOT(HandleValueVarianceEditorValueChanged(float, float)));

    return editor;
}

#if 0
void EmitterAttributeEditor::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!maxParticlesChanged_)
        return;

    maxParticlesChanged_ = false;

    //GetEffect()->SetMaxParticles(maxParticlesEditor_->value());
    //GetEmitter()->SetMaxParticles(maxParticlesEditor_->value());
}
#endif
}
