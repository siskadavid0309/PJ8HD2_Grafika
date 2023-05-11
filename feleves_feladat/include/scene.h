#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model f1;
	Model fan;
	Model grass;
	Model barrier;
	
	
	float fan_rotation;
    Material material;
	GLuint f1_texture_id;
	GLuint fan_texture_id;
	GLuint grass_texture_id;
	GLuint barrier_texture_id;
	
} Scene;

typedef struct Objects
{

	Model road;
	GLuint road_texture_id;
	
} Objects;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene, Objects* objects);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene, const Objects* objects);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
