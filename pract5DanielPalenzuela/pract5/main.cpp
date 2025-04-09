#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "nif.hpp"
#include "Sequence.hpp"
#include "SortMethods.hpp"

using namespace std;

// Daniel Palenzuela Álvarez alu0101140469

// Función que imprime el uso correcto del programa en consola.
void printUsage(char* progName) {
    cout << "  Programa de algoritmos de ordenación con NIF\n";
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
    staticSequence<nif> seq(size);
    
    // Inicializa la secuencia según el modo especificado.
    if(initMode == "manual") {
        cout << "Introduce " << size << " números de 8 dígitos:\n";
        for (unsigned i = 0; i < size; i++) {
            long num;
            cout << "Elemento " << i+1 << ": ";
            cin >> num;
            // Se asigna el valor al elemento i de la secuencia.
            seq[i] = nif(num);
        }
    } else if(initMode == "random") {
        // Se rellenan los elementos utilizando el constructor por defecto de nif.
        for (unsigned i = 0; i < size; i++) {
            seq[i] = nif();
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
        long num;
        unsigned count = 0;
        // Lee números de 8 dígitos hasta llenar la secuencia o agotar el fichero.
        while(infile >> num && count < size) {
            seq[count] = nif(num);
            count++;
        }
        if(count < size) {
            cout << "El fichero no contiene suficientes datos. Se han leído " << count << " elementos.\n";
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
    SortMethod<nif>* sortMethod = nullptr;
    if (ord == 5) {  // ShellSort requiere el parámetro alfa.
        double alfa = 0.0;
        cout << "Introduce el factor de reducción alfa (0 < alfa < 1): ";
        cin >> alfa;
        if(alfa <= 0 || alfa >= 1) {
            cout << "Valor de alfa no válido.\n";
            return 1;
        }
        sortMethod = new ShellSortMethod<nif>(&seq, trace, alfa);
    } else if (ord == 1) {
        sortMethod = new InsertionSortMethod<nif>(&seq, trace);
    } else if (ord == 2) {
        sortMethod = new ShakeSortMethod<nif>(&seq, trace);
    } else if (ord == 3) {
        sortMethod = new QuickSortMethod<nif>(&seq, trace);
    } else if (ord == 4) {
        sortMethod = new HeapSortMethod<nif>(&seq, trace);
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