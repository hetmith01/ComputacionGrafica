/***********Dotar al programa de una tecla que permita cambiar el modo de proyección entre ORTOGONAL y PERSPECTIVA.*****/

/***********Programar otros modos de movimiento de cámara como son el MODO PAN o el MODO TRÍPODE.********************/




#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <string.h>

#include "camera.h"
#include "vector_tools.h"


static camera *LOCAL_MyCamera;
static int old_x, old_y;


GLdouble mModel[16];

int np = 0;

float px[10000];
float py[10000];
float pz[10000];
	

void tortuga3d(){

GLdouble cordx[] = { 0.0, 4.0, -8.0, 0.0, 8.0,-4.0};
GLdouble cordy[] = { -6.0, 2.0, 0.0, 8.0, 0.0,-4.0};
GLdouble r[] = { 6.0, 3.0, 2.0, 2.0, 2.0, 2.0};
GLint i;
glColor3f(1.0,0.0,1.0);

	for (i=0;i<6;i++){
	glutWireSphere(r[i], 15.0, 15.0);
	glTranslatef(cordx[i],cordy[i],0.0);
	}
}

void Tripode(int x, int y){
	float rotacion_x, rotacion_y;

	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	rotacion_y = (float)(old_y - y) * DEGREE_TO_RAD / 5;
	YawCamera(LOCAL_MyCamera, rotacion_x);
	PitchCamera(LOCAL_MyCamera, rotacion_y);


	old_y = y;
	old_x = x;

	glutPostRedisplay();
}


void Pan(int x, int y){
	float avance_x, avance_y;

	avance_x = (float)(old_x - x) / 10;
	avance_y = (float)(y - old_y) / 10;
	PanCamera( LOCAL_MyCamera, avance_x, avance_y);

	old_y = y;
	old_x = x;

	glutPostRedisplay();
}



void MouseMotion(int x, int y){
	old_y = y;
	old_x = x;
}


void Examinar(int x, int y){
	float rot_x, rot_y;

	rot_y = (float)(old_y - y);
	rot_x = (float)(x - old_x);
	Rotar_Latitud( LOCAL_MyCamera, rot_y * DEGREE_TO_RAD );
	Rotar_Longitud( LOCAL_MyCamera, rot_x * DEGREE_TO_RAD );

	old_y = y;
	old_x = x;

	glutPostRedisplay();
}



void Andar(int x, int y){

	float rotacion_x, avance_y;
	avance_y = (float)(y - old_y) / 10;
	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	YawCamera( LOCAL_MyCamera, rotacion_x );
	AvanceFreeCamera( LOCAL_MyCamera, avance_y);

	old_y = y;
	old_x = x;

	glutPostRedisplay();
}


void Zoom(int x, int y){
	float zoom; 

	zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
	old_y = y;

	switch(LOCAL_MyCamera->camMovimiento){

	case CAM_EXAMINAR:
		if (LOCAL_MyCamera->camAperture + zoom > (5 * DEGREE_TO_RAD) &&
			LOCAL_MyCamera->camAperture + zoom < 175 * DEGREE_TO_RAD)
			LOCAL_MyCamera->camAperture=LOCAL_MyCamera->camAperture + zoom;
	break;
	}

	glutPostRedisplay();
}


static void SpecialKey ( int key, int x, int y ){

switch(key) {

case GLUT_KEY_F1:
	glutPassiveMotionFunc(MouseMotion);
	LOCAL_MyCamera->camMovimiento = CAM_STOP;
	break;

case GLUT_KEY_F2: 
	glutPassiveMotionFunc(Examinar);
	LOCAL_MyCamera->camMovimiento = CAM_EXAMINAR;
	break;

case GLUT_KEY_F3:
	glutPassiveMotionFunc(MouseMotion);
	LOCAL_MyCamera->camMovimiento = CAM_PASEAR;
	LOCAL_MyCamera->camAtY = 0;
	LOCAL_MyCamera->camViewY = 0;
	SetDependentParametersCamera( LOCAL_MyCamera );
	break;

case GLUT_KEY_HOME: //Reset Camera
	LOCAL_MyCamera->camAtX =0;
	LOCAL_MyCamera->camAtY =0;
	LOCAL_MyCamera->camAtZ =0;
	LOCAL_MyCamera->camViewX = 0;
	LOCAL_MyCamera->camViewY = 1;
	LOCAL_MyCamera->camViewZ = -3;
	SetDependentParametersCamera( LOCAL_MyCamera );
	break;

//Camera//
case GLUT_KEY_F4:
	if(LOCAL_MyCamera->camProjection == CAM_CONIC){
		LOCAL_MyCamera->x1=-3;
		LOCAL_MyCamera->x2=3;
		LOCAL_MyCamera->y1=-3;
		LOCAL_MyCamera->y2=3;
		LOCAL_MyCamera->z1=-5;
		LOCAL_MyCamera->z2=5;
		LOCAL_MyCamera->camProjection = CAM_PARALLEL;
} else LOCAL_MyCamera->camProjection = CAM_CONIC;
break;	


case GLUT_KEY_F5:
	//if (current_mode!= 0) break;
	//current_mode = 3;
	LOCAL_MyCamera->camMovimiento = CAM_TRIPODE;
	break;


// default:
// 	printf("key %d %c X %d Y %d\n", key, key, x, y );
}

glutPostRedisplay();
}



void mouse(int button, int state, int x, int y){
	old_x = x;
	old_y = y;
	switch(button){
		case GLUT_LEFT_BUTTON:
			switch(LOCAL_MyCamera->camMovimiento){

		case CAM_EXAMINAR:
			if (state == GLUT_DOWN) glutMotionFunc(Zoom);
				if (state == GLUT_UP){
				glutPassiveMotionFunc(Examinar);
				glutMotionFunc(NULL);
				}
		break;

		case CAM_PASEAR:
			if (state == GLUT_DOWN) glutMotionFunc(Andar);
				if (state == GLUT_UP) glutMotionFunc(NULL);
			break;

		//Camera//
		case CAM_TRIPODE:
			if (state == GLUT_DOWN) glutMotionFunc(Tripode);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;

		case CAM_PAN:
			if (state == GLUT_DOWN) glutMotionFunc(Pan);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;	
			
		}

		break;

		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) ;
			break;

		default:
			break;

		}
		glutPostRedisplay();
}

void display(void) {

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//glPushMatrix();
//glMultMatrixd(mModel);
glColor3f(1.0,1.0,0.0) ;
tortuga3d();
glPopMatrix();
//displayTrace();
glutSwapBuffers();

//Camera//

SetGLCamera( LOCAL_MyCamera );


}

void reshape(int width, int height) {

glViewport(0, 0, width, height);
// glMatrixMode(GL_PROJECTION);
// glLoadIdentity();
// gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
// glMatrixMode(GL_MODELVIEW);
// glLoadIdentity();
// gluLookAt(0.0, 1.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

SetGLAspectRatioCamera( LOCAL_MyCamera );

}


int main(int argc, char **argv)
{
	
	LOCAL_MyCamera = CreatePositionCamera(0.0f, 1.0f, -3.0f);

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
	glPopMatrix();


	glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 640, 640 );
    glutCreateWindow("Perspectiva");
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    ///Camera////

    glutSpecialFunc(SpecialKey);
    glutPassiveMotionFunc(MouseMotion);
    glutMouseFunc(mouse);


    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
	
}
