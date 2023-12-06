//
// Created by Patrick Cunningham on 05/12/2023.
//

// #ifndef AREA_LIGHT_H
// #define AREA_LIGHT_H
//
// #endif //AREA_LIGHT_H

#pragma once
#include "light.h"

class AreaLight: public Light {
public:
    Vertex position;  // Position of the light
    Vector normal;    // Normal of the light's emitting surface
    float width;      // Width of the area light
    float height;     // Height of the area light
    Colour intensity; // Light intensity

    AreaLight(Vertex &pos, Vector &norm, float w, float h, Colour col);

    AreaLight();

    Vector getRandomOffset();

    bool get_direction(Vertex &surface, Vector &dir);
    void get_intensity(Vertex &surface, Colour &intensity);
};
