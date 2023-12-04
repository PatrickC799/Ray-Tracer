/****************************************************************************
*
* krt - Ken's Raytracer - Coursework Edition. (C) Copyright 1993-2022.
*
* I've put a lot of time and effort into this code. For the last decade
* it's been used to introduce hundreds of students at multiple universities
* to raytracing. It forms the basis of your coursework but you are free
* to continue using/developing forever more. However, I ask that you don't
* share the code or your derivitive versions publicly. In order to continue
* to be used for coursework and in particular assessment it's important that
* versions containing solutions are not searchable on the web or easy to
* download.
*
* If you want to show off your programming ability, instead of releasing
* the code, consider generating an incredible image and explaining how you
* produced it.
*/

#include "quadratic_object.h"
#include <math.h>

using namespace std;

Quadratic::Quadratic(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j) : A(a),
  B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j) {

  next = (Object *)0;
}

Hit *Quadratic::intersection(Ray ray)
{
  float a = A * ray.direction.x * ray.direction.x +
          B * ray.direction.y * ray.direction.y +
          C * ray.direction.z * ray.direction.z +
          D * ray.direction.x * ray.direction.y +  // Missing cross-product term for D
          E * ray.direction.x * ray.direction.z +  // Missing cross-product term for E
          F * ray.direction.y * ray.direction.z;   // Missing cross-product term for F

  float b = 2 * A * ray.position.x * ray.direction.x +
            2 * B * ray.position.y * ray.direction.y +
            2 * C * ray.position.z * ray.direction.z +
            D * (ray.position.x * ray.direction.y + ray.direction.x * ray.position.y) +  // Cross-product term for D
            E * (ray.position.x * ray.direction.z + ray.direction.x * ray.position.z) +  // Cross-product term for E
            F * (ray.position.y * ray.direction.z + ray.direction.y * ray.position.z) +  // Cross-product term for F
            G * ray.direction.x +  // Missing linear term for G
            H * ray.direction.y +  // Missing linear term for H
            I * ray.direction.z;   // Missing linear term for I

  float c = A * ray.position.x * ray.position.x +
            B * ray.position.y * ray.position.y +
            C * ray.position.z * ray.position.z +
            D * ray.position.x * ray.position.y +  // Missing cross-product term for D
            E * ray.position.x * ray.position.z +  // Missing cross-product term for E
            F * ray.position.y * ray.position.z +  // Missing cross-product term for F
            G * ray.position.x +  // Missing linear term for G
            H * ray.position.y +  // Missing linear term for H
            I * ray.position.z +  // Missing linear term for I
            J;  // Constant term J

  // Calculate discriminant
  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) {
    return nullptr; // No intersection
  }

  // Calculate the two points of intersection t0 and t1
  float t0 = (-b - sqrt(discriminant)) / (2*a);
  float t1 = (-b + sqrt(discriminant)) / (2*a);

  if (t0 > t1) {
    std::swap(t0, t1);
  }

  // Check if the intersections are in the valid range
  if (t0 > 0) {
    Hit* hit = new Hit();
    hit->t = t0;
    hit->position = ray.position + ray.direction * t0;
    hit->normal = hit->position;
    hit->normal.normalise();
    hit->what = this;/* Material of the surface */;
    return hit;
  } else if (t1 > 0) {
    Hit* hit = new Hit();
    hit->t = t1;
    hit->position = ray.position + ray.direction * t1;
    hit->normal = hit->position;
    hit->normal.normalise();
    hit->what = this/* Material of the surface */;
    return hit;
  }

  return nullptr; // No valid intersection
}


void Quadratic::apply_transform(Transform& trans)
{

}