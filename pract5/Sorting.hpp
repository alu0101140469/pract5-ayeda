#ifndef SORTING_HPP
#define SORTING_HPP

#include "Sequence.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

// Daniel Palenzuela Álvarez alu0101140469

// Función auxiliar que imprime los elementos de la secuencia (para la traza de los algoritmos)
template<typename Key>
void printSequence(const Sequence<Key>& seq) {
    for (unsigned i = 0; i < seq.getSize(); i++) {
        std::cout << seq[i] << " ";
    }
    std::cout << "\n";
}

// 1. Ordenación por Inserción
template<typename Key>
void insertionSort(Sequence<Key>& seq, bool trace) {
    unsigned n = seq.getSize();
    // Se recorre el vector desde el segundo elemento hasta el final.
    for (unsigned i = 1; i < n; i++) {
        Key key = seq[i];  // Elemento a insertar en la parte ordenada.
        int j = i - 1;
        // Desplaza elementos mayores que key a una posición hacia la derecha.
        while (j >= 0 && seq[j] > key) {
            seq[j + 1] = seq[j];
            j--;
        }
        // Inserta key en la posición correcta.
        seq[j + 1] = key;
        // Si se solicita la traza, imprime el estado actual del vector.
        if (trace) {
            std::cout << "[Inserción] Iteración " << i << ": ";
            printSequence(seq);
        }
    }
}

// 2. Ordenación por Sacudida
template<typename Key>
void shakeSort(Sequence<Key>& seq, bool trace) {
    bool swapped = true;         // Para ver si hubo intercambios.
    unsigned start = 0;          // Índice inicial del recorrido.
    unsigned end = seq.getSize() - 1;  // Índice final del recorrido.
    unsigned iteration = 0;      // Contador de iteraciones (para la traza).
    while (swapped) {
        swapped = false;
        // Recorrido de izquierda a derecha.
        for (unsigned i = start; i < end; i++) {
            if (seq[i] > seq[i + 1]) { // Si el elemento actual es mayor que el siguiente
                std::swap(seq[i], seq[i + 1]);  // Se intercambian
                swapped = true;
            }
        }
        iteration++;
        if (trace) {
            std::cout << "[Sacudida] Iteración " << iteration << " (ida): ";
            printSequence(seq);
        }
        // Si no se produjo ningún intercambio, la secuencia está ordenada.
        if (!swapped)
            break;
        swapped = false;
        if (end > 0)
            end--;
        // Recorrido de derecha a izquierda.
        for (unsigned i = end; i > start; i--) {
            if (seq[i - 1] > seq[i]) {
                std::swap(seq[i - 1], seq[i]);
                swapped = true;
            }
        }
        start++;
        iteration++;
        if (trace) {
            std::cout << "[Sacudida] Iteración " << iteration << " (vuelta): ";
            printSequence(seq);
        }
    }
}

// 3. Ordenación por QuickSort
// Función de partición que coloca el pivote en su posición correcta.
template<typename Key>
int partition(Sequence<Key>& seq, int low, int high) {
    Key pivot = seq[high];   // Se elige el último elemento como pivote.
    int i = low - 1;         // Índice del elemento menor.
    for (int j = low; j <= high - 1; j++) {
        if (seq[j] < pivot) {
            i++;
            std::swap(seq[i], seq[j]);
        }
    }
    std::swap(seq[i + 1], seq[high]);
    return i + 1;  // Devuelve la posición del pivote.
}

// Función recursiva auxiliar de QuickSort.
template<typename Key>
void quickSortHelper(Sequence<Key>& seq, int low, int high, bool trace) {
    if (low < high) {
        int pi = partition(seq, low, high);
        // Muestra la traza si se ha activado.
        if (trace) {
            std::cout << "[QuickSort] Partición en índice " << pi << ": ";
            printSequence(seq);
        }
        // Llamada recursiva para los subarreglos.
        quickSortHelper(seq, low, pi - 1, trace);
        quickSortHelper(seq, pi + 1, high, trace);
    }
}

// Función principal de QuickSort.
template<typename Key>
void quickSort(Sequence<Key>& seq, bool trace) {
    quickSortHelper(seq, 0, seq.getSize() - 1, trace);
}

// 4. Ordenación por HeapSort
// Función auxiliar heapify para mantener la propiedad del heap.
template<typename Key>
void heapify(Sequence<Key>& seq, int n, int i) {
    int largest = i; // Inicialmente el mayor es la raíz
    int l = 2 * i + 1; // Índice del hijo izquierdo
    int r = 2 * i + 2; // Índice del hijo derecho

    // Si el hijo izquierdo es mayor que la raíz.
    if (l < n && seq[l] > seq[largest])
        largest = l;
    // Si el hijo derecho es mayor que el mayor actual.
    if (r < n && seq[r] > seq[largest])
        largest = r;
    // Si el mayor no es la raíz.
    if (largest != i) {
        std::swap(seq[i], seq[largest]);
        // Se recurre para el subárbol afectado.
        heapify(seq, n, largest);
    }
}

// Función principal de HeapSort.
template<typename Key>
void heapSort(Sequence<Key>& seq, bool trace) {
    int n = seq.getSize();
    // Se construye el heap (reorganiza el arreglo).
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(seq, n, i);
    }
    if (trace) {
        std::cout << "[HeapSort] Heap inicial: ";
        printSequence(seq);
    }
    // Se extraen elementos del heap uno a uno.
    for (int i = n - 1; i > 0; i--) {
        std::swap(seq[0], seq[i]);  // Mueve la raíz al final.
        heapify(seq, i, 0); // Ajusta el heap reducido.
        if (trace) {
            std::cout << "[HeapSort] Tras extraer el máximo: ";
            printSequence(seq);
        }
    }
}

// 5. Ordenación por ShellSort
// Se utiliza una secuencia de incrementos determinada por el factor alfa (0 < alfa < 1)
template<typename Key>
void shellSort(Sequence<Key>& seq, double alfa, bool trace) {
    int n = seq.getSize();
    int gap = n; // Inicialmente gap es igual al tamaño de la secuencia.
    int iteration = 0; // Contador de iteraciones
    // Mientras se puedan generar gaps mayores que 0.
    while ((gap = int(gap * alfa)) > 0) {
        // Para cada elemento a partir del índice gap
        for (int i = gap; i < n; i++) {
            Key temp = seq[i];
            int j = i;
            // Desplaza elementos que están en gap posiciones detrás si son mayores que temp.
            while (j >= gap && seq[j - gap] > temp) {
                seq[j] = seq[j - gap];
                j -= gap;
            }
            // Coloca temp en la posición correcta.
            seq[j] = temp;
        }
        iteration++;
        if (trace) {
            std::cout << "[ShellSort] Iteración " << iteration << " con gap = " << gap << ": ";
            printSequence(seq);
        }
    }
}

#endif