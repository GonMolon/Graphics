#include "BoundingBox.h"
#include "glwidget.h"

void BoundingBox::onPluginLoad() {
	loadShaders();

	GLfloat cube_coords[]={
		1, 1, 1,
		0, 1, 1,
		1, 0, 1,
		0, 0, 1,
		1, 0, 0,
		0, 0, 0,
		1, 1, 0,
		0, 1, 0,
		1, 1, 1,
		0, 1, 1,
		0, 1, 1,
		0, 1, 0,
		0, 0, 1,
		0, 0, 0,
		1, 0, 1,
		1, 0, 0,
		1, 1, 1,
		1, 1, 0
	};
	GLfloat cube_colors[]={
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0
	};

	glGenVertexArrays(1, &VAO_box);
	glBindVertexArray(VAO_box);

	GLuint VBO_coords;
	glGenBuffers(1, &VBO_coords);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_coords), cube_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLuint VBO_colors;
	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
} 

void BoundingBox::onObjectAdd() {} 

void BoundingBox::preFrame() {} 

void BoundingBox::postFrame() {
	program->bind();
	GLint polygonMode;                              // en que polygon mode estamos? (GL_LINE, GL_FILL, GL_POINTS)
	glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // pinta el wireframe
	drawBoxes();                                    // de las cajas contenedoras de todos los objetos de la escena
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);  // reestablecer el poygon mode anterior
	program->release();
}

void BoundingBox::drawBoxes() {
	QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);

	Scene* scn = scene();
	const vector<Object> &obj = scn->objects();
	for (int i = 0; i < obj.size(); ++i) {
	  program->setUniformValue("boundingBoxMin", obj[i].boundingBox().min());
	  program->setUniformValue("boundingBoxMax", obj[i].boundingBox().max());
	  glBindVertexArray(VAO_box);
	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);
	  glBindVertexArray(0);
	}
}

bool BoundingBox::paintGL() {return false;} 

bool BoundingBox::drawScene() {return false;} 

void BoundingBox::keyPressEvent(QKeyEvent *) {} 

void BoundingBox::keyReleaseEvent(QKeyEvent *) {} 

void BoundingBox::mouseMoveEvent(QMouseEvent *) {} 

void BoundingBox::mousePressEvent(QMouseEvent *) {} 

void BoundingBox::mouseReleaseEvent(QMouseEvent *) {} 

void BoundingBox::wheelEvent(QWheelEvent *) {}

void BoundingBox::loadShaders() {
	vs = new QGLShader(QGLShader::Vertex, this);
	vs->compileSourceFile("plugins/BoundingBox/BoundingBox.vert");

	fs = new QGLShader(QGLShader::Fragment, this);
	fs->compileSourceFile("plugins/BoundingBox/BoundingBox.frag");

	program = new QGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
}

