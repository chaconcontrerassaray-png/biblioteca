#include <iostream>
#include <vector>

using namespace std;

// Estructura para manejar fechas
struct Fecha {
    int dia;
    int mes;
    int anio;
};

// Estructura para representar un libro
struct Libro {
    int id;
    string titulo;
    string autor;
    bool prestado;
    Fecha fechaPrestamo;
    Fecha fechaDevolucion;
};

// Variables globales
vector<Libro> biblioteca;
Fecha fechaActual;

// Funcion para pedir la fecha actual al arrancar el programa
void pedirFechaActual() {
    cout << "=== BIENVENIDO AL SISTEMA DE BIBLIOTECA ===" << endl;
    cout << "Por favor, configure la fecha actual." << endl;
    cout << "Dia: "; cin >> fechaActual.dia;
    cout << "Mes: "; cin >> fechaActual.mes;
    cout << "Anio: "; cin >> fechaActual.anio;
}

// Funcion para registrar un nuevo libro
void registrarLibro() {
    Libro nuevoLibro;
    cout << "\n--- REGISTRAR LIBRO ---" << endl;
    cout << "ID del libro: ";
    cin >> nuevoLibro.id;
    cin.ignore(); // Limpiar el buffer de entrada antes de usar getline
    cout << "Titulo: ";
    getline(cin, nuevoLibro.titulo);
    cout << "Autor: ";
    getline(cin, nuevoLibro.autor);

    nuevoLibro.prestado = false;
    nuevoLibro.fechaPrestamo = {0, 0, 0};
    nuevoLibro.fechaDevolucion = {0, 0, 0};

    biblioteca.push_back(nuevoLibro);
    cout << "Libro registrado exitosamente." << endl;
}

// Funcion para listar los libros
void listarLibros() {
    cout << "\n--- LISTA DE LIBROS ---" << endl;
    if (biblioteca.empty()) {
        cout << "No hay libros registrados en la biblioteca." << endl;
    } else {
        for (size_t i = 0; i < biblioteca.size(); i++) {
            cout << "ID: " << biblioteca[i].id
                 << " | Titulo: " << biblioteca[i].titulo
                 << " | Autor: " << biblioteca[i].autor
                 << " | Estado: " << (biblioteca[i].prestado ? "PRESTADO" : "DISPONIBLE");

            if (biblioteca[i].prestado) {
                cout << " (Devolver el: " << biblioteca[i].fechaDevolucion.dia << "/"
                     << biblioteca[i].fechaDevolucion.mes << "/" << biblioteca[i].fechaDevolucion.anio << ")";
            }
            cout << endl;
        }
    }
}

// Funcion para eliminar un libro
void eliminarLibro() {
    cout << "\n--- ELIMINAR LIBRO ---" << endl;
    if (biblioteca.empty()) {
        cout << "No hay libros para eliminar." << endl;
        return;
    }

    int idEliminar;
    cout << "Ingrese el ID del libro a eliminar: ";
    cin >> idEliminar;

    bool encontrado = false;
    for (size_t i = 0; i < biblioteca.size(); i++) {
        if (biblioteca[i].id == idEliminar) {
            if (biblioteca[i].prestado) {
                cout << "No se puede eliminar el libro porque esta prestado." << endl;
            } else {
                biblioteca.erase(biblioteca.begin() + i);
                cout << "Libro eliminado exitosamente." << endl;
            }
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Libro con ID " << idEliminar << " no encontrado." << endl;
    }
}

// Funcion para realizar el prestamo de libros
void prestarLibro() {
    cout << "\n--- PRESTAMO DE LIBROS ---" << endl;
    if (biblioteca.empty()) {
        cout << "No hay libros en la biblioteca." << endl;
        return;
    }

    int idPrestar;
    cout << "Ingrese el ID del libro a prestar: ";
    cin >> idPrestar;

    bool encontrado = false;
    for (size_t i = 0; i < biblioteca.size(); i++) {
        if (biblioteca[i].id == idPrestar) {
            encontrado = true;
            if (biblioteca[i].prestado) {
                cout << "El libro ya se encuentra prestado." << endl;
            } else {
                // Registrar fecha de prestamo (fecha actual)
                biblioteca[i].fechaPrestamo = fechaActual;

                // Pedir fecha de devolucion
                cout << "La fecha de prestamo es hoy: " << fechaActual.dia << "/" << fechaActual.mes << "/" << fechaActual.anio << endl;
                cout << "Ingrese la fecha de devolucion:" << endl;
                cout << "Dia: "; cin >> biblioteca[i].fechaDevolucion.dia;
                cout << "Mes: "; cin >> biblioteca[i].fechaDevolucion.mes;
                cout << "Anio: "; cin >> biblioteca[i].fechaDevolucion.anio;

                biblioteca[i].prestado = true;
                cout << "Prestamo registrado exitosamente." << endl;
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "Libro con ID " << idPrestar << " no encontrado." << endl;
    }
}

// Funcion para mostrar el menu de opciones
void mostrarMenu() {
    cout << "\n--- MENU PRINCIPAL ---" << endl;
    cout << "1. Listar libros" << endl;
    cout << "2. Registrar libro" << endl;
    cout << "3. Eliminar libro" << endl;
    cout << "4. Prestamo de libros" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    pedirFechaActual();

    int opcion = 0;
    while (opcion != 5) {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                listarLibros();
                break;
            case 2:
                registrarLibro();
                break;
            case 3:
                eliminarLibro();
                break;
            case 4:
                prestarLibro();
                break;
            case 5:
                cout << "Gracias por usar el sistema." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    }
    return 0;
}
