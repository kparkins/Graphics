#include "Platoon.h"


Platoon::Platoon(int rows, int cols, Vector3 origin, GeodePtr geom)  {
    this->rows = rows;
    this->cols = cols;
    this->origin = origin;
    m_geometry = geom;
    m_rotation = make_shared<MatrixTransform>();
    m_rotation->addChild(m_geometry);
    m_xOffsetSign = 1.f;
}

Platoon::~Platoon() {

}

void Platoon::invertXOffset() {
    m_xOffsetSign *= -1.f;
}


void Platoon::draw(Matrix4 & c) {
    Matrix4 trans;
    int delta = 8.f;

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            trans.makeTranslate((m_xOffsetSign * i * delta) + origin.x, 0.f, (j * delta) + origin.z);
            Matrix4 res = c * trans;
            m_rotation->draw(res);
        }
    }
    //m_geometry->draw(c);
}
