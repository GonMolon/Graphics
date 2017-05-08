#include "ModelInfo1.h"
#include "glwidget.h"

void ModelInfo1::onPluginLoad() {
	writeStats();
} 

void ModelInfo1::onObjectAdd() {
	writeStats();
} 

void ModelInfo1::preFrame() {} 

void ModelInfo1::postFrame() {} 

bool ModelInfo1::paintGL() {} 

bool ModelInfo1::drawScene() {} 

void ModelInfo1::keyPressEvent(QKeyEvent *) {} 

void ModelInfo1::keyReleaseEvent(QKeyEvent *) {} 

void ModelInfo1::mouseMoveEvent(QMouseEvent *) {} 

void ModelInfo1::mousePressEvent(QMouseEvent *) {} 

void ModelInfo1::mouseReleaseEvent(QMouseEvent *) {} 

void ModelInfo1::wheelEvent(QWheelEvent *) {}

void ModelInfo1::writeStats() {
	int total_obj = scene()->objects().size();
	int total_tri = 0;
	int total_pol = 0;
	int total_vert = 0;
	for(int i = 0; i < total_obj; ++i) {
		const Object &obj = scene()->objects()[i];
		for(int j = 0; j < obj.faces().size(); ++j) {
			const Face &face = obj.faces()[i];
			total_vert += face.numVertices();
			++total_pol;
			total_tri += face.numVertices() == 3 ? 1 : 0;
		}
	}
	cout << "Objects: " << total_obj << endl;
	cout << "Poligons: " << total_pol << endl;
	cout << "Vertex: " << total_vert << endl;
	cout << "Triangles/Poligons: " << double(total_tri)/total_pol * 100 << "%" << endl;
}