#include "Heightfield.h"

struct heightfieldInfo
{
	float zu,zv,zuv,sx,sy,dx,dy;
};

Heightfield::Heightfield(Material* _material, string filename, const Point& _min, const Point& _max)
{
	mat = _material;
	Pmin = _min;
	Pmax = _max;
	D = Pmax - Pmin;
	
	readData(filename);
	
	cellsize = D/Vector(nx, ny, 1);
	
	float dz = maxz - minz;
	float dz2 = Pmax.z() - Pmin.z();
	float ratio = dz2/dz;
		
	boundingBox = new Box(_material, Pmin, Pmax);
}

Heightfield::~Heightfield()
{
	delete boundingBox;
	delete[] data;
	delete[] p;
	delete mat;
}

bool Heightfield::hit(HitRecord& record, 
					  const RenderContext& context,
					  const Ray& ray) const
{
	float tnear, tfar;
	if(boundingBox->intersect(tnear, tfar, ray))
	{
		Point P = ray.point(tnear);
		int Lx, Ly;
		Lx = (int)((P.x() - Pmin.x())/cellsize.x());
		if(Lx < 0)
			Lx = 0;
		else if(Lx >= nx)
			Lx = nx - 1;
		Ly = (int)((P.y() - Pmin.y())/cellsize.y());
		if(Ly < 0)
			Ly = 0;
		else if(Ly >= ny)
			Ly = ny - 1;
		
		float tempx = D.x() * ray.direction().x();
		float tempy = D.y() * ray.direction().y();
		
		float dix, diy, stop_x, stop_y;
		
		if(tempx > 0)
		{
			dix = 1;
			stop_x = nx;
		}
		else
		{
			dix = -1;
			stop_x = -1;
		}
		
		if(tempy > 0)
		{
			diy = 1;
			stop_y = ny;
		}
		else
		{
			diy = -1;
			stop_y = -1;
		}
	
		float dtdx = fabs(cellsize.x()/ray.direction().x());
		float dtdy = fabs(cellsize.y()/ray.direction().y());
		
		float farx, fary;
		
		if(dix == 1)
			farx = (Lx + 1) * cellsize.x() + Pmin.x();
		else
			farx = Lx * cellsize.x() + Pmin.x();
		
		if(diy == 1)
			fary = (Ly + 1) * cellsize.y() + Pmin.y();
		else
			fary = Ly * cellsize.y() + Pmin.y();
			
		float tnext_x = (farx - ray.origin().x()) / ray.direction().x();
		float tnext_y = (fary - ray.origin().y()) / ray.direction().y();
		
		float zenter = ray.origin().z() + tnear * ray.direction().z();
		tfar = Min(tfar, (float) record.t);
		while(tnear < tfar)
		{
			float texit = Min(tnext_x, tnext_y);
			float zexit = ray.origin().z() + texit * ray.direction().z();
			
			float z00 = data[Lx][Ly];
			float z01 = data[Lx][Ly+1];
			float z10 = data[Lx+1][Ly];
			float z11 = data[Lx+1][Ly+1];
			
			float datamin = Min(Min(z00, z01), Min(z10, z11));			
			float zmin = Min(zenter, zexit);
			float datamax = Max(Max(z00, z01), Max(z10, z11));
			float zmax = Max(zenter, zexit);
			
			if((zmin < datamax) && (zmax > datamin))
			{
				Point E = ray.origin() + tnear * ray.direction();
				Point C;
				C.e[0] = Pmin.x() + Lx * cellsize.x();
				C.e[1] = Pmin.y() + Ly * cellsize.y();
				C.e[2] = 0;
				Vector EC = E - C;
				
				float Sx = EC.x() / cellsize.x();
				float Sy = EC.y() / cellsize.y();
				float Dx = ray.direction().x() / cellsize.x();
				float Dy = ray.direction().y() / cellsize.y();
				
				float Zc = z00;
				float Zu = z10 - z00;
				float Zv = z01 - z00;
				float Zuv = z11 - z10 - z01 + z00;
							
				float dxdy = Dx*Dy;
				float zuvdxdy = Zuv*dxdy;
				float sxdysydx = Sx*Dy + Sy*Dx;
				float zudxzvdy = Zu*Dx + Zv*Dy;
				
				float a = Dx*Dy*Zuv;
				float b = zudxzvdy + Zuv * sxdysydx - ray.direction().z();
				float c = Zc - E.z() + Zu*Sx + Zv*Sy + Zuv*Sx*Sy;
				
				if(fabs(a) < .0001)
				{
					float t = -c/b;
					if(t > 0 && tnear+t < texit)
					{
						if(record.hit(tnear+t, this, ray))
						{
							heightfieldInfo* save = record.getScratchpad<heightfieldInfo>();
							save->zu=Zu;
							save->zv=Zv;
							save->zuv=Zuv;
							save->sx=Sx;
							save->sy=Sy;
							save->dx=Dx;
							save->dy=Dy;
							
							return true;
						}
					}
				}
				else
				{
					bool hasHit = false;
					float discriminant = b*b - 4.0*a*c;
					
					if(discriminant > 0.0)
					{
						discriminant = sqrt(discriminant);
						float t1 = (-b + discriminant) / (2.0*a);
						float t2 = (-b - discriminant) / (2.0*a);
						
						if(t1 >= 0 && tnear+t1 <= texit)
							if(record.hit(tnear+t1, this, ray))
							   {
								   if(t2 >= 0)
									   record.hit(tnear+t2, this, ray);
								
									heightfieldInfo* save = record.getScratchpad<heightfieldInfo>();
									save->zu=Zu;
									save->zv=Zv;
									save->zuv=Zuv;
									save->sx=Sx;
									save->sy=Sy;
									save->dx=Dx;
									save->dy=Dy;
									
									return true;
							   }
					}
				}
				
			}
			
			zenter = zexit;
			
			if(tnext_x < tnext_y)
			{
				tnear = tnext_x;
				tnext_x += dtdx;
				Lx += dix;
				if(Lx == stop_x)
					break;
			}
			else
			{
				tnear = tnext_y;
				tnext_y += dtdy;
				Ly += diy;
				if(Ly == stop_y)
					break;
			}
			
		}
	}
	return false;
}

void Heightfield::getNormal(Normal& N, const HitRecord& record, const Point& pos) const
{
	heightfieldInfo* save = record.getScratchpad<heightfieldInfo>();
	
	Normal n(-(save->zu + save->zuv*save->sy)/cellsize.x(), -(save->zv + save->zuv*save->sx)/cellsize.x(), 1);
	n.normalize();
	
	N = n;
}

float Heightfield::Min(float f1, float f2) const
{
	if(f1 < f2)
		return f1;
	else
		return f2;
}

float Heightfield::Max(float f1, float f2) const
{
	if(f1 > f2)
		return f1;
	else
		return f2;
}

void Heightfield::readData(string filename)
{
   ifstream in(filename.c_str());
   if(!in)
   {
     cerr << "Error opening " << filename << "\n";
     exit(1);
   }
   
   in >> nx >> ny >> minz >> maxz;
   
   if(!in)
   {
     cerr << "Error reading hader from " << filename << "\n";
     exit(1);
   }
   
   in.get();
   data = new float*[nx+1];
   p = new float[(nx+1)*(ny+1)];
   for(int i=0;i<=nx;i++)
     data[i] = p+i*(ny+1);
   in.read((char*)data[0], sizeof(float)*(nx+1)*(ny+1));
   
   if(!in)
   {
     cerr << "Error reading data from " << filename << "\n";
     exit(1);
   }
}