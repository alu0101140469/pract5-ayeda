#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "nif.hpp"
#include "Sequence.hpp"
#include "SortMethods.hpp"

using namespace std;

// Daniel Palenzuela Álvarez alu0101140469

// MODIF:
// Cambiar objeto key de nif a persona con 3 tipos de ID (alu, prof, pas) seguido 
// de 7 números y la key debe guardar nombre, apellido1 y apellido2
// alu/prof/pas pueden repetirse en numeros, los diferenciará las letras (alu, prof y pas los clasifica)
// Ejemplo: Key { ID: alu0001345, prof0001234, pas0001234 }
// Generar por salida una tabla con las comparaciones de los intercambios con todos los metodos desordenados
// En comentarios de entrega copiar la tabla y explicar que cambios he hecho y que me faltó

// Función que imprime el uso correcto del programa en consola.
void printUsage(char* progName) {
    cout << "  Programa de algoritmos de ordenación con PERSONA\n";
    cout << "Instrucciones:\n";
    cout << "  " << progName << " -size <s> -ord <m> -init <i> [f] -trace <y|n>\n";
    cout << "Opciones:\n";
    cout << "  -size <s>   Tamaño de la secuencia.\n";
    cout << "  -ord <m>    Método de ordenación:\n";
    cout << "                1 -> Inserción\n";
    cout << "                2 -> Sacudida\n";
    cout << "                3 -> QuickSort\n";
    cout << "                4 -> HeapSort\n";
    cout << "                5 -> ShellSort\n";
    cout << "  -init <i> [f]  Forma de inicializar la secuencia:\n";
    cout << "                manual   -> Introduce los datos por teclado.\n";
    cout << "                random   -> Genera datos aleatorios.\n";
    cout << "                file     -> Lee los datos de un fichero (se debe especificar el nombre del fichero f)\n";
    cout << "  -trace <y|n>   Mostrar sí (y) o no (n) la traza de la ordenación.\n";
    cout << "  --help         Muestra este mensaje de ayuda.\n";
}

int main(int argc, char* argv[]) {
    // Mostrar la guía con el comando --help y finaliza
    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        printUsage(argv[0]);
        return 0;
    }

    // Se comprueba que se han pasado al menos los parámetros mínimos.
    if(argc < 7) {
        printUsage(argv[0]);
        return 1;
    }
    
    unsigned size = 0;      // Tamaño de la secuencia
    int ord = 0;            // Código del método de ordenación
    string initMode = "";   // Modo de inicialización (manual, random o file)
    string fileName = "";   // Nombre del fichero en caso de usar el modo file
    bool trace = false;     // Para determinar si se imprimirá la traza

    // Se procesan los parámetros de la línea de comandos.
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-size") == 0 && i+1 < argc) {
            // Convierte el siguiente argumento a número entero.
            size = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-ord") == 0 && i+1 < argc) {
            // Selecciona el método de ordenación.
            ord = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-init") == 0 && i+1 < argc) {
            // Determina el modo de inicialización.
            initMode = argv[++i];
            // Si el modo es file, el siguiente argumento es el nombre del fichero.
            if(initMode == "file" && i+1 < argc) {
                fileName = argv[++i];
            }
        } else if(strcmp(argv[i], "-trace") == 0 && i+1 < argc) {
            // Configura la opción de traza (la impresión intermedia de la secuencia).
            string t = argv[++i];
            trace = (t == "y" || t == "Y");
        }
    }
    
    // Validación de parámetros mínimos.
    if(size == 0 || ord < 1 || ord > 5 || initMode == "") {
        printUsage(argv[0]);
        return 1;
    }
    
    // Se crea la secuencia de elementos tipo nif, con tamaño size.
    staticSequence<persona> seq(size);
    
    // Inicializa la secuencia según el modo especificado.
    if(initMode == "manual") {
        cout << "Introduce la información de " << size << " personas:\n";
        for (unsigned i = 0; i < size; i++) {
            string tipo, nombre, apellido1, apellido2;
            string numStr;
            int num;
            cout << "Persona " << i+1 << ":\n";
            cout << "  Tipo de ID (alu, prof o pas): ";
            cin >> tipo;
            cout << "  Número de 7 dígitos: ";
            cin >> numStr;
            // Se valida que el número tenga exactamente 7 dígitos.
            if(numStr.length() != 7) {
                cerr << "Error: Debe introducir 7 dígitos. Se ha introducido \"" 
                     << numStr << "\"\n";
                exit(1);
            }
            // Convertir la cadena a entero.
            num = stoi(numStr);
            cout << "  Nombre: ";
            cin >> nombre;
            cout << "  Apellido1: ";
            cin >> apellido1;
            cout << "  Apellido2: ";
            cin >> apellido2;
            // Se asigna el valor al elemento i de la secuencia.
            seq[i] = persona(tipo, num, nombre, apellido1, apellido2);
        }
    } else if(initMode == "random") {
        // Se rellenan los elementos utilizando datos aleatorios
        string tipos[3] = {"alu", "prof", "pas"};
        for (unsigned i = 0; i < size; i++) {
            string tipo = tipos[rand() % 3];
            int num = 1000000 + rand() % 9000000; // Número de 7 dígitos
            seq[i] = persona(tipo, num, "Nombre", "Apellido1", "Apellido2");
        }
    } else if(initMode == "file") {
        // Inicialización desde fichero.
        if(fileName == "") {
            cout << "No se especificó fichero para la inicialización.\n";
            return 1;
        }
        ifstream infile(fileName);
        if (!infile) {
            cout << "No se pudo abrir el fichero " << fileName << "\n";
            return 1;
        }
        string id, nombre, apellido1, apellido2; // los datos del fichero
        unsigned count = 0;
        // Lee los datos del fichero hasta llenar la secuencia o agotar el fichero
        while(infile >> id >> nombre >> apellido1 >> apellido2 && count < size) {
            // Extraer el tipo y la parte numérica
            string tipo = "";
            for (char c : id) {
                if(isalpha(c))
                    tipo.push_back(c);
                else
                    break;
            }
            // La parte numérica se extrae a partir del tamaño del prefijo
            string numStr = id.substr(tipo.size());
            // Compruebo que el número tenga 7 dígitos
            if(numStr.length() != 7) {
                cerr << "Error: El ID '" << id << "' no contiene 7 dígitos.\n";
                exit(1);
            }
            int num = stoi(numStr);
            seq[count] = persona(tipo, num, nombre, apellido1, apellido2);
            count++;
        }
        if(count < size) {
            cout << "El fichero no contiene suficientes datos. Se han leído " << count << " registros.\n";
            return 1;
        }
        infile.close();
    } else {
        cout << "Modo de inicialización no reconocido.\n";
        printUsage(argv[0]);
        return 1;
    }
    
    // Muestra la secuencia original antes de ordenar.
    cout << "\nSecuencia original:\n";
    seq.print();
    
    // Selecciona e instancia el método de ordenación correspondiente.
    SortMethod<persona>* sortMethod = nullptr;
    if (ord == 5) {  // ShellSort requiere el parámetro alfa.
        double alfa = 0.0;
        cout << "Introduce el factor de reducción alfa (0 < alfa < 1): ";
        cin >> alfa;
        if(alfa <= 0 || alfa >= 1) {
            cout << "Valor de alfa no válido.\n";
            return 1;
        }
        sortMethod = new ShellSortMethod<persona>(&seq, trace, alfa);
    } else if(ord == 1) {
        sortMethod = new InsertionSortMethod<persona>(&seq, trace);
    } else if(ord == 2) {
        sortMethod = new ShakeSortMethod<persona>(&seq, trace);
    } else if(ord == 3) {
        sortMethod = new QuickSortMethod<persona>(&seq, trace);
    } else if(ord == 4) {
        sortMethod = new HeapSortMethod<persona>(&seq, trace);
    } else {
        cout << "Código de método de ordenación no reconocido.\n";
        return 1;
    }
    
    // Ejecuta el método de ordenación.
    cout << "\nOrdenando la secuencia...\n";
    sortMethod->Sort();
    
    // Muestra el resultado final tras la ordenación.
    cout << "\nSecuencia ordenada:\n";
    seq.print();
    
    // Libera la memoria dinámica utilizada para el método de ordenación.
    delete sortMethod;
    return 0;
}