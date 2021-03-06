#ifndef _SHOWDEGREE_H
#define _SHOWDEGREE_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class ShowDegree : public QObject, public BasicPlugin {
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
   
    GLuint VAO_info;
    void initializeVAOInfo();
    void drawInfo(int n, QString info[n]);

    float degree = 0;
    float getDegree();
};

#endif
