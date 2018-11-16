#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    //they have to be 90 degrees so theres false
    //if perpandicular, they do not intersect, so return flase;
    //perpen if dot prof = 0
    //second if condition, if dot prod not eqal 0, check if t positive

    vec3 u = ray.endpoint;
    vec3 w = ray.direction;
    vec3 normal = this->normal;
    vec3 x1 = this->x1;

    double intersect = dot(normal, w); // doing the n * w
    double t;
    t = -(dot(normal,(u - x1)) / (intersect)); //from the notes cassio did in class
    Hit t1 = {this, t, true}; //need to check if true or false

    if (intersect == 0) {
      return false;
    }
    else if (intersect != 0 ) {
      if (t >= 0 ) {
         hits.push_back(t1);
         return true;
      }
      else
        return false;
    }
    else {
    return false;
  }
}

vec3 Plane::
Normal(const vec3& point) const
{

    return normal;
}
