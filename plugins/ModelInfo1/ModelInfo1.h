#ifndef _MODELINFO1_H
#define _MODELINFO1_H
#include "basicplugin.h"

class ModelInfo1 : public QObject, public BasicPlugin {
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
	void writeStats();
};

#endif