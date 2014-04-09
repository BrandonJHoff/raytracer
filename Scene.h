#ifndef _SCENE_H_
#define _SCENE_H_

#include "Background.h"
#include "Object.h"
#include "Color.h"
#include "Light.h"
#include "Camera.h"
#include "Image.h"
#include "Sample.h"
#include "Filter.h"
#include <vector>

class Object;
class Background;

class Scene
{
public:
	Scene() {}
	~Scene();
	void renderScene(int xres, int yres);
	void setBackground(Background* _back);
	void setObject(Object* _object);
	void setAmbient(const Color& _color);
	void addLight(Light* _light);
	void setCamera(Camera* _camera);
	void setMaxRayDepth(int _depth);
	void setMinAttenuation(float _attenuation);
	void setSampleNum(int _num_samples);
	void setSample(Sample* _sample);
	void setFilter(Filter* _filter);
	void renderCos(int xres, int yres);
	
	Background* background;
	Object* object;
	Color ambient;
	vector<Light*> lights;
	Camera* camera;
	int maxDepth;
	float attenuation;
	int num_samples;
	Sample* sample;
	Filter* filter;

	vector<Vector> imageSamples;
	vector<Vector> lensSamples;

};

#endif 
