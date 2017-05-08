#include "ModelInfo2.h"
#include "glwidget.h"
#include <list>

void ModelInfo2::onPluginLoad() {
	vs = new QGLShader(QGLShader::Vertex, this);
	QString code = readFile("plugins/ModelInfo2/ModelInfo2.vert");
	vs->compileSourceCode(code);

	fs = new QGLShader(QGLShader::Fragment, this);
	code = readFile("plugins/ModelInfo2/ModelInfo2.frag");
	fs->compileSourceCode(code);

	program = new QGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	// Create VAO for showing the info on the screen
	glGenVertexArrays(1, &VAO_info);
	glBindVertexArray(VAO_info);
	float z = -0.99999;
	float coords[] = {	-1, -1, z, 
						 1, -1, z, 
						-1,  1, z, 
						 1,  1, z };
	GLuint VBO_coords;
	glGenBuffers(1, &VBO_coords);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
} 

void ModelInfo2::onObjectAdd() {
	updateInfo();
} 

void ModelInfo2::preFrame() {} 

void ModelInfo2::postFrame() {
	updateInfo();

	GLWidget &g = *glwidget();
	g.makeCurrent();

	QString info[] = {
		"Objects: " + QString::number(total_obj),
		"Poligons: " + QString::number(total_pol),
		"Vertex: " + QString::number(total_vert),
		"Tri/Pol: " + QString::number(float(total_tri)/total_pol*100) + "%"
	};
	drawInfo(4, info);
} 

bool ModelInfo2::paintGL() {} 

bool ModelInfo2::drawScene() {} 

void ModelInfo2::keyPressEvent(QKeyEvent *) {} 

void ModelInfo2::keyReleaseEvent(QKeyEvent *) {} 

void ModelInfo2::mouseMoveEvent(QMouseEvent *) {} 

void ModelInfo2::mousePressEvent(QMouseEvent *) {} 

void ModelInfo2::mouseReleaseEvent(QMouseEvent *) {} 

void ModelInfo2::wheelEvent(QWheelEvent *) {}

void ModelInfo2::updateInfo() {
	int act_obj = scene()->objects().size();
	if(total_obj != act_obj) {
		total_obj = act_obj;
		total_tri = 0;
		total_pol = 0;
		total_vert = 0;
		for(int i = 0; i < total_obj; ++i) {
			const Object &obj = scene()->objects()[i];
			for(int j = 0; j < obj.faces().size(); ++j) {
				const Face &face = obj.faces()[i];
				total_vert += face.numVertices();
				++total_pol;
				total_tri += face.numVertices() == 3 ? 1 : 0;
			}
		}
	}
}

void ModelInfo2::drawInfo(int n, QString info[n]) {
	const int size = 1024;
	QImage image(size, size, QImage::Format_ARGB32);
	QColor fill_color(Qt::white);
	fill_color.setAlpha(0);
	image.fill(fill_color);    
	QPainter painter(&image);
	QFont font;
	font.setPixelSize(32);
	painter.setFont(font);
	painter.setPen(QColor(50, 50, 50, 255));
	int x = 15;
	int y = 50;
	for(int i = 0; i < n; ++i) {
		painter.drawText(x, y+40*i, info[i]);
	}
	painter.end();

	// Load image to texture
	const int textureUnit = 5;
	GLuint textureID;

	glActiveTexture(GL_TEXTURE0 + textureUnit);
	QImage im = QGLWidget::convertToGLFormat(image);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im.width(), im.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im.bits());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Active shaders
	program->bind();
	program->setUniformValue("colorMap", textureUnit);
	program->setUniformValue("width", float(glwidget()->width()*2));
	program->setUniformValue("height", float(glwidget()->height()*2));    

	// Draw
	glBindVertexArray(VAO_info);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	// Release resources
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureID);
	program->release();
}

QString ModelInfo2::readFile(QString path) {
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