#### [Volver al menú principal](../README.md)
# MQTT

<!-- TOC -->

            - [[Volver al menú principal](../README.md)](#volver-al-menú-principalreadmemd)
- [MQTT](#mqtt)
    - [Overview](#overview)
    - [Introducción](#introducción)
        - [Publish/Subscribe](#publishsubscribe)
        - [Cliente](#cliente)
        - [Broker](#broker)
        - [Conexión MQTT](#conexión-mqtt)
            - [Mensaje CONNECT](#mensaje-connect)
            - [Mensaje CONNACK](#mensaje-connack)
    - [Publicar, suscribir y anular suscripción](#publicar-suscribir-y-anular-suscripción)
        - [Publicar](#publicar)
        - [Suscribirse](#suscribirse)
            - [Mensaje SUBACK](#mensaje-suback)
        - [Anular la suscripción](#anular-la-suscripción)
            - [Mensaje UNSUBACK](#mensaje-unsuback)
    - [Temas en MQTT y mejores prácticas](#temas-en-mqtt-y-mejores-prácticas)
        - [Comodines](#comodines)
            - [Comodín de nivel único: +](#comodín-de-nivel-único-)
            - [Comodín de multinivel: \](#comodín-de-multinivel-\)
            - [Temas que comienzan con $](#temas-que-comienzan-con-)
        - [Mejores prácticas](#mejores-prácticas)
        - [Mensajes de sesión persistente y cola de espera](#mensajes-de-sesión-persistente-y-cola-de-espera)
            - [Sesión persistente](#sesión-persistente)
            - [¿Cómo inicializar/finalizar una sesión persistente?](#¿cómo-inicializarfinalizar-una-sesión-persistente)
            - [¿Cómo sabe el cliente si ya hay una sesión almacenada?](#¿cómo-sabe-el-cliente-si-ya-hay-una-sesión-almacenada)
            - [Sesión persistente del lado del cliente.](#sesión-persistente-del-lado-del-cliente)

<!-- /TOC -->

## Overview
En la parte anterior tratamos todo lo referido a nuestro servidor, que va a ser el encargado de almacenar, administrar y poner en disponibilidad los datos recolectados por nuestros microcontroladores/microprocesadores. También hablamos sobre las diferencias y diversas ventajas que ofrece utilizar uno y otro tipo en nuestros proyectos.
Pero si usted sigue hasta ahora la línea de los temas abordados, se dará cuenta que en ningún momento hemos mencionado sobre **cómo se conectarán nuestro/s microcontrolador(es)/microprocesador(es) al servidor, y cómo se comunicaran entre ellos (ya sea con el servidor, o entre microcontrolador(es)/microprocesador(es))**. En este apartado vamos a tratar todo lo referído a este tema.

## Introducción
![MQTT Logo](http://www.qpcb-design.com/wp-content/uploads/2014/11/MQTT.png)

**MQTT es un protocolo de mensajería de tipo publish/subscribe especialmente diseñado para dispositivos de recursos limitados, redes de gran latencia o no fidedignas.**

### Publish/Subscribe
![Imágen descripción de Publish/Suscribe](http://www.arduinoblocks.com/blog/wp-content/uploads/2017/04/mqtt_publisher_subscriber.png)

El protocolo se basa en el principio de **publicar mensajes en un tema, y luego que otros clientes se suscriban a ese tema**. Esto hace que se pueda desacoplar a un cliente que envía información sobre un tema (llamado editor) de otros clientes que requieren esa información (denominados suscriptores).
**¿Cómo se logra desacoplar un primer componente cliente (editor) de otros componentes clientes (suscriptores)?** Esto se hace gracias a un tercer componente: **el broker**. Un broker es, en esencia, un servidor que tiene la función primaria de recibir los mensajes de un editor, filtrarlos por temas y luego distribuirlo a todos los suscriptores. Esto permite un **desacoplamiento entre editor y suscriptor, tanto en tiempo como en sincronización (de trabajo)**, haciendo que no sea necesario que se conozcan entre si,aumentando la **escalabilidad** del sistema.
En un ejemplo práctico, si tenemos dos placas que se comunican entre si mediante otro protocolo, si queremos agregar una tercera seguramente deberíamos modificar el código de las dos primeras para que reconozcan a la tercera. En el caso de MQTT, **nos libramos de esto**, ya que como están conectadas a un broker y postean información a un determinado tema, sólo es necesario suscribir la última placa al tema en cuestión para que pueda empezar a comunicarse. También, permite retirar cualquiera las placas (para mantenimiento, por ejemplo) sin que el flujo de trabajo se encuentre modificado de alguna manera.

### Cliente
Cuando mencionamos la palabra **cliente**, en realidad estamos haciendo referencia a **cualquier dispositivo que tiene una librería MQTT funcionando y se conecta en cualquier tipo de red**. Observe que en ningún momento nos referimos a un *cliente suscriptor* y a un *cliente editor*. Esto es, porque en MQTT, **cualquier cliente puede ser editor o suscriptor, independientemente de la situación a la que esté sometido**.

### Broker
**Es el corazón del protocolo** (y de cualquier protocolo basado en la idea de publish/subscription). Es el responsable de recibir todos los mensajes, filtrarlos por temas y luego reenviarlo a todos los clientes suscritos a cada tema.
Debido a que es el puente por el que todos los mensajes deben pasar, es fundamental que **sea altamente escalable, integrable a otros sistemas de tipo backend, resistente a fallos y fácil de monitorear**.

### Conexión MQTT
MQTT se basa en la parte superior de TCP/IP, por lo que tanto el cliente como el broker necesitan tener una pila TCP/IP.

#### Mensaje CONNECT
La conexión se inicía a través de un cliente que envía un mensaje CONNECT al broker con el siguiente contenido, entre otras cosas:

|_Campos_|_Descripción_|
|--------|-------------|
|clientId|Identificador único del cliente en el broker|
|cleanSession|Indicador de sesión limpia. Indica al broker si el cliente quiere iniciar una sesión persistente o no. Se denomina sesión persistente al estado donde el broker guarda todas las suscripciones y mensajes del cliente en caso de que se pierda la conexión|
|username|Nombre de usuario del cliente para la autenticación en el broker|
|password|Contraseña para la autenticación del cliente|
|lastWillTopic|Permite notificar a otros clientes cuando uno se desconecta. Esta característica es parte de la última actualización de MQTT.
|KeepAlive|El cliente se compromete a enviar mensajes tipo PING regulares al broker. Este mecanismo permitirá tanto al broker como al cliente saber si el otro está todavía vivo y alcanzable.

#### Mensaje CONNACK
Cuando a un broker le llega un mensaje CONNECT, tiene que contestar de manera obligatoria con un mensaje CONNACK. Éste sólo tiene dos entradas de datos:

|_Campos_|_Descripción_|
|--------|-------------|
|sessionPresent|El indicador de sesión indica si el broker ya tiene una sesión persistente del cliente respecto a interacciones anteriores. Si un cliente, con anterioridad, ha establecido el flag cleanSession en true, este flag tendrá valor false (ya que no habrá ninguna sesión disponible). Este indicador se encuentra disponible desde MQTT 3.1.1.
|returnCode|Indica el estado del intento de conexión.

|_Código de retorno_|_Descripción_|
|--------|-------------|
|0|Conexión aceptada
|1|Conexión rechazada. Versión de protocolo no compatible
|2|Conexión rechazada. ID Rechazado.
|3|Conexión rechazada. Servidor no disponible.
|4|Conexión rechazada. User/Password incorrecto.
|5|Conexión rechazada. No autorizado.

## Publicar, suscribir y anular suscripción
### Publicar
Después de que un cliente logra conectarse a un broker, puede empezar a publicar mensajes. MQTT ofrece un filtrado basado en temas, por lo que cada mensaje debe estar contenido dentro de uno, que sera reutilizado luego por el broker para enviar ese mensaje a los clientes interesados. Cada mensaje típicamente tiene una carga útil que contiene datos reales para transmitir en formato de byte. Cabe aclarar que MQTT es agnóstico de datos y depende totalmente del caso de uso cómo está estructurada la carga útil.
El mensaje PUBLISH contiene los siguientes campos:

|_Campo_|_Descripción_|
|--------|-------------|
|packetId| ID del paquete enviado.
|topicName|Una cadena simple que está estructurada jerarquicamente con barras inclinadas. Un ejemplo: "topic/1".
|qos|Quality of Service (o calidad de servicio) es una forma de identificar la garantía con la que un mensaje llega al otro extremo. Existen tres niveles: 0, 1 y 2.
|retainFlag|Esta bandera determina si el broker ha guardado el mensaje como último valor conocido para ese tema. Los nuevos clientes que se suscriban al tema lo recibiran luego de suscribirse.
|payload|Es el contenido real del mensaje.
|dupFlag|El indicador duplicado indica que este mensaje es un duplicado y que no se volverá a enviar. Esto es importante sólo en QoS mayores que cero.

### Suscribirse
Para que un cliente pueda recibir actualizaciones sobre un cierto tema que le interesa, primeramente tiene que suscribirse. Para ello debe enviar un mensaje del tipo SUBSCRIBE al broker. Es bastante simple y sólo consta de un identificador de paquete y una lista de suscripciónes. Cada suscripción es un par de tema y QoS.

#### Mensaje SUBACK
Cada suscripción debe ser confirmada por el broker mediante el envío de un mensaje tipo SUBACK. Este mensaje contiene en su cuerpo el mismo indicador de paquete que el mensaje de suscripción y una lista de códigos de retorno.

|_Campo_|_Descripción_|
|--------|-------------|
|packetId|Identificador único del paquete
|returnCode| Código de retorno para cada par de tema/QoS que recibió en el mensaje SUBSCRIBE.

|_Código de retorno_|_Descripción_|
|--------|-------------|
|0|Éxito - QoS máximo 0
|1|Éxito - QoS máximo 1
|2|Éxito - QoS máximo 2
|128|Fracaso

### Anular la suscripción
Lo contrario al mensaje de suscripción es el mensaje UNSUBSCRIBE, que elimina las suscripciones existentes de un cliente en el broker. El mensaje es similar al enviado cuando nos suscribimos.
#### Mensaje UNSUBACK
El broker confirma que recibió el mensaje UNSUBSCRIBE enviando al cliente un mensaje tipo UNSUBACK. Éste sólo contiene un identificador de paquete. Luego de ser recibido, el cliente puede asumar que las suscripciones enviadas en el primer mensaje se eliminan.

## Temas en MQTT y mejores prácticas
Un tema (o topic) es una cadena UTF-8 que el broker utiliza para filtrar los mensajes de todos los clientes. Cada tema está jerarquizado y esta jerarquía está denotada por una barra inclinada (/).
Un ejemplo es: **EdificioNorte/PrimerPiso/OficinaIT/Temperatura**
Cada tema debe contener como mínimo un caracter válido. Los temas son Case Sensitive y los temas aceptan espacios.

### Comodines
Cuando un cliente necesita suscribirse a más de un tema correspondientes a un tema de mayor jerarquía, puede hacerlo utilizando **comodines**. Un comodín sólo puede ser utilizado con el fin de suscribirse y no con el de publicar.

#### Comodín de nivel único: +
Un comodín de nivel único es un sustituto de un nivel de tema. Por ejemplo, dada la cadena **EdificioNorte/PrimerPiso/+/Temperatura** vamos a estar suscripto a los siguientes temas:
* **EdificioNorte/PrimerPiso/OficinaGerente/Temperatura**
* **EdificioNorte/PrimerPiso/OficinaComercial/Temperatura**

Pero no a los siguientes temas:

* **EdificioNorte/PrimerPiso/OficinaComercial/Computadora/Temperatura**
* **EdificioNorte/PrimerPiso/OficinaIT/MaquinaCafe/Estado**

#### Comodín de multinivel: \#
Mientras que el comodín de nivel único sólo cubre un nivel de temas, el comodín de nivel múltiple cubre un nivel arbitrario de temas:
**EdificioNorte/PrimerPiso/#**

Vamos a suscribirnos a los siguientes temas:
* **EdificioNorte/PrimerPiso/OficinaIT/Temperatura**
* **EdificioNorte/PrimerPiso/OficinaIT/MaquinaCafe/Estado**
* **EdificioNorte/PrimerPiso/OficinaGerencial/Temperatura**

Pero no a los siguientes temas:
* **EdificioNorte/PlantaBaja/Recepción/Temperatura**

#### Temas que comienzan con $
Cada tema que comienza con el símbolo $ está reservado para las estadísticas internas del broker, por lo que no es posible que los clientes publiquen sobre estos temas.

### Mejores prácticas
* No terminar un tema con barra inclinada. Esto agrega un tema nuevo de caracter cero innecesariamente.
* No utilizar espaciones en un tema.
* Mantener el tema corto y conciso.
* Utilice sólo caracteres ASCII.
* Incluya un ID único en el tema.
* No suscribirse utilizando \#
* Utilizar temas especificos en lugar de generales.

### Mensajes de sesión persistente y cola de espera
#### Sesión persistente
Un cliente debe suscribirse en un broker a todos los temas de los cuales está interesado en recibir mensajes. En una reconexión, estos temas se pierden y el cliente debe enviar nuevamente la información indicada primeramente. Este comportamiento es el esperado en una sesión en una sesión sin persistencia. Ahora, si el cliente tiene recursos escasos sería una carga importante suscribirse cada vez que haya una reconexión.
Una sesión persistente se encarga de guardar toda la información necesaria del cliente en el broker, identificada mediante un *clientId*, que es proporcionado por el cliente al momento de la conexión.

Entonces, **¿Qué se almacenará en la sesión?**
* **Existencia de una sesión**, incluso si no hay suscripciones.
* **Todas las suscripciones.**
* **Todos los mensajes en un flujo de QoS 1 o 2, que no son firmados por el cliente.**
* **Todos los nuevos mensajes QoS 1 o 2 que el cliente perdió mientras se apagó.**
* **Todos los mensajes QoS recibidos, que no fueron confirmados por el cliente**

#### ¿Cómo inicializar/finalizar una sesión persistente?
Una sesión persistente puede ser solicitada por el cliente al momento de pedir una conexión con el broker. El cliente puede controlar si el broker almacena la sesión utilizando el flag cleanSession.

#### ¿Cómo sabe el cliente si ya hay una sesión almacenada?
Desde la versión 3.1.1, el mensaje CONNACK del broker contiene el indicador de sesión actual, que indica al cliente si hay una sesión disponible en el broker.

#### Sesión persistente del lado del cliente.
Al igual que el broker, cada cliente debe almacenar una sesión persistente. Por lo tanto, cuando un cliente solicita al servidor que contenga ciertos datos, también tiene la responsabilidad de mantener alguna información por si mismo.