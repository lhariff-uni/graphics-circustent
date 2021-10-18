#include "objects.h"
#include "shapes.h"


GLfloat entrance_top[4][4][3] = {
	{{-4.5, 0., -1.5}, {-2.25, -0.7, -1.5},
	{2.25, -0.7, -1.5}, {4.5, 0., -1.5}},
   {{-4.5, -.0, -.5}, {-2.25, -1.5, -.5},
	{2.25, -1.5, -.5}, {4.5, -0.5, -.5}},
   {{-4.5, -.0, .5}, {-2.25, -1.5, .5},
	{2.25, -1.5, .5}, {4.5, -0.5, .5}},
   {{-4.5, 0., 1.5}, {-2.25, -.7, 1.5},
	{2.25, -.7, 1.5}, {4.5, 0., 1.5}}
};
GLfloat entrance_bottom[4][4][3] = {
   {{-4.5, 0., 1.5}, {-2.25, -.7, 1.5},
	{2.25, -.7, 1.5}, {4.5, 0., 1.5}},
	{{-4.5, -.0, .5}, {-2.25, -1.5, .5},
	{2.25, -1.5, .5}, {4.5, -0.5, .5}},
	{{-4.5, -.0, -.5}, {-2.25, -1.5, -.5},
	{2.25, -1.5, -.5}, {4.5, -0.5, -.5}},
	{{-4.5, 0., -1.5}, {-2.25, -0.7, -1.5},
	{2.25, -0.7, -1.5}, {4.5, 0., -1.5}}
};

GLfloat flag1[4][4][3] = {
	{{0., -1.5, 0}, {2., -1.5, .5},
	{4., -1.5, -.5}, {6., -1.5, 0}},
    {{.7, -0.5, 0}, {2., -0.5, 1.7},
	{4., -0.5, -.4}, {6., -0.5, .3}},
    {{1., 0.5, -.2}, {2., 0.5, 1.5},
	{4., 0.5, -.6}, {6., 0.5, 0.1}},
    {{0., 1.5, 0.}, {2., 1.5, 0.5},
	{4., 1.5, -0.2}, {6., 1.5, 0.2}}
};
GLfloat flag2[4][4][3] = {
    {{0., -1.5, 0}, {2., -1.5, -1.1},
	{4., -1.5, -1.5}, {6., -1.5, 0}},
	{{.7, -0.5, -.5}, {2., -0.5, -1.5},
	{4., -0.5, -.9}, {6., -0.5, -.5}},
	{{1., 0.5, .5}, {2., 0.5, -.5},
	{4., 0.5, 0.}, {6., 0.5, 0.2}},
	{{0., 1.5, 0.}, {2., 1.5, 0.1},
	{4., 1.5, 0.5}, {6., 1.5, 0.5}}
};

float light_brown[] = { 0.33333333333f, 0.18431372549f, 0.1294117647f, 1.f };
float dark_brown[] = { 0.22333333333f, 0.08431372549f, 0.0294117647f, 1.f };
float steel[] = { .14901960784f, .17647058823f, .18431372549f, 1.f };
float dark_steel[] = { .04901960784f, .07647058823f, .08431372549f, 1.f };
float light_red[] = { 1.f, .6f, .6f, 1.f };

float no_emission[] = { 0.f, 0.f, 0.f, .5f };
float def_emission[] = { 0.1f, 0.1f, 0.1f, .5f };
float mat_emission0[] = { .3f, .3f, .1f, .5f };
float mat_emission1[] = { 1.f, 1.f, .8f, .5f };
float mat_emission2[] = { .8f, .8f, .6f, .5f };

void entrance(bool mesh)
{
	int i, j;
	// TOP
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
		0, 1, 12, 4, &entrance_top[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	if (mesh) {
		for (j = 0; j <= 8; j++) {
			glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
			glEnd();
			glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
			glEnd();
		}
	}
	else {
		glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	}
	glFlush();

	
	// BOTTOM
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
		0, 1, 12, 4, &entrance_bottom[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	if (mesh) {
		for (j = 0; j <= 8; j++) {
			glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
			glEnd();
			glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
			glEnd();
		}
	}
	else {
		glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	}
	glFlush();
}

void flag(float aS, int numOfStages, bool mesh) {
	int i, j;
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	cylinder(.3f, 4, 4.f, mesh);
	numOfStages = numOfStages / 2;
	aS = (int)aS;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, light_red);
	glColor3f(light_red[0], light_red[1], light_red[2]);
	if (aS < (numOfStages)) {
		GLfloat flag_front[4][4][3] = {
				{{0., -1.5, flag1[0][0][2] + (flag2[0][0][2] - flag1[0][0][2]) / numOfStages * aS}, {2., -1.5, flag1[0][1][2] + (flag2[0][1][2] - flag1[0][1][2]) / numOfStages * aS},
				{4., -1.5, flag1[0][2][2] + (flag2[0][2][2] - flag1[0][2][2]) / numOfStages * aS}, {6., -1.5, flag1[0][3][2] + (flag2[0][3][2] - flag1[0][3][2]) / numOfStages * aS}},
				{{.7, -0.5, flag1[1][0][2] + (flag2[1][0][2] - flag1[1][0][2]) / numOfStages * aS}, {2., -0.5, flag1[1][1][2] + (flag2[1][1][2] - flag1[1][1][2]) / numOfStages * aS},
				{4., -0.5, flag1[1][2][2] + (flag2[1][2][2] - flag1[1][2][2]) / numOfStages * aS}, {6., -0.5, flag1[1][3][2] + (flag2[1][3][2] - flag1[1][3][2]) / numOfStages * aS}},
				{{1., 0.5, flag1[2][0][2] + (flag2[2][0][2] - flag1[2][0][2]) / numOfStages * aS}, {2., 0.5, flag1[2][1][2] + (flag2[2][1][2] - flag1[2][1][2]) / numOfStages * aS},
				{4., 0.5, flag1[2][2][2] + (flag2[2][2][2] - flag1[2][2][2]) / numOfStages * aS}, {6., 0.5, flag1[2][3][2] + (flag2[2][3][2] - flag1[2][3][2]) / numOfStages * aS}},
				{{0., 1.5, flag1[3][0][2] + (flag2[3][0][2] - flag1[3][0][2]) / numOfStages * aS}, {2., 1.5, flag1[3][1][2] + (flag2[3][1][2] - flag1[3][1][2]) / numOfStages * aS},
				{4., 1.5, flag1[3][2][2] + (flag2[3][2][2] - flag1[3][2][2]) / numOfStages * aS}, {6., 1.5, flag1[3][3][2] + (flag2[3][3][2] - flag1[3][3][2]) / numOfStages * aS}}
		};
		GLfloat flag_back[4][4][3] = {
			{{0., 1.5, flag1[3][0][2] + (flag2[3][0][2] - flag1[3][0][2]) / numOfStages * aS}, {2., 1.5, flag1[3][1][2] + (flag2[3][1][2] - flag1[3][1][2]) / numOfStages * aS},
			{4., 1.5, flag1[3][2][2] + (flag2[3][2][2] - flag1[3][2][2]) / numOfStages * aS}, {6., 1.5, flag1[3][3][2] + (flag2[3][3][2] - flag1[3][3][2]) / numOfStages * aS}},
			{{1., 0.5, flag1[2][0][2] + (flag2[2][0][2] - flag1[2][0][2]) / numOfStages * aS}, {2., 0.5, flag1[2][1][2] + (flag2[2][1][2] - flag1[2][1][2]) / numOfStages * aS},
			{4., 0.5, flag1[2][2][2] + (flag2[2][2][2] - flag1[2][2][2]) / numOfStages * aS}, {6., 0.5, flag1[2][3][2] + (flag2[2][3][2] - flag1[2][3][2]) / numOfStages * aS}},
			{{.7, -0.5, flag1[1][0][2] + (flag2[1][0][2] - flag1[1][0][2]) / numOfStages * aS}, {2., -0.5, flag1[1][1][2] + (flag2[1][1][2] - flag1[1][1][2]) / numOfStages * aS},
			{4., -0.5, flag1[1][2][2] + (flag2[1][2][2] - flag1[1][2][2]) / numOfStages * aS}, {6., -0.5, flag1[1][3][2] + (flag2[1][3][2] - flag1[1][3][2]) / numOfStages * aS}},
			{{0., -1.5, flag1[0][0][2] + (flag2[0][0][2] - flag1[0][0][2]) / numOfStages * aS}, {2., -1.5, flag1[0][1][2] + (flag2[0][1][2] - flag1[0][1][2]) / numOfStages * aS},
			{4., -1.5, flag1[0][2][2] + (flag2[0][2][2] - flag1[0][2][2]) / numOfStages * aS}, {6., -1.5, flag1[0][3][2] + (flag2[0][3][2] - flag1[0][3][2]) / numOfStages * aS}}
		};
		glPushMatrix();
		glTranslatef(0.f, 2.f, 0.f);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &flag_front[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_FLAT);

		if (mesh) {
			for (j = 0; j <= 8; j++) {
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
				glEnd();
			}
		}
		else {
			glEvalMesh2(GL_FILL, 0, 20, 0, 20);
		}
		glFlush();

		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &flag_back[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_FLAT);

		if (mesh) {
			for (j = 0; j <= 8; j++) {
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
				glEnd();
			}
		}
		else {
			glEvalMesh2(GL_FILL, 0, 20, 0, 20);
		}
		glFlush();
		glPopMatrix();
	}
	else {
		aS = aS - 2 * (((int)aS % numOfStages) + 1) - 1;
		GLfloat flag_front[4][4][3] = {
				{{0., -1.5, flag1[0][0][2] + (flag2[0][0][2] - flag1[0][0][2]) / numOfStages * aS}, {2., -1.5, flag1[0][1][2] + (flag2[0][1][2] - flag1[0][1][2]) / numOfStages * aS},
				{4., -1.5, flag1[0][2][2] + (flag2[0][2][2] - flag1[0][2][2]) / numOfStages * aS}, {6., -1.5, flag1[0][3][2] + (flag2[0][3][2] - flag1[0][3][2]) / numOfStages * aS}},
				{{.7, -0.5, flag1[1][0][2] + (flag2[1][0][2] - flag1[1][0][2]) / numOfStages * aS}, {2., -0.5, flag1[1][1][2] + (flag2[1][1][2] - flag1[1][1][2]) / numOfStages * aS},
				{4., -0.5, flag1[1][2][2] + (flag2[1][2][2] - flag1[1][2][2]) / numOfStages * aS}, {6., -0.5, flag1[1][3][2] + (flag2[1][3][2] - flag1[1][3][2]) / numOfStages * aS}},
				{{1., 0.5, flag1[2][0][2] + (flag2[2][0][2] - flag1[2][0][2]) / numOfStages * aS}, {2., 0.5, flag1[2][1][2] + (flag2[2][1][2] - flag1[2][1][2]) / numOfStages * aS},
				{4., 0.5, flag1[2][2][2] + (flag2[2][2][2] - flag1[2][2][2]) / numOfStages * aS}, {6., 0.5, flag1[2][3][2] + (flag2[2][3][2] - flag1[2][3][2]) / numOfStages * aS}},
				{{0., 1.5, flag1[3][0][2] + (flag2[3][0][2] - flag1[3][0][2]) / numOfStages * aS}, {2., 1.5, flag1[3][1][2] + (flag2[3][1][2] - flag1[3][1][2]) / numOfStages * aS},
				{4., 1.5, flag1[3][2][2] + (flag2[3][2][2] - flag1[3][2][2]) / numOfStages * aS}, {6., 1.5, flag1[3][3][2] + (flag2[3][3][2] - flag1[3][3][2]) / numOfStages * aS}}
		};
		GLfloat flag_back[4][4][3] = {
			{{0., 1.5, flag1[3][0][2] + (flag2[3][0][2] - flag1[3][0][2]) / numOfStages * aS}, {2., 1.5, flag1[3][1][2] + (flag2[3][1][2] - flag1[3][1][2]) / numOfStages * aS},
			{4., 1.5, flag1[3][2][2] + (flag2[3][2][2] - flag1[3][2][2]) / numOfStages * aS}, {6., 1.5, flag1[3][3][2] + (flag2[3][3][2] - flag1[3][3][2]) / numOfStages * aS}},
			{{1., 0.5, flag1[2][0][2] + (flag2[2][0][2] - flag1[2][0][2]) / numOfStages * aS}, {2., 0.5, flag1[2][1][2] + (flag2[2][1][2] - flag1[2][1][2]) / numOfStages * aS},
			{4., 0.5, flag1[2][2][2] + (flag2[2][2][2] - flag1[2][2][2]) / numOfStages * aS}, {6., 0.5, flag1[2][3][2] + (flag2[2][3][2] - flag1[2][3][2]) / numOfStages * aS}},
			{{.7, -0.5, flag1[1][0][2] + (flag2[1][0][2] - flag1[1][0][2]) / numOfStages * aS}, {2., -0.5, flag1[1][1][2] + (flag2[1][1][2] - flag1[1][1][2]) / numOfStages * aS},
			{4., -0.5, flag1[1][2][2] + (flag2[1][2][2] - flag1[1][2][2]) / numOfStages * aS}, {6., -0.5, flag1[1][3][2] + (flag2[1][3][2] - flag1[1][3][2]) / numOfStages * aS}},
			{{0., -1.5, flag1[0][0][2] + (flag2[0][0][2] - flag1[0][0][2]) / numOfStages * aS}, {2., -1.5, flag1[0][1][2] + (flag2[0][1][2] - flag1[0][1][2]) / numOfStages * aS},
			{4., -1.5, flag1[0][2][2] + (flag2[0][2][2] - flag1[0][2][2]) / numOfStages * aS}, {6., -1.5, flag1[0][3][2] + (flag2[0][3][2] - flag1[0][3][2]) / numOfStages * aS}}
		};
		glPushMatrix();
		glTranslatef(0.f, 2.f, 0.f);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &flag_front[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_FLAT);

		if (mesh) {
			for (j = 0; j <= 8; j++) {
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
				glEnd();
			}
		}
		else {
			glEvalMesh2(GL_FILL, 0, 20, 0, 20);
		}
		glFlush();

		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &flag_back[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_FLAT);

		if (mesh) {
			for (j = 0; j <= 8; j++) {
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for (i = 0; i <= 30; i++)
					glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
				glEnd();
			}
		}
		else {
			glEvalMesh2(GL_FILL, 0, 20, 0, 20);
		}
		glFlush();
		glPopMatrix();
	}
}

void cage_square(float x, float y, float z, float unit, bool mesh) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .2f, .2f, .2f, 1.f };
	float mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.f };
	float mat_shininess[] = { 128.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, dark_steel);
	glColor3f(dark_steel[0], dark_steel[1], dark_steel[2]);

	// TOP AND BOTTOM
	glPushMatrix();
	glTranslatef(0.f, y - 0.025f, 0.f);
	cuboid(x + unit * 2, 0.025f, z + unit * 2, mesh);
	glPopMatrix();
	cuboid(x + unit * 2, 0.025f, z + unit * 2, mesh);

	// X HORIZONTAL BARS
	glPushMatrix();
	glTranslatef(0.f, (y/2) - ((y - 0.05f) / 10) / 2, -z / 2);
	cuboid(x + unit, (y - 0.05f) / 10, unit, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, (y/2) - ((y - 0.05f) / 10) / 2, z / 2);
	cuboid(x + unit, (y - 0.05f) / 10, unit, mesh);
	glPopMatrix();
	
	// Z HORIZONTAL BARS
	glPushMatrix();
	glTranslatef(-x / 2, (y / 2) - ((y - 0.05f) / 10) / 2, 0.f);
	cuboid(unit, (y - 0.05f) / 10, z, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x / 2, (y / 2) - ((y - 0.05f) / 10) / 2, 0.f);
	cuboid(unit, (y - 0.05f) / 10, z, mesh);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	for (float i = -(x / 2.f); i < x / 2.f; i += unit * 5) {
		glPushMatrix();
		glTranslatef(i, 0.025f, z / 2.f);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(i, (y / 2) + ((y - 0.05f) / 10) / 2, z / 2.f);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(i, 0.025f, -z / 2.f);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(i, (y / 2) + ((y - 0.05f) / 10) / 2, -z / 2.f);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
	}
	for (float i = -(z / 2.f); i < z / 2.f; i += unit * 5) {
		glPushMatrix();
		glTranslatef(x / 2.f, 0.025f, i);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x / 2.f, (y / 2) + ((y - 0.05f) / 10) / 2, i);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-x / 2.f, 0.025f, i);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-x / 2.f, (y / 2) + ((y - 0.05f) / 10) / 2, i);
		cylinder(unit / 2.f, 5, (y / 2) - 0.025f - ((y - 0.05f) / 10) / 2, mesh);
		glPopMatrix();
	}
	glPopAttrib();
}

void ball_subdivision(int divisions, float radius) {
	float r = radius;

	subdivide(0, r, 0,
		r, 0, 0,
		0, 0, -r, divisions, radius);
	subdivide(0, -r, 0,
		0, 0, -r,
		r, 0, 0, divisions, radius);

	subdivide(0, r, 0,
		-r, 0, 0,
		0, 0, r, divisions, radius);
	subdivide(-r, 0, 0,
		0, -r, 0,
		0, 0, r, divisions, radius);

	subdivide(0, 0, -r,
		-r, 0, 0,
		0, r, 0, divisions, radius);
	subdivide(0, 0, -r,
		0, -r, 0,
		-r, 0, 0, divisions, radius);

	subdivide(r, 0, 0,
		0, r, 0,
		0, 0, r, divisions, radius);
	subdivide(r, 0, 0,
		0, 0, r,
		0, -r, 0, divisions, radius);
	
}

void colourful_ball(float radius) {
	ball_subdivision(4, radius);
	int i;
	int lineAmount = 100;

	circle_outline(radius);
}

void spotlight(float tilt, bool mesh, bool light) {
	float x = 0.f;
	float y = 0.f;
	float radius = .3f;
	float height = .4f;
	int i;
	int triangleAmount = 50;

	std::vector < std::pair<float, float> > outer;
	std::vector < std::pair<float, float> > inner;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		outer.push_back(std::make_pair<float, float>(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount))));
		inner.push_back(std::make_pair<float, float>(x + ((radius - .1f) * cos(i * twicePi / triangleAmount)), y + ((radius - .1f) * sin(i * twicePi / triangleAmount))));
	}

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .2f, .2f, .2f, 1.f };
	float mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.f };
	float mat_shininess[] = { 128.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);

	glPushMatrix();
	glTranslatef(0.f, height/4 * 3, 0.f);
	glRotatef(tilt, 1.0f, 0.f, 0.f);

	// BOTTOM
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, 0.f, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex3f(
			outer.at(i).first, 0.f,
			outer.at(i).second
		);
	}
	glEnd();
	// TOP
	glPushMatrix();
	glTranslatef(0.f, height, 0.f);
	for (i = 0; i < triangleAmount; i++) {
		square(inner.at(i).first, 0.f, inner.at(i).second,
			inner.at(i + 1).first, 0.f, inner.at(i + 1).second,
			outer.at(i + 1).first, 0.f, outer.at(i + 1).second,
			outer.at(i).first, 0.f, outer.at(i).second,
			(inner.at(i).first + inner.at(i + 1).first + outer.at(i + 1).first + outer.at(i).first) / 4, 0.f,
			(inner.at(i).second + inner.at(i + 1).second + outer.at(i + 1).second + outer.at(i).second) / 4, mesh);
	}
	glPopMatrix();

	// INNER
	glPushMatrix();
	glTranslatef(0.f, height - .15f, 0.f);
	for (i = 0; i < triangleAmount; i++) {
		square(inner.at(i + 1).first, 0.f, inner.at(i + 1).second,
			inner.at(i + 1).first, .15f, inner.at(i + 1).second,
			inner.at(i).first, .15f, inner.at(i).second,
			inner.at(i).first, 0.f, inner.at(i).second,
			(inner.at(i + 1).first + inner.at(i).first) / 2, .15f / 2.f, 
			(inner.at(i + 1).second + inner.at(i).second) / 2, mesh);
	}
	glPopMatrix();

	// OUTER
	for (i = 0; i < triangleAmount; i++) {
		square(outer.at(i).first, 0.f, outer.at(i).second,
			outer.at(i).first, height, outer.at(i).second,
			outer.at(i + 1).first, height, outer.at(i + 1).second,
			outer.at(i + 1).first, 0.f, outer.at(i + 1).second,
			(outer.at(i).first + outer.at(i + 1).first) / 2, height / 2, 
			(outer.at(i).second + outer.at(i + 1).second) / 2, mesh);
	}

	// MIDDLE - TOP
	for (i = 0; i < triangleAmount; i++) {
		subdivide_flat(inner.at(i).first, height - 0.02f, inner.at(i).second,
			x, height - 0.5f, y,
			inner.at(i + 1).first, height - 0.02f, inner.at(i + 1).second, 3, mesh);
	}

	// MIDDLE - BOTTOM
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	if (light) {
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
	}
	else {
		glMaterialfv(GL_FRONT, GL_EMISSION, def_emission);
	}
	for (i = 0; i < triangleAmount; i++) {
		subdivide_flat(inner.at(i).first, 0.25f, inner.at(i).second,
			x, 0.25f, y,
			inner.at(i + 1).first, 0.25f, inner.at(i + 1).second, 3, mesh);
	}
	glPopMatrix();

	// SUPPORTS
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
	glPushMatrix();
	glTranslatef(radius + 0.025f, 0.f, 0.f);
	cuboid(0.05f, height + height/3, radius * 2 / 3, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-radius - 0.025f, 0.f, 0.f);
	cuboid(0.05f, height + height / 3, radius * 2 / 3, mesh);
	glPopMatrix();

	cuboid(radius*2, 0.05f, radius * 2 / 3, mesh);
	glPopAttrib();
}

void stands_stairspart(float s_height, float s_length, bool mesh) {
	cuboid(s_length, s_height, .1f, mesh);

	glPushMatrix();
	glTranslatef(0.f, 0.f, .1f);
	cuboid(s_length, s_height * 2, .1f, mesh);

	glPushMatrix();
	glTranslatef(0.f, 0.f, .1f);
	cuboid(s_length, s_height * 3, .1f, mesh);

	glPushMatrix();
	glTranslatef(0.f, 0.f, .1f);
	cuboid(s_length, s_height * 4, .1f, mesh);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void stands_stairs(float s_height, float s_length, float height, bool mesh) {
	glPushMatrix();
	glTranslatef(0.f, 0.f, -.55f);
	stands_stairspart(s_height, s_length, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, height, -.15f);
	stands_stairspart(s_height, s_length, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, height * 2, .25f);
	stands_stairspart(s_height, s_length, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, 0.f);
	glRotatef(180.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, -height, -.15f);
	stands_stairspart(s_height, s_length, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, 0.f);
	glRotatef(180.f, 1.f, 0.f, 0.f);
	glTranslatef(0.f, -height * 2, -.55f);
	stands_stairspart(s_height, s_length, mesh);
	glPopMatrix();
}

void stands(bool mesh) {
	float height = .25f, length = 1.5f;
	float s_height = height / 4, s_length = .2f;
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, light_brown);
	glColor3f(light_brown[0], light_brown[1], light_brown[2]);

	cuboid(length, height, 1.2f, mesh);

	glPushMatrix();
	glTranslatef(0.f, height, .2f);
	cuboid(length, height, .8f, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, height * 2, .4f);
	cuboid(length, height, .4f, mesh);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, dark_brown);
	glColor3f(dark_brown[0], dark_brown[1], dark_brown[2]);
	// STAIRS - RIGHT
	glPushMatrix();
	glTranslatef((length / 2) + (s_length / 2), 0.f, 0.f);
	stands_stairs(s_height, s_length, height, mesh);
	glPopMatrix();

	// STAIRS - LEFT
	glPushMatrix();
	glTranslatef(-(length / 2) - (s_length / 2), 0.f, 0.f);
	stands_stairs(s_height, s_length, height, mesh);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, 0.75f);
	cuboid(length + s_length * 2, height * 3 + .1f, .3f, mesh);
	glPopMatrix();

	glPopMatrix();
}

void stands_with_seats(bool mesh) {
	float height = .25f, length = 1.5f;
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .2f, .2f, .2f, .3f };
	float mat_specular[] = { 0.3f, 0.0f, 0.0f, 1.f };
	float mat_shininess[] = { 0.0f };
	float mat_emission[] = { .0f, .0f, .0f, 1.f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	stands(mesh);

	float x = 0.f, z = 0.f;
	for (int l = 1; l <= 3; l++) {
		switch (l) {
		case 1:
			x = -0.4f;
			break;
		case 2:
			x = 0.f;
			break;
		case 3:
			x = 0.4f;
			break;
		}
		for (int i = 1; i <= 3; i++) {
			switch (i) {
			case 1:
				z = -0.4f;
				break;
			case 2:
				z = 0.f;
				break;
			case 3:
				z = 0.4f;
				break;
			}
			glPushMatrix();
			glTranslatef(x, height * i, z);
			bench(mesh);
			glPopMatrix();
		}
	}
	glPopAttrib();
}

void lamppost(int aS, bool light, bool mesh, bool flicker) {
	glPushMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_diffuse[] = { .2f, .2f, .2f, 1.f };
	float mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.f };
	float mat_shininess[] = { 128.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	// BASE
	cylinder(.1f, 10, .3f, mesh);

	glPushMatrix();
	glTranslatef(0.f, .3f, 0.f);
	cylinder(.085f, 10, .03f, mesh);
	glPopMatrix();

	// POST - VERTICAL
	glPushMatrix();
	glTranslatef(0.f, .33f, 0.f);
	cylinder(.045f, 8, 1.f, mesh);
	glPopMatrix();
	// POST - HORIZONTAL
	glPushMatrix();
	glTranslatef(.2f, 1.33f, 0.f);
	glRotatef(90.f, 0.f, 0.f, 1.f);
	cylinder(.045f, 8, .9f, mesh);
	glPopMatrix();

	// LIGHT - BOX
	glPushMatrix();
	glTranslatef(-.8f, 1.32f, 0.f);
	cuboid(.2f, .05f, .1f, mesh);
	glPopMatrix();
	// LIGHT - DECAL
	glPushMatrix();
	glTranslatef(-.8f, 1.325f, 0.f);
	cuboid(.19f, .05f, .08f, mesh);
	glPopMatrix();
	
	glMaterialfv(GL_FRONT, GL_EMISSION, def_emission);
	if (light) {
		if (flicker) {
			switch (aS) {
			case 0:
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission0);
				break;
			case 1:
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
				break;
			case 2:
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission2);
				break;
			}
		}
		else {
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
		}
	}

	// LIGHT - LIGHT OUT
	glPushMatrix();
	glTranslatef(-.8f, 1.28f, 0.f);
	cuboid(.14f, .04f, .065f, mesh);
	glPopMatrix();

	glPopMatrix();
	glPopAttrib();
}

void bench(bool mesh) {
	
	float legx = 0.035f, legy = 0.1f, legz = 0.05f;
	float leg_distancex = 0.4f, leg_distancez = 0.14f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, dark_brown);
	glColor3f(dark_brown[0], dark_brown[1], dark_brown[2]);

	// FRONT SEAT
	glPushMatrix();
	glTranslatef(.0f, 0.1f, -0.14f / 2 + 0.015f);
	cuboid(.5f, .02f, .1f, mesh);
	glPopMatrix();

	// BACK SEAT
	glPushMatrix();
	glTranslatef(.0f, 0.1f, 0.14f / 2 - 0.015f);
	cuboid(.5f, .02f, .1f, mesh);
	glPopMatrix();

	// BACK SUPPORT
	glPushMatrix();
	glTranslatef(0.f, 0.16f, (leg_distancez / 2) + (legx / 2) - 0.018f);
	cuboid(.5f, .1f, .02f, mesh);
	glPopMatrix();

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	float mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.f };
	float mat_shininess[] = { 128.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, steel);
	glColor3f(steel[0], steel[1], steel[2]);
	// LEFT FRONT
	glPushMatrix();
	glTranslatef(-leg_distancex / 2, 0.f, leg_distancez / 2);
	cuboid(legx, legy, legz, mesh);
	cuboid(legx + 0.009f, 0.009f, legz + 0.009f, mesh);
	glPopMatrix();

	// RIGHT FRONT
	glPushMatrix();
	glTranslatef(leg_distancex / 2, 0.f, leg_distancez / 2);
	cuboid(legx, legy, legz, mesh);
	cuboid(legx + 0.009f, 0.009f, legz + 0.009f, mesh);
	glPopMatrix();

	// LEFT BACK
	glPushMatrix();
	glTranslatef(-leg_distancex / 2, 0.f, -leg_distancez / 2);
	cuboid(legx, legy, legz, mesh);
	cuboid(legx + 0.009f, 0.009f, legz + 0.009f, mesh);
	glPopMatrix();

	// RIGHT BACK
	glPushMatrix();
	glTranslatef(leg_distancex / 2, 0.f, -leg_distancez / 2);
	cuboid(legx, legy, legz, mesh);
	cuboid(legx + 0.009f, 0.009f, legz + 0.009f, mesh);
	glPopMatrix();

	// LEFT LINK
	glPushMatrix();
	glTranslatef(-leg_distancex / 2, .05f, 0.f);
	cuboid(.02f, .02f, leg_distancez, mesh);
	glPopMatrix();

	// RIGHT LINK
	glPushMatrix();
	glTranslatef(leg_distancex / 2, .05f, 0.f);
	cuboid(.02f, .02f, leg_distancez, mesh);
	glPopMatrix();

	// LEFT BACK LINK
	glPushMatrix();
	glTranslatef(-leg_distancex / 2, legy + .02f, (leg_distancez / 2) + (legx / 2));
	cuboid(.03f, legy, .015f, mesh);
	glPopMatrix();

	// RIGHT BACK LINK
	glPushMatrix();
	glTranslatef(leg_distancex / 2, legy + .02f, (leg_distancez / 2) + (legx / 2));
	cuboid(.03f, legy, .015f, mesh);
	glPopMatrix();
	glPopAttrib();
	
}