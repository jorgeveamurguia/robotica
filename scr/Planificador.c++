/*
 * Planificador.cpp
 *
 *  Created on: 05/02/2012
 *      Author: jorge
 */
#include "Aria.h"
#include "Planificador.h"

Planificador::Planificador() {
	// TODO Auto-generated constructor stub
    AccionActivadaBuscarPared =1;
	AccionActivadaAndarParalelo =2;
	AccionActivadaEvitarObstaculo =3;


	AccionActivada =AccionActivadaBuscarPared;

}

Planificador::~Planificador() {
	// TODO Auto-generated destructor stub
}

void Planificador::Accion() {
	// TODO Auto-generated constructor stub
    if(AccionActivada == AccionActivadaBuscarPared  ){
    	printf("Accion: BuscarPared %d\n",AccionActivada);
    }else  if(AccionActivada == AccionActivadaAndarParalelo  ){
    	printf("Accion: AndarParalelo %d\n",AccionActivada);
    }else  if(AccionActivada == AccionActivadaEvitarObstaculo){
    	printf("Accion: EvitarObstaculo %d\n",AccionActivada);
    }else  {
    	printf("Accion: accion no controlada %d\n",AccionActivada);
    }
}
