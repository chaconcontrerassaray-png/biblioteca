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
                 << " | Estado: " << (biblioteca[i].prestado ? "PRESTADO" : "DISPONIBLE") << endl;
        }
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
                cout << ">> Opcion 'Eliminar libro' aun no implementada." << endl;
                break;
            case 4:
                cout << ">> Opcion 'Prestamo de libros' aun no implementada." << endl;
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
