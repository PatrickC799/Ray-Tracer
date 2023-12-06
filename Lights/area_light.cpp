//
// Created by Patrick Cunningham on 05/12/2023.
//

#include "area_light.h"

#include <iostream>
#include <algorithm>
#include <math.h>

AreaLight::AreaLight() {
    Light();
}

AreaLight::AreaLight(Vertex &pos, Vector &norm, float w, float h, Colour col)
{
    Light();

    position = pos;
    normal = norm;
    width = w;
    height = h;
    intensity = col;
    normal.normalise(); // Ensure the normal is a unit vector
}

Vector AreaLight :: getRandomOffset() {
    float randomX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * width;
    float randomY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * height;
    // Assuming the area light is oriented along the Z-axis, and X and Y define the plane
    return Vector(randomX, randomY, 0.0f);
}

bool AreaLight :: get_direction(Vertex &surface, Vector &dir){
    Vector randomOffset = getRandomOffset();
    Vertex lightPoint = position + randomOffset; // Use a random point on the light

    // Calculate the direction from the surface point to the random point on the light
    dir = lightPoint - surface;
    dir.normalise();
    return true;
}

void AreaLight :: get_intensity(Vertex &surface, Colour &level){
    // std::cout << "Babes it is not looking good" << std::endl;
    Vector dir;
    get_direction(surface, dir);

    // Calculate the squared distance before normalizing dir
    float distanceSquared = dir.len_sqr();

    dir.normalise(); // Normalizing the dir after calculating the squared distance

    float attenuation = std::max(0.0f, dir.dot(normal)) / distanceSquared;
    level = intensity * attenuation;

    // std::cout << "Light Level: "
    //       << "R: " << level.r << ", "
    //       << "G: " << level.g << ", "
    //       << "B: " << level.b << std::endl;

}
