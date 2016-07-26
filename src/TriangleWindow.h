//
// Created by dexter on 26.07.16.
//

#ifndef HELLOQT_TRIANGLEWINDOW_H
#define HELLOQT_TRIANGLEWINDOW_H


#include <QtGui/QOpenGLShaderProgram>
#include "OpenGLWindow.h"

class TriangleWindow : public OpenGLWindow {
public:
    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;

    void render() Q_DECL_OVERRIDE;

private:
    GLuint posAttr;
    GLuint colAttr;
    GLuint matrixUniform;

    QOpenGLShaderProgram *program;
    unsigned int frame;

};


#endif //HELLOQT_TRIANGLEWINDOW_H
