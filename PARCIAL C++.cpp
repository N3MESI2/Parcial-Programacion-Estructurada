
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

// Estructura para almacenar la información de los libros
struct Book {
    string titulo;
    string autor;
    int year;
    string editorial;
    string isbn;
    int paginas;
    Book* siguiente;
};

// Estructura para gestionar los lectores que solicitan libros
struct Lector {
    string nombre;
    string dni;
    string libroSolicitado;
    Lector* siguiente;
};

// Estructura para el historial de movimientos
struct Movimiento {
    string descripcion;
    Movimiento* siguiente;
};

// Clase Biblioteca para manejar libros, lectores y el historial de movimientos
class Biblioteca {
private:
    Book* listaLibros;
    Lector* listaLectores;
    queue<Lector*> colaLectores;
    stack<Movimiento*> historialMovimientos;

public:
    Biblioteca() : listaLibros(nullptr), listaLectores(nullptr) {}

   void cargarLibros() {
    ifstream archivo("biblioteca.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo biblioteca.txt" << endl;
        return;
    }
    while (!archivo.eof()) {
        Book* nuevoLibro = new Book();
        // Leer los datos y verificar si la lectura fue exitosa
        if (archivo >> nuevoLibro->titulo >> nuevoLibro->autor >> nuevoLibro->year
                    >> nuevoLibro->editorial >> nuevoLibro->isbn >> nuevoLibro->paginas) {
            nuevoLibro->siguiente = listaLibros;
            listaLibros = nuevoLibro;
        } else {
            // Si la lectura falla, eliminamos el objeto nuevoLibro para evitar memoria perdida
            delete nuevoLibro;
            break; // Salimos del ciclo si no se pueden leer más datos
        }
    }
    archivo.close();
    agregarMovimiento("Libros cargados desde archivo");
}
    void guardarLibros() {
        ofstream archivo("biblioteca.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo biblioteca.txt para guardar" << endl;
            return;
        }
        
        Book* actual = listaLibros;
        while (actual != nullptr) {
            archivo << actual->titulo << " " << actual->autor << " " << actual->year << " "
                    << actual->editorial << " " << actual->isbn << " " << actual->paginas << endl;
            actual = actual->siguiente;
        }
        
        archivo.close();
        agregarMovimiento("Libros guardados en archivo");
    }

    void agregarLibro() {
        Book* nuevoLibro = new Book();
        cout << "Ingrese el título del libro: ";
        cin >> nuevoLibro->titulo;
        cout << "Ingrese el autor del libro: ";
        cin >> nuevoLibro->autor;
        cout << "Ingrese el año de edición: ";
        cin >> nuevoLibro->year;
        cout << "Ingrese la editorial: ";
        cin >> nuevoLibro->editorial;
        cout << "Ingrese el ISBN: ";
        cin >> nuevoLibro->isbn;
        cout << "Ingrese el número de páginas: ";
        cin >> nuevoLibro->paginas;

        nuevoLibro->siguiente = listaLibros;
        listaLibros = nuevoLibro;
        agregarMovimiento("Libro agregado: " + nuevoLibro->titulo);
    }

    void mostrarLibros() {
        if (listaLibros == nullptr) {
            cout << "No hay libros en la biblioteca." << endl;
            return;
        }
        
        Book* actual = listaLibros;
        while (actual != nullptr) {
            cout << "Título: " << actual->titulo << ", Autor: " << actual->autor 
                 << ", Año: " << actual->year << ", Editorial: " << actual->editorial 
                 << ", ISBN: " << actual->isbn << ", Páginas: " << actual->paginas << endl;
            actual = actual->siguiente;
        }
    }

    void solicitarLibro() {
        Lector* nuevoLector = new Lector();
        cout << "Ingrese el nombre del lector: ";
        cin >> nuevoLector->nombre;
        cout << "Ingrese el DNI del lector: ";
        cin >> nuevoLector->dni;
        cout << "Ingrese el título del libro que desea solicitar: ";
        cin >> nuevoLector->libroSolicitado;

        nuevoLector->siguiente = listaLectores;
        listaLectores = nuevoLector;
        colaLectores.push(nuevoLector);
        agregarMovimiento("Solicitud de préstamo: " + nuevoLector->nombre + " solicitó " + nuevoLector->libroSolicitado);
    }

    void devolverLibro() {
        if (colaLectores.empty()) {
            cout << "No hay solicitudes pendientes." << endl;
            return;
        }
        
        Lector* lector = colaLectores.front();
        colaLectores.pop();
        cout << "Libro devuelto: " << lector->libroSolicitado 
             << " solicitado por " << lector->nombre << endl;
        agregarMovimiento("Libro devuelto: " + lector->libroSolicitado + " por " + lector->nombre);
    }

    void mostrarLectores() {
        if (listaLectores == nullptr) {
            cout << "No hay lectores que hayan solicitado libros." << endl;
            return;
        }

        Lector* actual = listaLectores;
        while (actual != nullptr) {
            cout << "Nombre: " << actual->nombre << ", DNI: " << actual->dni 
                 << ", Libro solicitado: " << actual->libroSolicitado << endl;
            actual = actual->siguiente;
        }
    }

    void mostrarHistorial() {
        if (historialMovimientos.empty()) {
            cout << "No hay movimientos en el historial." << endl;
            return;
        }
        
        stack<Movimiento*> temp = historialMovimientos;
        cout << "Historial de movimientos:" << endl;
        while (!temp.empty()) {
            Movimiento* mov = temp.top();
            cout << mov->descripcion << endl;
            temp.pop();
        }
    }

    // Función para agregar un movimiento al historial
    void agregarMovimiento(const string& descripcion) {
        Movimiento* nuevoMovimiento = new Movimiento();
        nuevoMovimiento->descripcion = descripcion;
        historialMovimientos.push(nuevoMovimiento);
    }

    ~Biblioteca() {
        while (listaLibros != nullptr) {
            Book* temp = listaLibros;
            listaLibros = listaLibros->siguiente;
            delete temp;
        }
        while (listaLectores != nullptr) {
            Lector* temp = listaLectores;
            listaLectores = listaLectores->siguiente;
            delete temp;
        }
        while (!historialMovimientos.empty()) {
            Movimiento* temp = historialMovimientos.top();
            historialMovimientos.pop();
            delete temp;
        }
    }
};

void mostrarMenu() {
    cout << "\nSistema de Gestión de Biblioteca Digital" << endl;
    cout << "1. Cargar libros desde archivo" << endl;
    cout << "2. Guardar libros en archivo" << endl;
    cout << "3. Agregar un libro nuevo" << endl;
    cout << "4. Mostrar todos los libros" << endl;
    cout << "5. Solicitar un libro" << endl;
    cout << "6. Devolver un libro" << endl;
    cout << "7. Mostrar lectores que solicitaron libros" << endl;
    cout << "8. Mostrar historial de movimientos" << endl;
    cout << "9. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    Biblioteca biblioteca;
    int opcion;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                biblioteca.cargarLibros();
                break;
            case 2:
                biblioteca.guardarLibros();
                break;
            case 3:
                biblioteca.agregarLibro();
                break;
            case 4:
                biblioteca.mostrarLibros();
                break;
            case 5:
                biblioteca.solicitarLibro();
                break;
            case 6:
                biblioteca.devolverLibro();
                break;
            case 7:
                biblioteca.mostrarLectores();
                break;
            case 8:
                biblioteca.mostrarHistorial();
                break;
            case 9:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 9);
    
    return 0;
}
