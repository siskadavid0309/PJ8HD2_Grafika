#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene, Objects* objects)
{
    glClearColor(0.5, 0.8, 0.9, 1.5);
	scene->fan_rotation = 0.0;
	
	load_model(&(scene->f1), "assets/models/f1.obj");
    scene->f1_texture_id = load_texture("assets/textures/f1.png");
	
	load_model(&(scene->fan), "assets/models/fan.obj");
	scene->fan_texture_id = load_texture("assets/textures/fan.jpg");
	
	
	load_model(&(scene->grass), "assets/models/grass.obj");
    scene->grass_texture_id = load_texture("assets/textures/grass.jpg");
	
	load_model(&(objects->road), "assets/models/road.obj");
    objects->road_texture_id = load_texture("assets/textures/originall.png");
	
	load_model(&(scene->barrier), "assets/models/barrier.obj");
    scene->barrier_texture_id = load_texture("assets/textures/barrier.png");
	
    
	///
	
	///
	
	
	
	
	
	
	
	
	
	

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 11.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
	scene->fan_rotation += 100.0*time;
}

void render_scene(const Scene* scene, const Objects* objects)
{
    	glPushMatrix();
	glRotatef(scene->fan_rotation, 0, 0, 1);
	glScalef(0.008, 0.008, 0.008);
	//glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, scene->fan_texture_id);
	draw_model(&(scene->fan));
	glPopMatrix();
	
	set_material(&(scene->material));
    set_lighting();
    draw_origin();
    //draw_model(&(scene->cube));
	
	
	glPushMatrix();
	//glDisable(GL_CULL_FACE);
	glTranslatef(1, 2, 0.02);
	glScalef(0.01, 0.01, 0.01);
	glBindTexture(GL_TEXTURE_2D, scene->f1_texture_id);
	draw_model(&(scene->f1));
	glPopMatrix();
	
	/*
	glPushMatrix();
	//glDisable(GL_CULL_FACE);
	glTranslatef(0, 1, 0.5);
	glScalef(0.1, 0.1, 0.1);
	glBindTexture(GL_TEXTURE_2D, objects->road_texture_id);
	//glRotatef(180, 1, 0, 0);
	draw_model(&(objects->road));
	
	glPopMatrix();
	*/

	
	
	glPushMatrix();
glTranslatef(0, 1, -0.03);
glScalef(0.3, 0.3, 0.3);

for (int i = 0; i < 20; i++) {
    glPushMatrix();
    glTranslatef(i * 5, 0.0, 0.0);  // Az X tengely mentén történő eltolás
    glBindTexture(GL_TEXTURE_2D, objects->road_texture_id);
    draw_model(&(objects->road));
    glPopMatrix();
}
for (int i = 0; i < 20; i++) {
    glPushMatrix();
    glTranslatef(-i * 5, 0.0, 0.0);  // Az X tengely mentén történő eltolás
    glBindTexture(GL_TEXTURE_2D, objects->road_texture_id);
    draw_model(&(objects->road));
    glPopMatrix();
}

glPopMatrix();

	

	
	glPushMatrix();

glScalef(0.07, 0.07, 0.01);

//float distance = 100.0; // Kezdőponttól való távolság
float offset = 200.0; // Az objektumok közötti távolság
float startX = -offset; // Az első oszlop x-koordinátája
float startY = -offset; // Az első sor y-koordinátája

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        glPushMatrix();
        glTranslatef(startX + j * offset, startY + i * offset, -10);
		glBindTexture(GL_TEXTURE_2D, scene->grass_texture_id);
        draw_model(&(scene->grass));
        glPopMatrix();
    }
}
glPopMatrix();

/*
	glPushMatrix();
	int i=0;
	for(i=0;i<2;i++){
	glPushMatrix();
	glTranslatef(13, 0.2*2*i, 0);
	glScalef(0.65, 0.65, 0.65);
	glBindTexture(GL_TEXTURE_2D, scene->barrier_texture_id);
	draw_model(&(scene->barrier));
	glPopMatrix();
	}
	glPopMatrix();
	*/
	glPushMatrix();
int i=0;
for(i=0;i<2;i++){
    glPushMatrix();
    glTranslatef(13, 1.5*i+0.25, 0); // hozzáadott tér
    glScalef(0.6, 0.6, 0.6);
    glBindTexture(GL_TEXTURE_2D, scene->barrier_texture_id);
    draw_model(&(scene->barrier));
    glPopMatrix();
}
glPopMatrix();


	glPushMatrix();
 i=0;
for(i=0;i<2;i++){
    glPushMatrix();
    glTranslatef(-13, 1.5*i+0.25, 0); // hozzáadott tér
    glScalef(0.6, 0.6, 0.6);
    glBindTexture(GL_TEXTURE_2D, scene->barrier_texture_id);
    draw_model(&(scene->barrier));
    glPopMatrix();
}
glPopMatrix();

	/*
		glPushMatrix();
	//glDisable(GL_CULL_FACE);
	glTranslatef(-13, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, scene->barrier_texture_id);
	draw_model(&(scene->barrier));
	glPopMatrix();
*/


}

void draw_origin()
{
    /*glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();*/
}
