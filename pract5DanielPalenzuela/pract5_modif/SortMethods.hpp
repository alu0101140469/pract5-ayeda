#ifndef SORTMETHODS_HPP
#define SORTMETHODS_HPP

#include "Sorting.hpp"
#include "Sequence.hpp"
#include <iostream>
#include <iomanip>

// Daniel Palenzuela Álvarez alu0101140469

// Clase base abstracta SortMethod, que encapsula una secuencia (staticSequence)
// y la opción de traza para visualizar la ordenación.
template<typename Key>
class SortMethod {
protected:
    staticSequence<Key>* seq;  // Puntero a la secuencia a ordenar
    bool trace;                // Para indicar si se imprimirá la traza
public:
    // Constructor que inicializa la secuencia y la opción de traza.
    SortMethod(staticSequence<Key>* s, bool t) : seq(s), trace(t) {}
    // Método puro que realiza la ordenación.
    virtual void Sort() = 0;
    virtual ~SortMethod() {}
};

// Clase para ordenación por Inserción.
template<typename Key>
class InsertionSortMethod : public SortMethod<Key> {
public:
    InsertionSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        insertionSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| Inserción     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "-------------------------------------------------\n";
    }
};

// Clase para ordenación por Sacudida.
template<typename Key>
class ShakeSortMethod : public SortMethod<Key> {
public:
    ShakeSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        shakeSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| Sacudida      | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "-------------------------------------------------\n";
    }
};

// Clase para ordenación por QuickSort.
template<typename Key>
class QuickSortMethod : public SortMethod<Key> {
public:
    QuickSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        quickSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| QuickSort     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "-------------------------------------------------\n";
    }
};
// Clase para ordenación por HeapSort.
template<typename Key>
class HeapSortMethod : public SortMethod<Key> {
public:
    HeapSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        heapSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| HeapSort      | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "-------------------------------------------------\n";
    }
};

// Clase para ordenación por ShellSort, y incluye la constante alfa.
template<typename Key>
class ShellSortMethod : public SortMethod<Key> {
private:
    double alfa;
public:
    ShellSortMethod(staticSequence<Key>* s, bool t, double a) : SortMethod<Key>(s, t), alfa(a) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        shellSort(*this->seq, alfa, this->trace, comparisons, swaps);
        std::cout << "\n-------------------------------------------------\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "| ShellSort     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "-------------------------------------------------\n";
    }
};

#endif