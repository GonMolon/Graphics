#ifndef _FRAMERATE_H
#define _FRAMERATE_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QElapsedTimer>

class FrameRate : public QObject, public BasicPlugin {
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

	int frames = 0;
	int fps = 0;

	GLuint VAO_info;

	void drawInfo(int n, QString info[n]);
	QString readFile(QString path);

public slots:
	void updateFPS();
};

#endif