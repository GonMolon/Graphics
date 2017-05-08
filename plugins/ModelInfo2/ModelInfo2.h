#ifndef _MODELINFO2_H
#define _MODELINFO2_H
#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class ModelInfo2 : public QObject, public BasicPlugin {
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
	int total_obj = 0;
	int total_tri = 0;
	int total_pol = 0;
	int total_vert = 0;

	QGLShaderProgram* program;
	QGLShader* vs;
	QGLShader* fs;

	GLuint VAO_info;

	void updateInfo();
	QString readFile(QString path);
};

#endif