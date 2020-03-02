
#include "ActionEvitarObstaculos.h"

ActionEvitarObstaculos::ActionEvitarObstaculos(Planificador *planificador) :
  ArAction("ActionEvitaObstaculos")
{
  mySonar = NULL;
  myPlanificador= planificador;
}


void ActionEvitarObstaculos::setRobot(ArRobot *robot)
{
  ArAction::setRobot(robot);
  mySonar = robot->findRangeDevice("sonar");
  if (robot == NULL)
    {
      ArLog::log(ArLog::Terse, "actionExample: ActionGo: Warning: I found no sonar, deactivating.");
      deactivate();
    }
}

ArActionDesired *ActionEvitarObstaculos::fire(ArActionDesired currentDesired)
{
  double range1, range2, range3, range4;

  // reset the actionDesired (must be done), to clear
  // its previous values.
  myDesired.reset();

  // if the sonar is null we can't do anything, so deactivate
  if (mySonar == NULL)
  {
    deactivate();
    return NULL;
  }
  // get the range of the sonar


  range1= mySonar->currentReadingPolar(-60, -30) - myRobot->getRobotRadius();
  range2= mySonar->currentReadingPolar(-30,0) - myRobot->getRobotRadius();
  range3= mySonar->currentReadingPolar(0, 30) - myRobot->getRobotRadius();
  range4= mySonar->currentReadingPolar(30, 60) - myRobot->getRobotRadius();

  if(range1< 200 ||range2< 200 ||range3< 200 ||range4< 200   ){
		myPlanificador->AccionActivada = myPlanificador->AccionActivadaEvitarObstaculo;
  }else{
	if(myPlanificador->AccionActivada == myPlanificador->AccionActivadaEvitarObstaculo)
	myPlanificador->AccionActivada = myPlanificador->AccionActivadaBuscarPared;
  }


  if(myPlanificador->AccionActivada != myPlanificador->AccionActivadaEvitarObstaculo)
	  return &myDesired;
	printf("Evitando obstaculos %g, %g, %g, %g \n",range1,range2,range3,range4);


  if(range2 < 100 && range3 < 100 ){//enfrente esta cerrado girar o retroceder
	if(range1 < 100 && range4 < 100  ){//laterales
		myDesired.setDeltaHeading(-180);
	}
	else{ //girar a iz o derecha
		if(range1 < 100 ){
			myDesired.setDeltaHeading(-45); //girar a derechas
		}else if(range4 < 100 ){
			myDesired.setDeltaHeading(45);//girar a iz
		}
	}
  }else{//solo los laterales
		if(range1 < 100 ||range4 < 100 ){
			myDesired.setDeltaHeading(myDesired.getDeltaHeading()*-1); //al lado contrario
		}
  }


  // return a pointer to the actionDesired to the resolver to make our request
  return &myDesired;
}


