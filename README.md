# Charla IoT - UTN FRCon 2017

## Introducción
Arduino, Raspberry Pi, PIC, NodeMCU… Así, cientos de herramientas que nos permiten automatizar procesos y tareas que antes teníamos que revisar o hacer de manera manual. Por ejemplo, cargar un tanque de agua que tenemos en nuestra casa respecto a otro. Esto conlleva a que un sistema se comunique con el otro (para saber cuando el tanque 1 necesita agua, pero también si la que necesita está contenida en el tanque 2 para no quemar la bomba). Si lo anterior, a su vez, lo conectamos a otros sistemas de nuestra casa (automatización de luz según la hora o una orden externa dada por nosotros, lavar ropa automaticamente o proporcionar un comedero para nuestras mascotas) a un servidor para poder acceder a esta información a través de internet, nos topamos claramente con el concepto de Internet of Things (IoT, o internet de las cosas). Pero, ¿Qué es IoT? ¿Para qué sirve? ¿Puedo hacerlo yo? ¿Qué puedo utilizar para hacerlo?, ¿Es lo mismo Arduino que Raspberry Pi?. Estas, junto a otras preguntas, son las primeras que comenzamos a hacer cuando investigamos algo respecto al tema, y es sobre lo que nos queremos enfocar tanto en la charla como en los ejemplos (teóricos y prácticos) que vas a encontrar en esta guía.

## Overview
En este repositorio, lo que pretendemos con [juanchip](https://github.com/juanchip), es que tengas una base desde donde comenzar a experimentar con IoT. Vas a encontrar documentación con explicaciones, configuraciones y, por último, algunos ejemplos donde vas a poder entender ciertos conceptos y practicar para crear tus propios proyectos. Esperamos, te sirva y lo disfrutes tanto como nosotros lo hicimos armando el contenido.


## Lista de temas
1. [¿Qué es IoT? Introducción al concepto.](./Teoría/Iot.md)
2. [Arduino vs.  Raspberry Pi / Microcontrolador vs Microprocesador.  ¿Qué es mejor para un proyecto?](./Teoría/RaspberryVsArduino.md)
3. [Desde el lado del servidor: Node.JS. Qué es y qué función cumple en nuestro proyecto.](./Teoría/NodeJS.md)
4. [Comunicación entre el servidor y nuestro Micro: MQTT. Introducción](./Teoría/MQTT.md)
5. [Integrando NodeJS con Arduino: Johnny Five. Qué es y para qué nos sirve. Ventajas y desventajas.](./Teoría/NodeJS-JhonnyFive.md)

## ¿Quienes somos?

![Juan Blanc](https://k61.kn3.net/B/E/1/3/6/C/2DD.png)

### Juan Blanc
> Estudiante de Ingenería Electrónica. Cuando tenía dos años, un destornillador cayó en mis manos y desarmaba absolutamente todo lo que tocaba. Mas adelante, Una Colección de la revista Genios (APC Kids) me guió bastante hasta los 14 Años: A raíz de una infección provocada por un Troyano en mi computadora de aquel entonces, decidí emprender un camino de -Ensayo y Error- en esta área. Actualmente estoy trabajando en uno de los Talleres del Museo de Informática de la República Argentina como Reparador/Programador/Desarrollador de equipos informáticos de todas las épocas.

![Dual Giupponi](https://scontent-eze1-1.xx.fbcdn.net/v/t1.0-9/17951464_10210657098077882_8886991022186783812_n.jpg?oh=97757eec4035a00f053389bf785353fb&oe=5A24C745)

### Dual Giupponi
> Estudiante de Ingeniería eléctrica y Tecnicatura Superior en Programación. Empecé por hobbie en la computadora, confundiendo el gabinete con un decodificador gigante y el teclado como un tipo de control remoto alienígena, y de ahí no paré más. Actualmente trabajo como freelance en la parte de desarrollo de NodeJS y colaboro en proyectos (propios o de terceros) con amigos.
