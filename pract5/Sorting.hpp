#ifndef SORTING_HPP
#define SORTING_HPP

#include "Sequence.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

// Función auxiliar para imprimir la secuencia (para traza)
template<typename Key>
void printSequence(const Sequence<Key>& seq) {
    for (unsigned i = 0; i < seq.getSize(); i++) {
        std::cout << seq[i] << " | ";
    }
    std::cout << "\n";
}

// 1. Ordenación por Inserción
template<typename Key>
void insertionSort(Sequence<Key>& seq, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    comparisons = 0;
    swaps = 0;
    unsigned n = seq.getSize();
    for (unsigned i = 1; i < n; i++) {
        Key key = seq[i];
        int j = i - 1;
        // Comparar y mover elementos que sean mayores que key
        while (j >= 0) {
            comparisons++;  // Se realiza una comparación
            if (seq[j] > key) {
                seq[j + 1] = seq[j];
                swaps++;    // Se cuenta el movimiento (swap)
                j--;
            } else {
                break;
            }
        }
        seq[j + 1] = key;
        swaps++;  // Se cuenta la asignación de key
        if (trace) {
            std::cout << "[Inserción] Iteración " << i << ": ";
            printSequence(seq);
        }
    }
}

// 2. Ordenación por Sacudida (Cocktail Shaker Sort)
template<typename Key>
void shakeSort(Sequence<Key>& seq, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    comparisons = 0;
    swaps = 0;
    bool swapped = true;
    unsigned start = 0;
    unsigned end = seq.getSize() - 1;
    unsigned iteration = 0;
    while (swapped) {
        swapped = false;
        // Recorrido de izquierda a derecha.
        for (unsigned i = start; i < end; i++) {
            comparisons++;  // Cada comparación en el if
            if (seq[i] > seq[i + 1]) {
                std::swap(seq[i], seq[i + 1]);
                swaps++;
                swapped = true;
            }
        }
        iteration++;
        if (trace) {
            std::cout << "[Sacudida] Iteración " << iteration << " (ida): ";
            printSequence(seq);
        }
        if (!swapped)
            break;
        swapped = false;
        if (end > 0) end--;
        // Recorrido de derecha a izquierda.
        for (unsigned i = end; i > start; i--) {
            comparisons++;
            if (seq[i - 1] > seq[i]) {
                std::swap(seq[i - 1], seq[i]);
                swaps++;
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
// Función de partición que reubica el pivote en su posición correcta.
template<typename Key>
int partition(Sequence<Key>& seq, int low, int high, unsigned long &comparisons, unsigned long &swaps) {
    Key pivot = seq[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (seq[j] < pivot) {
            i++;
            std::swap(seq[i], seq[j]);
            swaps++;
        }
    }
    std::swap(seq[i + 1], seq[high]);
    swaps++;
    return i + 1;
}

// Función recursiva auxiliar de QuickSort.
template<typename Key>
void quickSortHelper(Sequence<Key>& seq, int low, int high, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    if (low < high) {
        int pi = partition(seq, low, high, comparisons, swaps);
        if (trace) {
            std::cout << "[QuickSort] Pivote en índice " << pi << ": ";
            printSequence(seq);
        }
        quickSortHelper(seq, low, pi - 1, trace, comparisons, swaps);
        quickSortHelper(seq, pi + 1, high, trace, comparisons, swaps);
    }
}

// Función principal de QuickSort.
template<typename Key>
void quickSort(Sequence<Key>& seq, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    comparisons = 0;
    swaps = 0;
    quickSortHelper(seq, 0, seq.getSize() - 1, trace, comparisons, swaps);
}

// 4. Ordenación por HeapSort
// Función auxiliar heapify para mantener la propiedad del heap.
template<typename Key>
void heapify(Sequence<Key>& seq, int n, int i, unsigned long &comparisons, unsigned long &swaps) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n) {
        comparisons++;
        if (seq[l] > seq[largest])
            largest = l;
    }
    if (r < n) {
        comparisons++;
        if (seq[r] > seq[largest])
            largest = r;
    }
    if (largest != i) {
        std::swap(seq[i], seq[largest]);
        swaps++;
        heapify(seq, n, largest, comparisons, swaps);
    }
}

// Función principal de HeapSort.
template<typename Key>
void heapSort(Sequence<Key>& seq, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = seq.getSize();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(seq, n, i, comparisons, swaps);
    }
    if (trace) {
        std::cout << "[HeapSort] Heap inicial: ";
        printSequence(seq);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(seq[0], seq[i]);
        swaps++;
        heapify(seq, i, 0, comparisons, swaps);
        if (trace) {
            std::cout << "[HeapSort] Tras extraer el máximo: ";
            printSequence(seq);
        }
    }
}

// 5. Ordenación por ShellSort
// Utiliza la reducción del gap multiplicándolo por alfa en cada iteración.
template<typename Key>
void shellSort(Sequence<Key>& seq, double alfa, bool trace, unsigned long &comparisons, unsigned long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = seq.getSize();
    int gap = n;
    int iteration = 0;
    while ((gap = int(gap * alfa)) > 0) {
        for (int i = gap; i < n; i++) {
            Key temp = seq[i];
            int j = i;
            while (j >= gap) {
                comparisons++;
                if (seq[j - gap] > temp) {
                    seq[j] = seq[j - gap];
                    swaps++;
                    j -= gap;
                } else {
                    break;
                }
            }
            seq[j] = temp;
            swaps++;
        }
        iteration++;
        if (trace) {
            std::cout << "[ShellSort] Iteración " << iteration << " (gap = " << gap << "): ";
            printSequence(seq);
        }
    }
}

#endif
