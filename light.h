#ifndef GFX_LIGHT_H
#define GFX_LIGHT_H

#include "mat4.h"
#include "vec4.h"
#include "color.h"
#include "vec3.h"
#include "material_factory.h"

#include <memory>
#include <vector>

namespace  gfx {
    class light {

    public:

        light();
        virtual ~light();

        void id(int id);
        void bind();
        void unbind();

        int id();
        vec4 position();
        float constant_attenuation();
        float linear_attenuation();
        float quadratic_attentuation();
        float angle();
        float exponent();

        void constant_attenuation(float c);
        void linear_attenuation(float c);
        void quadratic_attentuation(float c);
        void position(const vec4 & pos);
        void angle(float angle);
        void direction(const vec3 & lookat);
        void exponent(float exp);
        void directional(bool on);
        void ambient(color c);
        void diffuse(color c);
        void specular(color c);

    protected:

        color m_ambient;
        color m_diffuse;
        color m_specular;

        float m_constantatt;
        float m_linearatt;
        float m_quadraticatt;
        float m_exponent;
        float m_angle;

        bool m_directional;

        vec3 m_direction;
        vec4 m_position;

        int m_id;

    private:

        static unsigned int m_light_counter;

    };

    typedef std::shared_ptr<light> light_ptr;
}

#endif
