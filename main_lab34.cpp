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
#include "area_light.h"

// classes that contain the materials applied to an object, all derived from Material
#include "phong_material.h"
#include "falsecolour_material.h"
#include "global_material.h"

//classes that contain cameras, all derived from Camera
#include <complex>

#include "simple_camera.h"
#include "full_camera.h"
#include "quadratic_object.h"
#include "CSG_object.h"

using namespace std;

// you will find it useful during development/debugging to create multiple functions that fill out the scene.
void build_scene(Scene& scene)
{
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
	Phong *brownMaterial = new Phong(&scene , new MaterialColour(0.05f, 0.02f, 0.01f, 1.0f),
									new MaterialColour(0.4f, 0.2f, 0.1f, 1.0f),
									new MaterialColour(0.2f, 0.1f, 0.05f, 1.0f),30.0f);
	Phong *goldMaterial = new Phong(&scene, new MaterialColour(0.24725f, 0.1995f, 0.0745f, 1.0f),
									new MaterialColour(0.75164f, 0.60648f, 0.22648f, 1.0f),
									new MaterialColour(0.628281f, 0.555802f, 0.366065f, 1.0f), 51.2f);


	DirectionalLight* dl = new DirectionalLight(Vector(0.0f, 0.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 0.0f));
	scene.add_light(dl);

	// The following transform allows 4D homogeneous coordinates to be transformed.It moves the supplied teapot model to somewhere visible.
	Transform * transform = new Transform(1.0f, 0.0f, 0.0f, 7.0f,  // Scale X by 0.5
									  0.0f, 0.0f, 1.0f, -75.0f,  // Scale Y by 0.5
									  0.0f, 1.0f, 0.0f, 20.0f,  // Scale Z by 0.5
									  0.0f, 0.0f, 0.0f, 1.0f); // No translation

	//  Read in the teapot model.
	PolyMesh* teapot = new PolyMesh((char *)"teapot.obj", true);
	// Spheres for tree trunk
	Sphere* sphere = new Sphere(Vertex(-15.0f, -26.0f, 20.0f), 4.0f);
	Sphere* sphere1 = new Sphere(Vertex(-15.0f, -25.5f, 20.0f), 4.0f);
	Sphere* sphere2 = new Sphere(Vertex(-15.0f, -25.0f, 20.0f), 4.0f);
	Sphere* sphere3 = new Sphere(Vertex(-15.0f, -24.5f, 20.0f), 4.0f);
	Sphere* sphere4 = new Sphere(Vertex(-15.0f, -24.0f, 20.0f), 4.0f);
	// Spheres for tree
	Sphere* leaves = new Sphere(Vertex(-15.0f, -20.0f, 22.0f), 6.0f);
	Sphere* leaves2 = new Sphere(Vertex(-15.0f, -19.0f, 22.0f), 6.0f);
	Sphere* leaves3 = new Sphere(Vertex(-15.0f, -15.0f, 22.0f), 5.0f);
	Sphere* leaves4 = new Sphere(Vertex(-15.0f, -14.0f, 22.0f), 5.0f);
	Sphere* leaves5 = new Sphere(Vertex(-15.0f, -10.0f, 22.0f), 4.0f);
	Sphere* leaves6 = new Sphere(Vertex(-15.0f, -9.0f, 22.0f), 4.0f);
	Sphere* leaves7 = new Sphere(Vertex(-15.0f, -6.0f, 22.0f), 2.0f);
	Sphere* leaves8 = new Sphere(Vertex(-15.0f, -5.0f, 22.0f), 2.0f);
	// Christmas Tree Baubles
	Sphere* bauble = new Sphere(Vertex(-15.0f, -20.0f, 16.0f), 1.0f);
	Sphere* bauble2 = new Sphere(Vertex(-8.0f, -12.0f, 12.0f), 1.0f);
	Sphere* bauble3 = new Sphere(Vertex(-14.0f, -6.0f, 18.0f), 1.0f);
	// Walls
	Plane *ceiling = new Plane(0.0f, 1.0f, 0.0f, -25.0f);
	Plane *floor = new Plane(0.0f, -1.0f, 0.0f, -25.0f);
	Plane *backWall = new Plane(0.0f, 0.0f, 1.0f, -24.0f);
	Plane *frontWall = new Plane(0.0f, 0.0f, -1.0f, 26.0f);
	Plane *rightWall = new Plane(1.0f, 0.0f, 0.0f, -25.0f);
	Plane *leftWall = new Plane(-1.0f, 0.0f, 0.0f, -25.0f);
	// Ellipsoid
	// Semi-axes lengths
	float a = 2.0f;  // Semi-axis length in the x-direction
	float b = 1.0f;  // Semi-axis length in the y-direction
	float c = 0.5f;  // Semi-axis length in the z-direction

	// Create an ellipsoid using the original constructor
	Quadratic *ellipsoid1 = new Quadratic(1 / (a * a), 1 / (b * b), 1 / (c * c), 0.0f, 0.0f,
	0.0f,0.0f,0.0f, 0.0f, -1.0f);

	Quadratic *ellipsoid2 = new Quadratic(1 / (a * a * a), 1 / (b * b * b), 1 / (c * c * c), 0.0f, 0.0f,
	0.0f,0.0f,0.0f, 0.0f, -1.0f);

	// CSG Objects
	CSG* trunk = new CSG(CSG::CSG_UNION, sphere, sphere1);
	trunk = new CSG(CSG::CSG_UNION, trunk, sphere2);
	trunk = new CSG(CSG::CSG_UNION, trunk, sphere3);
	trunk = new CSG(CSG::CSG_UNION, trunk, sphere4);

	CSG* tree = new CSG(CSG::CSG_INTER, leaves, leaves2);
	CSG* tree2 = new CSG(CSG::CSG_INTER, leaves3, leaves4);
	CSG* tree3 = new CSG(CSG::CSG_INTER, leaves5, leaves6);
	CSG* tree4 = new CSG(CSG::CSG_INTER, leaves7, leaves8);

	CSG* ellipsoid = new CSG(CSG::CSG_DIFF, ellipsoid1, ellipsoid2);

	// Apply Transforms
	teapot->apply_transform(*transform);

	// Set Materials
	teapot->set_material(goldMaterial);
	sphere->set_material(brownMaterial);
	sphere1->set_material(brownMaterial);
	sphere2->set_material(brownMaterial);
	sphere3->set_material(brownMaterial);
	sphere4->set_material(brownMaterial);
	ceiling->set_material(whiteMaterial);
	floor ->set_material(whiteMaterial);
	backWall->set_material(blueMaterial);
	leftWall->set_material(redMaterial);
	rightWall->set_material(greenMaterial);
	frontWall->set_material(blueMaterial);
	ellipsoid1 ->set_material(gm2);
	ellipsoid2->set_material(gm2);
	leaves ->set_material(greenMaterial);
	leaves2 ->set_material(greenMaterial);
	leaves3 ->set_material(greenMaterial);
	leaves4 ->set_material(greenMaterial);
	leaves5 ->set_material(greenMaterial);
	leaves6 ->set_material(greenMaterial);
	leaves7 ->set_material(greenMaterial);
	leaves8 ->set_material(greenMaterial);
	bauble->set_material(goldMaterial);
	bauble2->set_material(goldMaterial);
	bauble3->set_material(goldMaterial);

	// Add objects into the Scene
	scene.add_object(teapot);
	// scene.add_object(sphere);
	scene.add_object(ceiling);
	scene.add_object(floor);
	scene.add_object(backWall);
	scene.add_object(leftWall);
	scene.add_object(rightWall);
	// scene.add_object(frontWall);
	// scene.add_object(ellipsoid1);
	scene.add_object(ellipsoid2);
	scene.add_object(trunk);
	scene.add_object(tree);
	scene.add_object(tree2);
	scene.add_object(tree3);
	scene.add_object(tree4);

	scene.add_object(bauble);
	scene.add_object(bauble2);
	scene.add_object(bauble3);

	scene.add_object(ellipsoid);
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

	Vertex cameraPosition (0.0f, 0.0f, -5.0f);
	Vector cameraLookAT (0.0f, 0.0f, 1.0f);
	Vector cameraUP (0.0f, 1.0f, 0.0f);

	// Camera* camera = new SimpleCamera(0.5f);
	Camera* camera = new FullCamera(0.4f, cameraPosition, cameraLookAT, cameraUP);
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
