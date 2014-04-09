#include "PhongVolumeMaterial.h"

void swap(short& data)
{
	char* p=(char*)&data;
	char tmp=p[0];
	p[0]=p[1];
	p[1]=tmp;
}

int Floor(double d) 
{
	
	if(d < 0)
	{
		int i = -static_cast<int>(-d);
		if(i == d)
			return i;
		else
			return i-1;
	}
	else 
	{
		return static_cast<int>(d);
	}
	
}

int Ceil(double d)
{
	if(d > 0) 
	{ 
		int i = -static_cast<int>(-d);
		return i;
	}
	else
	{
		int i = static_cast<int>(d);
		if(i == d)
			return i;
		else
			return i+1;
	}
}

PhongVolumeMaterial::PhongVolumeMaterial(string headername, string cmapname, 
										 const Point& _lower, const Point& _upper,
										 double _grid_stepsize, float _maxopacity,
										 float kd, float ka, const Color& _phongColor, float _n)
{
	cmap = Colormap(cmapname);
	lower = _lower;
	upper = _upper;
	grid_stepsize = _grid_stepsize;
	maxopacity = _maxopacity;
	Kd = kd;
	Ka = ka;
	exp = _n;
	phongColor = _phongColor;
	
	diag = upper-lower;
	
	ifstream hdr(headername.c_str());
	string volumename;
	hdr >> volumename;
	hdr >> nx >> ny >> nz;
	short offsetvalue;
	hdr >> offsetvalue;
	string fileendian;
	hdr >> fileendian;
	if(!hdr)
	{
		cerr << "Error reading header: " << headername << '\n';
		exit(1);
	}
	if(fileendian != "BigEndian" && fileendian != "LittleEndian")
	{
		cerr << "Bad data endian: " << fileendian << " in " << headername << "\n";
		exit(1);
	}
	cerr << "Reading " << volumename << ": " << nx << 'x' << ny << 'x' << nz << '\n';
	
	data = vector< vector < vector < short > > >(nx, vector< vector < short > >(ny, vector< short >(nz, 0)));
	short* temp_data = new short[nx*ny*nz];
	cellsize = diag * Vector(1./(nx-1), 1./(ny-1), 1./(nz-1));
	ifstream in(volumename.c_str()); //
	in.read(reinterpret_cast<char*>(temp_data), nx*ny*nz*sizeof(short));
	if(!in)
	{
		cerr << "Error reading data: " << volumename << '\n';
		exit(1);
	}
	
	world_stepsize = cellsize.length()/pow(3, 1./3.) * grid_stepsize;
	cmap.rescale(world_stepsize);
	
	short tmp = 0x1234;
	string machineendian;
	if(*reinterpret_cast<char*>(&tmp) == 0x12)
		machineendian = "BigEndian";
	else
		machineendian = "LittleEndian";
	

	for(int i=0;i<nz;i++)
	{
		for(int j=0;j<ny;j++)
		{
			for(int k=0;k<nx;k++)
			{
				short tempValue = *temp_data;
				if(machineendian != fileendian)
				{
					char* p=(char*)&tempValue;
					char tmp=p[0];
					p[0]=p[1];
					p[1]=tmp;
				}
				
				data[k][j][i] = tempValue + offsetvalue;
				temp_data++;
			}
		}
	}
}

void PhongVolumeMaterial::shade(Color& result,
						  const RenderContext& context,
						  const Ray& ray,
						  const HitRecord& record,
						  float attenuation,
						  int depth) const
{
	HitRecord temp_record;
	Point enter_position = record.p;
	
	temp_record.reset();	
	Ray exit_ray(enter_position, ray.direction());
	
	if(!record.obj->hit(temp_record, context, exit_ray))
	{
		temp_record.reset();
		if(context.scene->object->hit(temp_record, context, exit_ray))
		{
			temp_record.t += record.t;
			temp_record.mat->shade(result, context, ray, temp_record, 1.0, 1);
		}
		else
		{	
			context.scene->background->getBackgroundColor(result, context, ray);
		}
		return;
	}
	
	
	double texit = record.t + temp_record.t;
	
	int it = Ceil(record.t/world_stepsize);
	double t = it*world_stepsize;
	double accum_opacity = 0;
	Color accum_color = Color(0,0,0);
	
	while(t < texit)
	{
		Point position = ray.point(t);
		Vector tp = position - lower;
		tp = tp/cellsize;

		int xf = (int)(tp.x());
		int yf = (int)(tp.y());
		int zf = (int)(tp.z());
		
		int xc = Ceil(tp.x());
		int yc = Ceil(tp.y());
		int zc = Ceil(tp.z());
		
		float xv = tp.x() - xf;
		float yv = tp.y() - yf;
		float zv = tp.z() - zf;
		
		float i1 = data[xf][yf][zf] * (1 - zv) + data[xf][yf][zc] * zv;
		float i2 = data[xf][yc][zf] * (1 - zv) + data[xf][yc][zc] * zv;
		float j1 = data[xc][yf][zf] * (1 - zv) + data[xc][yf][zc] * zv;
		float j2 = data[xc][yc][zf] * (1 - zv) + data[xc][yc][zc] * zv;
		
		float w1 = i1*(1 - yv) + i2*yv;
		float w2 = j1*(1 - yv) + j2*yv;
		float value = w1*(1 - xv) + w2*xv;
		
		float opacity;
		Color color;
		cmap.lookup(value, opacity, color);
		
		double Nx, Ny, Nz;
		
		if(opacity > 0)
		{
			if(xf == 0)
				Nx = (data[xf+1][yf][zf] - data[xf][yf][zf]) * cellsize.x();
			else if(xf == (nx - 1))
				Nx = (data[xf][yf][zf] - data[xf-1][yf][zf]) * cellsize.x();
			else
				Nx = (data[xf+1][yf][zf] - data[xf-1][yf][zf]) * (2.0 * cellsize.x());
			
			if(yf == 0)
				Ny = (data[xf][yf+1][zf] - data[xf][yf][zf]) * cellsize.y();
			else if(yf == (ny - 1))
				Ny = (data[xf][yf][zf] - data[xf][yf-1][zf]) * cellsize.y();
			else
				Ny = (data[xf][yf+1][zf] - data[xf][yf-1][zf]) * (2.0 * cellsize.y());
			
			if(zf == 0)
				Nz = (data[xf][yf][zf+1] - data[xf][yf][zf]) * cellsize.z();
			else if(zf == (nz - 1))
				Nz = (data[xf][yf][zf] - data[xf][yf][zf-1]) * cellsize.z();
			else
				Nz = (data[xf][yf][zf+1] - data[xf][yf][zf-1]) * (2.0 * cellsize.z());
			
			Normal N(Nx, Ny, Nz);
			N.normalize();
			if(N.length() == 0)
			{
				N.e[0] = ray.dir.x();
				N.e[1] = ray.dir.y();
				N.e[2] = ray.dir.z();
			}
			
			float costheta = dot(N, ray.direction());
			
			if(costheta > 0)
			{
				N = -N;
			}
			
			Color difflight= context.scene->ambient*Ka;
			Color speclight = Color(0, 0, 0);
			
			for(int i = 0; i < context.scene->lights.size(); i++)
			{
				Vector light_direction;
				Color light_color;
				context.scene->lights[i]->getLight(light_color, light_direction, context, enter_position);
				float cosphi = dot(N, light_direction);
				Ray shadow_ray(enter_position, light_direction);
				
				if(cosphi > 0)
				{
					difflight += light_color*(Kd * cosphi);
					
					Vector H = light_direction - ray.direction();
					H.normalize();
					float cosalpha = dot(H, N);
					if(cosalpha > 0)
						speclight += light_color * pow(cosalpha, exp);
				}
			}
			
			color = color*difflight + phongColor*speclight;
			accum_color += color*opacity*(1 - accum_opacity);
			accum_opacity += opacity*(1 - accum_opacity);
		}
		
		t += world_stepsize;
	}
	
	if(accum_opacity < .999)
	{
		Point origin = ray.point(texit);
		Ray exit_dir(origin, ray.dir);
		Color exit_color;
		temp_record.reset();
		if(context.scene->object->hit(temp_record, context, exit_dir))
		{
			temp_record.t += texit;
			temp_record.mat->shade(exit_color, context, ray, temp_record, 1.0, 1);
			accum_color += exit_color * (1 - accum_opacity);
		}
		else
		{	
			context.scene->background->getBackgroundColor(exit_color, context, exit_dir);
			accum_color += exit_color * (1 - accum_opacity);
		}
	}

	result = accum_color;
}