#ifndef _MULTITEXTURING_H
#define _MULTITEXTURING_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class Multitexturing : public QObject, public BasicPlugin {
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
    void loadShaders();

    GLuint textureId0, textureId1;
    void loadTexture(GLuint GLTEXTURE, GLuint textureID);
};

#endif
