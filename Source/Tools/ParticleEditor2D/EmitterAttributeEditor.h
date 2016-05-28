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

#pragma once

#include "ParticleEffectEditor.h"
#include "ScrollAreaWidget.h"

class QComboBox;
class QLineEdit;

namespace Urho3D
{

class FloatEditor;
class IntEditor;
class ValueVarianceEditor;
class Vector2Editor;

class EmitterAttributeEditor : public ScrollAreaWidget, public ParticleEffectEditor
{
    Q_OBJECT
    //OBJECT(EmitterAttributeEditor)

    //URHO3D_OBJECT(EmitterAttributeEditor, Object);



public:
    EmitterAttributeEditor();
    virtual ~EmitterAttributeEditor();

private slots:
    void HandleMaxParticlesEditorValueChanged(int value);
    void HandleXAngleValueChanged(float value,float spread);
    void HandleYAngleValueChanged(float value,float spread);
    void HandleSpeedValueChanged(float value,float spread);

    void HandleTexturePushButtonClicked();
    void HandleBlendModeEditorChanged(int index);
    
    void HandleEmitterTypeEditorChanged(int index);
    //void HandleSourcePositionVarianceEditorValueChanged(const Vector2& value);
    //void HandleGravityEditorValueChanged(const Vector2& value);

    void HandleValueVarianceEditorValueChanged(float average, float variance);

private:
    virtual void HandleUpdateWidget();

    void CreateMaxParticlesEditor();
    void Createx_angleVarianceEditor();
    void Createy_angleVarianceEditor();
    void Create_Speed_VarianceEditor();

    void CreateTextureEditor();
    void CreateBlendModeEditor();

    void CreateEmitterTypeEditor();
    void CreateGravityTypeEditor();
    void CreateRadialTypeEditor();
    void ShowRadialTypeEditor(bool visible);
    void ShowGravityTypeEditor(bool visible);
    ValueVarianceEditor* CreateValueVarianceEditor(const QString& name, float min, float max);

    //void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Max particle editor.
    IntEditor* maxParticlesEditor_;
    /// Is max particles changed.
    bool maxParticlesChanged_;

   ValueVarianceEditor* x_angleVarianceEditor_;

   ValueVarianceEditor* y_angleVarianceEditor_;

   ValueVarianceEditor* speed_VarianceEditor_;


#if 0
    speed = f0.0
    speed_spread = f0.4
    rotation = f0.0
    rotation_spread = f3.14
    rotation_speed = f0.0
    rotation_speed_spread = f0.0
    size = f0.5
    size_spread = f0.25
    duration = f15.0
    duration_spread = f0.0
    emit_rate = f3.0
    animation = 45
    animation_spread = 15
    animation_x = 8
    animation_y = 8
    color = f[0.8, 0.5, 0.2, 1.0]
    max_particles = 60
    texture = 'explosion.dds'
    id = 0
    emitter_type = 1
    emitter_size = f[0.0, 0.5]
#endif


    /// Duration editor.
    FloatEditor* durationEditor_;
    /// Texture editor.
    QLineEdit* textureEditor_;
    /// Blend mode editor.
    QComboBox* blendModeEditor_;
    /// Emitter type editor.
    QComboBox* emitterTypeEditor_;


    /// Source position variance editor.
    Vector2Editor* sourcePositionVarianceEditor_;
    /// Speed editor.
    ValueVarianceEditor* speedEditor_;
    /// Angle editor.
    ValueVarianceEditor* angleEditor_;
    /// Gravity editor.
    Vector2Editor* gravityEditor_;
    /// Radial acceleration editor.
    ValueVarianceEditor* radialAccelerationEditor_;
    /// Tangential acceleration editor.
    ValueVarianceEditor* tangentialAccelerationEditor_;

    /// Max radius editor.
    ValueVarianceEditor* maxRadiusEditor_;
    /// Min radius editor.
    ValueVarianceEditor* minRadiusEditor_;
    /// Rotate per second editor.
    ValueVarianceEditor* rotatePerSecondEditor_;
};

}
