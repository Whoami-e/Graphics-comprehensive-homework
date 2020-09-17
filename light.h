#pragma once
class Light {
public:
	Light();
	void setLight(GLenum lig, GLfloat pos[], GLfloat amb[], GLfloat dif[], GLfloat spec[]);
	void setLight(GLenum lig, GLfloat pos[], GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat spot_dir[]);
	void setLightMode();
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat spot_direction[4];
	GLenum light;
};
Light::Light()
{
	position[4] = { 0 };
	ambient[4] = { 0 };
	diffuse[4] = { 0 };
	specular[4] = { 0 };
	light = 0;
}
void Light::setLight(GLenum lig, GLfloat pos[], GLfloat amb[], GLfloat dif[], GLfloat spec[])
{
	memcpy(position, pos, sizeof(pos) * 4);
	memcpy(ambient, amb, sizeof(amb) * 4);
	memcpy(diffuse, dif, sizeof(dif) * 4);
	memcpy(specular, spec, sizeof(spec) * 4);
	light = lig;
}
void Light::setLight(GLenum lig, GLfloat pos[], GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat spot_dir[])
{
	memcpy(position, pos, sizeof(pos) * 4);
	memcpy(ambient, amb, sizeof(amb) * 4);
	memcpy(diffuse, dif, sizeof(dif) * 4);
	memcpy(specular, spec, sizeof(spec) * 4);
	memcpy(spot_direction, spot_dir, sizeof(spot_dir) * 4);
	light = lig;
}
void Light::setLightMode()
{

	glLightfv(light, GL_AMBIENT, ambient);
	glLightfv(light, GL_DIFFUSE, diffuse);
	glLightfv(light, GL_SPECULAR, specular);
	glLightfv(light, GL_POSITION, position);

	if (position[3])  //direction or no-direction
	{
		glLightf(light, GL_SPOT_CUTOFF, 30.0);
		glLightfv(light, GL_SPOT_DIRECTION, spot_direction);
		glLightf(light, GL_SPOT_EXPONENT, 2.0); //¾Û¹âµÆÖ¸Êý
	}
}
class material {
public:
	material();
	void setMaterial(GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat shine[]);
	void setmaterialMode();
	void emissionMode(GLint emis);
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat no_mat[4];
	GLfloat shininess[4];
};
material::material()
{
	ambient[4] = { 0 };
	diffuse[4] = { 0 };
	specular[4] = { 0 };
	emission[0] = 0.4; emission[1] = 0.2; emission[2] = 0.2; emission[3] = 0.2;
	no_mat[0] = 0.0; no_mat[1] = 0.0; no_mat[2] = 0.0; no_mat[3] = 1.0;
	shininess[4] = { 0.0 };
}
void material::setMaterial(GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat shine[])
{

	memcpy(ambient, amb, sizeof(amb) * 4);
	memcpy(diffuse, dif, sizeof(dif) * 4);
	memcpy(specular, spec, sizeof(spec) * 4);
	memcpy(shininess, shine, sizeof(shine) * 4);
}
void material::setmaterialMode()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
void material::emissionMode(GLint emis)
{
	if (emis)
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}