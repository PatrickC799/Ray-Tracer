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

/* This is the top level for the program you need to create for lab three and four.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// these are core raytracing classes
#include "framebuffer.h"
#include "scene.h"
#include "material_colour.h"

// classes that contain our objects to be rendered, all derived from Object
#include "polymesh_object.h"
#include "sphere_object.h"
#include "plane_object.h"

// classes that contain our lights, all derived from Light
#include "directional_light.h"

// classes that contain the materials applied to an object, all derived from Material
#include "phong_material.h"
#include "falsecolour_material.h"
#include "global_material.h"

//classes that contain cameras, all derived from Camera
#include "simple_camera.h"
#include "full_camera.h"
#include "quadratic_object.h"
#include "CSG_object.h"

using namespace std;

// you will find it useful during development/debugging to create multiple functions that fill out the scene.
void build_scene(Scene& scene)
{
	// scene.ambientLight = Colour(0.2f, 0.2f, 0.2f);
	// The following transform allows 4D homogeneous coordinates to be transformed.It moves the supplied teapot model to somewhere visible.
	Transform * transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f,  // Scale X by 0.5
									  0.0f, 0.0f, 1.0f, -60.0f,  // Scale Y by 0.5
									  0.0f, 1.0f, 0.0f, 20.0f,  // Scale Z by 0.5
									  0.0f, 0.0f, 0.0f, 1.0f); // No translation


	//  Read in the teapot model.
	PolyMesh* pm = new PolyMesh((char *)"teapot.obj", true);
	pm->apply_transform(*transform);

	Sphere* sphere = new Sphere(Vertex(-5.0f, 5.0f, 10.0f), 1.5f);

	DirectionalLight* dl = new DirectionalLight(Vector(0.0f, 0.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 0.0f));
	DirectionalLight* dl1 = new DirectionalLight(Vector(0.0f, 0.0f, 0.5f), Colour(1.0f, 1.0f, 1.0f, 0.0f));

	scene.add_light(dl1);
	scene.add_light(dl);

    Environment* environment = new Environment();

    float ior = 15.0f;
    Colour reflectWeight (0.1f, 0.1f, 0.1f);
    Colour refractWeight (0.9f, 0.9f, 0.9f);

	Colour reflectWeight1 (0, 0.52f, 0.52f);
	Colour refractWeight1 (1.0f, 0.48f, 0.48f);

    GlobalMaterial* gm1 = new GlobalMaterial(environment, &scene, reflectWeight, refractWeight, ior);
	GlobalMaterial* gm2 = new GlobalMaterial(environment, &scene, reflectWeight1, refractWeight1, ior);

	Phong* bp1 = new Phong(&scene, new MaterialColour(0.0f, 0.1f, 0.0f,1.0f), new MaterialColour(0.0f, 0.4f, 0.0f,1.0f), new MaterialColour(0.4f, 0.4f, 0.4f,1.0f), 40.f);
	Phong* bp2 = new Phong(&scene, new MaterialColour(0.1f, 0.1f, 0.1f,1.0f), new MaterialColour(0.5f, 0.0f, 0.0f,1.0f), new MaterialColour(0.4f, 0.4f, 0.4f,1.0f), 40.f);

	Phong *whiteMaterial = new Phong(&scene, new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f),
									 new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f),
									 new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f), 40.f);
	Phong *greenMaterial = new Phong(&scene, new MaterialColour(0.0f, 1.0f, 0.0f, 1.0f),
									 new MaterialColour(0.0f, 0.5f, 0.0f, 1.0f),
									 new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f), 40.f);
	Phong *redMaterial = new Phong(&scene, new MaterialColour(1.0f, 0.0f, 0.0f, 1.0f),
								   new MaterialColour(0.5f, 0.0f, 0.0f, 1.0f),
								   new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f), 40.f);
	Phong *blueMaterial = new Phong(&scene , new MaterialColour(0.0f, 0.0f, 0.5f, 1.0f),
									new MaterialColour(0.0f, 0.0f, 0.5f, 1.0f),
									new MaterialColour(1.0f, 1.0f, 1.0f, 1.0f), 40.f);

	pm->set_material(bp1);

	scene.add_object(pm);

	sphere->set_material(gm1);

	scene.add_object(sphere);

	Plane *ceiling = new Plane(0.0f, 1.0f, 0.0f, -9.0f);
	Plane *floor = new Plane(0.0f, -1.0f, 0.0f, -14.0f);
	Plane *backWall = new Plane(0.0f, 0.0f, 1.0f, -25.0f);
	Plane *leftWall = new Plane(1.0f, 0.0f, 0.0f, -20.0f);
	Plane *rightWall = new Plane(-1.0f, 0.0f, 0.0f, -20.0f);

	ceiling->set_material(whiteMaterial);
	floor ->set_material(whiteMaterial);
	backWall->set_material(blueMaterial);
	leftWall->set_material(redMaterial);
	rightWall->set_material(greenMaterial);

	scene.add_object(ceiling);
	scene.add_object(floor);
	scene.add_object(backWall);
	scene.add_object(leftWall);
	scene.add_object(rightWall);

	// Semi-axes lengths
	float a = 2.0f;  // Semi-axis length in the x-direction
	float b = 1.0f;  // Semi-axis length in the y-direction
	float c = 0.5f;  // Semi-axis length in the z-direction

	// Create an ellipsoid using the original constructor
	Quadratic *ellipsoid1 = new Quadratic(1 / (a * a), 1 / (b * b), 1 / (c * c), 0.0f, 0.0f,
		0.0f,0.0f,0.0f, 0.0f, -1.0f);

	ellipsoid1 ->set_material(gm2);
	scene.add_object(ellipsoid1);
}


// This is the entry point function to the program.
int main(int argc, char *argv[])
{
	int width = 512;
	int height = 512;
	// Create a framebuffer
	FrameBuffer* fb = new FrameBuffer(width, height);
	
	// Create a scene
	Scene scene;
	
	// Setup the scene
	build_scene(scene);
	
	// Declare a camera
	// Camera *camera = new SimpleCamera(0.5f);

	Vertex cameraPosition (0.0f, -3.0f, -5.0f);
	Vector cameraLookAT (0.0f, 0.0f, 1.0f);
	Vector cameraUP (0.0f, 1.0f, 0.0f);

	// Camera* camera = new SimpleCamera(0.5f);
	Camera* camera = new FullCamera(0.5f, cameraPosition, cameraLookAT, cameraUP);
	// Camera* camera = new FullCamera(0.5f, Vertex(-1.0f, 0.0f, 0.0f), Vector(1.0f, 0.0f, 1.0f), Vector(0.0f, 1.0f, 0.0f));
	
	// Camera generates rays for each pixel in the framebuffer and records colour + depth.
	camera->render(scene,*fb);
	
	// Output the framebuffer colour and depth as two images
	fb->writeRGBFile((char *)"test.ppm");
	fb->writeDepthFile((char *)"depth.ppm");
	
	cerr << "\nDone.\n" << flush;
	
	// a debug check to make sure we don't leak hits.
	cerr << "Hit Pool " << Hit::pool_size << " Allocated " << Hit::allocated << "\n" << flush;
	return 0;
}
