#include "cuboid.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Cuboid cuboid;
	double volume;
	double surface;
	set_size(&cuboid);
	volume=calc_volume(&cuboid);
	surface=calc_surface(&cuboid);
	square(&cuboid);
	printf("Teglatest terfogata: %lf \n", volume);
	printf("Teglatest felszine: %lf \n", surface);
	return 0;
}
