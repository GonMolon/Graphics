#include "KeyboardSelection.h"
#include "glwidget.h"

void KeyboardSelection::onPluginLoad() {} 

void KeyboardSelection::onObjectAdd() {} 

void KeyboardSelection::preFrame() {} 

void KeyboardSelection::postFrame() {} 

bool KeyboardSelection::paintGL() {return false;} 

bool KeyboardSelection::drawScene() {return false;} 

void KeyboardSelection::keyPressEvent(QKeyEvent* e) {
	if(e->key() >= Qt::Key_0 && e->key() <= Qt::Key_9){
		scene()->setSelectedObject(e->key()-Qt::Key_0);
		glwidget()->update();
	}
} 

void KeyboardSelection::keyReleaseEvent(QKeyEvent* e) {} 

void KeyboardSelection::mouseMoveEvent(QMouseEvent* e) {} 

void KeyboardSelection::mousePressEvent(QMouseEvent* e) {} 

void KeyboardSelection::mouseReleaseEvent(QMouseEvent* e) {} 

void KeyboardSelection::wheelEvent(QWheelEvent* e) {}

