/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#define  GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <QGLFunctions>

#include <QtOpenGL>

//#include <QOpenGLBuffer>
#include "glwidget.h"
#include "rt_particles.h"
#include <iostream>
#include "pfx.h"


uint32_t vis::s_random_seed = 4711;


// Stupid OPenGL API :-P
#ifndef  GL_SHADER_STORAGE_BUFFER
#define GL_SHADER_STORAGE_BUFFER 0x90D2
#endif
#ifndef  GL_STREAM_DRAW
#define GL_STREAM_DRAW 0x88E0
#endif

GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget)
{
    zoomFactor=0.5;
    deltaX=0.0;
    deltaY=0.5;


    clearColor = Qt::black;
    xRot = 0;
    yRot = 0;
    zRot = 0;
#ifdef QT_OPENGL_ES_2
    program = 0;
#endif
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}

void GLWidget::updateFrame()
{
    updateGL();
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    updateGL();
}

void GLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    updateGL();
}

void GLWidget::initializeGL()
{
    makeObject();

    // Set core version??
    // Inferit from QOpenGLFunctions_4_3_Core
    //QSurfaceFormat format;
    //format.setVersion(4, 3);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    //setFormat(format);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
#ifndef QT_OPENGL_ES_2
    glEnable(GL_TEXTURE_2D);
#endif

//#ifdef QT_OPENGL_ES_2

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_ANIM_ATTRIBUTE 2

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    const char *vsrc =
        "#version 430\n"
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "attribute mediump vec2 animFraction;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "mediump vec2 vca[4];\n"
         "   vec2 rotate(vec2 p, float a)\n"
         "   {\n"
         "       float s = sin(a);\n"
         "       float c = cos(a);\n"
         "       return vec2(p.x * c - p.y * s, p.x * s + p.y * c);\n"
         "   }\n"
        "    struct Particle\n"
        "    {\n"
        "        vec3 pos;\n"
        "        float rot;\n"
        "        float size;\n"
        "        float anim;\n"
        "        uint color;\n"
        "    };\n"
        "    layout(std430, binding = 0) buffer P_data\n"
        "    {\n"
        "        Particle p_data[];\n"
        "    };\n"
        "void main(void)\n"
        "{\n"
        "    vca[0] = vec2(0.0, 0.0);\n"
        "    vca[1] = vec2(0.0, 1.0);\n"
        "    vca[2] = vec2(1.0, 1.0);\n"
        "    vca[3] = vec2(1.0, 0.0);\n"
        "    vec2 pos = (2.0 * vca[gl_VertexID%4] - 1.0) * p_data[gl_InstanceID].size;"
        "	 pos = rotate(vec2(vertex), p_data[gl_InstanceID].rot);"
        "	 gl_Position = matrix  * vec4(pos.xy, 0.0, 1.0);"
#if 0
        "    gl_Position = matrix * vertex;\n"
#endif
        "    gl_Position.xyz += p_data[gl_InstanceID].pos.xyz;\n"
        "    float anim = floor(p_data[gl_InstanceID].anim + 0.5) * animFraction.x;\n"
        "    vec2 uv_anim;\n"
        "	 uv_anim.x = fract(anim);\n"
        "    uv_anim.y = animFraction.y * (anim - uv_anim.x);\n"
        "	 texc = vec4(uv_anim + vca[gl_VertexID%4] * animFraction,0.0,0.0);\n"
        "    //texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    //gl_FragColor = vec4(0.0,1.0,0.0,1.0);\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->bindAttributeLocation("animFraction", PROGRAM_ANIM_ATTRIBUTE);


    //std::cerr << "Create streambuffer\n";

    glGenBuffers(1, &_sb);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _sb);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vis::RT_particles::VS_particle) * 1000, 0, GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);



    //glCreateBuffers(1, &_sb);
    //glNamedBufferData(_sb, sizeof(VS_particle) * 1000, 0, GL_STREAM_DRAW);


    program->link();

    program->bind();
    program->setUniformValue("texture", 0);






//#endif
}

inline uint32_t pack_color(const float c[4])
{
    uint32_t r = uint32_t(c[0] * 255.0f);
    uint32_t g = uint32_t(c[1] * 255.0f) << 8;
    uint32_t b = uint32_t(c[2] * 255.0f) << 16;
    uint32_t a = uint32_t(c[3] * 255.0f) << 24;
    return r | g | b | a;
}

vis::RT_particles::VS_particle vs_particles[1000];
int n_particles=1;


void GLWidget::paintGL()
{
    qglClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//#if !defined(QT_OPENGL_ES_2)
#if 0
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

#else

    QMatrix4x4 m;


    m.ortho(zoomFactor*-0.5f, zoomFactor*0.5f, zoomFactor*0.5f, zoomFactor*-0.5f, -4.0f, 150.0f);
    m.translate(deltaX, deltaY, -10.0f);


    m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    program->setUniformValue("matrix", m);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_ANIM_ATTRIBUTE);

    program->setAttributeArray
        (PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
    program->setAttributeArray
        (PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());

    float anim_params[2] = { 1.0f / 8.0f, 1.0f / 8.0f};
    animParams.append(QVector2D(anim_params[0],anim_params[0]));
    program->setAttributeArray(PROGRAM_ANIM_ATTRIBUTE, animParams.constData());

    //glProgramUniform2fv(_vs_prog, _u_anim_params, 1, &anim_params[0]);


#endif

    vis::Particle_fx* pfx=PFX::instance()->pfx;

    n_particles= PFX::instance()->getLoadedEmitter(1)->max_particles;

    vis::Particle_fx::Emitter* em=PFX::instance()->getLoadedEmitter(1);
    pfx->update_emitter(*em, 0.01);

    uint32_t n_particles = em->active_particles;
    const vis::Particle* particles = em->particles;

    assert(n_particles<1000);
    //VS_particle vs_particles[1000];
    for (uint32_t i = 0; i < n_particles; ++i) {
        const vis::Particle& p = particles[i];
        vis::RT_particles::VS_particle& vp = vs_particles[i];
        vp.pos[0] = p.position[0];
        vp.pos[1] = p.position[1];
        vp.pos[2] = p.position[2];
        vp.rot = p.rotation;
        vp.size = p.size;
        vp.anim = p.animation;
        vp.color = pack_color(p.color);
    }


#if 0
    float c[4]={1.0f,0.0f,0.0f,1.0f};
    for (uint32_t i = 0; i < n_particles; ++i) {
        vis::RT_particles::VS_particle& vp = vs_particles[i];
        vp.pos[0] = vp.pos[0] +  0.01*(vis::rand_f() -0.5f) ;
        vp.pos[1] = vp.pos[1] +  0.01*(vis::rand_f() - 0.45f);
        vp.pos[2] =  0.0f;
        vp.rot =  vp.rot  + 0.01f;
        vp.size = 0.1f;
        vp.anim = vp.anim+1.0;
        if (vp.anim>50) {
            vp.anim=0.0;
        }
        vp.color = pack_color(c);
    }
#endif


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _sb);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(vis::RT_particles::VS_particle)* n_particles, &vs_particles[0]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _sb);


    // One side only
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    //glDrawArrays(GL_TRIANGLE_FAN, 0 * 4, 4);

    // Draw all active particles
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, n_particles);

    //for (int i = 0; i < 6; ++i) {
    //    glBindTexture(GL_TEXTURE_2D, textures[i]);
    //    glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    //}
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
#if 0
#if !defined(QT_OPENGL_ES_2)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


#ifndef QT_OPENGL_ES
    glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
#else
    glOrthof(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
#endif
#endif
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    //qDebug() << "Wheel" << event;
    if (event->delta()>0) {
      zoomFactor=zoomFactor*2;
    }
    else
    {
        zoomFactor=zoomFactor/2;
    }
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        //rotateBy(8 * dy, 8 * dx, 0);
        deltaX+=dx/100.0f;
        deltaY+=dy/100.0f;

    } else if (event->buttons() & Qt::RightButton) {
        //rotateBy(8 * dy, 0, 8 * dx);
        deltaX=0.0f;
        deltaY=0.0f;

    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::makeObject()
{
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    for (int j=0; j < 6; ++j) {
        //textures[j] = bindTexture
        //    (QPixmap(QString(":/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);

        textures[j] = bindTexture(QPixmap(QString(":/dds/explosion.png")), GL_TEXTURE_2D);

    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            texCoords.append
                (QVector2D(j == 0 || j == 3, j == 0 || j == 1));
            vertices.append
                (QVector3D(0.2 * coords[i][j][0], 0.2 * coords[i][j][1],
                           0.2 * coords[i][j][2]));
        }
    }
}
