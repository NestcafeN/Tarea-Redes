# Tarea de Comunicacion de datos y Redes

## Alumnos: José Acuña, Diego Gutierréz

## Estructura del Proyecto

Tarea-Redes/
│
├── build/
│ ├── client
│ ├── server
│
├── src/
│ ├── server/
│ │ └── server.cpp
│ ├── client/
│ │ └── client.cpp
│ ├── common/
│ ├── common.cpp
│ └── common.hpp
│
└── Makefile

### Descripción de las Carpetas

- **build/**: Contiene los archivos objeto (`.o`) y los ejecutables generados después de compilar el proyecto.
- **src/**: Contiene el código fuente del proyecto dividido en subcarpetas:
  - **server/**: Contiene el código fuente del servidor.
  - **client/**: Contiene el código fuente del cliente.
  - **common/**: Contiene los archivos comunes (`common.cpp` y `common.hpp`) utilizados tanto por el cliente como por el servidor.
- **Makefile**: Script de compilación para construir el proyecto.

## Compilación del Proyecto

Para compilar el proyecto, asegúrate de estar en el directorio raíz del proyecto y ahi ejecutamos el siguiente comando:

make

Este comando compilará los archivos fuente y generará los ejecutables en el directorio build.

### Ejecutar el Servidor

Para ejecutar el servidor, utiliza el siguiente comando:

./build/server <puerto>
Donde <puerto> es el puerto en el que deseas que el servidor escuche las conexiones entrantes. Ejemplo:
./build/server 7777

### Ejecutar el Cliente

Para ejecutar el cliente, utiliza el siguiente comando:
./build/client <ip_del_servidor> <puerto>
Donde <ip_del_servidor> es la dirección IP del servidor y <puerto> es el puerto en el que el servidor está escuchando. Ejemplo:
./build/client 127.0.0.1 7777

### Descripción del Código

server.cpp
El archivo server.cpp contiene la lógica del servidor. El servidor acepta conexiones entrantes de múltiples clientes y maneja cada conexión en un hilo separado. La lógica del juego se gestiona utilizando la clase Game definida en common.cpp y common.hpp.

client.cpp
El archivo client.cpp contiene la lógica del cliente. El cliente se conecta al servidor y permite al usuario jugar a Conecta 4 interactuando con el servidor. La lógica del juego se gestiona utilizando la clase Game definida en common.cpp y common.hpp.

common.cpp y common.hpp
Estos archivos contienen la implementación y las declaraciones de la clase Game, que gestiona el estado y la lógica del juego Conecta 4. La clase Game proporciona métodos para realizar movimientos, verificar victorias y comprobar si el tablero está lleno.