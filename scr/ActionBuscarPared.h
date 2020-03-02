

#include "Aria.h"
#include "Planificador.h"

class ActionBuscarPared : public ArAction
{
public:
  // constructor, sets the turnThreshold, and turnAmount
  ActionBuscarPared(Planificador *planificador);
  // destructor, its just empty, we don't need to do anything
  virtual ~ActionBuscarPared(void) {};
  // fire, this is what the resolver calls to figure out what this action wants
  virtual ArActionDesired *fire(ArActionDesired currentDesired);
  // sets the robot pointer, also gets the sonar device, or deactivates this action if there is no sonar.
  virtual void setRobot(ArRobot *robot);
protected:
  ArRangeDevice *mySonar;
  ArActionDesired myDesired;
  bool girando ; // -1 == left, 1 == right, 0 == none
  Planificador *myPlanificador;

};


