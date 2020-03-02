#include "Aria.h"

#include "ActionBuscarPared.h"
#include "ActionAndarParalelo.h"
#include "ActionEvitarObstaculos.h"

#include "Planificador.h"

int main(int argc, char** argv)
{
  Aria::init();

  ArSimpleConnector conn(&argc, argv);
  ArRobot robot;
  ArSonarDevice sonar;

  Planificador planificador;


  ActionAndarParalelo andarParalelo(&planificador);
  ActionBuscarPared buscarPared( &planificador);
  ActionEvitarObstaculos evitarObstaculos(&planificador);

  ArActionStallRecover recover;

    
  // Parse all command-line arguments
  if(!Aria::parseArgs())
  {
    Aria::logOptions();
    return 1;
  }
  
  // Connect to the robot
  if(!conn.connectRobot(&robot))
  {
    ArLog::log(ArLog::Terse, "actionExample: Could not connect to robot! Exiting.");
    return 2;
  }

  // Add the range device to the robot. You should add all the range 
  // devices and such before you add actions
  robot.addRangeDevice(&sonar);

 
  //robot.addAction(&recover, 100);
  robot.addAction(&andarParalelo, 50);
  robot.addAction(&buscarPared, 49);
  robot.addAction(&evitarObstaculos, 49);


  // Enable the motors, disable amigobot sounds
  robot.enableMotors();

  // Run the robot processing cycle.
  // 'true' means to return if it loses connection,
  // after which we exit the program.
  robot.run(false);
  
  Aria::shutdown();
  return 0;
}
