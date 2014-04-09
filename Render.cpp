#include "Scene.h"
#include "BBox.h"
#include "BVH.h"
#include "ConstantBackground.h"
#include "Color.h"
#include "Group.h"
#include "Sphere.h"
#include "LambertianMaterial.h"
#include "Plane.h"
#include "Normal.h"
#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Image.h"
#include "PointLight.h"
#include "PinholeCamera.h"
#include "Disk.h"
#include "Ring.h"
#include "Triangle.h"
#include "Box.h"
#include "Heightfield.h"
#include "PhongMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include "Object.h"
#include "CheckerMaterial.h"
#include "PhongImageMaterial.h"
#include "SpherePolar.h"
#include "PhongMarbleMaterial.h"
#include "TileMaterial.h"
#include "JitterSample.h"
#include "BoxFilter.h"
#include "TentFilter.h"
#include "CubicSplineFilter.h"
#include "PhongVolumeMaterial.h"
#include "Matrix.h"
#include "Instance.h"
#include "ThinLensCamera.h"
#include "InfiniteAreaLight.h"
#include "TextureBackground.h"
#include "ImageMaterial.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//int xres = 512;
//int yres = 320;
int xres = 2560;
int yres = 1600;

Scene* mainScene;
vector<Object*> objects;

static void error()
{
	cerr << "Error reading triangle mesh\n";
	exit(1);
}


Scene* hw4()
{
	Scene* scene = new Scene();
	scene->setBackground(new TextureBackground(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 1.3));
	
	Group* world = new Group();
	
	Material* groundmatl = new LambertianMaterial(Color(0.25, 0.95, 0.25), .6, .4);
	world->addObject(new Plane(groundmatl, Point(0,0,2.5), Normal(0,0,1)));
	
	for(int i=0;i<4;i++){
		double eta = 1 + i*0.5 + .05;
		Material* transp_matl = new DielectricMaterial(eta, 100);
		Point corner(i*1.3 - 4, -3, 2.5+1.e-2);
		Vector size(0.20, 2.5, 1.4);
		world->addObject(new Box(transp_matl,
								 corner, corner+size));
	}
	
	Material* ringmatl = new LambertianMaterial(Color(.6, .6, .9), .6, .4);
	for(int i=0;i<9;i++){
		double r = .30;
		Point center(-6, 0, 2.5+r);
		Vector offset(2.25*r, 0, 0);
		world->addObject(new Ring(ringmatl,
								  center+offset*i, Normal(0.2, -1, -0.2), r*0.5, r));
	}
	Material* ball_matl = new MetalMaterial(Color(0.8, 0.8, 0.8), 100);
	world->addObject(new Sphere(ball_matl, Point(-6, 3.5, 3.5), 1.0));
	world->addObject(new Sphere(ball_matl, Point(-7, 2.5, 2.5), 1.0));
	world->addObject(new Sphere(ball_matl, Point(-5, 4.5, 4.5), 1.0));
	
	Material* phongmatl = new PhongMaterial(Color(0.3, 0.3, 0.9), 0.6, 0.4,
											Color(1,1,1), 30);
	for (int i=0; i<5; ++i)
		world->addObject(new Sphere(phongmatl, Point(-4.5 + i, 3.5 + i/4., 3 + i/2.), 0.5));
	
	Material* phongmatl2 = new PhongMaterial(Color(0.9, 0.3, 0.3), 0.6, 0.4,
											 Color(1,1,1), 30);
	world->addObject(new Box(phongmatl2,
							 Point(-8.5, -8.5, 2), Point(-4.5, -4.5, 8)));
	scene->setObject(world);
	
	scene->setAmbient(Color(.0, .0, .0));
	scene->addLight(new InfiniteAreaLight(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 1.3));
	
	scene->setCamera(new ThinLensCamera(Point(8.3, -18, 7),
                                     	 Point(-4.7, 2.5, 3.),
                                     	Vector(0, 0, 1),
										15.0, (float)(xres/yres), 25, .001));
	scene->setMaxRayDepth(25);
	scene->setMinAttenuation(.01);
	scene->setSampleNum(100);
	scene->setSample(new JitterSample());
	scene->setFilter(new TentFilter());

	return scene;
}

Scene* focus()
{
	Scene* scene = new Scene();
	scene->setBackground(new TextureBackground(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 2.5));
	Group* world = new Group();
	Material* ball_matl = new MetalMaterial(Color(0.8, 0.8, 0.8), 100);
	world->addObject(new Sphere(new LambertianMaterial(Color(.1, .3, .9), .7, .3),
								Point(1.5*20, 3.5, 4), 2.4));
	world->addObject(new Sphere(ball_matl,
								Point(-0.5, -1.5, 2), 1.8));
	world->addObject(new Sphere(new LambertianMaterial(Color(1,.9,.1), .6, .4),
								Point(0.5*-25, 1.5, 1), 2.5));
	world->addObject(new Plane(new LambertianMaterial(Color(.4, .4, .7), .4, .6),
							   Point(0,0,0), Normal(0,0,1)));
	
	scene->setObject(world);
	
	scene->setAmbient(Color(0, 0, 0));
	scene->addLight(new InfiniteAreaLight(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 2.5));
	
	scene->setCamera(new ThinLensCamera(Point(-30, -2, 5.2),
                                     	Point(1,1, 2.6),
                                     	Vector(0, 0, 1),
										22.0, (float)(xres)/(float)(yres), 30, 4));
	
	scene->setMaxRayDepth(25);
	scene->setMinAttenuation(.01);
	scene->setSampleNum(100);
	scene->setSample(new JitterSample());
	scene->setFilter(new TentFilter());
	
	return scene;
}

Scene* water()
{
	Scene* scene = new Scene();
	scene->setBackground(new TextureBackground(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 1.3));
	Group* world = new Group();
	
	world->addObject(new Plane(new LambertianMaterial(Color(.4, .7, .4), .4, .6),
							   Point(0,0,0), Normal(0,0,1)));
	
	Material* transp_matl = new DielectricMaterial(1.333, 100);
	
	Matrix m = scale(1, 1, .5);
	world->addObject(new Instance(m, new Sphere(transp_matl, Point(0, 0, .1), 2.0)));

	scene->setObject(world);
	
	scene->setAmbient(Color(0, 0, 0));
	scene->addLight(new InfiniteAreaLight(Point(0, 0, 10), 1000.0, Vector(0,0,1), Vector(1, 0, 0), "midday.ppm", 1.3));
	
	scene->setCamera(new ThinLensCamera(Point(0, -25, 5),
                                     	Point(0,0,1),
                                     	Vector(0, 0, 1),
										15.0, (float)(xres/yres), 25, 2));
	
	scene->setMaxRayDepth(25);
	scene->setMinAttenuation(.01);
	scene->setSampleNum(4);
	scene->setSample(new JitterSample());
	scene->setFilter(new TentFilter());
	
	
	return scene;
}

int main()
{
	
	//mainScene = hw4();
	mainScene = focus();
	// mainScene = water();
	mainScene->renderScene(xres, yres);
	
	return 0;
}