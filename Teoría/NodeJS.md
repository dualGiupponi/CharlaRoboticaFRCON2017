# Node.js

![Simbolo Nodejs](https://dab1nmslvvntp.cloudfront.net/wp-content/uploads/2015/07/1436439824nodejs-logo.png)

## Overview
Node.js ha ganado gran popularidad en la red ultimamente, es una herramienta muy utilizada y (seguramente) si viste/hiciste algún curso de JavaScript de un tiempo a esta parte, seguramente (cómo mínimo) lo nombraron.
Ahora bien, cuando hablamos de Node.js, aunque no lo parezca, rompemos con muchas ideas o paradigmas que traemos de otros lenguajes (como PHP), especialmente para aquellos que trabajamos en el backend de las aplicaciones web (es decir, la parte del "servidor", por ponerle un nombre).
En este breve artículo intentaremos explicar algo de lo que es Node.js, para qué nos sirve y por qué sufre de tanta popularidad.

## ¿Qué es Node.js?
Tal como podemos encontrar en su [página oficial](https://nodejs.org/en/), la definición estricta de Node.js es:
>Node.js® es un entorno de ejecución para JavaScript construido con el motor de JavaScript V8 de Chrome. Node.js usa un modelo de operaciones E/S sin bloqueo y orientado a eventos, que lo hace liviano y eficiente. El ecosistema de paquetes de Node.js, npm, es el ecosistema mas grande de librerías de código abierto en el mundo.

Claro, que si es la primera vez que te topas con la definición, seguramente no entiendas nada de nada, por lo que voy a descomponerlo lo más posible a lo que está escrito más arriba.

> Node.js® es un entorno de ejecución para JavaScript construido con el motor de JavaScript V8 de Chrome.

Bienvenido al primer choque de ideas. Si trabajaste (o leiste) sobre otros lenguajes de programación, ejemplo, PHP, habrás visto que es necesario tener que instalar un servidor HTTP (como Apache o NGINX). **Esto es necesario porque PHP corre sobre un servidor web**, que interpreta el código contenido dentro de un script que luego es lanzado al cliente que realizó la petición.
Cuando instalas Node.js, esto no es necesario (aunque si para colocarlo en producción). 