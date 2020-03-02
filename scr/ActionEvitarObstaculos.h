
#include "Aria.h"
#include "Planificador.h"


class ActionEvitarObstaculos : public ArAction
{
public:
  ActionEvitarObstaculos(Planificador *planificador);
  virtual ~ActionEvitarObstaculos(void) {};
  virtual ArActionDesired *fire(ArActionDesired currentDesired);
  virtual void setRobot(ArRobot *robot);

protected:

  ArRangeDevice *mySonar;
  ArActionDesired myDesired;
  Planificador *myPlanificador;


};
