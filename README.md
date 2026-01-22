SISTEMA DE GESTION DE BIBLIOTECA DIGITAL

DESCRIPCION
Este proyecto implementa un Sistema de Gestion de Biblioteca Digital desarrollado en Python.
Permite administrar libros, solicitudes de lectores y un historial de movimientos utilizando
estructuras de datos dinamicas como listas enlazadas, colas y archivos de texto para la
persistencia de datos.

El sistema funciona mediante un menu interactivo por consola y esta orientado a fines
educativos, reforzando conceptos como manejo de archivos, estructuras de datos y
programacion orientada a objetos.

FUNCIONALIDADES

El sistema permite:

Cargar libros desde un archivo de texto (biblioteca.txt)

Guardar libros en un archivo de texto

Agregar nuevos libros manualmente

Mostrar todos los libros registrados

Registrar solicitudes de prestamo de libros

Gestionar devoluciones de libros utilizando una cola (FIFO)

Mostrar lectores que han solicitado libros

Consultar el historial de movimientos del sistema

ESTRUCTURA DEL PROYECTO

El sistema esta compuesto por las siguientes clases:

Clase Book
Representa un libro dentro de la biblioteca.
Atributos: titulo, autor, anio, editorial, ISBN, paginas.
Cada libro funciona como un nodo dentro de una lista enlazada.

Clase Lector
Representa a un lector que solicita un libro.
Atributos: nombre, DNI, libro solicitado.
Se utiliza tanto en una lista enlazada como en una cola de solicitudes.

Clase Movimiento
Representa una accion realizada dentro del sistema.
Atributo: descripcion del movimiento.
Se almacena en un historial de movimientos.

Clase Biblioteca
Clase principal del sistema. Gestiona:

Lista enlazada de libros

Lista enlazada de lectores

Cola de solicitudes de libros

Historial de movimientos

REQUISITOS

Python 3.8 o superior

Sistema operativo con acceso a consola

Archivo de texto biblioteca.txt (opcional para carga inicial)

No se requieren librerias externas. Solo se utilizan modulos estandar de Python
(os y collections).

FORMATO DEL ARCHIVO biblioteca.txt

Cada linea del archivo debe contener los datos de un libro separados por espacios,
en el siguiente orden:

titulo autor anio editorial isbn paginas

Ejemplo:
CleanCode Martin 2008 PrenticeHall 9780132350884 464

Importante:
Los campos no deben contener espacios internos.

USO DEL SISTEMA

Ejecutar el programa desde la consola:
python main.py

Seleccionar una opcion del menu:

Cargar libros desde archivo

Guardar libros en archivo

Agregar un libro nuevo

Mostrar todos los libros

Solicitar un libro

Devolver un libro

Mostrar lectores que solicitaron libros

Mostrar historial de movimientos

Salir

Ingresar los datos solicitados segun la opcion elegida.

CONSIDERACIONES TECNICAS

Los libros se almacenan en memoria mediante listas enlazadas.

Las solicitudes de prestamo se gestionan con una cola para respetar el orden de atencion.

El historial de movimientos se guarda en una lista y se muestra del mas reciente al mas antiguo.

El sistema no valida duplicados de libros ni controla disponibilidad de ejemplares.

![6abbd5ff-2c86-4357-9185-383308649537](https://github.com/user-attachments/assets/c9777302-ae6b-42ad-9173-e94f105c4555)
