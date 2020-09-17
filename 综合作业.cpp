#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "tree.h"
#include "light.h"
using namespace std;

#define ORTHO 1  
#define FRUSTUM 2  
#define PERSPECTIVE 3  
GLint WindW = 800;
GLint WindH = 800;
//旋转
GLfloat xangle, yangle;
GLfloat oldx, oldy;
//放大缩小
GLfloat X, Y, Z;
GLfloat PI = 3.14;
string way[3]; //提供生成规则 
string rule, temprule;

float len; //单步长
float len1;
//float Alphax;
float Alphay;
float Alphaz;
int k;   //树干树
int n;  //迭代次数

Node   stack[150];
int    stackpointer;
void LSystemRule();

material goldMat;
Light light1;

static GLuint textName[7];
char* filename[7] = { "data\\tieban1.bmp", "data\\wall1.bmp", "data\\qiangzhu.bmp","data\\ground2.bmp","data\\xiaoba.bmp","data\\daba.bmp","data\\apex.bmp"};
Image image[7];

float a = 5.0;
//地板（底部） y,x,z
static const GLfloat vertex_list1[][3] = {
	 0.0f, -2.0f, -2.0f,
	 0.05f, -2.0f, -2.0f,
	 0.0f,  2.0f, -2.0f,
	 0.05f,  2.0f, -2.0f,
	 0.0f, -2.0f,  2.0f,
	 0.05f, -2.0f,  2.0f,
	 0.0f,  2.0f,  2.0f,
	 0.05f,  2.0f,  2.0f,
};
//地板（上部）
static const GLfloat vertex_list2[][3] = {
	 0.05f, -2.0f, 0.5f,
	 0.15f, -2.0f, 0.5f,
	 0.05f,  2.0f, 0.5f,
	 0.15f,  2.0f, 0.5f,
	 0.05f, -2.0f,  2.0f,
	 0.15f, -2.0f,  2.0f,
	 0.05f,  2.0f,  2.0f,
	 0.15f,  2.0f,  2.0f,
};

//枪柱1
static const GLfloat vertex_list3[][3] = {
	 0.15f, 1.0f, 1.9f,
	 0.5f, 1.0f, 1.9f,
	 0.15f,  1.1f, 1.9f,
	 0.5f,  1.1f, 1.9f,
	 0.15f, 1.0f,  2.0f,
	 0.5f, 1.0f,  2.0f,
	 0.15f,  1.1f,  2.0f,
	 0.5f,  1.1f,  2.0f,
};

//枪柱2
static const GLfloat vertex_list4[][3] = {
	 0.15f, 1.0f, 1.2f,
	 0.5f, 1.0f, 1.2f,
	 0.15f,  1.1f, 1.2f,
	 0.5f,  1.1f, 1.2f,
	 0.15f, 1.0f,  1.3f,
	 0.5f, 1.0f,  1.3f,
	 0.15f,  1.1f,  1.3f,
	 0.5f,  1.1f,  1.3f,
};

//枪柱3
static const GLfloat vertex_list5[][3] = {
	 0.15f, 1.0f, 0.5f,
	 0.5f, 1.0f, 0.5f,
	 0.15f,  1.1f, 0.5f,
	 0.5f,  1.1f, 0.5f,
	 0.15f, 1.0f,  0.6f,
	 0.5f, 1.0f,  0.6f,
	 0.15f,  1.1f,  0.6f,
	 0.5f,  1.1f,  0.6f,
};

//枪柱4
static const GLfloat vertex_list6[][3] = {
	 0.15f, -1.0f, 0.5f,
	 0.5f, -1.0f, 0.5f,
	 0.15f,  -1.1f, 0.5f,
	 0.5f,  -1.1f, 0.5f,
	 0.15f, -1.0f,  0.6f,
	 0.5f, -1.0f,  0.6f,
	 0.15f,  -1.1f,  0.6f,
	 0.5f,  -1.1f,  0.6f,
};

//枪柱5
static const GLfloat vertex_list7[][3] = {
	 0.15f, -1.0f, 1.2f,
	 0.5f, -1.0f, 1.2f,
	 0.15f,  -1.1f, 1.2f,
	 0.5f,  -1.1f, 1.2f,
	 0.15f, -1.0f,  1.3f,
	 0.5f, -1.0f,  1.3f,
	 0.15f,  -1.1f,  1.3f,
	 0.5f,  -1.1f,  1.3f,
};

//枪柱6
static const GLfloat vertex_list8[][3] = {
	 0.15f, -1.0f, 1.9f,
	 0.5f, -1.0f, 1.9f,
	 0.15f,  -1.1f, 1.9f,
	 0.5f,  -1.1f, 1.9f,
	 0.15f, -1.0f,  2.0f,
	 0.5f, -1.0f,  2.0f,
	 0.15f,  -1.1f,  2.0f,
	 0.5f,  -1.1f,  2.0f,
};

//靶底1
static const GLfloat vertex_list9[][3] = {
	 0.05f, 0.2f, -0.4f,
	 0.15f, 0.2f, -0.4f,
	 0.05f,  1.0f, -0.4f,
	 0.15f,  1.0f, -0.4f,
	 0.05f, 0.2f,  -0.7f,
	 0.15f, 0.2f,  -0.7f,
	 0.05f,  1.0f,  -0.7f,
	 0.15f,  1.0f,  -0.7f,
};

//靶底2
static const GLfloat vertex_list10[][3] = {
	 0.05f, -0.2f, -0.4f,
	 0.15f, -0.2f, -0.4f,
	 0.05f,  -1.0f, -0.4f,
	 0.15f,  -1.0f, -0.4f,
	 0.05f, -0.2f,  -0.7f,
	 0.15f, -0.2f,  -0.7f,
	 0.05f,  -1.0f,  -0.7f,
	 0.15f,  -1.0f,  -0.7f,
};

//靶1
static const GLfloat vertex_list11[][3] = {
	 0.3f, 0.7f, -0.52f,
	 0.5f, 0.7f, -0.52f,
	 0.3f,  0.9f, -0.52f,
	 0.5f,  0.9f, -0.52f,
	 0.3f, 0.7f,  -0.58f,
	 0.5f, 0.7f,  -0.58f,
	 0.3f, 0.9f,  -0.58f,
	 0.5f,  0.9f,  -0.58f,
};

//靶2
static const GLfloat vertex_list12[][3] = {
	 0.3f, 0.3f, -0.52f,
	 0.5f, 0.3f, -0.52f,
	 0.3f,  0.5f, -0.52f,
	 0.5f,  0.5f, -0.52f,
	 0.3f, 0.3f,  -0.58f,
	 0.5f, 0.3f,  -0.58f,
	 0.3f, 0.5f,  -0.58f,
	 0.5f,  0.5f,  -0.58f,
};

//靶3
static const GLfloat vertex_list13[][3] = {
	 0.3f, -0.3f, -0.52f,
	 0.5f, -0.3f, -0.52f,
	 0.3f,  -0.5f, -0.52f,
	 0.5f,  -0.5f, -0.52f,
	 0.3f, -0.3f,  -0.58f,
	 0.5f, -0.3f,  -0.58f,
	 0.3f, -0.5f,  -0.58f,
	 0.5f,  -0.5f,  -0.58f,
};

//靶4
static const GLfloat vertex_list14[][3] = {
	 0.3f, -0.7f, -0.52f,
	 0.5f, -0.7f, -0.52f,
	 0.3f,  -0.9f, -0.52f,
	 0.5f,  -0.9f, -0.52f,
	 0.3f, -0.7f,  -0.58f,
	 0.5f, -0.7f,  -0.58f,
	 0.3f, -0.9f,  -0.58f,
	 0.5f,  -0.9f,  -0.58f,
};

//大靶底
static const GLfloat vertex_list15[][3] = {
	 0.05f, 0.4f, -1.0f,
	 0.15f, 0.4f, -1.0f,
	 0.05f,  -0.4f, -1.0f,
	 0.15f,  -0.4f, -1.0f,
	 0.05f, 0.4f,  -1.3f,
	 0.15f, 0.4f,  -1.3f,
	 0.05f,  -0.4f,  -1.3f,
	 0.15f,  -0.4f,  -1.3f,
};

//大靶
static const GLfloat vertex_list16[][3] = {
	 0.25f, 0.2f, -1.12f,
	 0.65f, 0.2f, -1.12f,
	 0.25f,  -0.2f, -1.12f,
	 0.65f,  -0.2f, -1.12f,
	 0.25f, 0.2f,  -1.18f,
	 0.65f, 0.2f,  -1.18f,
	 0.25f,  -0.2f,  -1.18f,
	 0.65f,  -0.2f,  -1.18f,
};

//土块1
static const GLfloat vertex_list17[][3] = {
	 0.05f, 2.0f, -0.9f,
	 0.25f, 2.0f, -0.9f,
	 0.05f, 1.3f, -0.9f,
	 0.25f, 1.3f, -0.9f,
	 0.05f, 2.0f,  -2.0f,
	 0.25f, 2.0f,  -2.0f,
	 0.05f, 1.3f,  -2.0f,
	 0.25f, 1.3f,  -2.0f,
};

//土块2
static const GLfloat vertex_list18[][3] = {
	 0.05f, -2.0f, -0.9f,
	 0.25f, -2.0f, -0.9f,
	 0.05f, -1.3f, -0.9f,
	 0.25f, -1.3f, -0.9f,
	 0.05f, -2.0f,  -2.0f,
	 0.25f, -2.0f,  -2.0f,
	 0.05f, -1.3f,  -2.0f,
	 0.25f, -1.3f,  -2.0f,
};

//土块3
static const GLfloat vertex_list19[][3] = {
	 0.05f, -1.3f, -1.4f,
	 0.25f, -1.3f, -1.4f,
	 0.05f, 1.3f, -1.4f,
	 0.25f, 1.3f, -1.4f,
	 0.05f, -1.3f,  -2.0f,
	 0.25f, -1.3f,  -2.0f,
	 0.05f, 1.3f,  -2.0f,
	 0.25f, 1.3f,  -2.0f,
};

//大靶柱1
static const GLfloat vertex_list20[][3] = {
	 0.15f, 0.2f, -1.12f,
	 0.25f, 0.2f, -1.12f,
	 0.15f, 0.15f, -1.12f,
	 0.25f, 0.15f, -1.12f,
	 0.15f, 0.2f,  -1.18f,
	 0.25f, 0.2f,  -1.18f,
	 0.15f, 0.15f,  -1.18f,
	 0.25f, 0.15f,  -1.18f,
};

//大靶柱2
static const GLfloat vertex_list21[][3] = {
	 0.15f, -0.2f, -1.12f,
	 0.25f, -0.2f, -1.12f,
	 0.15f, -0.15f, -1.12f,
	 0.25f, -0.15f, -1.12f,
	 0.15f, -0.2f,  -1.18f,
	 0.25f, -0.2f,  -1.18f,
	 0.15f, -0.15f,  -1.18f,
	 0.25f, -0.15f,  -1.18f,
};

//小靶柱1
static const GLfloat vertex_list22[][3] = {
	 0.15f, 0.86f, -0.52f,
	 0.3f, 0.86f, -0.52f,
	 0.15f,  0.9f, -0.52f,
	 0.3f,  0.9f, -0.52f,
	 0.15f, 0.86f,  -0.58f,
	 0.3f, 0.86f,  -0.58f,
	 0.15f, 0.9f,  -0.58f,
	 0.3f,  0.9f,  -0.58f,
};

//小靶柱2
static const GLfloat vertex_list23[][3] = {
	 0.15f, 0.7f, -0.52f,
	 0.3f, 0.7f, -0.52f,
	 0.15f,  0.74f, -0.52f,
	 0.3f,  0.74f, -0.52f,
	 0.15f, 0.7f,  -0.58f,
	 0.3f, 0.7f,  -0.58f,
	 0.15f, 0.74f,  -0.58f,
	 0.3f,  0.74f,  -0.58f,
};

//小靶柱3
static const GLfloat vertex_list24[][3] = {
	 0.15f, 0.46f, -0.52f,
	 0.3f, 0.46f, -0.52f,
	 0.15f,  0.5f, -0.52f,
	 0.3f,  0.5f, -0.52f,
	 0.15f, 0.46f,  -0.58f,
	 0.3f, 0.46f,  -0.58f,
	 0.15f, 0.5f,  -0.58f,
	 0.3f,  0.5f,  -0.58f,
};

//小靶柱4
static const GLfloat vertex_list25[][3] = {
	 0.15f, 0.3f, -0.52f,
	 0.3f, 0.3f, -0.52f,
	 0.15f,  0.34f, -0.52f,
	 0.3f,  0.34f, -0.52f,
	 0.15f, 0.3f,  -0.58f,
	 0.3f, 0.3f,  -0.58f,
	 0.15f, 0.34f,  -0.58f,
	 0.3f,  0.34f,  -0.58f,
};

//小靶柱5
static const GLfloat vertex_list26[][3] = {
	 0.15f, -0.86f, -0.52f,
	 0.3f, -0.86f, -0.52f,
	 0.15f,  -0.9f, -0.52f,
	 0.3f,  -0.9f, -0.52f,
	 0.15f, -0.86f,  -0.58f,
	 0.3f, -0.86f,  -0.58f,
	 0.15f, -0.9f,  -0.58f,
	 0.3f,  -0.9f,  -0.58f,
};

//小靶柱6
static const GLfloat vertex_list27[][3] = {
	 0.15f, -0.7f, -0.52f,
	 0.3f, -0.7f, -0.52f,
	 0.15f,  -0.74f, -0.52f,
	 0.3f,  -0.74f, -0.52f,
	 0.15f, -0.7f,  -0.58f,
	 0.3f, -0.7f,  -0.58f,
	 0.15f, -0.74f,  -0.58f,
	 0.3f,  -0.74f,  -0.58f,
};

//小靶柱7
static const GLfloat vertex_list28[][3] = {
	 0.15f, -0.46f, -0.52f,
	 0.3f, -0.46f, -0.52f,
	 0.15f,  -0.5f, -0.52f,
	 0.3f,  -0.5f, -0.52f,
	 0.15f, -0.46f,  -0.58f,
	 0.3f, -0.46f,  -0.58f,
	 0.15f, -0.5f,  -0.58f,
	 0.3f,  -0.5f,  -0.58f,
};

//小靶柱8
static const GLfloat vertex_list29[][3] = {
	 0.15f, -0.3f, -0.52f,
	 0.3f, -0.3f, -0.52f,
	 0.15f,  -0.34f, -0.52f,
	 0.3f,  -0.34f, -0.52f,
	 0.15f, -0.3f,  -0.58f,
	 0.3f, -0.3f,  -0.58f,
	 0.15f, -0.34f,  -0.58f,
	 0.3f,  -0.34f,  -0.58f,
};

static const GLint index_list[][4] = {
		0,1,3,2,  //front
		4,5,7,6,  //back
		2,3,7,6,  //top
		0,1,5,4,  //bottom
		0,2,6,4,  //left
		1,3,7,5   //right
};
//法向量
static const GLfloat normal[][3] = {
	0.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
};

//********************************读图**************************************

void readImage(char* fname, int m)
{
	FILE* pfile = NULL;
	fopen_s(&pfile, fname, "rb");
	if (pfile == 0) exit(0);
	//读取图像大小

	fseek(pfile, 0x0012, SEEK_SET);
	fread(&image[m].imagewidth, sizeof(image[m].imagewidth), 1, pfile);
	fread(&image[m].imageheight, sizeof(image[m].imageheight), 1, pfile);
	//计算像素数据长度
	image[m].pixellength = image[m].imagewidth * 3;
	while (image[m].pixellength % 4 != 0) image[m].pixellength++; // 补充数据，直到pixellength是的倍数
	image[m].pixellength *= image[m].imageheight;
	//读取像素数据
	image[m].pixeldata = (GLubyte*)malloc(image[m].pixellength);
	if (image[m].pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(image[m].pixeldata, image[m].pixellength, 1, pfile);

	//关闭文件
	fclose(pfile);

}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)800 / (GLfloat)800, 2, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	xangle = 0; yangle = 0;
	LSystemRule();
	//**********************************纹理**************************************

	for (int i = 0; i < 7; i++)
	{
		//读取图像文件
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		readImage(filename[i], i);

		glGenTextures(1, &textName[i]);
		glBindTexture(GL_TEXTURE_2D, textName[i]);
		//加载纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[i].imagewidth, image[i].imageheight, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE, image[i].pixeldata);

		//设置纹理过滤
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	//**********************************纹理**************************************

	

	//****************************光照**********************************
	//material is gold colour
	GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 0.0 };

	GLfloat mat_shininess[] = { 80.0 };
	GLfloat mat_emission[] = { 0.2, 0.2, 0.2, 1.0 };
	goldMat.setMaterial(mat_ambient, mat_diffuse, mat_specular, mat_shininess);
	goldMat.setmaterialMode();
	goldMat.emissionMode(1);

	GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0,1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_position[] = { -5.0, -2.0, 1.0, 1.0 };
	GLfloat spot_direction[] = { 1.0, 1.0, -1.0, 0.0 };
	light1.setLight(GL_LIGHT1, light1_position, light1_ambient, light1_diffuse, light1_specular, spot_direction);
	light1.setLightMode();

	GLfloat local_view[] = { -1.0, 1.0, 1.0 };
	//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);  //使用颜色
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//****************************光照**********************************
}

void LSystemRule()
{
	//初始化
	way[0] = "FA[+X][-&X]-%XB";
	len = 0.35;
	Alphaz = 30;
	Alphay = 60;
	n = 8;
	k = 0;
	stackpointer = 0;//栈顶指针
	for (int i = 0; i < 150; i++)
	{
		stack[i].x = 0.0;
		stack[i].y = 0.0;
		stack[i].z = 0.0;
		stack[i].directionz = 0;
		stack[i].directiony = 0;
	}
	temprule = way[0];
	for (int i = 1; i <= n; i++)
	{
		int curlen = temprule.length();
		int pos = 0, j = 0;
		while (j < curlen)
		{
			if (temprule[j] == 'X')//迭代，将其中的F替换成文法模型
			{
				rule += way[0];
				j++;
				pos = rule.length() - 1;
			}
			else//保留转角
			{
				rule += temprule[j];
				pos++;
				j++;
			}
		}
		temprule = rule;
		rule.clear();
	}
	rule = temprule;//迭代好之后的文法规则
}

void drawTree()
{
	Node  Nextnode, Curnode;
	Curnode.x = 0.15;
	Curnode.y = 0.0;
	Curnode.z = 1.25;
	Curnode.directionz = 0;
	Curnode.directiony = 0;
	int length = rule.length();
	int  i = 0;

	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	while (i < length)
	{
		switch (rule[i])
		{
		case 'F':
			if (len <= 0.1)
			{
				glLineWidth(2);
				glColor3f((float)250 / 255, (float)125 / 255, (float)19 / 255);
			}
			else if (len > 0.5 && len < 2)
			{
				glLineWidth(2);
				glColor3f((float)34 / 255, (float)139 / 255, (float)34 / 255);
			}
			else
			{
				glLineWidth(10);
				glColor3f((float)62 / 255, (float)42 / 255, (float)45 / 255);
			}
			Nextnode.x = Curnode.x + len * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			k++;
			break;
		case 'X':
			glColor3f((float)34 / 255, (float)139 / 255, (float)34 / 255);
			glLineWidth(1);
			Nextnode.x = Curnode.x + len1 * cos(Curnode.directionz * PI / 180) * cos(Curnode.directiony * PI / 180);
			Nextnode.y = Curnode.y + len1 * sin(Curnode.directionz * PI / 180);
			Nextnode.z = Curnode.z - len1 * cos(Curnode.directionz * PI / 180) * sin(Curnode.directiony * PI / 180);
			Nextnode.directionz = Curnode.directionz;
			Nextnode.directiony = Curnode.directiony;
			glBegin(GL_LINES);
			glVertex3f(Curnode.x, Curnode.y, Curnode.z);
			glVertex3f(Nextnode.x, Nextnode.y, Nextnode.z);
			glEnd();
			Curnode = Nextnode;
			break;
		case 'A':
			len = len * 7 / 10;
			len1 = len;
			break;
		case 'B':
			len = len * 10 / 7;
			break;
		case '[':
			stack[stackpointer] = Curnode;
			stackpointer++;
			break;
		case ']':
			Curnode = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+':
			Curnode.directionz = Curnode.directionz + Alphaz;
			break;
		case '-':
			Curnode.directionz = Curnode.directionz - Alphaz;
			break;
		case '&':
			Curnode.directiony = Curnode.directiony + Alphay;
			break;
		case '%':
			Curnode.directiony = Curnode.directiony - Alphay;
			break;
		default:
			;
		}
		i++;
	}
	glPopMatrix();

}

//void Reshape(int w, int h)
//{
//	WindW = w;
//	WindH = h;
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	if (w <= h)
//	{
//		gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 2, 100.0);
//	}
//	else
//	{
//		gluPerspective(60.0, (GLfloat)h / (GLfloat)w, 2, 100.0);
//	}
//	glMatrixMode(GL_MODELVIEW);
//}

//画
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPushMatrix();
	
	gluLookAt(0.0, 0.0, a, 0, 0, 0, 1.0, 0.0, 0);
	glRotatef(xangle, 0.0, 1.0, 0.0);
	glRotatef(yangle, 1.0, 0.0, 0.0);
	/*glScalef(X,Y,Z);*/
	drawTree();
	//*******************************纹理映射*********************************
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < 6; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textName[1]);
		//地板下
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list1[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list1[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list1[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list1[index_list[i][3]]);
		glEnd();
		//地板上
		
		glBindTexture(GL_TEXTURE_2D, textName[0]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list2[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list2[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list2[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list2[index_list[i][3]]);
		glEnd();
		//*******************************枪柱*******************************
		glColor3f(0.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, textName[2]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list3[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list3[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list3[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list3[index_list[i][3]]);
		glEnd();
	
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list4[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list4[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list4[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list4[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list5[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list5[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list5[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list5[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list6[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list6[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list6[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list6[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list7[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list7[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list7[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list7[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list8[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list8[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list8[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list8[index_list[i][3]]);
		glEnd();
		//*******************************枪柱*******************************

		//*******************************小靶底*******************************
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textName[3]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list9[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list9[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list9[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list9[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list10[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list10[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list10[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list10[index_list[i][3]]);
		glEnd();
		//*******************************小靶底*******************************

		//*******************************小靶*******************************
		glColor3f(1.0f, 1.0f, 1.0f);
		/*glBindTexture(GL_TEXTURE_2D, textName[4]);*/
		glBegin(GL_POLYGON);
		/*glTexCoord2f(0.0, 0.0);*/ glVertex3fv(vertex_list11[index_list[i][0]]);
		/*glTexCoord2f(0.0, 1.0);*/ glVertex3fv(vertex_list11[index_list[i][1]]);
		/*glTexCoord2f(1.0, 1.0);*/ glVertex3fv(vertex_list11[index_list[i][2]]);
		/*glTexCoord2f(1.0, 0.0);*/ glVertex3fv(vertex_list11[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		/*glTexCoord2f(0.0, 0.0); */glVertex3fv(vertex_list12[index_list[i][0]]);
		/*glTexCoord2f(0.0, 1.0);*/ glVertex3fv(vertex_list12[index_list[i][1]]);
		/*glTexCoord2f(1.0, 1.0);*/ glVertex3fv(vertex_list12[index_list[i][2]]);
		/*glTexCoord2f(1.0, 0.0);*/ glVertex3fv(vertex_list12[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		/*glTexCoord2f(0.0, 0.0);*/ glVertex3fv(vertex_list13[index_list[i][0]]);
		/*glTexCoord2f(0.0, 1.0);*/ glVertex3fv(vertex_list13[index_list[i][1]]);
		/*glTexCoord2f(1.0, 1.0);*/ glVertex3fv(vertex_list13[index_list[i][2]]);
		/*glTexCoord2f(1.0, 0.0);*/ glVertex3fv(vertex_list13[index_list[i][3]]);
		glEnd();

		glBegin(GL_POLYGON);
		/*glTexCoord2f(0.0, 0.0);*/ glVertex3fv(vertex_list14[index_list[i][0]]);
		/*glTexCoord2f(0.0, 1.0);*/ glVertex3fv(vertex_list14[index_list[i][1]]);
		/*glTexCoord2f(1.0, 1.0);*/ glVertex3fv(vertex_list14[index_list[i][2]]);
		/*glTexCoord2f(1.0, 0.0);*/ glVertex3fv(vertex_list14[index_list[i][3]]);
		glEnd();
		//*******************************小靶*******************************

		//*******************************大靶底*******************************
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textName[3]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vertex_list15[index_list[i][0]]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vertex_list15[index_list[i][1]]);
		glTexCoord2f(1.0, 1.0); glVertex3fv(vertex_list15[index_list[i][2]]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vertex_list15[index_list[i][3]]);
		glEnd();
		//*******************************大靶底*******************************

		//*******************************大靶*******************************
		glColor3f(1.0f, 0.9f, 1.0f);
		/*glBindTexture(GL_TEXTURE_2D, textName[5]);*/
		glBegin(GL_POLYGON);
		/*glTexCoord2f(0.0, 0.0); */glVertex3fv(vertex_list16[index_list[i][0]]);
		/*glTexCoord2f(0.0, 1.0); */glVertex3fv(vertex_list16[index_list[i][1]]);
		/*glTexCoord2f(1.0, 1.0); */glVertex3fv(vertex_list16[index_list[i][2]]);
		/*glTexCoord2f(1.0, 0.0); */glVertex3fv(vertex_list16[index_list[i][3]]);
		glEnd();
		//*******************************大靶*******************************

		//*******************************背景*******************************
	/*	glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textName[6]);
		glBegin(GL_POLYGON);
		glTexCoord2d(0.0, 0.0); glVertex3d(0.0,-2.0,-2.0);
		glTexCoord2d(0.0, 1.0); glVertex3d(4.0, -2.0, -2.05);
		glTexCoord2d(1.0, 1.0); glVertex3d(4.0, 2.0, -2.05);
		glTexCoord2d(1.0, 0.0); glVertex3d(0.0, 2.0, -2.05);
		glEnd();*/
		//*******************************背景*******************************

	}
	glDisable(GL_TEXTURE_2D);
	//*******************************纹理映射*********************************
	
	glEnable(GL_LIGHT1);
	//*******************************画场景***********************************
	for (int i = 0; i < 6; i++) //
	{
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		//地板（底部）
		/*glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j) 
			glVertex3fv(vertex_list1[index_list[i][j]]);
		glEnd();*/
		//地板（上部）
		/*glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j) 
			glVertex3fv(vertex_list2[index_list[i][j]]);
		glEnd();*/
		//glColor3f(0.0f, 1.0f, 1.0f);
		////枪柱1
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list3[index_list[i][j]]);
		//glEnd();
		//枪柱2
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list4[index_list[i][j]]);
		//glEnd();
		////枪柱3
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list5[index_list[i][j]]);
		//glEnd();
		////枪柱4
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list6[index_list[i][j]]);
		//glEnd();
		////枪柱5
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list7[index_list[i][j]]);
		//glEnd();
		////枪柱6
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list8[index_list[i][j]]);
		//glEnd();
		//靶底1
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list9[index_list[i][j]]);
		//glEnd();
		////靶底2
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list10[index_list[i][j]]);
		//glEnd();
		//靶1
		/*glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j) 
			glVertex3fv(vertex_list11[index_list[i][j]]);
		glEnd();*/
		//靶2
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list12[index_list[i][j]]);
		//glEnd();
		////靶3
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j)
		//	glVertex3fv(vertex_list13[index_list[i][j]]);
		//glEnd();
		////靶4
		//glBegin(GL_POLYGON);
		//for (int j = 0; j < 4; ++j) 
		//	glVertex3fv(vertex_list14[index_list[i][j]]);
		//glEnd();
		//大靶底
		/*glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list15[index_list[i][j]]);
		glEnd();*/
		//大靶
		/*glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list16[index_list[i][j]]);
		glEnd();*/
		//**************************靶柱**************************
		glColor3f(0.0f, 0.0f, 0.0f);
		//大靶柱1
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list20[index_list[i][j]]);
		glEnd();
		//大靶柱2
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list21[index_list[i][j]]);
		glEnd();
		//小靶柱1
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list22[index_list[i][j]]);
		glEnd();
		//小靶柱2
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list23[index_list[i][j]]);
		glEnd();
		//小靶柱3
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list24[index_list[i][j]]);
		glEnd();
		//小靶柱4
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list25[index_list[i][j]]);
		glEnd();
		//小靶柱5
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list26[index_list[i][j]]);
		glEnd();
		//小靶柱6
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list27[index_list[i][j]]);
		glEnd();
		//小靶柱7
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list28[index_list[i][j]]);
		glEnd();
		//小靶柱8
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list29[index_list[i][j]]);
		glEnd();
		//**************************靶柱**************************
		glColor3f((float)218 / 255, (float)165 / 255, (float)105 / 255);
		//土块1
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list17[index_list[i][j]]);
		glEnd();
		//土块2
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list18[index_list[i][j]]);
		glEnd();
		//土块3
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list19[index_list[i][j]]);
		glEnd();
	}
	//*******************************画场景***********************************
	//******************************画甜甜圈**********************************
	glColor3f(1.0, 0.0,0.0);
	glTranslated(0.25, 0.0, 1.3);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.13, 0.25, 30.0, 30.0);
	//******************************画甜甜圈**********************************
	//*******************************画土块***********************************
	glColor3f((float)94 / 255, (float)38 / 255, (float)18 / 255);
	glTranslated(3.11, 1.81, 0.1);
	glutSolidCube(0.35);
	glTranslated(-0.065, -0.4, 0);
	glutSolidCube(0.5);
	glTranslated(-0.3, 0.385, -0.1);
	glutSolidCube(0.4);
	glTranslated(-0.1, -0.2, 0.1);
	glutSolidCube(0.4);
	glTranslated(-0.1, 0.264, 0.0);
	glutSolidCube(0.27);
	glTranslated(-0.2, -0.09, 0.0);
	glutSolidCube(0.27);
	glTranslated(0.0, -0.2, 0.0);
	glutSolidCube(0.23);
	glTranslated(0.75, -0.5, 0.0);
	glutSolidCube(0.4);
	glTranslated(-0.05, -0.4, 0.1);
	glutSolidCube(0.5);
	glTranslated(-0.05, -0.4, 0.0);
	glutSolidCube(0.35);
	glTranslated(-0.01, -0.45, 0.0);
	glutSolidCube(0.55);
	glTranslated(-0.01, -0.45, 0.0);
	glutSolidCube(0.4);
	glTranslated(-0.01, -0.45, 0.05);
	glutSolidCube(0.5);
	glTranslated(0.15, -0.4, -0.1);
	glutSolidCube(0.32);
	glTranslated(-0.35, -0.01, 0.0);
	glutSolidCube(0.38);
	glTranslated(0.28, -0.25, 0.0);
	glutSolidCube(0.5);
	glTranslated(-0.45, 0.0, 0.05);
	glutSolidCube(0.4);
	glTranslated(-0.2, 0.2, -0.05);
	glutSolidCube(0.3);
	glTranslated(-0.09, -0.25, -0.05);
	glutSolidCube(0.2);
	//*******************************画土块***********************************

	//*******************************画靶心***********************************
	//大靶
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslated(0.12, 1.794, 0.1);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.01, 0.17, 30.0, 30.0);
	glutSolidTorus(0.01, 0.12, 30.0, 30.0);
	glutSolidTorus(0.01, 0.07, 30.0, 30.0);
	glutSolidTorus(0.01, 0.02, 30.0, 30.0);
	//小靶
	glTranslated(0.05, 0.8, -0.6);
	glutSolidTorus(0.01, 0.09, 30.0, 30.0);
	glutSolidTorus(0.01, 0.055, 30.0, 30.0);
	glutSolidTorus(0.01, 0.02, 30.0, 30.0);

	glTranslated(0.0, -0.4, 0.0);
	glutSolidTorus(0.01, 0.09, 30.0, 30.0);
	glutSolidTorus(0.01, 0.055, 30.0, 30.0);
	glutSolidTorus(0.01, 0.02, 30.0, 30.0);

	glTranslated(0.0, -0.8, 0.0);
	glutSolidTorus(0.01, 0.09, 30.0, 30.0);
	glutSolidTorus(0.01, 0.055, 30.0, 30.0);
	glutSolidTorus(0.01, 0.02, 30.0, 30.0);

	glTranslated(0.0, -0.4, 0.0);
	glutSolidTorus(0.01, 0.09, 30.0, 30.0);
	glutSolidTorus(0.01, 0.055, 30.0, 30.0);
	glutSolidTorus(0.01, 0.02, 30.0, 30.0);
	//*******************************画靶心***********************************
	glPopMatrix();
	glutSwapBuffers();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case'B':
		case'b':
			a = a - 1;
			break;
		case'S':
		case's':
			a = a + 1;
			break;
	}
	display();
}
void mouse(int btn, int state, int x, int y)
{
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		oldx = x; oldy = y;
	}
}

void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	yangle += 360 * (GLfloat)deltax / (GLfloat)WindW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	xangle += 360 * (GLfloat)deltay / (GLfloat)WindH;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标  
	oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控  
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("综合大作业");
	init();
	//glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}