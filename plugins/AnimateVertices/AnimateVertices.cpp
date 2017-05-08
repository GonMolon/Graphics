#include "AnimateVertices.h"
#include "glwidget.h"
#include <QFile.h>

void AnimateVertices::onPluginLoad() {
	vs = new QGLShader(QGLShader::Vertex, this);
	QString code = readFile("shaders/animate-vertices-1.vert");
	vs->compileSourceCode(code);

	fs = new QGLShader(QGLShader::Fragment, this);
	code = readFile("shaders/animate-vertices-1.frag");
	fs->compileSourceCode(code);

	program = new QGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	elapsedTimer.start();

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
	timer->start();
}

void AnimateVertices::onObjectAdd() {} 

void AnimateVertices::preFrame() {
	program->bind();
	program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", NM); 
	QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP); 
} 

void AnimateVertices::postFrame() {
	program->release();
} 

bool AnimateVertices::paintGL() {} 

bool AnimateVertices::drawScene() {} 

void AnimateVertices::keyPressEvent(QKeyEvent *) {} 

void AnimateVertices::keyReleaseEvent(QKeyEvent *) {} 

void AnimateVertices::mouseMoveEvent(QMouseEvent *) {} 

void AnimateVertices::mousePressEvent(QMouseEvent *) {} 

void AnimateVertices::mouseReleaseEvent(QMouseEvent *) {} 

void AnimateVertices::wheelEvent(QWheelEvent *) {}

QString AnimateVertices::readFile(QString path) {
	QFile file(path, this);
	if(!file.open(QIODevice::ReadOnly)) {
		cerr << "Error reading file " << path.toStdString() << ": " << file.errorString().toStdString() << endl;
	}
	QTextStream in(&file);
	QString result;
	while(!in.atEnd()) {
	    result += in.readLine() + '\n';    
	}
	file.close();
	return result;
}