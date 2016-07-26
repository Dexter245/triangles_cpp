//
// Created by dexter on 26.07.16.
//

#ifndef HELLOQT_OPENGLWINDOW_H
#define HELLOQT_OPENGLWINDOW_H


#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLPaintDevice>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);

    ~OpenGLWindow();

    virtual void render(QPainter *painter);

    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:

    void renderLater();

    void renderNow();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

private:
    bool update_pending;
    bool animating;

    QOpenGLContext *context;
    QOpenGLPaintDevice *device;

};


#endif //HELLOQT_OPENGLWINDOW_H
