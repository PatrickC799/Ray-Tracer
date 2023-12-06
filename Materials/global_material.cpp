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

#include "global_material.h"

#include <math.h>

GlobalMaterial::GlobalMaterial(Environment* p_env, Scene* p_sce, Colour p_reflect_weight, Colour p_refract_weight, float p_ior)
: environment(p_env), scene(p_sce), reflect_weight(p_reflect_weight), refract_weight(p_refract_weight), ior(p_ior)
{

}

Vector reflect(Vector incident, Vector& normal) {

    return incident - 2 * (incident.dot(normal)) * normal;
}

bool refract(Vector& incident, Vector& normal, float ior, Vector& refractDir) {
    float cosi = -incident.dot(normal);
    float etai = 1, etat = ior;
    Vector n = normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n= -normal;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) {
        return true; // Total internal reflection
    } else {
        refractDir = eta * incident + (eta * cosi - sqrtf(k)) * n;
        return false;
    }
}

float computeFresnel(Vector& incident, Vector& normal, float ior) {
    float cosi = incident.dot(normal);
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    if (sint >= 1) {
        return 1; // Total internal reflection
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (Rs * Rs + Rp * Rp) / 2;
    }
}


// reflection and recursion computation goes here
Colour GlobalMaterial::compute_once(Ray& viewer, Hit& hit, int recurse)
{
    if (recurse <= 0) return Colour(); // Recursion limit

    // Calculate reflected ray
    Vector reflectDir = reflect(viewer.direction, hit.normal);
    Ray reflectedRay(hit.position + 0.0001f * reflectDir, reflectDir);
    Colour reflectedColor;
    float reflectedDepth;
    if (scene != nullptr) {
        scene->raytrace(reflectedRay, recurse - 1, reflectedColor, reflectedDepth);
    } else {
        std::cout << "Didn't work babes " << recurse << std::endl;
    }

    // Calculate refracted ray
    Vector refractDir;
    refractDir.normalise();
    bool tir = refract(viewer.direction, hit.normal, ior, refractDir);
    Colour refractedColor;
    float refractedDepth;
    if (!tir) {
        Ray refractRay (hit.position + 0.0001f * refractDir, refractDir);
        scene->raytrace(refractRay, recurse - 1, refractedColor, refractedDepth);
    }

    // Compute Fresnel effect
    float fresnelEffect = computeFresnel(viewer.direction, hit.normal, ior);

    // Combine reflected and refracted colors based on Fresnel effect
    Colour finalColor;
    finalColor.r = fresnelEffect * reflectedColor.r + (1 - fresnelEffect) * (tir ? 0 : refractedColor.r);
    finalColor.g = fresnelEffect * reflectedColor.g + (1 - fresnelEffect) * (tir ? 0 : refractedColor.g);
    finalColor.b = fresnelEffect * reflectedColor.b + (1 - fresnelEffect) * (tir ? 0 : refractedColor.b);
    finalColor.a = 1.0f; // Assuming alpha is always 1, adjust if needed

    // int AO_SAMPLES = 128; // Number of samples for AO, adjust as needed
    // float aoFactor = scene->computeAmbientOcclusion(hit, AO_SAMPLES);
    // finalColor.a *= (1.0 - aoFactor * scale);
    // finalColor.r *= (1.0 - aoFactor * scale);
    // finalColor.g *= (1.0 - aoFactor * scale);
    // finalColor.b *= (1.0 - aoFactor * scale);

    return finalColor;

}

Colour GlobalMaterial::compute_per_light(Vector& viewer, Hit& hit, Vector& ldir)
{
	Colour result;


	return result;
}

