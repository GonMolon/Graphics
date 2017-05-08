#include "Lighting.h"
#include "glwidget.h"

void Lighting::onPluginLoad() {
    loadShaders();
} 

void Lighting::onObjectAdd() {} 

void Lighting::preFrame() {} 

void Lighting::postFrame() {} 

bool Lighting::paintGL() {return false;} 

bool Lighting::drawScene() {return false;} 

void Lighting::keyPressEvent(QKeyEvent *) {} 

void Lighting::keyReleaseEvent(QKeyEvent *) {} 

void Lighting::mouseMoveEvent(QMouseEvent *) {} 

void Lighting::mousePressEvent(QMouseEvent *) {} 

void Lighting::mouseReleaseEvent(QMouseEvent *) {} 

void Lighting::wheelEvent(QWheelEvent *) {}

void Lighting::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    QString code = readFile("plugins/Lighting/Lighting.vert");
    vs->compileSourceCode(code);

    fs = new QGLShader(QGLShader::Fragment, this);
    code = readFile("plugins/Lighting/Lighting.frag");
    fs->compileSourceCode(code);

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

QString Lighting::readFile(QString path) {
    QFile file(path, this);
    if(!file.open(QIODevice::ReadOnly)) {
        cerr << "Error reading file " << path.toStdString() << ": " << file.errorString().toStdString() << endl;
    }
    QTextStream in(&file);
    QString result;
    while(!in.atEnd()) {
        result += in.readLine() + "\n";
    }
    file.close();
    return result;
}

