#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    //ambient lighting
    color = color + world.ambient_intensity * world.ambient_color * this->color_ambient;

    for (unsigned int i = 0; i < world.lights.size(); i++) {
      vec3 l = world.lights.at(i)->position - intersection_point;
      vec3 light_color = world.lights.at(i)->Emitted_Light(ray)/(l.magnitude_squared());
      double diffuseIntense = dot(same_side_normal, l.normalized());
      //std::cout << same_side_normal << ", " << l << std::endl;
      //need to do max
      //if (diffuseIntense >= 0) { //cant be less than 0
      //  std::cout << "in statement " <<  std::endl;
          color += fmax(diffuseIntense,0) *color_diffuse* light_color;
        //  std::cout << color << std::endl;

    } //end of foor loop

    //RdLd(L*n)
    // L , n
    //use fmax(0,(L*N))
    //vec3 N = same_side_normal;
    //vec3 L = intersection_point;
   //fmax(dot(L,N),0)∗color_diffuse∗light_color
    return color;
}
