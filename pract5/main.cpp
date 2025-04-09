#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Persona.hpp"      // Usamos la clase persona
#include "Sequence.hpp"     // Para staticSequence
#include "SortMethods.hpp"  // Para los métodos de ordenación

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
    // Si se invoca con --help se muestra la guía y se termina.
    if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        printUsage(argv[0]);
        return 0;
    }

    if(argc < 7) {
        printUsage(argv[0]);
        return 1;
    }
    
    unsigned size = 0;      // Tamaño de la secuencia
    int ord = 0;            // Código del método de ordenación
    string initMode = "";   // Modo de inicialización (manual, random, file)
    string fileName = "";   // Nombre del fichero para modo file
    bool trace = false;     // Opción de traza
     
    // Procesar argumentos de línea de comandos.
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
    
    // Crear la secuencia de objeto persona.
    staticSequence<persona> seq(size);
    
    // Inicializar la secuencia.
    if(initMode == "manual") {
        cout << "Ingrese los datos para " << size << " personas.\n";
        for (unsigned i = 0; i < size; i++) {
            string tipo, nombre, apellido1, apellido2;
            int num;
            cout << "Persona " << i+1 << ":\n";
            cout << "  Tipo de ID (alu, prof, pas): ";
            cin >> tipo;
            cout << "  Número (hasta 7 dígitos): ";
            cin >> num;
            cout << "  Nombre: ";
            cin >> nombre;
            cout << "  Apellido1: ";
            cin >> apellido1;
            cout << "  Apellido2: ";
            cin >> apellido2;
            seq[i] = persona(tipo, num, nombre, apellido1, apellido2);
        }
    } else if(initMode == "random") {
        // Para datos aleatorios, se asignan valores fijos o generados.
        string tipos[3] = {"alu", "prof", "pas"};
        for (unsigned i = 0; i < size; i++) {
            string tipo = tipos[rand() % 3];
            int num = rand() % 10000000; // Número de 0 a 9999999
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
        // El id estará en el formato (por ejemplo, alu0001345). Se extrae el tipo y el número.
        string id, nombre, apellido1, apellido2;
        unsigned count = 0;
        while(infile >> id >> nombre >> apellido1 >> apellido2 && count < size) {
            // Extraer el prefijo (letras) y la parte numérica.
            string tipo = "";
            int num = 0;
            // Asumimos que el id comienza con letras y luego 7 dígitos.
            for (char c : id) {
                if (isalpha(c))
                    tipo.push_back(c);
                else
                    break;
            }
            // La parte numérica es el resto.
            string numStr = id.substr(tipo.size());
            num = stoi(numStr);
            seq[count] = persona(tipo, num, nombre, apellido1, apellido2);
            count++;
        }
        if(count < size) {
            cout << "El fichero no contiene suficientes datos (se leyeron " << count << " elementos).\n";
            return 1;
        }
        infile.close();
    } else {
        cout << "Modo de inicialización no reconocido.\n";
        printUsage(argv[0]);
        return 1;
    }
    
    // Mostrar la secuencia original.
    cout << "\nSecuencia original:\n";
    seq.print();
    
    // Seleccionar el método de ordenación.
    SortMethod<persona>* sortMethod = nullptr;
    if(ord == 5) {  // ShellSort
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
    
    // Ejecutar la ordenación.
    cout << "\nOrdenando la secuencia...\n";
    sortMethod->Sort();
    
    // Mostrar la secuencia ordenada.
    cout << "\nSecuencia ordenada:\n";
    seq.print();
    
    delete sortMethod;
    return 0;
}
