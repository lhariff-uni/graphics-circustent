#include "tent.h"
#define RADIUS .5f
#define HEIGHT .6f
#define SIDES 26

float red_in[] = { 1.0f, .5f, .5f, 1.f };
float red_out[] = { 1.0f, .0f, .0f, 1.f };
float white_in[] = { .5f, .5f, .5f, 1.f };
float white_out[] = { 1.0f, 1.0f, 1.0f, 1.f };
float sandy[] = { .87450980392f, .70196078431f, .45882352941f, .5f };

void stage(bool mesh) {
	float x = 0.f;
	float y = 0.f;
	float radius = 1.f;
	int i;
	int triangleAmount = 120;

	std::vector < std::pair<float, float> > outer;
	std::vector < std::pair<float, float> > inner;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		outer.push_back(std::make_pair<float, float>(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount))));
		inner.push_back(std::make_pair<float, float>(x + ((radius - .1f) * cos(i * twicePi / triangleAmount)), y + ((radius - .1f) * sin(i * twicePi / triangleAmount))));
	}

	bool red = false;

	// TOP
	glPushMatrix();
	glTranslatef(0.f, .3f, 0.f);
	for (i = 0; i < triangleAmount; i++) {
		red = (i / 15) % 2;
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
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
	glTranslatef(0.f, .2f, 0.f);
	for (i = 0; i < triangleAmount; i++) {
		red = (i / 15) % 2;
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
		square(inner.at(i + 1).first, 0.f, inner.at(i + 1).second,
			inner.at(i + 1).first, .1f, inner.at(i + 1).second,
			inner.at(i).first, .1f, inner.at(i).second,
			inner.at(i).first, 0.f, inner.at(i).second,
			(inner.at(i + 1).first + inner.at(i).first) / 2, 0.05f, (inner.at(i + 1).second + inner.at(i).second) / 2, mesh);
	}
	glPopMatrix();

	// OUTER
	for (i = 0; i < triangleAmount; i++) {
		red = (i / 15) % 2;
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
		square(outer.at(i).first, 0.f, outer.at(i).second,
			outer.at(i).first, .3f, outer.at(i).second,
			outer.at(i + 1).first, .3f, outer.at(i + 1).second,
			outer.at(i + 1).first, 0.f, outer.at(i + 1).second,
			(outer.at(i + 1).first + outer.at(i).first) / 2, 0.15f, (outer.at(i + 1).second + outer.at(i).second) / 2, mesh);
	}

	// MIDDLE
	float mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.f };
	float mat_shininess[] = { 0.0f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, sandy);
	glColor3f(sandy[0], sandy[1], sandy[2]);
	for (i = 0; i < triangleAmount; i++) {
		glNormal3f(0.f, 1.f, 0.f);
		subdivide_flat(inner.at(i).first, 0.2f, inner.at(i).second,
			x, 0.2f, y,
			inner.at(i + 1).first, 0.2f, inner.at(i + 1).second, 3, mesh);
	}
}

void tent_roof_mini(bool mesh) {
	float x = 0.f;
	float y = 0.f;
	int i;
	int triangleAmount = SIDES;

	std::vector < std::pair<float, float> > vtx;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		vtx.push_back(std::make_pair<float, float>(x +
			(RADIUS/2 * cos(i * twicePi / triangleAmount)), y + (RADIUS/2 * sin(i * twicePi / triangleAmount))));
	}
	bool red = true;
	// SIDES
	glBegin(GL_TRIANGLES);
	// OUTSIDE
	for (i = triangleAmount - 1; i >= 0; i--) {
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
		subdivide_flat(
			x, 0.f, y,
			vtx.at(i).first, HEIGHT / 2, vtx.at(i).second,
			vtx.at(i + 1).first, HEIGHT / 2, vtx.at(i + 1).second, 4, mesh
		);
		red = !red;
	}
	glEnd();
}

void tent_roof(bool mesh) {
	float x = 0.f;
	float y = 0.f;
	int i;
	int triangleAmount = SIDES;

	std::vector < std::pair<float, float> > vtx;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		vtx.push_back(std::make_pair<float, float>(x + 
			(RADIUS * cos(i * twicePi / triangleAmount)), y + (RADIUS * sin(i * twicePi / triangleAmount))));
	}

	bool red = true;
	// SIDES
	
	// OUTSIDE
	for (i = triangleAmount - 1; i >= 0; i--) {
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
		
		subdivide_flat(
			x, 0.f, y,
			vtx.at(i).first, HEIGHT, vtx.at(i).second,
			vtx.at(i + 1).first, HEIGHT, vtx.at(i + 1).second, 4, mesh
		);
		red = !red;
	}
	// INSIDE
	for (i = triangleAmount-1; i >= 0; i--) {
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_in);
			glColor3f(red_in[0], red_in[1], red_in[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_in);
			glColor3f(white_in[0], white_in[1], white_in[2]);
		}

		subdivide_flat(
			vtx.at(i + 1).first, HEIGHT, vtx.at(i + 1).second,
			vtx.at(i).first, HEIGHT, vtx.at(i).second,
			x, 0.f, y, 4, mesh
		);
		red = !red;
	}
}

void tent_walls(bool mesh) {
	float x = 0.f;
	float y = 0.f;
	int i;
	int triangleAmount = SIDES;

	std::vector < std::pair<float, float> > vtx;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		vtx.push_back(std::make_pair<float, float>(x + (RADIUS * cos(i * twicePi / triangleAmount)), y + (RADIUS * sin(i * twicePi / triangleAmount))));
	}
	bool red = true;
	// INSIDE
	for (i = 0; i < triangleAmount-1; i++) {
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_in);
			glColor3f(red_in[0], red_in[1], red_in[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_in);
			glColor3f(white_in[0], white_in[1], white_in[2]);
		}
		square(vtx.at(i + 1).first, 0.f, vtx.at(i + 1).second,
			vtx.at(i + 1).first, HEIGHT / 2, vtx.at(i + 1).second,
			vtx.at(i).first, HEIGHT / 2, vtx.at(i).second,
			vtx.at(i).first, 0.f, vtx.at(i).second,
			(vtx.at(i + 1).first + vtx.at(i).first) / 2, HEIGHT / 2 / 2, (vtx.at(i + 1).second + vtx.at(i).second) / 2, mesh);
		red = !red;
	}

	// OUTSIDE
	red = true;
	for (i = 0; i < triangleAmount-1; i++) {
		if (red) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, red_out);
			glColor3f(red_out[0], red_out[1], red_out[2]);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT, white_out);
			glColor3f(white_out[0], white_out[1], white_out[2]);
		}
		square(vtx.at(i).first, 0.f, vtx.at(i).second,
			vtx.at(i).first, HEIGHT / 2, vtx.at(i).second,
			vtx.at(i + 1).first, HEIGHT / 2, vtx.at(i + 1).second,
			vtx.at(i + 1).first, 0.f, vtx.at(i + 1).second,
			(vtx.at(i + 1).first + vtx.at(i).first) / 2, HEIGHT / 2 / 2, (vtx.at(i + 1).second + vtx.at(i).second) / 2, mesh);
		red = !red;
	}
}