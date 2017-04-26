#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "Vec3.h"
#include "Ray.h"
int w= 640, h = 480, n = 4;

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	unsigned char *data = stbi_load("img.png", &w, &h, &n, 4);

Vec3 color(const Ray& r)
{
	Vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*Vec3(1.0f,1.0f,1.0f) + t*Vec3(0.5f,0.7f,1.0f);
}
int main()
{
	int nx = 200;
	int ny = 100;
//	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 lower_left_corner(-2.0,-1.0,-1.0);
	Vec3 horizontal(4.0,0.0,0.0);
	Vec3 vertical(0.0,2.0,0.0);
	Vec3 origin(0.0,0.0,0.0);

	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			float u = float(i)/float(nx);
			float v = float(j) / float(ny);
			Ray r(origin,lower_left_corner + u*horizontal + v*vertical);
			Vec3 col = color(r);

			unsigned char ir = int(255.99*col[0]);
			unsigned char ig = int(255.99*col[1]);
			unsigned char ib = int(255.99*col[2]);


			setPixel(i,j,ir,ig,ib,255);
//			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}

	// for(int i = 0; i < w; i++)
	// {
	// 	for(int j = 0; j < h; j++)
	// 	{
	// 		setPixel(i,j,0,0,255,255);
	// 	}
	// }

	stbi_write_png("out.png",w,h,4,data,w*4);

	    //int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);

}

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{

	int i = h*x + y;
	data[i*4] = r;
	data[i*4+1] = g;
	data[i*4+2] = b;
	data[i*4+3] = a;		
}
void setPixel(int x, int y, Vec3 color)
{
	int i = h*x+y;
	data[i*4] = (unsigned char)(color.r());
	data[i*4+1] = (unsigned char)(color.g());
	data[i*4+2] = (unsigned char)(color.b());

}
