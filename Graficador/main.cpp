#include <GL/glut.h>
#include "punto.h"
using namespace std;

void mouse(int boton,int estado,int x,int y){
	if(boton == GLUT_LEFT_BUTTON){
		if(estado == GLUT_UP){ 
			band = false;
			punto.x = x;
			punto.y = ALTO-y;
			puntos.push_back(punto);

			glBegin(GL_POINTS);
				glVertex2d(punto.x,punto.y);
			glEnd();
			cout<<punto.x<<" "<<punto.y<<endl;
		}
	}
	glutPostRedisplay();
}

void pintar (){
	int tam = puntos.size();
	glLineWidth(5.0);
	glBegin(GL_LINES);
		for(int i=1;i<tam;i++){
			if (puntos[i-1].x < puntos[i].x){
				float pendiente = (puntos[i].y-puntos[i-1].y)/(puntos[i].x-puntos[i-1].x);
				int y;
				for (int j=puntos[i-1].x ; j<=puntos[i].x;j++){
					y = j*pendiente - puntos[i-1].x * pendiente + puntos[i-1].y;
					glVertex2d(j,y);
					glVertex2d((*centro).x,(*centro).y);
				}
			}

			else {
					float pendiente = (puntos[i-1].y-puntos[i].y)/(puntos[i-1].x-puntos[i].x);
					int y;
					for (int j=puntos[i].x ; j<=puntos[i-1].x;j++){
						y = j*pendiente - puntos[i].x * pendiente + puntos[i].y;
						glVertex2d(j,y);
						glVertex2d((*centro).x,(*centro).y);			
					}
				
			}
		}

		if (puntos[tam-1].x < puntos[0].x){
				float pendiente = (puntos[0].y-puntos[tam-1].y)/(puntos[0].x-puntos[tam-1].x);
				int y;
				for (int j=puntos[tam-1].x ; j<=puntos[0].x;j++){
					y = j*pendiente - puntos[tam-1].x * pendiente + puntos[tam-1].y;
					glVertex2d(j,y);
					glVertex2d((*centro).x,(*centro).y);
				}
			}

			else {
					float pendiente = (puntos[tam-1].y-puntos[0].y)/(puntos[tam-1].x-puntos[0].x);
					int y;
					for (int j=puntos[0].x ; j<=puntos[tam-1].x;j++){
						y = j*pendiente - puntos[0].x * pendiente + puntos[0].y;
						glVertex2d(j,y);
						glVertex2d((*centro).x,(*centro).y);			
					}
				
			}
	glEnd();

}


void trasladar(void){
	int distX,distY;
	int cambioX, cambioY;
	int XP,YP;
	cout<<"Distancia "<<endl;
	cout<<"distancia en X: ";
	cin>>distX;
	cout<<"distancia en Y: ";
	cin>>distY;
	cout<<endl;

	(*centro).x += distX;
	(*centro).y += distY;

	cout<<"nuevo centro: "<<(*centro).x<<" "<<(*centro).y<<endl;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);		
	glLineWidth(2.0);
	int tam = puntos.size();

	XP = puntos[0].x;
	YP = puntos[0].y;

	glBegin(GL_LINES);
		for(int i=1;i<tam;i++){

			cambioX = XP + distX;
			cambioY = YP + distY;

			puntos[i-1].x = cambioX;
			puntos[i-1].y = cambioY;
			
			glVertex2d( cambioX , cambioY );
			glVertex2d(puntos[i].x + distX ,puntos[i].y + distY);

			XP = puntos[i].x;
			YP = puntos[i].y;
		}
		puntos[tam-1].x += distX;
		puntos[tam-1].y += distY;

		glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );
		glVertex2d(puntos[0].x ,puntos[0].y);
	glEnd();
	pintar();

	return;

}

void escalar(void){
	float escX,escY;
	int XP, YP,X2P,Y2P;
	int actX, actY;

	cout<<"Distancia "<<endl;
	cout<<"escala en X: ";
	cin>>escX;
	cout<<"escala en Y: ";
	cin>>escY;
	cout<<endl;

	if(escX == 0 || escY == 0){
		escX = 1;
		escY = 1;
		cout<<"El valor 0 no es valido"<<endl;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);		
	glLineWidth(2.0);
	int tam = puntos.size();

	actX = puntos[0].x;
	actY = puntos[0].y;

	glBegin(GL_LINES);
		for(int i=1;i<tam;i++){

			XP = actX * escX + (*centro).x * (1 - escX);
			YP = actY * escY + (*centro).y * (1 - escY);

			puntos[i-1].x = XP;
			puntos[i-1].y = YP;

			X2P = puntos[i].x * escX + (*centro).x * (1 - escX);
			Y2P = puntos[i].y * escY + (*centro).y * (1 - escY); 

			glVertex2d(XP ,YP);
			glVertex2d(X2P ,Y2P);

			actX = puntos[i].x;
			actY = puntos[i].y;
		}

		puntos[tam-1].x = actX * escX + (*centro).x * (1 - escX);
		puntos[tam-1].y = actY * escY + (*centro).y * (1 - escY);

		glVertex2d(puntos[0].x ,puntos[0].y);
		glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

		(*centro).x = (*centro).x * escX + (*centro).x * (1 - escX);
		(*centro).y = (*centro).y * escY + (*centro).y * (1 - escY);
	glEnd();

	pintar();

}

void rotar(void){
	int angulo;
	int XP, YP,X2P,Y2P;
	int actX, actY;

	cout<<"Angulo: "<<endl;
	cin>>angulo;
	cout<<endl;

	angulo = (angulo * pi) / 180;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);		
	glLineWidth(2.0);
	int tam = puntos.size();
	actX = puntos[0].x;
	actY = puntos[0].y;

	glBegin(GL_LINES);
		for(int i=1;i<tam;i++){
			XP = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
			YP = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

			puntos[i-1].x = XP;
			puntos[i-1].y = YP;

			X2P = (puntos[i].x * cos(angulo)) + (-sin(angulo) * puntos[i].y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
			Y2P = (puntos[i].x * sin(angulo)) + (cos(angulo) * puntos[i].y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

			glVertex2d(XP ,YP);
			glVertex2d(X2P ,Y2P);

			actX = puntos[i].x;
			actY = puntos[i].y;

		}

		puntos[tam-1].x = (actX * cos(angulo)) + (-sin(angulo) * actY) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
		puntos[tam-1].y = (actX * sin(angulo)) + (cos(angulo) * actY) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

		glVertex2d(puntos[0].x ,puntos[0].y);
		glVertex2d(puntos[tam-1].x ,puntos[tam-1].y );

		(*centro).x = ((*centro).x * cos(angulo)) + (-sin(angulo) * (*centro).y) + (((*centro).x * (1-cos(angulo))) + ( (*centro).y * sin(angulo)));
		(*centro).y = ((*centro).x * sin(angulo)) + (cos(angulo) * (*centro).y) + (((*centro).y * (1-cos(angulo))) - ( (*centro).x * sin(angulo)));

	glEnd();

	pintar();
	return;

}


void menu(){
	int opcion=5;
	
				while(opcion != 4)
				{
					glFlush();
					cout<<"Transformaciones"<<endl;
					cout<<"--------------------------------------------------"<<endl;
					cout<<"1) Trasladar"<<endl;
					cout<<"2) Escalar"<<endl;
					cout<<"3) Rotar"<<endl;
					cout<<"4) Salir"<<endl;
					cout<<"--------------------------------------------------"<<endl;
					cout<<"Seleccionar opcion: ";
					cin>>opcion;

					if(opcion == 1)
					{
						trasladar();
					}
					else if(opcion == 2){
						escalar();
					}
					else if(opcion ==3){
						rotar();
					}
				}

				return;
	glFlush();
}

void draw(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);		
	glLineWidth(2.0);
	int tam = puntos.size();

	glBegin(GL_LINES);
		for(int i=1;i<tam;i++){
			glVertex2d(puntos[i-1].x,puntos[i-1].y);
			glVertex2d(puntos[i].x,puntos[i].y);
		}
	glEnd();

		if(tam > 2 ){
			if(distance(puntos[0].x ,puntos[0].y ,puntos[tam-1].x,puntos[tam-1].y)){
				glBegin(GL_LINES);
					glVertex2d(puntos[0].x,puntos[0].y);
					glVertex2d(puntos[tam-1].x,puntos[tam-1].y);
				glEnd();

				glutMouseFunc(NULL);
				cerrado = true;		
				centro = centroide();
				
				pintar();
				glFlush();
				menu();
				exit(0);
			}
		}
	glFlush();
}


void inicializa(){	
	glClearColor(0.0,0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,ANCHO,0,ALTO);
}

int main(int argc, char **argv){	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(ANCHO,ALTO);
	glutInitWindowPosition(100,50);
	glutCreateWindow("Pintado");	
	inicializa();

	glutDisplayFunc(draw);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0
}
