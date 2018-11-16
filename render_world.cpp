#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <vector>
#include <cmath>

using namespace std;


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
  Object *obj_closest = nullptr;

  hit.t = numeric_limits<decltype(hit.t)>::max();

  for(Object *object : objects) {
    vector<Hit> hits;

    if(object->Intersection(ray, hits)) {
      for(unsigned int i =0; i < hits.size(); i++) {
          if(hits.at(i).t < hit.t && hits.at(i).t > small_t) {
              hit = hits.at(i);
              obj_closest = object;
            }
          }
      }

    }
    //return 0;
    return obj_closest;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    Ray ray; // set up the initial view ray here

    ray.endpoint = camera.position;
    ray.direction = (camera.World_Position(pixel_index) - camera.position).normalized();

    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO
    vec3 color;
    vec3 dummy;
    Hit hit;
    Object *obj; //sphers
    vec3 intersect;
    vec3 norm;
    obj = Closest_Intersection(ray, hit);
    if (obj != nullptr ) {
      //<Hit> hit;
      intersect = ray.Point(hit.t);
      norm = obj->Normal(intersect); //normal at that point
      //plane has no exiting ray but sphere does
      //if (hit.ray_exiting){
      //  norm = norm*(-1);
      //}
      color = obj->material_shader->Shade_Surface(ray,intersect,norm,recursion_depth);
    }
    else { //need to change from dummy
      color = background_shader->Shade_Surface(ray,dummy,dummy,recursion_depth);
    }

    // determine the color here

    return color;
}
