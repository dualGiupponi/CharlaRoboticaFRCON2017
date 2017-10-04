<!-- TOC -->

- [Node.js](#nodejs)
    - [Overview](#overview)
    - [¿Qué es Node.js?](#¿qué-es-nodejs)
        - [¿Cómo funciona Node.js?](#¿cómo-funciona-nodejs)
            - [Node.js y Threads.](#nodejs-y-threads)

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

Claro, que si es la primera vez que te topas con la definición, seguramente no entiendas nada de nada, por lo que vamos a explicarlo lo más posible.

### ¿Cómo funciona Node.js?
Node.js se basa mayormente en el motor de Chrome, V8. Cuando Google creó el V8, escribió un interprete ultra-rápido en C++ de JavaScript, con una ventaja enorme: **El motor se puede descargar separado del navegador**, por lo que es posible colocarlo en cualquier tipo de aplicación, razón por la cual Ryan Lienhart Dahl lo aplicó al desarrollo de aplicaciones de servidores.
Desde entonces la comunidad (y los proyectos en torno a la plataforma) no han dejado de crecer, y muchas empresas de gran renombre lo están utilizando.

#### Node.js y Threads.
Cuando trabajamos con programas escritos en lenguajes de gran popularidad (como PHP o Java), cada conexión entrante genera un hilo que, generalmente, puede ocup