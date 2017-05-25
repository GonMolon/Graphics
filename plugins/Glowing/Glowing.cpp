#include "Glowing.h"
#include "glwidget.h"

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

int Glowing::printOglError(const char file[], int line, const char func[]) {
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR) {
        printf("glError in file %s @ line %d: %s function: %s\n",
            file, line, "gluErrorString(glErr)", func);
        retCode = 1;
    }
    return retCode;
}

void Glowing::onPluginLoad() {
    loadShaders();
    initializeVAOInfo();

    glActiveTexture(GL_TEXTURE0);
    glGenTextures( 1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
              GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
           0, GL_RGB, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glwidget()->resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}

void Glowing::onObjectAdd() {} 

void Glowing::preFrame() {} 

void Glowing::postFrame() {} 

bool Glowing::paintGL() {
    // Pass 1. Draw scene
    glClearColor(0,0,0,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    if(drawPlugin()) {
        drawPlugin()->drawScene();
    }

    // Get texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Pass 2. Draw quad using texture
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    program->bind();
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));  

	// Quad covering viewport 
    program->setUniformValue("modelViewProjectionMatrix", QMatrix4x4() );  

    // Draw
    glBindVertexArray(VAO_rect);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    program->release();
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
} 

bool Glowing::drawScene() {return false;} 

void Glowing::keyPressEvent(QKeyEvent *) {} 

void Glowing::keyReleaseEvent(QKeyEvent *) {} 

void Glowing::mouseMoveEvent(QMouseEvent *) {} 

void Glowing::mousePressEvent(QMouseEvent *) {} 

void Glowing::mouseReleaseEvent(QMouseEvent *) {} 

void Glowing::wheelEvent(QWheelEvent *) {}

void Glowing::loadShaders() {
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plugins/Glowing/Glowing.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plugins/Glowing/Glowing.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void Glowing::initializeVAOInfo() {
    // Create VAO for showing the info on the screen
    glGenVertexArrays(1, &VAO_rect);
    glBindVertexArray(VAO_rect);
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

