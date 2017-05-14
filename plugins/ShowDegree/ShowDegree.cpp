#include "ShowDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad() {
    loadShaders();
    initializeVAOInfo();
} 

void ShowDegree::onObjectAdd() {
    degree = getDegree();
} 

void ShowDegree::preFrame() {} 

void ShowDegree::postFrame() {
    QString info[] = {"Degree: " + QString::number(degree)};
    drawInfo(1, info);
} 

bool ShowDegree::paintGL() {return false;} 

bool ShowDegree::drawScene() {return false;} 

void ShowDegree::keyPressEvent(QKeyEvent *) {} 

void ShowDegree::keyReleaseEvent(QKeyEvent *) {} 

void ShowDegree::mouseMoveEvent(QMouseEvent *) {} 

void ShowDegree::mousePressEvent(QMouseEvent *) {} 

void ShowDegree::mouseReleaseEvent(QMouseEvent *) {} 

void ShowDegree::wheelEvent(QWheelEvent *) {}

float ShowDegree::getDegree() {
    const Object &obj = scene()->objects()[0];
    const vector<Vertex> &vert = obj.vertices();
    cout << &obj << endl;
    vector<int> count(vert.size(), 0);
    for(int i = 0; i < obj.faces().size(); ++i) {
        const Face &face = obj.faces()[i];
        for(int j = 0; j < face.numVertices(); ++j) {
            ++count[face.vertexIndex(j)];
        }
    }
    double total = 0;
    for(int i = 0; i < count.size(); ++i) {
        total += count[i];
    }
    return total/vert.size();
}

void ShowDegree::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plugins/ShowDegree/ShowDegree.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plugins/ShowDegree/ShowDegree.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void ShowDegree::initializeVAOInfo() {
    // Create VAO for showing the info on the screen
    glGenVertexArrays(1, &VAO_info);
    glBindVertexArray(VAO_info);
    float z = -0.99999;
    float coords[] = {  -1, -1, z, 
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

void ShowDegree::drawInfo(int n, QString info[n]) {
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

