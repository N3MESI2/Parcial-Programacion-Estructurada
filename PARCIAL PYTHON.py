import os
from collections import deque

# Estructura para almacenar la información de los libros
class Book:
    def __init__(self, titulo, autor, year, editorial, isbn, paginas):
        self.titulo = titulo
        self.autor = autor
        self.year = year
        self.editorial = editorial
        self.isbn = isbn
        self.paginas = paginas
        self.siguiente = None


# Estructura para gestionar los lectores que solicitan libros
class Lector:
    def __init__(self, nombre, dni, libroSolicitado):
        self.nombre = nombre
        self.dni = dni
        self.libroSolicitado = libroSolicitado
        self.siguiente = None


# Estructura para el historial de movimientos
class Movimiento:
    def __init__(self, descripcion):
        self.descripcion = descripcion
        self.siguiente = None


# Clase Biblioteca para manejar libros, lectores y el historial de movimientos
class Biblioteca:
    def __init__(self):
        self.listaLibros = None
        self.listaLectores = None
        self.colaLectores = deque()
        self.historialMovimientos = []

  # Método para borrar la lista de libros
    def borrarLibros(self):
        self.listaLibros = None
        self.agregarMovimiento("Lista de libros borrada")
        print("La lista de libros ha sido borrada.")
    def cargarLibros(self):
        self.borrarLibros()        
        if not os.path.isfile("biblioteca.txt"):
            print("No se pudo abrir el archivo biblioteca.txt")
            return
        
        with open("biblioteca.txt", "r") as archivo:
            for line in archivo:
                datos = line.strip().split()
                if len(datos) == 6:
                    titulo, autor, year, editorial, isbn, paginas = datos
                    nuevoLibro = Book(titulo, autor, int(year), editorial, isbn, int(paginas))
                    nuevoLibro.siguiente = self.listaLibros
                    self.listaLibros = nuevoLibro
        
        self.agregarMovimiento("Libros cargados desde archivo")

    def guardarLibros(self):
        with open("biblioteca.txt", "w") as archivo:
            actual = self.listaLibros
            while actual:
                archivo.write(f"{actual.titulo} {actual.autor} {actual.year} "
                              f"{actual.editorial} {actual.isbn} {actual.paginas}\n")
                actual = actual.siguiente
        
        self.agregarMovimiento("Libros guardados en archivo")

    def agregarLibro(self):
        titulo = input("Ingrese el título del libro: ")
        autor = input("Ingrese el autor del libro: ")
        year = int(input("Ingrese el año de edición: "))
        editorial = input("Ingrese la editorial: ")
        isbn = input("Ingrese el ISBN: ")
        paginas = int(input("Ingrese el número de páginas: "))
        
        nuevoLibro = Book(titulo, autor, year, editorial, isbn, paginas)
        nuevoLibro.siguiente = self.listaLibros
        self.listaLibros = nuevoLibro
        self.agregarMovimiento(f"Libro agregado: {titulo}")

    def mostrarLibros(self):
        if not self.listaLibros:
            print("No hay libros en la biblioteca.")
            return
        
        actual = self.listaLibros
        while actual:
            print(f"Título: {actual.titulo}, Autor: {actual.autor}, Año: {actual.year}, "
                  f"Editorial: {actual.editorial}, ISBN: {actual.isbn}, Páginas: {actual.paginas}")
            actual = actual.siguiente

    def solicitarLibro(self):
        nombre = input("Ingrese el nombre del lector: ")
        dni = input("Ingrese el DNI del lector: ")
        libroSolicitado = input("Ingrese el título del libro que desea solicitar: ")
        
        nuevoLector = Lector(nombre, dni, libroSolicitado)
        nuevoLector.siguiente = self.listaLectores
        self.listaLectores = nuevoLector
        self.colaLectores.append(nuevoLector)
        self.agregarMovimiento(f"Solicitud de préstamo: {nombre} solicitó {libroSolicitado}")

    def devolverLibro(self):
        if not self.colaLectores:
            print("No hay solicitudes pendientes.")
            return
        
        lector = self.colaLectores.popleft()
        print(f"Libro devuelto: {lector.libroSolicitado} solicitado por {lector.nombre}")
        self.agregarMovimiento(f"Libro devuelto: {lector.libroSolicitado} por {lector.nombre}")

    def mostrarLectores(self):
        if not self.listaLectores:
            print("No hay lectores que hayan solicitado libros.")
            return

        actual = self.listaLectores
        while actual:
            print(f"Nombre: {actual.nombre}, DNI: {actual.dni}, Libro solicitado: {actual.libroSolicitado}")
            actual = actual.siguiente

    def mostrarHistorial(self):
        if not self.historialMovimientos:
            print("No hay movimientos en el historial.")
            return
        
        print("Historial de movimientos:")
        for movimiento in reversed(self.historialMovimientos):
            print(movimiento.descripcion)

    # Función para agregar un movimiento al historial
    def agregarMovimiento(self, descripcion):
        nuevoMovimiento = Movimiento(descripcion)
        self.historialMovimientos.append(nuevoMovimiento)

    def __del__(self):
        self.listaLibros = None
        self.listaLectores = None
        self.historialMovimientos = []


def mostrarMenu():
    print("\nSistema de Gestión de Biblioteca Digital")
    print("1. Cargar libros desde archivo")
    print("2. Guardar libros en archivo")
    print("3. Agregar un libro nuevo")
    print("4. Mostrar todos los libros")
    print("5. Solicitar un libro")
    print("6. Devolver un libro")
    print("7. Mostrar lectores que solicitaron libros")
    print("8. Mostrar historial de movimientos")
    print("9. Salir")
    return int(input("Seleccione una opción: "))


def main():
    biblioteca = Biblioteca()
    while True:
        opcion = mostrarMenu()
        if opcion == 1:
            biblioteca.cargarLibros()
        elif opcion == 2:
            biblioteca.guardarLibros()
        elif opcion == 3:
            biblioteca.agregarLibro()
        elif opcion == 4:
            biblioteca.mostrarLibros()
        elif opcion == 5:
            biblioteca.solicitarLibro()
        elif opcion == 6:
            biblioteca.devolverLibro()
        elif opcion == 7:
            biblioteca.mostrarLectores()
        elif opcion == 8:
            biblioteca.mostrarHistorial()
        elif opcion == 9:
            print("Saliendo del sistema...")
            break
        else:
            print("Opción no válida. Intente de nuevo.")

if __name__ == "__main__":
    main()
