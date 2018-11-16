#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    // TODO: determine the color
    //has shader pointer
  //  Shader *shader;
    //shade surface function:
    /*
color = shader->shader_surface():
//then, need to cast ray and create r vector
r : ray on the surface (reflected direciton)
need to compute vector direction
c = (1 - reflectivity).c + reflectivity + world->Cast_Ray(.);
w.Cast_Ray TODO: This is a function {
RS -> shader_surface() {
pass recursion_depth + 1 into the world cast ray function!!
w.Cast_Ray
RS-> Shade_Surface
} //need to check if iin the recursive numeric_limits
recrsive_depth <= recursive_limit
}

    */
    return color;
}



/* how to do the reflective shader:
have v, r and n which are all unit vectors
how to do you find v?
r  = 2(v*n)*n vector - v (might need to normalized)

*/
