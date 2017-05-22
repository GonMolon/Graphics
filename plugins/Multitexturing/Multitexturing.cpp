#include "Multitexturing.h"
#include "glwidget.h"

void Multitexturing::onPluginLoad() {
    loadShaders();
    loadTexture(GL_TEXTURE0, textureId0);
    loadTexture(GL_TEXTURE1, textureId1);
} 

void Multitexturing::onObjectAdd() {} 

void Multitexturing::preFrame() {
    /*// bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 

    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId1);*/
} 

void Multitexturing::postFrame() {
    // // unbind shader
    // program->release();
    // // unbind textures
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, 0);
} 

bool Multitexturing::paintGL() {return false;} 

bool Multitexturing::drawScene() {return false;} 

void Multitexturing::keyPressEvent(QKeyEvent *) {} 

void Multitexturing::keyReleaseEvent(QKeyEvent *) {} 

void Multitexturing::mouseMoveEvent(QMouseEvent *) {} 

void Multitexturing::mousePressEvent(QMouseEvent *) {} 

void Multitexturing::mouseReleaseEvent(QMouseEvent *) {} 

void Multitexturing::wheelEvent(QWheelEvent *) {}

void Multitexturing::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plugins/Multitexturing/Multitexturing.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plugins/Multitexturing/Multitexturing.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void Multitexturing::loadTexture(GLuint GLTEXTURE, GLuint textureID) {
    glActiveTexture(GLTEXTURE);
    QString filename = QFileDialog::getOpenFileName(0, "Open Image", "textures", "Image file (*.png *.jpg)"); 
    QImage img = QGLWidget::convertToGLFormat(QImage(filename));
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

