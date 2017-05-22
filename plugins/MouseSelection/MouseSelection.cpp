#include "MouseSelection.h"
#include "glwidget.h"

void MouseSelection::onPluginLoad() {
    loadShaders();
} 

void MouseSelection::onObjectAdd() {} 

void MouseSelection::preFrame() {} 

void MouseSelection::postFrame() {} 

bool MouseSelection::paintGL() {return false;} 

bool MouseSelection::drawScene() {return false;} 

void MouseSelection::keyPressEvent(QKeyEvent *) {} 

void MouseSelection::keyReleaseEvent(QKeyEvent *) {} 

void MouseSelection::mouseMoveEvent(QMouseEvent* e) {} 

void MouseSelection::mousePressEvent(QMouseEvent*) {} 

void MouseSelection::mouseReleaseEvent(QMouseEvent* e) {
	if (! (e->button() & Qt::RightButton)) return;
	if (   e->modifiers() & (Qt::ShiftModifier)) return; 
	if (! (e->modifiers() & Qt::ControlModifier)) return;
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	program->bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	for(int i = 0; i < scene()->objects().size(); ++i) {
		program->setUniformValue("color", QVector3D((i+1)/255., 0, 0));
		drawPlugin()->drawObject(i);
	}
	program->release();

	int x = e->x();
	int y = glwidget()->height() - e->y();
	GLubyte read[4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

	scene()->setSelectedObject(read[0]%255-1);

	cout << scene()->selectedObject() << endl;

	glwidget()->update();
} 

void MouseSelection::wheelEvent(QWheelEvent *) {}

void MouseSelection::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plugins/MouseSelection/MouseSelection.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plugins/MouseSelection/MouseSelection.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

