#ifndef SORTMETHODS_HPP
#define SORTMETHODS_HPP

#include "Sorting.hpp"
#include "Sequence.hpp"
#include <iostream>
#include <iomanip>

// Clase base abstracta para un método de ordenación.
template<typename Key>
class SortMethod {
protected:
    staticSequence<Key>* seq; // Secuencia a ordenar
    bool trace;               // Bandera para habilitar la traza
public:
    SortMethod(staticSequence<Key>* s, bool t) : seq(s), trace(t) {}
    virtual void Sort() = 0;
    virtual ~SortMethod() {}
};

// Ordenación por Inserción
template<typename Key>
class InsertionSortMethod : public SortMethod<Key> {
public:
    InsertionSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        insertionSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n+---------------+---------------+---------------+\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "+---------------+---------------+---------------+\n";
        std::cout << "| Inserción     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "+---------------+---------------+---------------+\n";
    }
};

// Ordenación por Sacudida
template<typename Key>
class ShakeSortMethod : public SortMethod<Key> {
public:
    ShakeSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        shakeSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n+---------------+---------------+---------------+\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "+---------------+---------------+---------------+\n";
        std::cout << "| Sacudida      | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "+---------------+---------------+---------------+\n";
    }
};

// Ordenación por QuickSort
template<typename Key>
class QuickSortMethod : public SortMethod<Key> {
public:
    QuickSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        quickSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n+---------------+---------------+---------------+\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "+---------------+---------------+---------------+\n";
        std::cout << "| QuickSort     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "+---------------+---------------+---------------+\n";
    }
};

// Ordenación por HeapSort
template<typename Key>
class HeapSortMethod : public SortMethod<Key> {
public:
    HeapSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        heapSort(*this->seq, this->trace, comparisons, swaps);
        std::cout << "\n+---------------+---------------+---------------+\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "+---------------+---------------+---------------+\n";
        std::cout << "| HeapSort      | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "+---------------+---------------+---------------+\n";
    }
};

// Ordenación por ShellSort (requiere el factor alfa).
template<typename Key>
class ShellSortMethod : public SortMethod<Key> {
private:
    double alfa;
public:
    ShellSortMethod(staticSequence<Key>* s, bool t, double a) : SortMethod<Key>(s, t), alfa(a) {}
    void Sort() override {
        unsigned long comparisons = 0, swaps = 0;
        shellSort(*this->seq, alfa, this->trace, comparisons, swaps);
        std::cout << "\n+---------------+---------------+---------------+\n";
        std::cout << "| Algoritmo     | Comparaciones | Intercambios  |\n";
        std::cout << "+---------------+---------------+---------------+\n";
        std::cout << "| ShellSort     | " << std::setw(13) << comparisons << " | " << std::setw(13) << swaps << " |\n";
        std::cout << "+---------------+---------------+---------------+\n";
    }
};

#endif
