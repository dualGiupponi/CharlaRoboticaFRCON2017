<!-- TOC -->

- [Node.js](#nodejs)
    - [Overview](#overview)
    - [¿Qué es Node.js?](#¿qué-es-nodejs)
        - [¿Cómo funciona Node.js?](#¿cómo-funciona-nodejs)
            - [¿Qué es el event loop?](#¿qué-es-el-event-loop)
            - [Descripción general de las fases.](#descripción-general-de-las-fases)
        - [Ventajas y desventajas.](#ventajas-y-desventajas)

<!-- /TOC -->


# Node.js

![Simbolo Nodejs](https://dab1nmslvvntp.cloudfront.net/wp-content/uploads/2015/07/1436439824nodejs-logo.png)

## Overview
Node.js ha ganado gran popularidad en la red ultimamente, es una herramienta muy utilizada y (seguramente) si viste/hiciste algún curso de JavaScript de un tiempo a esta parte, seguramente (cómo mínimo) lo nombraron.
Ahora bien, cuando hablamos de Node.js, aunque no lo parezca, rompemos con muchas ideas o paradigmas que traemos de otros lenguajes (como PHP), especialmente para aquellos que trabajamos en el backend de las aplicaciones web (es decir, la parte del "servidor", por ponerle un nombre).
En este breve artículo intentaremos explicar algo de lo que es Node.js, para qué nos sirve y por qué sufre de tanta popularidad.

## ¿Qué es Node.js?
Tal como podemos encontrar en su [página oficial](https://nodejs.org/en/), la definición que podemos encontrar de Node.js es:
>Node.js® es un entorno de ejecución para JavaScript construido con el motor de JavaScript V8 de Chrome. Node.js usa un modelo de operaciones E/S sin bloqueo y orientado a eventos, que lo hace liviano y eficiente. El ecosistema de paquetes de Node.js, npm, es el ecosistema mas grande de librerías de código abierto en el mundo.

NPM, para aquellos que no conozcan, es el gestor de paquetes de Node. Para los que no estén relacionados con el término, un gestor de paquetes es un programa que descarga paquetes (en este caso módulos de JavaScript, que puede ser desde un encriptador para contraseña hasta conectores de base de datos) para nuestro proyecto. También es el encargado de revisar los paquetes instalados y verificar si existen actualizaciones.

### ¿Cómo funciona Node.js?
Node.js se basa mayormente en el motor de Chrome, V8. Cuando Google creó el V8, escribió un interprete ultra-rápido en C++ de JavaScript, con una ventaja enorme: **El motor se puede descargar separado del navegador**, por lo que es posible colocarlo en cualquier tipo de aplicación, razón por la cual Ryan Lienhart Dahl lo aplicó al desarrollo de aplicaciones de servidores.
Desde entonces la comunidad (y los proyectos en torno a la plataforma) no han dejado de crecer, y muchas empresas de gran renombre lo están utilizando.
Dentro del funcionamiento de Node.js, el punto fuerte es un subproceso denominado **event loop**. 

#### ¿Qué es el event loop?
El bucle de eventos (event loop) es lo que permite a Node realizar operaciones no bloqueantes de Entrada/Salida. El evento loop es proporcionado por la biblioteca Libuv.
Cuando Node se inicia, inicializa el event loop, procesa el script de entrada proporcionado que puede hacer llamadas de API asincrónicas, programar temporizadores o llamar al process.nextTick(), entonces se comienza a procesar el event loop.

El diagrama simplificado del orden de operaciones del event loop es el siguiente:

* Timers (Temporizadores)
* I/O callbacks
* Idle/prepare
* Poll <- (Conexiones entrantes, data, etc)
* Check
* Close callbacks

Cada fase descripta tiene una cola tipo FIFO de callbacks para ejecutar. Aunque cada fase es especial (a su manera), generalmente cuando el bucle entra en una fase dada, realizará cualquier operación específica de la misma, luego ejecutará los callbacks en la cola de esa fase hasta que se hayan agotado o se haya llegado al número máximo de callbacks ejecutados. Luego, se mueve a la siguiente fase, y así sucesivamente.

#### Descripción general de las fases.
* **Timers (temporizadores):** Esta fase ejecuta los callbacks programados por setTimeout() o setInterval.
* **I/O callbacks:** ejecuta casi todos los callbacks, con la excepción de los callbacks de cierre, los programados por los temporizadores y setImmediate(). Cabe aclarar que en Node, todo el código escrito por el usuario es básicamente callbacks.
* **Idle/Prepare:** sólo se utiliza internamente.
* **Poll:** es el encargado de sondear y recuperar nuevos eventos de Entrada/Salida que serán ejecutados en la próxima ejecución. Node se bloqueará aquí cuando sea apropiado.
* **Close callbacks:** Aquí se procesan todos los callbacks de evento "close".

![Imágen de las fases](https://cdn-images-1.medium.com/max/1600/1*ROxiavz7LeRpIfcgRDE7CA.png)

Es por este bucle de eventos es que se recomienda (casi a nivel de exigencia) que **el código de programación debe ser NO bloqueante**, mediante el uso de callbacks (o promesas, según el nuevo estandar ES6).

### Ventajas y desventajas.

Gracias al event loop, **Node.js maneja sistemas de alta concurrencia con muy poco consumo de recursos en el servidor y a una gran tasa de velocidad**. Esto se debe a que en lugar de crear un hilo por petición de usuario (como en el caso de Apache) y otorgarle a éste su correspondiente memoria, **la petición es tomada por el event loop y descompuesta en callbacks que luego son resueltos, llevando n cantidad de hilos (por las peticiones de todos los usuarios) a uno solo**.

La desventaja **clara** es que, si usamos operaciones bloqueantes (lectura/escritura de muchos archivos, operaciones pesadas o cálculos muy complejos), **el event loop se bloquea**, perdiendo así la potencia que ofrece Node (y hasta en algunos casos, produciendo la caida completa de la aplicación). Es por ello que es recomendable que, en caso de hacer operaciones muy complejas o pesadas, se cree un servicio en un lenguaje que esté optimizado para esa función y luego sea llamada por Node.