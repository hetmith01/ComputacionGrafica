#include <vector>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

#define ALTO 600
#define ANCHO 600

#define pi 3.14159265

struct Punto{
	GLdouble x;
	GLdouble y;
}punto;

int Cordx=1000,Cordy=1000;
bool band = false;
vector<Punto> puntos;


bool cerrado = false;
Punto * centro = NULL;

bool distance(int x1 ,int y1,int x2 ,int y2){
	int distancia = sqrt(pow(x1 - x2 ,2)+pow(y1 - y2,2));
	
	if (distancia < 100) return true;
	else return false;
	return false;
}

Punto * centroide(){
	int tam = puntos.size();
	int xMin = puntos[0].x,xMax=puntos[0].x,yMin = puntos[0].y,yMax = puntos[0].y;

	for(int i=1;i<tam;i++){
		if(puntos[i].x <= xMin) xMin = puntos[i].x;
		else if(puntos[i].x >= xMax) xMax = puntos[i].x; 

		if(puntos[i].y <= yMin) yMin = puntos[i].y;
		else if(puntos[i].y >= yMax) yMax = puntos[i].y; 
	}

	cout<<endl;

	Punto * res =new Punto;
	
	(*res).x = (xMax + xMin)/2;
	(*res).y = (yMax + yMin)/2;

	return res ;

}
