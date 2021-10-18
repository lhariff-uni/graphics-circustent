#include "shapes.h"

#define SUBDIVISION_LEVEL 3

void subdivide(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz, int level, float distance) {
	if (level == 1) {
		glBegin(GL_TRIANGLES);
		glVertex3f(ax, ay, az);
		glVertex3f(bx, by, bz);
		glVertex3f(cx, cy, cz);
		glEnd();
	}
	else {
		float ab_x = (ax + bx) / 2;
		float ab_y = (ay + by) / 2;
		float ab_z = (az + bz) / 2;
		float s = distance / sqrt(ab_x * ab_x + ab_y * ab_y + ab_z * ab_z);
		ab_x *= s;
		ab_y *= s;
		ab_z *= s;

		float ac_x = (ax + cx) / 2;
		float ac_y = (ay + cy) / 2;
		float ac_z = (az + cz) / 2;
		s = distance / sqrt(ac_x * ac_x + ac_y * ac_y + ac_z * ac_z);
		ac_x *= s;
		ac_y *= s;
		ac_z *= s;

		float bc_x = (bx + cx) / 2;
		float bc_y = (by + cy) / 2;
		float bc_z = (bz + cz) / 2;
		s = distance / sqrt(bc_x * bc_x + bc_y * bc_y + bc_z * bc_z);
		bc_x *= s;
		bc_y *= s;
		bc_z *= s;

		subdivide(ax, ay, az,
			ab_x, ab_y, ab_z,
			ac_x, ac_y, ac_z,
			level - 1, distance);
		subdivide(ab_x, ab_y, ab_z,
			bx, by, bz,
			bc_x, bc_y, bc_z,
			level - 1, distance);
		subdivide(ac_x, ac_y, ac_z,
			bc_x, bc_y, bc_z,
			cx, cy, cz,
			level - 1, distance);
		subdivide(ab_x, ab_y, ab_z,
			bc_x, bc_y, bc_z,
			ac_x, ac_y, ac_z,
			level - 1, distance);
	}
}

void subdivide_flat(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz, int level, bool mesh) {
	if (level == 1) {
		if (mesh) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(ax, ay, az);
			glVertex3f(bx, by, bz);
			glVertex3f(cx, cy, cz);
			glEnd();
		}
		else {
			glBegin(GL_TRIANGLES);
			glVertex3f(ax, ay, az);
			glVertex3f(bx, by, bz);
			glVertex3f(cx, cy, cz);
			glEnd();
		}
	}
	else {
		float ab_x = (ax + bx) / 2;
		float ab_y = (ay + by) / 2;
		float ab_z = (az + bz) / 2;

		float ac_x = (ax + cx) / 2;
		float ac_y = (ay + cy) / 2;
		float ac_z = (az + cz) / 2;

		float bc_x = (bx + cx) / 2;
		float bc_y = (by + cy) / 2;
		float bc_z = (bz + cz) / 2;

		subdivide_flat(ax, ay, az,
			ab_x, ab_y, ab_z,
			ac_x, ac_y, ac_z,
			level - 1, mesh);
		subdivide_flat(ab_x, ab_y, ab_z,
			bx, by, bz,
			bc_x, bc_y, bc_z,
			level - 1, mesh);
		subdivide_flat(ac_x, ac_y, ac_z,
			bc_x, bc_y, bc_z,
			cx, cy, cz,
			level - 1, mesh);
		subdivide_flat(ab_x, ab_y, ab_z,
			bc_x, bc_y, bc_z,
			ac_x, ac_y, ac_z,
			level - 1, mesh);
	}
}

void octahedron_subdivision(int divisions, float radius) {
	float r = radius;
	subdivide(r, 0, 0,
		0, r, 0,
		0, 0, r, divisions, radius);

	subdivide(r, 0, 0,
		0, 0, r,
		0, -r, 0, divisions, radius);

	subdivide(0, r, 0,
		r, 0, 0,
		0, 0, -r, divisions, radius);

	subdivide(0, -r, 0,
		0, 0, -r,
		r, 0, 0, divisions, radius);

	subdivide(0, 0, -r,
		-r, 0, 0,
		0, r, 0, divisions, radius);
	subdivide(0, 0, -r,
		0, -r, 0,
		-r, 0, 0, divisions, radius);

	subdivide(0, r, 0,
		-r, 0, 0,
		0, 0, r, divisions, radius);

	subdivide(-r, 0, 0,
		0, -r, 0,
		0, 0, r, divisions, radius);
}

void sphere(float radius) {
	octahedron_subdivision(5, radius);
}

void circle_outline(float radius) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 100; i++) {
		glVertex3f(
			0.f + ((radius) * cos(i * (2.0f * M_PI) / 100)), 0.f,
			0.f + ((radius) * sin(i * (2.0f * M_PI) / 100))
		);
	}
	glEnd();
}

void square(float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz,
	float dx, float dy, float dz,
	float midx, float midy, float midz, bool mesh) {
	int level = SUBDIVISION_LEVEL;
	subdivide_flat(midx, midy, midz,
		ax, ay, az,
		bx, by, bz, level, mesh);
	subdivide_flat(midx, midy, midz,
		bx, by, bz,
		cx, cy, cz, level, mesh);
	subdivide_flat(midx, midy, midz,
		cx, cy, cz,
		dx, dy, dz, level, mesh);
	subdivide_flat(midx, midy, midz,
		dx, dy, dz,
		ax, ay, az, level, mesh);
}

void cone(float radius, int level, float height) {
	float x = 0.f;
	float y = 0.f;
	int i;
	int triangleAmount = level;

	std::vector < std::pair<float, float> > vtx;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		vtx.push_back(std::make_pair<float, float>(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount))));
	}
	
	// TOP
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, height, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex3f(
			vtx.at(i).first, height,
			vtx.at(i).second
		);
	}
	glEnd();

	bool red = true;
	// SIDES
	glBegin(GL_TRIANGLES);
	for (i = triangleAmount; i >= 0; i--) {
		if (red) {
			glColor4f(1.0f, .0f, .0f, 1.f);
		}
		else {
			glColor4f(1.0f, 1.0f, 1.0f, 1.f);
		}

		if (i == triangleAmount) {
			glVertex3f(
				vtx.at(0).first, height,
				vtx.at(0).second
			);
			glVertex3f(
				vtx.at(i).first, height,
				vtx.at(i).second
			);
			glVertex3f(x, 0.f, y);
		}
		else {
			glVertex3f(
				vtx.at(i + 1).first, height,
				vtx.at(i + 1).second
			);
			glVertex3f(
				vtx.at(i).first, height,
				vtx.at(i).second
			);
			glVertex3f(x, 0.f, y);
		}
		red = !red;
	}
	glEnd();
}

void cylinder(float radius, int level, float height, bool mesh, bool top, bool bottom) {
	float x = 0.f;
	float y = 0.f;
	int i;
	int triangleAmount = level;

	std::vector < std::pair<float, float> > vtx;
	GLfloat twicePi = 2.0f * M_PI;

	for (i = 0; i <= triangleAmount; i++) {
		vtx.push_back(std::make_pair<float, float>(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount))));
	}

	// TOP
	if (top) {
		for (i = 0; i < triangleAmount; i++) {
			subdivide_flat(vtx.at(i).first, height, vtx.at(i).second,
				x, height, y,
				vtx.at(i + 1).first, height, vtx.at(i + 1).second, 3, mesh);
		}
	}

	// BOTTOM
	if (bottom) {
		for (i = triangleAmount; i > 0; i--) {
			subdivide_flat(vtx.at(i).first, 0.f, vtx.at(i).second,
				x, 0.f, y,
				vtx.at(i - 1).first, 0.f, vtx.at(i - 1).second, 3, mesh);
		}
	}

	// SIDES
	for (i = 0; i < triangleAmount; i++) {
		square(vtx.at(i).first, 0.f, vtx.at(i).second,
			vtx.at(i).first, height, vtx.at(i).second,
			vtx.at(i + 1).first, height, vtx.at(i + 1).second,
			vtx.at(i + 1).first, 0.f, vtx.at(i + 1).second,
			(vtx.at(i + 1).first + vtx.at(i).first) / 2, height / 2, (vtx.at(i + 1).second + vtx.at(i).second) / 2, mesh);
	}
}

void cuboid(float lengthx, float height, float lengthz, bool mesh) {
	// TOP
	glNormal3f(0.f, 1.f, 0.f);
	square(-lengthx / 2, height, lengthz / 2,
		lengthx / 2, height, lengthz / 2,
		lengthx / 2, height, -lengthz / 2,
		-lengthx / 2, height, -lengthz / 2,
		0.f, height, 0.f, mesh);

	// BOTTOM
	glNormal3f(0.f, -1.f, 0.f);
	square(-lengthx / 2, 0.f, -lengthz / 2,
		lengthx / 2, 0.f, -lengthz / 2,
		lengthx / 2, 0.f, lengthz / 2,
		-lengthx / 2, 0.f, lengthz / 2,
		0.f, 0.f, 0.f, mesh);

	// BACK
	glNormal3f(0.f, 0.f, -1.f);
	square(-lengthx / 2, height, -lengthz / 2,
		lengthx / 2, height, -lengthz / 2,
		lengthx / 2, 0.f, -lengthz / 2,
		-lengthx / 2, 0.f, -lengthz / 2,
		0.f, height / 2, -lengthz / 2, mesh);

	// FRONT
	glNormal3f(0.f, 0.f, 1.f);
	square(-lengthx / 2, 0.f, lengthz / 2,
		lengthx / 2, 0.f, lengthz / 2,
		lengthx / 2, height, lengthz / 2,
		-lengthx / 2, height, lengthz / 2,
		0.f, height / 2, lengthz / 2, mesh);

	// LEFT
	glNormal3f(-1.f, 0.f, 0.f);
	square(-lengthx / 2, 0.f, lengthz / 2,
		-lengthx / 2, height, lengthz / 2,
		-lengthx / 2, height, -lengthz / 2,
		-lengthx / 2, 0.f, -lengthz / 2,
		-lengthx / 2, height / 2, 0.f, mesh);

	// RIGHT
	glNormal3f(1.f, 0.f, 0.f);
	square(lengthx / 2, 0.f, -lengthz / 2,
		lengthx / 2, height, -lengthz / 2,
		lengthx / 2, height, lengthz / 2,
		lengthx / 2, 0.f, lengthz / 2,
		lengthx / 2, height / 2, 0.f, mesh);
}