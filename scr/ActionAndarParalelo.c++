/*
 * ActionAndarParalelo.cpp
 *
 *  Created on: 04/02/2012
 *      Author: jorge
 */

#include "ActionAndarParalelo.h"

ActionAndarParalelo::ActionAndarParalelo(Planificador *planificador) :ArAction("ActionAndarParalelo") {
	mySonar = NULL;
	myPlanificador = planificador;
	giro = 0;
}

void ActionAndarParalelo::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	mySonar = robot->findRangeDevice("sonar");
	if (robot == NULL) {
		ArLog::log(
				ArLog::Terse,
				"actionExample: ActionGo: Warning: I found no sonar, deactivating.");
		deactivate();
	}
}

ArActionDesired *ActionAndarParalelo::fire(ArActionDesired currentDesired) {
	//double speed;
	double range, rangeIzquierdo, rangeDerecho, leftRange, rightRange,
			leftRangeDelante, rightRangeDelante;

	if (!(myPlanificador->AccionActivada
			== myPlanificador->AccionActivadaAndarParalelo))
		return &myDesired;
	myPlanificador->Accion();

	myDesired.reset();

	myDesired.setVel(100);

	// if the sonar is null we can't do anything, so deactivate
	if (mySonar == NULL) {
		deactivate();
		return NULL;
	}
	// get the range of the sonar

//	myDesired.setDeltaHeading(0);
	//lecturas derecha e izquierda a 90 grados con 20 de aplitud
	rightRange = (mySonar->currentReadingPolar(-55, -45)- myRobot->getRobotRadius());
	 rightRangeDelante= (mySonar->currentReadingPolar(-45, -30)- myRobot->getRobotRadius());

	 leftRange  = (mySonar->currentReadingPolar(45, 55)- myRobot->getRobotRadius());
	leftRangeDelante = (mySonar->currentReadingPolar(30, 45)- myRobot->getRobotRadius());

	rangeDerecho = rightRange - rightRangeDelante;
	rangeIzquierdo = leftRange - leftRangeDelante;
	//pegados a la pared por la derecha
	if (leftRange > rightRange) {
		printf("lado derecho 90º rightRange %g rightRangeDelante %g  range  %g\n",rightRange, rightRangeDelante, rangeDerecho);
		if (fabs(rangeDerecho) > 200) {
			if (rightRange > rightRangeDelante) { // si se descompensa aproximarlo
				myDesired.setDeltaHeading(10);
			} else if (rightRange < rightRangeDelante) {
				myDesired.setDeltaHeading(-10);
			}
		} else {
			myDesired.setDeltaHeading(0);
		}

	} else { //pegados a la izquierda
		printf("lado izquierdo 90º leftRange %g leftRangeDelantero %g  range  %g\n",leftRange, leftRangeDelante, rangeIzquierdo);
		if (fabs(rangeIzquierdo) > 200) {
			if (leftRange > leftRangeDelante) { // si se descompensa aproximarlo
				myDesired.setDeltaHeading(10);
			} else if (leftRange < leftRangeDelante) {
				myDesired.setDeltaHeading(-10);
			}
		} else {
			myDesired.setDeltaHeading(0);
		}
	}
	//endereza el robot

	rightRange = (mySonar->currentReadingPolar(-20, 0)- myRobot->getRobotRadius());
	leftRange =(mySonar->currentReadingPolar(0, 20) - myRobot->getRobotRadius());
	range = leftRange - rightRange;
	printf("enfrente leftRange %g rightRange %g  range  %g\n", leftRange,rightRange, range);

	//si encuentro una pared.
	if ((leftRange < 1000 && rightRange < 1000)) {
		//myPlanificador->AccionActivada = myPlanificador->AccionActivadaBuscarPared;
		//si llego a una pared gira hacia la escapatoria
		leftRange = (mySonar->currentReadingPolar(45, 90) - myRobot->getRobotRadius());
		rightRange = (mySonar->currentReadingPolar(-90, -45)- myRobot->getRobotRadius());
		range = leftRange - rightRange;
		if (giro == 0 && rightRange > leftRange) {
			printf("GIRO A LA DERECHA leftRange %g rightRange %g  range  %g\n",leftRange, rightRange, range);
			giro = 1;

		} else {
			printf("GIRO A LA IZQUIERDA leftRange %g rightRange %g  range  %g\n",leftRange, rightRange, range);
			giro = -1;

		}
		if (giro != 0)
			myDesired.setDeltaHeading(45 * giro);
		//myPlanificador->AccionActivada = myPlanificador->AccionActivadaBuscarPared;
	} else {
		giro = 0; //si llego a una esquina gira hacia el lado que tenga escapatoria
	}

	// if the range is greater than the stop distance, find some speed to go
	/*
	 if (range > myStopDistance)
	 {
	 // just an arbitrary speed based on the range
	 speed = range * .3;
	 // if that speed is greater than our max, cap it
	 if (speed > myMaxSpeed)
	 speed = myMaxSpeed;
	 // now set the velocity
	 myDesired.setVel(speed);

	 }*/
	// the range was less than the stop distance, so request stop
	// return a pointer to the actionDesired to the resolver to make our request
	return &myDesired;
}

