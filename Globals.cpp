#include "Globals.h"

Camera Globals::camera;

Cube Globals::cube(10.0);

Light Globals::light;

DrawData Globals::drawData;
UpdateData Globals::updateData;
Sphere Globals::sphere(4.f, 100, 10);

float Globals::spinValue = .005f;
bool Globals::useSphere = false;
