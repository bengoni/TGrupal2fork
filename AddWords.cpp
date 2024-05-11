#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

using namespace std;

// Estructura para almacenar una entrada de traducci�n
struct Traduccion {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Funci�n para cargar las traducciones desde el archivo
Traduccion* cargarTraducciones(int& cantidadTraducciones) {
    ifstream archivo("traducciones.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de traducciones." << endl;
        cantidadTraducciones = 0;
        return NULL;
    }
    cantidadTraducciones = 0;
    string palabra, traduccion, funcionalidad;
    while (archivo >> palabra >> traduccion) {
        getline(archivo, funcionalidad);
        cantidadTraducciones++;
    }
    archivo.close();

    Traduccion* traducciones = new Traduccion[cantidadTraducciones];
    ifstream archivo2("traducciones.txt");
    for (int i = 0; i < cantidadTraducciones; ++i) {
        archivo2 >> traducciones[i].palabra >> traducciones[i].traduccion;
        getline(archivo2, traducciones[i].funcionalidad);
    }
    archivo2.close();

    return traducciones;
}

// Funci�n para guardar las traducciones en el archivo
void guardarTraducciones(const Traduccion* traducciones, int cantidadTraducciones) {
    ofstream archivo("traducciones.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de traducciones." << endl;
        return;
    }
    for (int i = 0; i < cantidadTraducciones; ++i) {
        archivo << traducciones[i].palabra << " " << traducciones[i].traduccion << " " << traducciones[i].funcionalidad << endl;
    }
    archivo.close();
}

// Funci�n para a�adir una nueva traducci�n
void crearTraduccion(Traduccion*& traducciones, int& cantidadTraducciones) {
    Traduccion nueva;
    cout << "Ingrese la palabra en ingl�s: ";
    cin >> nueva.palabra;
    cout << "Ingrese la traducci�n al espa�ol: ";
    cin >> nueva.traduccion;
    cin.ignore(); // Limpiar el buffer del teclado
    cout << "Ingrese la funcionalidad: ";
    getline(cin, nueva.funcionalidad);

    // A�adir la nueva traducci�n al arreglo
    Traduccion* nuevoArreglo = new Traduccion[cantidadTraducciones + 1];
    for (int i = 0; i < cantidadTraducciones; ++i) {
        nuevoArreglo[i] = traducciones[i];
    }
    nuevoArreglo[cantidadTraducciones] = nueva;

    delete[] traducciones;
    traducciones = nuevoArreglo;
    cantidadTraducciones++;

    // Guardar las traducciones en el archivo
    guardarTraducciones(traducciones, cantidadTraducciones);

    cout << "La traducci�n ha sido agregada correctamente." << endl;
}

// Funci�n para mostrar todas las traducciones
void mostrarTraducciones(const Traduccion* traducciones, int cantidadTraducciones) {
    if (cantidadTraducciones == 0) {
        cout << "No hay traducciones para mostrar." << endl;
        return;
    }
    cout << "Traducciones:" << endl;
    for (int i = 0; i < cantidadTraducciones; ++i) {
        cout << "Palabra en ingl�s: " << traducciones[i].palabra << endl;
        cout << "Traducci�n al espa�ol: " << traducciones[i].traduccion << endl;
        cout << "Funcionalidad: " << traducciones[i].funcionalidad << endl << endl;
    }
}

// Funci�n para actualizar una traducci�n existente
void actualizarTraduccion(Traduccion*& traducciones, int cantidadTraducciones) {
    string palabra;
    cout << "Ingrese la palabra en ingl�s que desea actualizar: ";
    cin >> palabra;
    int indice = -1;
    for (int i = 0; i < cantidadTraducciones; ++i) {
        if (traducciones[i].palabra == palabra) {
            indice = i;
            break;
        }
    }
    if (indice != -1) {
        cout << "Ingrese la nueva traducci�n al espa�ol: ";
        cin >> traducciones[indice].traduccion;
        cin.ignore(); // Limpiar el buffer del teclado
        cout << "Ingrese la nueva funcionalidad: ";
        getline(cin, traducciones[indice].funcionalidad);
        guardarTraducciones(traducciones, cantidadTraducciones);
        cout << "La traducci�n ha sido actualizada correctamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

// Funci�n para borrar una traducci�n existente
void borrarTraduccion(Traduccion*& traducciones, int& cantidadTraducciones) {
    string palabra;
    cout << "Ingrese la palabra en ingl�s que desea borrar: ";
    cin >> palabra;
    int indice = -1;
    for (int i = 0; i < cantidadTraducciones; ++i) {
        if (traducciones[i].palabra == palabra) {
            indice = i;
            break;
        }
    }
    if (indice != -1) {
        Traduccion* nuevoArreglo = new Traduccion[cantidadTraducciones - 1];
        for (int i = 0, j = 0; i < cantidadTraducciones; ++i) {
            if (i != indice) {
                nuevoArreglo[j++] = traducciones[i];
            }
        }
        delete[] traducciones;
        traducciones = nuevoArreglo;
        cantidadTraducciones--;

        guardarTraducciones(traducciones, cantidadTraducciones);
        cout << "La traducci�n ha sido borrada correctamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

int main() {
	setlocale(LC_ALL, "");
    int cantidadTraducciones;
    Traduccion* traducciones = cargarTraducciones(cantidadTraducciones);

    int opcion;
    do {
        cout << "Men�:" << endl;
        cout << "1. Crear traducci�n" << endl;
        cout << "2. Mostrar traducciones" << endl;
        cout << "3. Actualizar traducci�n" << endl;
        cout << "4. Borrar traducci�n" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        //Limpia pantalla luego de seleccion
        system("cls");
        
        // llamamos los constructores de cada opcion a elegir
        switch (opcion) {
            case 1:
                crearTraduccion(traducciones, cantidadTraducciones);
                break;
            case 2:
                mostrarTraducciones(traducciones, cantidadTraducciones);
                break;
            case 3:
                actualizarTraduccion(traducciones, cantidadTraducciones);
                break;
            case 4:
                borrarTraduccion(traducciones, cantidadTraducciones);
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opci�n inv�lida. Int�ntelo de nuevo." << endl;
        }
    } while (opcion != 5);

    delete[] traducciones;

    return 0;
}

