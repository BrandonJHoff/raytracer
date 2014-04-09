#include "BVH.h"

BVH::BVH(vector<Object*>& objects)
{
	if(objects.size() == 1)
	{
		left = objects[0];
		right = objects[0];
		bbox = objects[0]->bbox;
	}
	else if(objects.size() == 2)
	{
		left = objects[0];
		right = objects[1];
		bbox = surround(objects[0]->bbox, objects[1]->bbox);
	}
	else
	{
		bbox = objects[0]->bbox;
		for(int i = 1; i < objects.size(); i++)
		{
			bbox = surround(bbox, objects[i]->bbox);
		}

		Point pivot = (bbox.max + bbox.min) / 2.0;
		
		vector<Object*> leftObjects;
		vector<Object*> rightObjects;
		
		split(objects, pivot.x(), 0, leftObjects, rightObjects);
		
		//cout << "object size: " << objects.size() << endl;
		//cout << "left : " << leftObjects.size() << " right: " << rightObjects.size() << endl;

		left = buildBranch(leftObjects, 1);
		right = buildBranch(rightObjects, 1); 
		
		if(left == NULL)
			cout << "left null" << endl;
	}
}
	
BVH::BVH(Object* o1, Object* o2)
{
	left = o1;
	right = o2;
	bbox = surround(o1->bbox, o2->bbox);
}

BVH::~BVH()
{
	delete left;
	delete right;
	delete mat;
}
	
bool BVH::hit(HitRecord& record, 
		const RenderContext& context,
		const Ray& ray) const
{
	float tnear, tfar;
	if(!(bbox.intersect(tnear, tfar, ray)))
		return false;

	bool hitObject1 = false;
	bool hitObject2 = false;

	hitObject1 = left->hit(record, context, ray);
	hitObject2 = right->hit(record, context, ray);

	return (hitObject1 || hitObject2);
}

Object* BVH::buildBranch(vector<Object*>& objects, int axis)
{
	if(objects.size() == 1)
		return objects[0];
	if(objects.size() == 2)
		return new BVH(objects[0], objects[1]);

	BBox tempBBox = objects[0]->bbox;
	for(int i = 1; i < objects.size(); i++)
		tempBBox = surround(tempBBox, objects[i]->bbox);

	Point pivot = (tempBBox.max + tempBBox.min) / 2.0;
		
	vector<Object*> leftObjects;
	vector<Object*> rightObjects;
		
	split(objects, pivot.e[axis], axis, leftObjects, rightObjects);
	
	//cout << "object size: " << objects.size() << endl;
	//cout << "left : " << leftObjects.size() << " right: " << rightObjects.size() << endl;
		
	Object* temp_left = buildBranch(leftObjects, (axis+1) % 3);
	Object* temp_right = buildBranch(rightObjects, (axis+1) % 3); 

	return new BVH(temp_left, temp_right);
}

void BVH::split(vector<Object*>& objects, 
		float pivot, 
		int axis, 
		vector<Object*>& leftObjects, 
		vector<Object*>& rightObjects)
{
	BBox tempBBox;
	float centroid;
	
	for(int i = 0; i < objects.size(); i++)
	{
		tempBBox = objects[i]->bbox;
		centroid = (tempBBox.min.e[axis] + tempBBox.max.e[axis]) / 2.0;
		if(centroid < pivot)
			leftObjects.push_back(objects[i]);
		else
			rightObjects.push_back(objects[i]);
	}

	if(leftObjects.size() == 0)
	{
		for(int j = 0; j < (rightObjects.size()/2); j++)
			leftObjects.push_back(rightObjects[j]);
		vector<Object*> temp;
		for(int k = (rightObjects.size()/2); k < rightObjects.size(); k++)
			temp.push_back(rightObjects[k]);
		rightObjects.clear();
		for(int l = 0; l < temp.size(); l++)
			rightObjects.push_back(temp[l]);
	}
	else if(rightObjects.size() == 0)
	{
		vector<Object*> temp;
		for(int j = 0; j < (leftObjects.size()/2); j++)
			temp.push_back(leftObjects[j]);
		for(int k = (leftObjects.size()/2); k < leftObjects.size(); k++)
			rightObjects.push_back(leftObjects[k]);
		leftObjects.clear();
		for(int l = 0; l < temp.size(); l++)
			leftObjects.push_back(temp[l]);

	}
}