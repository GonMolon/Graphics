#ifndef _GLOWING_H
#define _GLOWING_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class Glowing : public QObject, public BasicPlugin {
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
    void loadShaders();
    int printOglError(const char file[], int line, const char func[]);

    GLuint VAO_rect;
    void initializeVAOInfo();

};

#endif
