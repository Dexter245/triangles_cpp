//
// Created by dexter on 26.07.16.
//

#include "TriangleWindow.h"
#include <QtGui/QScreen>

TriangleWindow::TriangleWindow()
        : program(NULL),
          frame(0) {
}

static const char *vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
                "attribute lowp vec4 colAttr;\n"
                "varying lowp vec4 col;\n"
                "uniform highp mat4 matrix;\n"
                "void main() {\n"
                "   col = colAttr;\n"
                "   gl_Position = matrix * posAttr;\n"
                "}\n";

static const char *fragmentShaderSource =
        "varying lowp vec4 col;\n"
                "void main() {\n"
                "   gl_FragColor = col;\n"
                "}\n";

void TriangleWindow::initialize() {
    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
    posAttr = program->attributeLocation("posAttr");
    colAttr = program->attributeLocation("colAttr");
    matrixUniform = program->uniformLocation("matrix");
}

void TriangleWindow::render() {
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    program->bind();

    QMatrix4x4 matrix;
//    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
//    matrix.perspective(90.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f);
//    matrix.translate(0, 0, -2);
    matrix.translate(0.0f, 0.0f, -1);
//    matrix.rotate(100.0f * frame / screen()->refreshRate(), 0, 1, 0);
//    matrix.scale(sin(frame/screen()->refreshRate()));

    program->setUniformValue(matrixUniform, matrix);

    GLfloat vertices[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 0.866f
    };

    GLfloat colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    program->release();

    ++frame;
}
