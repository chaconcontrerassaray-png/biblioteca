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
                cout << ">> Opcion 'Listar libros' aun no implementada." << endl;
                break;
            case 2:
                cout << ">> Opcion 'Registrar libro' aun no implementada." << endl;
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
