#include <QtGui/QPainter>
#include <QtCore/QCoreApplication>
#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(QWindow *parent)
        : QWindow(parent),
          update_pending(false),
          animating(false),
          context(NULL),
          device(NULL) {
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow() {

}

void OpenGLWindow::initialize() {

}

void OpenGLWindow::render(QPainter *painter) {
    Q_UNUSED(painter)
}

void OpenGLWindow::render() {
    if (!device)
        device = new QOpenGLPaintDevice();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    device->setSize(size());

    QPainter painter(device);
    render(&painter);
}

void OpenGLWindow::renderNow() {
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if(!context){
        context = new QOpenGLContext(this);
        context->setFormat(requestedFormat());
        context->create();

        needsInitialize = true;
    }

    context->makeCurrent(this);

    if(needsInitialize){
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    context->swapBuffers(this);

    if(animating)
        renderLater();

}

void OpenGLWindow::renderLater() {
    if (!update_pending) {
        update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void OpenGLWindow::setAnimating(bool animating) {
    this->animating = animating;

    if(animating)
        renderLater();
}

bool OpenGLWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::UpdateRequest:
            update_pending = false;
            renderNow();
            return true;
        default:
            return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}
