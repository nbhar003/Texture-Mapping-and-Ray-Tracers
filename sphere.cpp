#include "sphere.h"
#include "ray.h"
#include <iostream>

using namespace std;


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{   // TODO
    vec3 u = ray.endpoint;
    vec3 w = ray.direction;
    vec3 center = this->center;
    double sphereRad = this->radius;
    vec3 v = u - center;

    double b = dot(w,v);
    double a = dot(w,w);
    double c = dot(v,v);

    double discrim; //creating the discriminant
    discrim = (b * b) - (c - sphereRad*sphereRad);
  //  cout << discrim << endl;
    if(discrim > 0){
      double quadt1, quadt2 ; // calcualting the quadratic formula
      quadt1 = (-b + pow(discrim, 1/2)); //the rest of the quadractic formula
      quadt2 = (-b - pow(discrim, 1/2));

      Hit h1 = {this, quadt1, true}; //need to check the hit
      Hit h2 = {this, quadt2, true}; //need to check the hit

      if (quadt1 >= 0) {
        hits.push_back(h1);
      }
      if (quadt2 >= 0) {
        hits.push_back(h2);
      }
    }
    // if (discrim < 0 ) {
    //   //cout << "no intersection" << endl;
    //   return false;
    // }
    // else {
    //   //cout << "there is an intersection" << endl;
    //   return true;
    // }
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal

    normal = (point - this->center).normalized();
//    normal[0] = point[0] / this->radius;
//    normal[1] = point[1] / this->radius;
//    normal[2] = point[2] / this->radius;

    return normal;
}
