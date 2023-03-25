#include "cuboid.h"
#include <stdio.h>

void set_size(Cuboid* cuboid){
	double x;
	double y;
	double z;
	
	do{
		printf("Csak pozitiv, 0-nal nagyobb szamokat adj meg! \n");
		scanf("%lf", &x);
		scanf("%lf", &y);
		scanf("%lf", &z);
	}while(x<=0.0 || y<=0.0 || z<=0.0);
	
	cuboid->x=x;
	cuboid->y=y;
	cuboid->z=z;
}

double calc_volume(const Cuboid* cuboid){
	double volume;
	volume=cuboid->x * cuboid->y * cuboid->z;
	return volume;
}

double calc_surface(const Cuboid* cuboid){
	double surface;
	surface=2*(cuboid->x*cuboid->y+cuboid->y*cuboid->z+cuboid->x*cuboid->z);
	return surface;
}

void square(const Cuboid* cuboid){
	if(cuboid->x==cuboid->y || cuboid->x==cuboid->z || cuboid->y==cuboid->z){
		printf("A teglatest egyik lapja negyzet \n");
	}
	else
	{
		printf("A teglatestnek nincs negyzet alapu oldala \n");
	}
}