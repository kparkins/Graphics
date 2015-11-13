#ifndef GFX_CAMERA_H
#define GFX_CAMERA_H

#include <memory>

#include "mat4.h"
#include "vec3.h"

using std::shared_ptr;

namespace gfx {
    class camera {

    public:

        camera();
        ~camera();

        void update();
        void reset();

        mat4& matrix();
        mat4& inverse_matrix();

        void set(vec3 & e, vec3 & d, vec3 & up);
        void set(float fov);

        vec3 e();
        vec3 d();
        vec3 up();

    protected:

        mat4 m_matrix;   //camera Matrix
        mat4 m_inverse;  //Inverse of camera Matrix
        vec3 m_center;   //Center of Projection
        vec3 m_lookat;   //Look At
        vec3 m_up;  //Up Vector ^
        float m_fov;

    };

    typedef shared_ptr<camera> camera_ptr;
}
#endif
