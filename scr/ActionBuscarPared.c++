#include "ActionBuscarPared.h"
#include "Aria.h"

#define PI 3.14159265

ActionBuscarPared::ActionBuscarPared(Planificador *planificador) :ArAction("ActionBuscarPared") {

	myPlanificador = planificador;
	girando = false;
}

void ActionBuscarPared::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	mySonar = robot->findRangeDevice("sonar");
	if (mySonar == NULL) {
		ArLog::log(
				ArLog::Terse,
				"actionExample: ActionBuscaPared: Warning: I found no sonar, deactivating.");
		deactivate();
	}
}

ArActionDesired *ActionBuscarPared::fire(ArActionDesired currentDesired) {
	double leftRange, rightRange;//; ,leftRange2, rightRange2;
	//si no estoy ejecutando mi tarea sal de ella
	if (!(myPlanificador->AccionActivada == myPlanificador->AccionActivadaBuscarPared))
		return &myDesired;
	myPlanificador->Accion();

	myDesired.reset();
	if (mySonar == NULL) {
		deactivate();
		return NULL;
	}
	//buscar la distancia mas corta
	double distanciaMasCorta=4700;//maximo alcance
	int grados=380;//sin asignar
	//int paralelo = 380;

	for(int i = 0 ; i < 180 ;i=i+10){
		leftRange = (mySonar->currentReadingPolar(i, i+10 ) - myRobot->getRobotRadius());
		rightRange = (mySonar->currentReadingPolar(-i, -i+10 ) - myRobot->getRobotRadius());
		if(distanciaMasCorta>leftRange){
			//busca una pared con el cos para saber si es paralela
			//for(int j = i+10 ; j < 180 ;j=j +10){
			//	leftRange2 = (mySonar->currentReadingPolar(j, j+10 ) - myRobot->getRobotRadius());
			//	if( fabs (cos (j * PI/180 ) * leftRange2 - leftRange)< 100){
					distanciaMasCorta = leftRange;
					grados	= i;
			//		paralelo = j;
			//	}
			//}
		}
		if(distanciaMasCorta>rightRange){
			//busca una pared con el cos para saber si es paralela
			//for(int j = i+10 ; j < 180 ;j = j+10){
			//	rightRange2 = (mySonar->currentReadingPolar(-j, -j+10 ) - myRobot->getRobotRadius());
			//	if( fabs(cos (j * PI/180 ) * rightRange2 - rightRange)< 100){
					distanciaMasCorta = rightRange;
					grados	=-i;
			//		paralelo = -j;
			//	}
			//}
		}
	}
	printf("distancia mas corta grados%d  distanciaMasCorta  %g  \n", grados , distanciaMasCorta );
	//buscar pared perpendicular


	leftRange =(mySonar->currentReadingPolar(-20, 0) - myRobot->getRobotRadius());
	rightRange = (mySonar->currentReadingPolar(0, 20) - myRobot->getRobotRadius());

	if(girando){
		myDesired.setDeltaHeading(grados-90);
		if(grados >= 80 && grados <= 100){
			girando = false;
			myPlanificador->AccionActivada = myPlanificador->AccionActivadaAndarParalelo;
		}
	}else
		if (leftRange > 300 && rightRange > 300) {
			myDesired.setVel(100); //sigue en marcha
			if(grados !=380)
				myDesired.setDeltaHeading(grados);
		} //empieza a girar.
		else{
			girando=true;
		}



	//rightRange = (mySonar->currentReadingPolar(69 , 89 ) - myRobot->getRobotRadius());


	/*myDesired.setVel(100);



    //la diferencia entre el rango iz y dere es pequeña, ya estoy en perpendicular a la pared
	if (girando) {
		leftRange = (mySonar->currentReadingPolar(91, 111 ) - myRobot->getRobotRadius());
		rightRange = (mySonar->currentReadingPolar(69 , 89 ) - myRobot->getRobotRadius());
		range = leftRange - rightRange;
		printf("leftRange %g rightRange %g  range  %g girando\n", leftRange, rightRange, range);
		if (fabs(leftRange - rightRange) < 100 || leftRange > 800 || rightRange > 800) {
			myDesired.setDeltaHeading(-45);
		} else {
			girando = false;
			myDesired.setDeltaHeading(0);
			myPlanificador->AccionActivada = myPlanificador->AccionActivadaAndarParalelo;

		}
	} else {
		leftRange =(mySonar->currentReadingPolar(-20, 0) - myRobot->getRobotRadius());
		rightRange = (mySonar->currentReadingPolar(0, 20) - myRobot->getRobotRadius());
		range = leftRange - rightRange;

		printf("leftRange %g rightRange %g  range  %g normal\n", leftRange, rightRange, range);
		if (fabs(leftRange - rightRange) < 75) {
			//no hace nada ya esta orientado
			printf("range %f \n", range);

			//si estoy cerca de la pared
			if (leftRange > 200 && rightRange > 200) {
				myDesired.setVel(100); //sigue en marcha
			} //empieza a girar.
			else {
				girando = true;
			}
		} //si la diferencia sigue siendo alta orientalo hasta que esten en perpendicular
		else if (leftRange > rightRange) {
			myDesired.setDeltaHeading(20);

		} //else if (leftRange < rightRange) {
		//	myDesired.setDeltaHeading(-20);
		//}

	}*/
	return &myDesired;
}


