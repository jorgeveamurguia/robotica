/*
 * Planificador.h
 *
 *  Created on: 05/02/2012
 *      Author: jorge
 */

#ifndef PLANIFICADOR_H_
#define PLANIFICADOR_H_



class Planificador {

private:


public:
	Planificador();
	virtual ~Planificador();
    int AccionActivadaBuscarPared ;
	int AccionActivadaAndarParalelo;
	int AccionActivadaEvitarObstaculo ;

	int AccionActivada ;

	virtual void Accion();

};

#endif /* PLANIFICADOR_H_ */
