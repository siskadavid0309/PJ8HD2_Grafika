typedef struct Cuboid{
	double x;
	double y;
	double z;
} Cuboid;

void set_size(Cuboid* cuboid);

double calc_volume(const Cuboid* cuboid);

double calc_surface(const Cuboid* cuboid);

void square(const Cuboid* cuboid);