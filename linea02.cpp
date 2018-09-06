#include <GL/glut.h>
#include <iostream>

GLfloat x1,x2,y1,y2;

using namespace std;
void reshape(int width, int height)
{
	 glViewport(0, 0, width, height);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(-1, 1, -1, 1, -1, 1);
	 glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0.5,0);
	glLoadIdentity();
	GLfloat dx, dy, incE, incNE, d, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	d = 2.0 * dy-dx;
	incE = 2.0 * dy;
	incNE = 2.0 * (dy-dx);
	x=x1;
	y=y1;
	glBegin(GL_POINTS);
	glVertex3f(x,y,0.0f);
	while(x<x2){
		if(d<=0.0){
			d = d + incE;	
			x = x + 0.00001;
	}else{
		d = d + incNE;
		x = x + 0.00001;
		y = y + 0.00001;
	}
	glVertex3f(x,y,0.0f);
	}
	glEnd();
	glFlush();
}

void init()
{
	glClearColor(0,0,0,0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	cout<<"Ingrese las coordenadas "<<endl;
	cout<<"x1:";
	cin>>x1;
	cout<<"y1:";
	cin>>y1;
	cout<<"x2:";
	cin>>x2;
	cout<<"y2:";
	cin>>y2;
	x1/=100; x2/=100; y1/=100; y2/=100;
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Línea con punto medio");
	init();
	glutDisplayFunc (display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
