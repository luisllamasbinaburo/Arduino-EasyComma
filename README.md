# Librería Arduino EasyComma
Librería para Arduino para leer de forma sencilla una serie de enteros enviados por el puerto de serie. Es una forma fácil de comunicarnos con nuestro proyecto, sobre todo en desarrollos sencillos o en primeras etapas. En desarrollos más avanzados, en general, preferiremos el envío directo de bytes como la librería ComCenter

Más información https://www.luisllamas.es/libreria-arduino-easycomma/

## Instrucciones de uso
Un objeto EasyComma se inicializa indicando su capacidad, que es el número máximo de enteros que puede almacenar el objeto. Para recibir datos empleamos el método Recieve(), que llamaremos frecuentemente en el bucle de control.

Durante la recepción, EasyComma comprueba si existen datos por recibir. Si es así, los procesa, y almacena los valores recibidos en el array de enteros interno. Por defecto, el separador entre enteros es la coma (',') y el separador entre grupos de enteros el salto de línea ('\n'), aunque podemos cambiarlos por cualquier otro carácter.

Cuando la recepción de un paquete se termina, se ejecuta la acción de callback que pasamos a la función Recieve(). Esto permite liberar al bucle principal de las funciones.

En caso de recibir más enteros que la capacidad con la que hemos creado EasyComma, se vuelve a escribir el array desde su principio, de forma similar a un buffer circular. De esta forma, los datos almacenados en EasyComma son siempre los últimos N valores recibidos.

La clase EasyComma disponer de los métodos Count() que devuelve el número de valores recibidos en el último paquete de enteros, y LastIndex() que devuelve la última posición en la que se ha escrito, empleado cuando tenemos desbordamiento del array interno.


### Constructor
```c++
EasyComma(size_t capacity);
```

### Usar la librería
```c++
// Acceder a los elementos recibidos
int& operator[](const size_t index);
	
// Separador entre integer recibidos
char Separator = ',';

// Separador entre grupos recibidos
char EndSeparator = '\n';

// Obtiene la capacidad 
size_t Capacity();

// Obtiene la cantidad de objetos almacenados
size_t Count();

// Obtiene el indice del ultimo elemento almacenado
size_t LastIndex();

// Devuelve true si el número de elementos del último paquete es mayor que la capacidad
bool IsOverflow();
```


## Ejemplos
La librería EasyComma incluye los siguientes ejemplos para ilustrar su uso.
* EasyComma: Ejemplo general de uso de la clase EasyComma.

```c++
#include "EasyCommaLib.h"

EasyComma easyComma(4);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  easyComma.Recieve(
  []() {  
    auto servoNum = easyComma[0];
    auto delayMs = easyComma[1];
  });
}
```
