/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 * g++ -lglut -lGL main.cpp -o main*/
//#include <windows.h>  // for MS Windows

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#define M_PI 3.14159265358979323846
using namespace std;

int num_lados;
float ratio;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
	glLoadIdentity();
	GLfloat grados_1;
	GLfloat grados_2;
	glBegin(GL_LINES);	

	double puntos = 360.0f/num_lados;
	for(double i=0; i<360; i=i+puntos)
	{
		grados_1 = (GLfloat)i*M_PI/180.0f;
		grados_2 = ((GLfloat)i+puntos)*M_PI/180.0f;
		glVertex3f(ratio*cos(grados_1),ratio*sin(grados_1),0.0f);
		glVertex3f(ratio*cos(grados_2),ratio*sin(grados_2),0.0f);
	}

	glEnd();
	glFlush();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void init()
{
	glClearColor(0,0,0,0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	cout<<"Ingrese el numero de lados"<<endl;
	cin>>num_lados;
	cout<<"ingrese el radio con valores entre 0 y 1"<<endl;
	cin>>ratio;
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Poligono");
	init();
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

