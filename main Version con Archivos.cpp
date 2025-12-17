#include <iostream>
#include <vector>
#include <fstream> // Libreria para manejo de archivos

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
const string NOMBRE_ARCHIVO = "biblioteca.txt";

// Funciones auxiliares para archivos
void guardarDatos() {
    ofstream archivo(NOMBRE_ARCHIVO);
    if (archivo.is_open()) {
        for (size_t i = 0; i < biblioteca.size(); i++) {
            archivo << biblioteca[i].id << endl;
            archivo << biblioteca[i].titulo << endl;
            archivo << biblioteca[i].autor << endl;
            archivo << biblioteca[i].prestado << endl;
            archivo << biblioteca[i].fechaPrestamo.dia << " "
                    << biblioteca[i].fechaPrestamo.mes << " "
                    << biblioteca[i].fechaPrestamo.anio << endl;
            archivo << biblioteca[i].fechaDevolucion.dia << " "
                    << biblioteca[i].fechaDevolucion.mes << " "
                    << biblioteca[i].fechaDevolucion.anio << endl;
        }
        archivo.close();
        // cout << "Datos guardados correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo para guardar." << endl;
    }
}

void cargarDatos() {
    ifstream archivo(NOMBRE_ARCHIVO);
    if (archivo.is_open()) {
        Libro libroTemp;
        // El bucle verifica si se pudo leer el ID correctamente antes de continuar
        while (archivo >> libroTemp.id) {
            archivo.ignore(); // Limpiar el salto de linea despues del ID
            getline(archivo, libroTemp.titulo);
            getline(archivo, libroTemp.autor);
            archivo >> libroTemp.prestado;
            archivo >> libroTemp.fechaPrestamo.dia >> libroTemp.fechaPrestamo.mes >> libroTemp.fechaPrestamo.anio;
            archivo >> libroTemp.fechaDevolucion.dia >> libroTemp.fechaDevolucion.mes >> libroTemp.fechaDevolucion.anio;

            biblioteca.push_back(libroTemp);
        }
        archivo.close();
        cout << "Datos cargados exitosamente. " << biblioteca.size() << " libros en memoria." << endl;
    } else {
        cout << "No se encontro archivo de datos previo. Se iniciara una biblioteca vacia." << endl;
    }
}

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
    guardarDatos(); // Guardar cambios
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
                guardarDatos(); // Guardar cambios
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
                guardarDatos(); // Guardar cambios
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
    // Cargar datos al inicio
    cargarDatos();

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
