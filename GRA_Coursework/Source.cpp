#include <iostream>

#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "loadimage.h"
#include <vector>

#include "shapes.h"
#include "tent.h"
#include "objects.h"

#define SIZE .5f

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

bool rotate = false;
bool mesh, lighting;
bool wKey, sKey, aKey, dKey;
float cam_height;
float cam_speed;
GLuint skybox_texture1, skybox_texture2;
GLuint skybox_texture3, skybox_texture4;
GLuint skybox_texture5;
GLuint grass_texture;

float light_steel[] = { .2901960784f, .25647058823f, .25431372549f, 1.f };

void loadTextures() {
	skybox_texture1 = loadimage("./resource/bluecloud_bk.bmp");
	skybox_texture2 = loadimage("./resource/bluecloud_ft.bmp");
	skybox_texture3 = loadimage("./resource/bluecloud_rt.bmp");
	skybox_texture4 = loadimage("./resource/bluecloud_lf.bmp");
	skybox_texture5 = loadimage("./resource/bluecloud_up.bmp");
	grass_texture = loadimage("./resource/Grass_Hill.bmp");
}

void drawSkybox(float r)
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Back face (z = r)
	glBindTexture(GL_TEXTURE_2D, skybox_texture1);
	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, -1.f);
		glTexCoord2f(1., 0.);
		glVertex3f(r, -r, r);
		glTexCoord2f(0., 0.);
		glVertex3f(-r, -r, r);
		glTexCoord2f(0., 1.);
		glVertex3f(-r, r, r);
		glTexCoord2f(1., 1.);
		glVertex3f(r, r, r);
	glEnd();

	// Near face (z = -r)
	glBindTexture(GL_TEXTURE_2D, skybox_texture2);
	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(1., 0.);
		glVertex3f(-r, r, -r);
		glTexCoord2f(1., 1.);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(0., 1.);
		glVertex3f(r, -r, -r);
		glTexCoord2f(0., 0.);
		glVertex3f(r, r, -r);
	glEnd();

	// Right face (x = r)
	glBindTexture(GL_TEXTURE_2D, skybox_texture3);
	glBegin(GL_QUADS);
		glNormal3f(-1.f, 0.f, 0.f);
		glTexCoord2f(1., 0.);
		glVertex3f(r, r, -r);
		glTexCoord2f(1., 1.);
		glVertex3f(r, -r, -r);
		glTexCoord2f(0., 1.);
		glVertex3f(r, -r, r);
		glTexCoord2f(0., 0.);
		glVertex3f(r, r, r);
	glEnd();

	// Left face (x = -r)
	glBindTexture(GL_TEXTURE_2D, skybox_texture4);
	glBegin(GL_QUADS);
		glNormal3f(1.f, 0.f, 0.f);
		glTexCoord2f(1., 0.);
		glVertex3f(-r, -r, r);
		glTexCoord2f(0., 0.);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(0., 1.);
		glVertex3f(-r, r, -r);
		glTexCoord2f(1., 1.);
		glVertex3f(-r, r, r);
	glEnd();

	// Top face (y = r)
	glBindTexture(GL_TEXTURE_2D, skybox_texture5);
	glBegin(GL_QUADS);
		glNormal3f(0.f, -1.f, 0.f);
		glTexCoord2f(0., 1.);
		glVertex3f(-r, r, r);
		glTexCoord2f(1., 1.);
		glVertex3f(-r, r, -r);
		glTexCoord2f(1., 0.);
		glVertex3f(r, r, -r);
		glTexCoord2f(0., 0.);
		glVertex3f(r, r, r);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void tent() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .5f, .5f, .5f, 1.f };
	float mat_specular[] = { 0.3f, 0.0f, 0.0f, 1.f };
	float mat_shininess[] = { 0.0f };
	float mat_emission[] = { .0f, .0f, .0f, 1.f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	// TENT
	tent_walls(mesh);
	glPushMatrix();
		glTranslatef(0.f, .9f, 0.f);
		glRotatef(180.0f, 1.f, 0.f, 0.f);
		tent_roof(mesh);
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(10.f, 0.f, 1.f, 0.f);
		glPushMatrix();
			glTranslatef(.0f, .7f, -.43f);
			glRotatef(135.0f, 1.f, 0.f, 0.f);
			tent_roof_mini(mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(.0f, .7f, .43f);
			glRotatef(-135.f, 1.f, 0.f, 0.f);
			tent_roof_mini(mesh);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f, .3f, 0.f);
		circle_outline(.498f);
		circle_outline(.497f);
		circle_outline(.497f);
		circle_outline(.495f);
	glPopMatrix();

	// ENTRANCE
	glPushMatrix();
		glScalef(0.0389f, 0.0389f, 0.0395f);
		glTranslatef(17.f, 7.8f, -1.95f);
		glRotatef(5.5f, 0.f, 1.f, 0.f);
		entrance(mesh);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, light_steel);
	glColor3f(light_steel[0], light_steel[1], light_steel[2]);
	glPushMatrix();
		glTranslatef(.83f, 0.f, -0.04f);
		cylinder(0.002f, 6, .3f, mesh);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(.822f, 0.f, -0.145f);
		cylinder(0.002f, 6, .3f, mesh);
	glPopMatrix();
	glPopAttrib();
}

void draw(float aS, int numOfStages, int faS) {
	drawSkybox(50.f);
	
	// GROUND
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, grass_texture);
	for (int x = -50; x < 50; x += 2) {
		for (int y = -50; y < 50; y += 2) {
			glPushMatrix();
				glTranslatef(x, 0.f, y);
				glRotatef(45.f * ((x+y)%4), 0.f, 1.f, 0.f);
				glBegin(GL_TRIANGLES);
				glNormal3f(0.f, 1.f, 0.f);
				glTexCoord2f(1., 0.);
				glVertex3f(1.f, 0.f, -1.f);
				glTexCoord2f(0., 0.);
				glVertex3f(-1.f, 0.f, -1.f);
				glTexCoord2f(1., 1.);
				glVertex3f(1.f, 0.f, 1.f);

				glNormal3f(0.f, 1.f, 0.f);
				glTexCoord2f(0., 0.);
				glVertex3f(-1.f, 0.f, -1.f);
				glTexCoord2f(0., 1.);
				glVertex3f(-1.f, 0.f, 1.f);
				glTexCoord2f(1., 1.);
				glVertex3f(1.f, 0.f, 1.f);
				glEnd();
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);

	// TENT
	glPushMatrix();
		glRotatef(-7.f, 0.f, 1.f, 0.f);
		glScalef(10.f, 10.0f, 10.0f);
		tent();
	glPopMatrix();

	// STAGE
	glPushMatrix();
	glScalef(2.f, 1.0f, 2.0f);
	stage(mesh);
	glPopMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .2f, .2f, .2f, 1.f };
	float mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.f };
	float mat_shininess[] = { 128.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, light_steel);
	glColor3f(light_steel[0], light_steel[1], light_steel[2]);

	// CENTER POLE
	cylinder(.08f, 5, 9.f, mesh);
	glPushMatrix();
		glRotatef(90.f, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -(2.05f), -5.5f);
		cylinder(.08f, 5, 4.f, mesh);
		glPushMatrix();
			glTranslatef(0.f, -(2.05f), 0.f);
			cylinder(.02f, 5, 4.f, mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, (2.05f), 0.f);
			cylinder(.02f, 5, 4.f, mesh);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glRotatef(90.f, 1.f, 0.f, 0.f);
		glRotatef(90.f, 0.f, 0.f, 1.f);
		glTranslatef(0.f, -(2.05f), -5.5f);
		cylinder(.08f, 5, 4.f, mesh);
	glPopMatrix();
	glPopAttrib();

	// SPOTLIGHTS
	glPushMatrix();
		glTranslatef(0.f, (5.6f), 1.f);
		glRotatef(180.f, 1.f, 0.f, 0.f);
		spotlight(15.f, mesh, true);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.f, (5.6f), -1.f);
		glRotatef(180.f, 1.f, 0.f, 0.f);
		spotlight(20.f, mesh);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, (5.6f), 1.f);
			glRotatef(180.f, 1.f, 0.f, 0.f);
			spotlight(-45.f, mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, (5.6f), -1.f);
			glRotatef(180.f, 1.f, 0.f, 0.f);
			spotlight(20.f, mesh);
		glPopMatrix();
	glPopMatrix();
	
	// STANDS
	glPushMatrix();
		glTranslatef(0.f, .0f, 0.f);
		glRotatef(45.f, 0.f, 1.f, 0.f);
		float distance = 3.2f;
		glPushMatrix();
			glTranslatef(distance, .0f, 0.f);
			glRotatef(90.f, 0.f, 1.f, 0.f);
			glScalef(1.5f, 1.5f, 1.5f);
			stands_with_seats(mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-distance, .0f, 0.f);
			glRotatef(-90.f, 0.f, 1.f, 0.f);
			glScalef(1.5f, 1.5f, 1.5f);
			stands_with_seats(mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, .0f, distance);
			glScalef(1.5f, 1.5f, 1.5f);
			stands_with_seats(mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, .0f, -distance);
			glRotatef(180.f, 0.f, 1.f, 0.f);
			glScalef(1.5f, 1.5f, 1.5f);
			stands_with_seats(mesh);
		glPopMatrix();
	glPopMatrix();

	// LAMPS
	glPushMatrix();
		glTranslatef(0.f, .0f, 0.f);
		glRotatef(-15.f, 0.f, 1.f, 0.f);
		distance = 4.f;
		glPushMatrix();
			glTranslatef(distance, .0f, 0.f);
			glRotatef(90.f, 0.f, 1.f, 0.f);
			glScalef(2.f, 2.0f, 2.0f);
			lamppost(faS, true, mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-distance, .0f, 0.f);
			glRotatef(-90.f, 0.f, 1.f, 0.f);
			glScalef(2.f, 2.0f, 2.0f);
			lamppost(faS, true, mesh, true);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, .0f, distance);
			glScalef(2.f, 2.0f, 2.0f);
			lamppost(faS, false, mesh);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.f, .0f, -distance);
			glRotatef(180.f, 0.f, 1.f, 0.f);
			glScalef(2.f, 2.0f, 2.0f);
			lamppost(faS, false, mesh);
		glPopMatrix();
	glPopMatrix();
	
	// CAGES
	glPushMatrix();
		glTranslatef(0.f, 0.f, 4.f);
		glRotatef(30.f, 0.f, 1.f, 0.f);
		cage_square(.9f,2.f,.7f, 0.01f, mesh);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(3.35f, 1.28f, 2.7f);
		glRotatef(30.f, 0.f, 1.f, 0.f);
		cage_square(.1f, .2f, .1f, 0.01f, mesh);
	glPopMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat2_diffuse[] = { .7f, .5f, .5f, 1.f };
	float mat2_specular[] = { 0.5f, 0.2f, 0.2f, 1.f };
	float mat2_shininess[] = { 50.0f };
	float mat2_emission[] = { .0f, .0f, .0f, 1.f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat2_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat2_emission);

	// FLAG
	glPushMatrix();
		glTranslatef(0.f, 9.f, 0.f);
		glRotatef(45.f, 0.f, 1.f, 0.f);
		glScalef(0.1f, 0.1f, 0.1f);
		flag(aS, numOfStages, mesh);
	glPopMatrix();

	// BALL
	glPushMatrix();
	glTranslatef(0.1f, .28f, 0.1f);
	glRotatef(40.f, 0.f, 1.f, 1.f);
	colourful_ball(.1f);
	glPopMatrix();
	
	glPopAttrib();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && (action == GLFW_PRESS))
	{
		wKey = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		wKey = false;
	}

	if (key == GLFW_KEY_S && (action == GLFW_PRESS))
	{
		sKey = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		sKey = false;
	}

	if (key == GLFW_KEY_A && (action == GLFW_PRESS))
	{
		aKey = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		aKey = false;
	}

	if (key == GLFW_KEY_D && (action == GLFW_PRESS))
	{
		dKey = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		dKey = false;
	}

	if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
	{
		mesh = !mesh;
	}
	if (key == GLFW_KEY_L && action == GLFW_RELEASE)
	{
		if (lighting) {
			glDisable(GL_LIGHTING);
		}
		else {
			glEnable(GL_LIGHTING);
		}
		lighting = !lighting;
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		cam_speed += 0.1;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		cam_speed -= 0.1;
	}

	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS))
	{
		cam_height += cam_speed;
	}
	if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT && (action == GLFW_PRESS))
	{
		cam_height -= cam_speed;
		if (cam_height < 0.5f) {
			cam_height = 0.6f;
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		glLoadIdentity();
	}
}

int main() {
	if (!glfwInit()) {
		std::cout << "GLFW initialisation failed." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Circus Scene", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW initialisation failed: "
			<< glewGetErrorString(err) << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat global_ambient[] = { 0.15f, 0.15f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_LIGHTING);

	GLfloat ambience[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position0[] = { 3.35f, 2.35f, 2.7f, 1.0f };
	GLfloat position1[] = { -3.35f, 2.35f, -2.7f, 1.0f };
	GLfloat position2[] = { 0.5f, 0.5f, .3f, 1.0f };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, .1f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.7f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .3f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.9f);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.3f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4f);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	

	glfwSetKeyCallback(window, key_callback);
	loadTextures();

	mesh = false;
	lighting = true;
	cam_speed = 0.3;
	static double previousSeconds = 0.0;
	static float rotateAngle = 0.f;
	static float aT = 0.f;

	cam_height = 0.6f;
	double mouseX = .0f, mouseY = 0.f;
	glm::vec3 pos = glm::vec3(15.0f, cam_height, 0.0f);
	glm::vec3 vd = glm::vec3(0.0f, 3.0f, -1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glm::vec3 eye = pos;
		glm::vec3 cen = pos + vd;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 cameraDirection = glm::normalize(cen - eye);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		vd = vd + cameraRight * (float)((xpos - mouseX) * 50.f);
		vd = vd + cameraUp * (float)(-(ypos - mouseY) * 50.f);
		mouseX = xpos;
		mouseY = ypos;

		glm::mat4 view = glm::mat4(
			cameraRight[0], cameraUp[0], -cameraDirection[0], 0.0f,
			cameraRight[1], cameraUp[1], -cameraDirection[1], 0.0f,
			cameraRight[2], cameraUp[2], -cameraDirection[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view = glm::translate(view, -eye);

		float* viewArray = glm::value_ptr(view);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float fovyInDegrees = 60.f;
		float aspectRatio = static_cast<GLdouble>(WINDOW_WIDTH) /
			static_cast<GLdouble>(WINDOW_HEIGHT);
		float znear = 0.1f;
		float zfar = 1000.f;
		glm::mat4 proj = glm::perspective(glm::radians(fovyInDegrees),
			aspectRatio, znear, zfar);
		float* matProjectionArray = glm::value_ptr(proj);
		glLoadMatrixf(matProjectionArray);
		
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(viewArray);
		
		double elapsedSeonds;
		double currentSeconds = glfwGetTime();
		elapsedSeonds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;
		float animationTime = 2.f;
		float numofStage = 24.f;
		aT = fmod(aT + elapsedSeonds, animationTime);
		float aS = numofStage * aT / animationTime;
		
		int faS = rand() % 3;
		switch (faS) {
		case 0:
			glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .3f);
			break;
		case 1:
			glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.3f);
			break;
		case 2:
			glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, .8f);
			break;
		}
		
		glPushMatrix();
		draw(aS, numofStage, faS);
		glPopMatrix();

		if (wKey)
		{
			pos = pos + cameraDirection * cam_speed;
		}
		if (sKey)
		{
			pos = pos + cameraDirection * -cam_speed;
		}
		if (aKey)
		{
			pos = pos + cameraRight * -cam_speed;
		}
		if (dKey)
		{
			pos = pos + cameraRight * cam_speed;
		}
		pos = glm::vec3(pos.x, cam_height, pos.z);
		
		glMatrixMode(GL_MODELVIEW);
		
		glLightfv(GL_LIGHT0, GL_POSITION, position0);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
		glLightfv(GL_LIGHT2, GL_POSITION, position2);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}