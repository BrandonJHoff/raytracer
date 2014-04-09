#include "Scene.h"
#include <iostream.h>

using namespace std;

Scene::~Scene()
{
	delete background;
	delete object;
	delete camera;
	
	for(int i = 0; i < lights.size(); i++)
		delete lights[i];
}

void Scene::renderScene(int xres, int yres)
{
	Image image(xres, yres);
	Ray ray;
	imageSamples = vector<Vector>(num_samples, Vector(0.5, 0.5, 0.0));
	lensSamples = vector<Vector>(num_samples, Vector(0.0, 0.0, 0.0));
	Color result, final_result;
	RenderContext context(this);
	HitRecord record;
	int count = 0;
	int percent = xres*yres/100;
	int percent_done = 0;
	
	for(int j = 0; j < yres; j++)
	{
		for(int i = 0; i < xres; i++)
		{
			if((count % percent) == 0)
			{
				cout << percent_done << "% done" << endl;
				percent_done++;
			}
			
			count++;
			
			final_result.e[0] = final_result.e[1] = final_result.e[2] = 0;
			
			
			if(sample != NULL)
				sample->getSamples(imageSamples );
			if(filter != NULL)
				filter->getFilter(imageSamples );
			if(camera->samples != NULL)
				camera->samples->getSamples(lensSamples);
			
			for(int k = 0; k < imageSamples.size(); k++)
			{
				
				double x = 2 * (i - xres/2. + imageSamples [k].x())/xres;
				double y = 2 * (j - yres/2. + imageSamples [k].y())/yres;
				
				camera->makeRay(ray, context, x, y, lensSamples[k].x(), lensSamples[k].y());
				record.reset();
				
				if(object->hit(record, context, ray))
				{
					record.mat->shade(result, context, ray, record, 1.0, 1);
				}
				else
				{	
					background->getBackgroundColor(result, context, ray);
				}
				
				final_result += result;
			}			
			
			final_result /= imageSamples .size();
			image.set(i, j, final_result);
		}
	}
	
	//image.bloom(0.1, 0.5, xres, yres);
	image.write("hw11.ppm");
}

void Scene::setBackground(Background* _back)
{
	background = _back;
}

void Scene::setObject(Object* _object)
{
	object = _object;
}

void Scene::setAmbient(const Color& _color)
{
	ambient = _color;
}

void Scene::addLight(Light* _light)
{
	lights.push_back(_light);
}

void Scene::setCamera(Camera* _camera)
{
	camera = _camera;
}

void Scene::setMaxRayDepth(int _depth)
{
	maxDepth = _depth;
}

void Scene::setMinAttenuation(float _attenuation)
{
	attenuation = _attenuation;
}

void Scene::setSampleNum(int _num_samples)
{
	num_samples = _num_samples;
}

void Scene::setSample(Sample* _sample)
{
	sample = _sample;
}

void Scene::setFilter(Filter* _filter)
{
	filter = _filter;
}

void Scene::renderCos(int xres, int yres)
{
	Image image(xres, yres);
	Color result;
	vector<Vector> samples(num_samples, Vector(0.5, 0.5, 0.0));
	int count = 0;
	int percent = xres*yres/100;
	int percent_done = 0;
	float value; 
	
	for(int j = 0; j < yres; j++)
	{
		for(int i = 0; i < xres; i++)
		{
			if((count % percent) == 0)
			{
				cout << percent_done << "% done" << endl;
				percent_done++;
			}
			
			count++;
			
			result.e[0] = result.e[1] = result.e[2] = 0;
			
			
			if(sample != NULL)
				sample->getSamples(samples);
			if(filter != NULL)
				filter->getFilter(samples);
			
			for(int k = 0; k < samples.size(); k++)
			{
						
				double x = 2 * (i - xres/2. + samples[k].x())/xres;
				double y = 2 * (j - yres/2. + samples[k].y())/yres;
				
				value = (cos(500*M_PI*(x*x + y*y)) + 1)/2.0;
				result.e[0] += value;
				result.e[1] += value;
				result.e[2] += value;			
			}			
			
			result /= samples.size();

			image.set(i, j, result);
		}
	}
	
	image.write("hw7.ppm");
}

