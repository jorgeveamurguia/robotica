PRÁCTICA DE ROBÓTICA AUTÓNOMA 1
El objetivo de ésta práctica es utilizar el simulador MobileSim para programar un control del tipo
"Behavior-based" simple.
Se programarán tres comportamientos:
- Aproximarse a una pared, hasta una distancia de seguridad.
- Seguir paralelo a una pared, cuando nos hayamos situado a la distancia de seguridad y con la
orientación adecuada.
- Evitar obstáculos.
Además de estos tres comportamientos, se programará un coordinador de comportamientos, esto es,
un método a elección del alumno para considerar que comportamiento toma el control del robot en
cada situación.
El software final se podrá probar en los robots reales Pioneer3AT y/= o AmigoBot del
Departamento.
Se utilizará un modelo del mundo a elegir entre los dos modelos que vienen de ejemplo en el
simulador.
Clases implementadas.
Planificador. Tiene 3 estados que corresponde con las acciones implementadas. Solo un estado
puede estar activado a la vez. El primer estado activo es ActionBuscar pared que pasa a
ActionAndarParalelo cuando deje el robot pegado a 300 de distancia de la pared y orientado a 90
grados. La accion ActionEvita obstáculos, se activa cuando este a menos de 200 de distancia de
cualquier objeto. Una vez que se evita el obtaculo salta a la accion ActionBuscarPared
ActionBuscarPared. Busca la distancia mínima y calcula el ángulo adecuado para llegar a el. Una
vez que esta a una distancia de seguridad gira 90 grados. Esta clase hereda de la clase ArAction
ActionAndarParalelo. Una vez que el robot esta en paralelo a una superficie, realiza las siguientes
operaciones. Calcula la distancia en 4 rangos , en 70, 90 grados en 90 en 110 y en negativos. El
objetivo es doble. 1º saber si la pared esta a derecha o a izquierda y saber si nos estamos desviando
de la pared haciendo la diferencia entre las dos medidas de un lado. Si la parte delantera es mayor
que la trasera es decir si el rango de 70 90 hay mas distancia que en 90 110 significa que nos
alejamos de la pared con lo cual rectificamos el anglo para acercarnos a la pared y a la inversa. Las
esquinas son difíciles de corregir, ya que se aleja mas rápido que el ángulo que se aplica. Esta clase
hereda de la clase ArAction
ActionEvitarObtaculos realiza un barrido en las regiones angulares 0 30 y 30 60, en ambos lados.
Si encontramos un objeto a menos de 200 realiza un escape de esa región. Dependiendo de la región
angular que se encuentre, realiza un escape de 180 grados o de 45 grados. Esta clase hereda de la
clase ArAction
La clase demo.c++ es donde está implementada la llamada a cada una de las inicializaciones de la
clase, la configuración del robot y el sonar.
Para realizar la práctica, se han usado 2 equipos, uno con la aplicación mobilSim para visualizar el
robot en movimiento y otro equipo donde se ha desarrollado la práctica. El sistema operativo usado
es Ubuntu 11.10 y el entorno de desarrollo eclipse. Primero se han instalado las librerías Aria. Para
compilar en eclipse se ha configurado el entorno, en include se añade /usr/local/Aria/include en lib
se añade Aria, dl, pthread, rt. Y en library path se añade /usr/local/Aria/lib. Para ejecutar hay que
introducir el path de la librería, LD_LIBRARY_PATH en variable enviroment con el valor de
usr/local/Aria/lib. Para configurar la conexión con el otro equipo se realiza como un parametro mas
a la hora de ejecutar la aplicación -remoteHost 192.168.1.5
Dificultades para realizar la practica. Debido a la falta de experiencia en la programación en C++ he
invertido gran cantidad de tiempo en conocer la sintaxis. Las librerías de Aria tienen una gran
cantidad de clases y métodos. Leer en profundidad todos esto ha sido imposible. Además, la falta de
referencias bibliográficas del funcionamiento de los métodos que hay que implementar ha
dificultado la compresión del funcionamiento
La configuración del robot ha sido básica y solo se ha utilizado el sonar para controlar las distancias
del los objetos.
Posibles mejoras: Se ha intentado calcular en el método ActionBuscarPared , al calcular distancia
mas próxima tiene puntos que dista el coseno del ángulo al punto para saber si es una pared.
Contenido del fichero zip
El fichero zip contiene las clases que lo implementa, la versión compilada demo.o y los
ficheros de configuración del eclipse .cproject y .project