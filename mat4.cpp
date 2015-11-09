#include "mat4.h"

gfx::mat4::mat4() {
    this->identity();
}

gfx::mat4::mat4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33 ) {
    this->set(m00, m01, m02, m03,
              m10, m11, m12, m13,
              m20, m21, m22, m23,
              m30, m31, m32, m33);
}

gfx::vec4 gfx::mat4::operator*(vec4 & a) {
    vec4 b(0.f, 0.f, 0.f, 0.f);
    
    _mm_store_ps(b.ptr(),
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[0]), _mm_set1_ps(a.x)),
                _mm_mul_ps(_mm_load_ps(m[1]), _mm_set1_ps(a.y))),
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[2]), _mm_set1_ps(a.z)),
                _mm_mul_ps(_mm_load_ps(m[3]), _mm_set1_ps(a.w)))));
    
    return b;
}

gfx::vec4 gfx::mat4::multiply(vec4 & a) {
	vec4 b(0.f, 0.f, 0.f, 0.f);
    
    _mm_store_ps(b.ptr(),
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[0]), _mm_set1_ps(a.x)),
                _mm_mul_ps(_mm_load_ps(m[1]), _mm_set1_ps(a.y))),
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[2]), _mm_set1_ps(a.z)),
                _mm_mul_ps(_mm_load_ps(m[3]), _mm_set1_ps(a.w)))));

	return b;
}

gfx::vec3 gfx::mat4::operator*(vec3 & a) {
    vec3 b(0.f, 0.f, 0.f);

    _mm_store_ps(&b.x,
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[0]), _mm_set1_ps(a.x)),
                _mm_mul_ps(_mm_load_ps(m[1]), _mm_set1_ps(a.y))),
            _mm_mul_ps(_mm_load_ps(m[2]), _mm_set1_ps(a.z))));
    
    return b;
}

gfx::vec3 gfx::mat4::multiply(vec3 & a) {
	vec3 b(0.f, 0.f, 0.f);

    _mm_store_ps(&b.x,
        _mm_add_ps(
            _mm_add_ps(
                _mm_mul_ps(_mm_load_ps(m[0]), _mm_set1_ps(a.x)),
                _mm_mul_ps(_mm_load_ps(m[1]), _mm_set1_ps(a.y))),
            _mm_mul_ps(_mm_load_ps(m[2]), _mm_set1_ps(a.z))));
    
	return b;
}

gfx::mat4& gfx::mat4::rotate_arbitrary(const vec3 &a, float angle) {
    this->identity();
    vec3 b = a.normalized();
    
    float cos0 = cos(angle);
    float sin0 = sin(angle);
    float omcos0 = 1 - cos0;
    float ux = b.x;
    float uy = b.y;
    float uz = b.z;
    float uzsin0 = uz * sin0;
    float uxsin0 = ux * sin0;
    float uysin0 = uy * sin0;
    
    m[0][0] = cos0 + ux * ux * omcos0;
    m[0][1] = uy * ux * omcos0 + uzsin0;
    m[0][2] = uz * ux * omcos0 - uysin0;
    
    m[1][0] = ux * uy * omcos0 - uzsin0;
    m[1][1] = cos0 + uy * uy * omcos0;
    m[1][2] = uz * uy * omcos0 + uxsin0;
    
    m[2][0] = ux * uz * omcos0 + uysin0;
    m[2][1] = uy * uz * omcos0 - uxsin0;
    m[2][2] = cos0 + uz * uz * omcos0;
    
    return *this;
}

gfx::mat4& gfx::mat4::translate(const vec3 &a) {
	this->identity();

	//Configure this matrix to be a translation by vector 'a'
	m[3][0] = a.x;
	m[3][1] = a.y;
	m[3][2] = a.z;

	return *this;
}

gfx::mat4 gfx::mat4::transpose() {
    mat4 b;
    __m128 row0 = _mm_load_ps(m[0]);
    __m128 row1 = _mm_load_ps(m[1]);
    __m128 row2 = _mm_load_ps(m[2]);
    __m128 row3 = _mm_load_ps(m[3]);
    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);
    _mm_store_ps(b.m[0], row0);
    _mm_store_ps(b.m[1], row1);
    _mm_store_ps(b.m[2], row2);
    _mm_store_ps(b.m[3], row3);
    return b;
}

//http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
gfx::mat4 gfx::mat4::inverse() {
    mat4 b;

    return b;
}

gfx::mat4 gfx::mat4::rigid_inverse() {
    mat4 b;
    mat4 c;

    c.identity();
    __m128 row0 = _mm_setr_ps(m[0][0], m[0][1], m[0][2], 0.f);
    __m128 row1 = _mm_setr_ps(m[1][0], m[1][1], m[1][2], 0.f);
    __m128 row2 = _mm_setr_ps(m[2][0], m[2][1], m[2][2], 0.f);
    __m128 row3 = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);

    _MM_TRANSPOSE4_PS(row0, row1, row2, row3);

    _mm_store_ps(b.m[0], row0);
    _mm_store_ps(b.m[1], row1);
    _mm_store_ps(b.m[2], row2);
    _mm_store_ps(b.m[3], row3);

    c[3][0] = -m[3][0];
    c[3][1] = -m[3][1];
    c[3][2] = -m[3][2];

    return b * c;
}


gfx::mat4& gfx::mat4::perspective_projection(float fov, float width, float height, float near, float far) {
    this->identity();
    float aspect = width / height;

    m[0][0] = 1.f / (aspect * tanf(fov / 2.f));
    m[1][1] =  1.f / tan(fov / 2.f);
    m[2][2] = (near + far) / (near - far) ;
    m[2][3] = -1.f;
    m[3][2] = (2.f * near * far) / (near - far);

    return *this;
}

gfx::mat4& gfx::mat4::viewport(float xmin, float xmax, float ymin, float ymax) {
    this->identity();

    m[0][0] = (xmax - xmin) / 2.f;
    m[1][1] = (ymax - ymin) / 2.f;
    m[2][2] = .5f;
    m[3][0] = (xmin + xmax) / 2.f;
    m[3][1] = (ymin + ymax) / 2.f;
    m[3][2] = .5f;
    m[3][3] = 1.f;

    return *this;
}

void gfx::mat4::print(const std::string & comment) {
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;
    
    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*) m;
    float maxValue = fabsf(*(elementPtr++));

    while (elementPtr++ < this->ptr() + 16) {
        if (fabsf(*elementPtr) > maxValue) {
            maxValue = fabsf(*elementPtr);
        }
    }

    while(maxValue >= 10.0) {
        ++integerWidth;
        maxValue /= 10.0; 
    }
    
    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;
    
    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);
    
    //Print the comment
    std::cout << comment << std::endl;
    
    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for(int element = 0; element < 4; element++) {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for(int vector = 0; vector < 4; vector++) {
            cellValue =  m[vector][element];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}