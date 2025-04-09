#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Persona.hpp"      // Define la clase persona (ID + nombre y apellidos)
#include "Sequence.hpp"     // Define la interfaz Sequence y la implementación staticSequence
#include "SortMethods.hpp"  // Define la jerarquía de clases de ordenación con tabla resumen

using namespace std;

// Función que muestra el uso correcto del programa.
void printUsage(char* progName) {
    cout << "Uso: " << progName << " -size <s> -ord <m> -init <i> [f] -trace <y|n>\n";
    cout << "  -size <s>   Tamaño de la secuencia\n";
    cout << "  -ord <m>    Método de ordenación:\n";
    cout << "                1 -> Inserción\n";
    cout << "                2 -> Sacudida\n";
    cout << "                3 -> QuickSort\n";
    cout << "                4 -> HeapSort\n";
    cout << "                5 -> ShellSort\n";
    cout << "  -init <i> [f]  Forma de inicializar la secuencia:\n";
    cout << "                manual   -> Introduce los datos por teclado\n";
    cout << "                random   -> Genera datos aleatorios\n";
    cout << "                file     -> Lee los datos de un fichero (formato: id nombre apellido1 apellido2)\n";
    cout << "  -trace <y|n>   Mostrar (y) o no (n) la traza de la ordenación\n";
    cout << "  --help         Muestra este mensaje de ayuda\n";
}

int main(int argc, char* argv[]) {
    // Si se invoca con "--help", muestra la ayuda y termina.
    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        printUsage(argv[0]);
        return 0;
    }
    // Se requieren al menos 7 parámetros.
    if(argc < 7) {
        printUsage(argv[0]);
        return 1;
    }
    
    unsigned size = 0;      // Tamaño de la secuencia
    int ord = 0;            // Código del método de ordenación
    string initMode = "";   // Modo de inicialización: manual, random, file
    string fileName = "";   // Nombre del fichero (en modo file)
    bool trace = false;     // Si se desea traza en la ordenación
    
    // Procesar los argumentos de línea de comandos.
    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-size") == 0 && i+1 < argc) {
            size = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-ord") == 0 && i+1 < argc) {
            ord = atoi(argv[++i]);
        } else if(strcmp(argv[i], "-init") == 0 && i+1 < argc) {
            initMode = argv[++i];
            if(initMode == "file" && i+1 < argc) {
                fileName = argv[++i];
            }
        } else if(strcmp(argv[i], "-trace") == 0 && i+1 < argc) {
            string t = argv[++i];
            trace = (t == "y" || t == "Y");
        }
    }
    
    if(size == 0 || ord < 1 || ord > 5 || initMode == "") {
        printUsage(argv[0]);
        return 1;
    }
    
    // Crear la secuencia de objetos "persona"
    staticSequence<persona> seq(size);
    
    // Inicialización de la secuencia en función del modo elegido.
    if(initMode == "manual") {
        cout << "Ingrese los datos para " << size << " personas.\n";
        for (unsigned i = 0; i < size; i++) {
            string tipo, nombre, apellido1, apellido2;
            string numStr;
            int num;
            cout << "Persona " << i+1 << ":\n";
            cout << "  Tipo de ID (alu, prof, pas): ";
            cin >> tipo;
            cout << "  Número (exactamente 7 dígitos): ";
            cin >> numStr;
            // Se valida que el número tenga exactamente 7 dígitos.
            if(numStr.length() != 7) {
                cerr << "Error: Debe ingresar exactamente 7 dígitos. Se ha ingresado \"" 
                     << numStr << "\"\n";
                exit(1);
            }
            // Convertir la cadena a entero (no se rellenan ceros, debe ser escrito completo).
            num = stoi(numStr);
            cout << "  Nombre: ";
            cin >> nombre;
            cout << "  Apellido1: ";
            cin >> apellido1;
            cout << "  Apellido2: ";
            cin >> apellido2;
            seq[i] = persona(tipo, num, nombre, apellido1, apellido2);
        }
    } else if(initMode == "random") {
        // En modo random se generan datos aleatorios (aseguramos 7 dígitos generando números entre 1000000 y 9999999)
        string tipos[3] = {"alu", "prof", "pas"};
        for (unsigned i = 0; i < size; i++) {
            string tipo = tipos[rand() % 3];
            int num = 1000000 + rand() % 9000000; // Número entre 1000000 y 9999999 (7 dígitos)
            // Se usan nombres ficticios.
            seq[i] = persona(tipo, num, "Nombre", "Apellido1", "Apellido2");
        }
    } else if(initMode == "file") {
        if(fileName == "") {
            cout << "No se especificó el fichero para la inicialización.\n";
            return 1;
        }
        ifstream infile(fileName);
        if (!infile) {
            cout << "No se pudo abrir el fichero " << fileName << "\n";
            return 1;
        }
        // Se asume que cada línea del fichero contiene: id nombre apellido1 apellido2.
        // Por ejemplo: alu1234567 Juan Pérez Gómez
        string id, nombre, apellido1, apellido2;
        unsigned count = 0;
        while(infile >> id >> nombre >> apellido1 >> apellido2 && count < size) {
            // Extraer el tipo (prefijo) y la parte numérica.
            string tipo = "";
            for (char c : id) {
                if(isalpha(c))
                    tipo.push_back(c);
                else
                    break;
            }
            // La parte numérica se extrae a partir del tamaño del prefijo.
            string numStr = id.substr(tipo.size());
            // Se valida que el número tenga 7 dígitos.
            if(numStr.length() != 7) {
                cerr << "Error: El ID '" << id << "' no contiene exactamente 7 dígitos.\n";
                exit(1);
            }
            int num = stoi(numStr);
            seq[count] = persona(tipo, num, nombre, apellido1, apellido2);
            count++;
        }
        if(count < size) {
            cout << "El fichero no contiene suficientes datos (se leyeron " << count << " registros).\n";
            return 1;
        }
        infile.close();
    } else {
        cout << "Modo de inicialización no reconocido.\n";
        printUsage(argv[0]);
        return 1;
    }
    
    // Muestra la secuencia original.
    cout << "\nSecuencia original:\n";
    seq.print();
    
    // Seleccionar el método de ordenación en función del parámetro -ord.
    SortMethod<persona>* sortMethod = nullptr;
    if(ord == 5) {  // ShellSort requiere además el factor alfa.
        double alfa = 0.0;
        cout << "Ingrese el factor de reducción alfa (0 < alfa < 1): ";
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
    
    // Ejecuta el método de ordenación seleccionado.
    cout << "\nOrdenando la secuencia...\n";
    sortMethod->Sort();
    
    // Muestra la secuencia ordenada.
    cout << "\nSecuencia ordenada:\n";
    seq.print();
    
    // Libera la memoria del objeto creado para la ordenación.
    delete sortMethod;
    return 0;
}
