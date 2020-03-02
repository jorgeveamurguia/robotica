


#ifndef ACTIONANDAR_H_
#define ACTIONANDAR_H_


#include "Aria.h"
#include "Planificador.h"


class ActionAndarParalelo : public ArAction
{
public:
  // constructor, sets myMaxSpeed and myStopDistance
  ActionAndarParalelo(Planificador *planificador);
  // destructor. does not need to do anything
  virtual ~ActionAndarParalelo(void) {};
  // called by the action resolver to obtain this action's requested behavior
  virtual ArActionDesired *fire(ArActionDesired currentDesired);
  // store the robot pointer, and it's ArSonarDevice object, or deactivate this action if there is no sonar.
  virtual void setRobot(ArRobot *robot);
protected:
  // the sonar device object obtained from the robot by setRobot()
  ArRangeDevice *mySonar;


  /* Our current desired action: fire() modifies this object and returns
      to the action resolver a pointer to this object.
      This object is kept as a class member so that it persists after fire()
      returns (otherwise fire() would have to create a new object each invocation,
      but would never be able to delete that object).
  */
  ArActionDesired myDesired;
  Planificador *myPlanificador;

  int giro;
};
#endif /* ACTIONANDAR_H_ */
