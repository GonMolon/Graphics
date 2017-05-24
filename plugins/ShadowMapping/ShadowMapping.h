#ifndef _SHADOWMAPPING_H
#define _SHADOWMAPPING_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class ShadowMapping : public QObject, public BasicPlugin {
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "BasicPlugin")
#endif
    Q_INTERFACES(BasicPlugin)
public:
    void onPluginLoad();
    void onObjectAdd();
    void preFrame();
    void postFrame();
    bool paintGL();
    bool drawScene();
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
private:
    QGLShaderProgram* program;
    QGLShader* vs;
    QGLShader* fs;
    GLuint textureId;
    Camera lightCamera;

    void drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
    void loadShaders();
};

#endif
