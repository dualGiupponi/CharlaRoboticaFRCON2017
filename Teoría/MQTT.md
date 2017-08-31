#### [Volver al menú principal](../README.md)
# MQTT

<!-- TOC -->

- [MQTT](#mqtt)
    - [Overview](#overview)
    - [Introducción](#introducción)

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
