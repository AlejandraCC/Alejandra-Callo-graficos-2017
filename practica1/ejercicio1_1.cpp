// Para compilar en MacOSX
// g++ -o practica01 practica01.cpp -framework OpenGL -framework GLUT

#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
#include "GLUT/glut.h"
#else
#include "GL/glut.h"
#endif

#define NUMVTX (8)

static int winwidth,winheight;
static int mx,my;
static int flag=0;
static float rotx=0.0f, roty=0.0f;



GLfloat lc[NUMVTX][3]={  {1,2,1},{1,2,-1},
                        {-1,2,1},{-1,2,-1},
                        //{0,-1,1},{0,-1,-1},

                        {-1,0,1},{-1,0,-1},
                        {1,0,1},{1,0,-1}
                        };
GLfloat la[10][3]={
                    {2,0,1},{2,0,-1},
                    {4,2,1},{4,2,-1},
                    {5,0,1},{5,0,-1},
                     {4.5,1,1},{4.5,1,-1},
                      {3.0,1,1},{3.0,1,-1}
                     } ;

GLfloat c[NUMVTX][3]={{1,0,0},{1,0,0},
                      {0,1,0},{0,1,0},
                      {0,0,1},{0,0,1},
                      {1,0,0},{1,0,0}};

void drawgraphix()
{
	int i;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();

	glTranslatef(2.0f,0.0f,-8.0f);

	glRotatef(rotx,0.0f,1.0f,0.0f);
	glRotatef(roty,1.0f,0.0f,0.0f);
	GLfloat temp[3]={0,0,0};

	glBegin(GL_QUAD_STRIP);
	for (i=0; i<10; i++)
	{
		glColor3fv(c[i]);
		//glVertex3fv(lc[i]);
		temp[0]=la[i][0]+ (-12);
		temp[1]=la[i][1];
		temp[2]=la[i][2];

		glVertex3fv(temp);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i=0; i<8; i++)
	{
		glColor3fv(c[i]);
		temp[0]=lc[i][0]+ (-4);
		temp[1]=lc[i][1];
		temp[2]=lc[i][2];

		glVertex3fv(temp);
		//glVertex3fv(la[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i=0; i<8; i++)
	{
		glColor3fv(c[i]);
		glNormal3f(0.0, 1.0, 1.0);
		glVertex3fv(lc[i]);
		//glVertex3fv(la[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (i=0; i<10; i++)
	{
		glColor3fv(c[i]);
		glNormal3f(1.0, 0.0, 1.0);
		//glVertex3fv(lc[i]);
		glVertex3fv(la[i]);
	}
	glEnd();




	glPopMatrix();

	glutSwapBuffers();
}

void reshapefunc(int width,int height)
{
	winwidth=width;
	winheight=height;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(float)width/height,1.0,30.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(  0.0f,0.0f,3.0f,
                0.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f);

}

void mousefunc(int button,int state,int x,int y)
{
	if (button==GLUT_LEFT_BUTTON) {
		if (state==GLUT_DOWN) {
			flag=1;
		} else {
			flag=0;
		}
	}
}

void motionfunc(int x,int y)
{
	if (flag>0) {
		if (flag>1) {
			rotx+=360.0f*(x-mx)/winwidth;
			roty+=360.0f*(y-my)/winheight;
		}

		mx=x;
		my=y;

		drawgraphix();

		flag=2;
	}
}

void keyboardfunc(unsigned char key,int x,int y)
{
	if (key=='q' || key==27) exit(0);
}


void idlefunc()
{
	glutPostRedisplay();
}

static void init(void) {
    GLfloat light0_diffuse[] = {2.0, 2.0, 2.0, 1.0};
    /* Plane wave coming from +z infinity. */
    GLfloat light0_position[] = {3.0, 2.0, 1.0, 0.0};
    glClearColor(1, 1, 1.0, 1.0);
    glShadeModel(GL_SMOOTH); // para interpolar en el poligono los colores de sus vertices
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}


int main(int argc,char **argv)
{
   winwidth=1200;
   winheight=800;

   glutInit(&argc,argv);
   glutInitWindowSize(winwidth,winheight);
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutCreateWindow("Practica 1 - Ejercicio 1.1");

   init();


   glutDisplayFunc(drawgraphix);
   glutReshapeFunc(reshapefunc);
   glutMouseFunc(mousefunc);
   glutMotionFunc(motionfunc);
   glutKeyboardFunc(keyboardfunc);
   glutIdleFunc(idlefunc);

   glutMainLoop();

   return(0);
}
