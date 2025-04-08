#ifndef SORTMETHODS_HPP
#define SORTMETHODS_HPP

#include "Sorting.hpp"
#include "Sequence.hpp"

// Daniel Palenzuela Álvarez alu0101140469

// Clase base abstracta SortMethod: encapsula una secuencia (staticSequence)
// y la opción de traza para visualizar la ordenación.
template<typename Key>
class SortMethod {
protected:
    staticSequence<Key>* seq;  // Puntero a la secuencia a ordenar
    bool trace;                // Bandera que indica si se imprimirá la traza
public:
    // Constructor que inicializa la secuencia y la opción de traza.
    SortMethod(staticSequence<Key>* s, bool t) : seq(s), trace(t) {}
    // Método puro que realiza la ordenación.
    virtual void Sort() = 0;
    virtual ~SortMethod() {}
};

// Clase para ordenación por Inserción.
// Llama a la función plantilla insertionSort.
template<typename Key>
class InsertionSortMethod : public SortMethod<Key> {
public:
    InsertionSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        insertionSort(*this->seq, this->trace);
    }
};

// Clase para ordenación por Sacudida.
// Llama a la función plantilla shakeSort.
template<typename Key>
class ShakeSortMethod : public SortMethod<Key> {
public:
    ShakeSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        shakeSort(*this->seq, this->trace);
    }
};

// Clase para ordenación por QuickSort.
template<typename Key>
class QuickSortMethod : public SortMethod<Key> {
public:
    QuickSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        quickSort(*this->seq, this->trace);
    }
};

// Clase para ordenación por HeapSort.
template<typename Key>
class HeapSortMethod : public SortMethod<Key> {
public:
    HeapSortMethod(staticSequence<Key>* s, bool t) : SortMethod<Key>(s, t) {}
    void Sort() override {
        heapSort(*this->seq, this->trace);
    }
};

// Clase para ordenación por ShellSort. Incluye la constante alfa.
template<typename Key>
class ShellSortMethod : public SortMethod<Key> {
private:
    double alfa;  // Constante de reducción, 0 < alfa < 1.
public:
    // Constructor que recibe la secuencia, la traza y la constante alfa.
    ShellSortMethod(staticSequence<Key>* s, bool t, double a) : SortMethod<Key>(s, t), alfa(a) {}
    void Sort() override {
        shellSort(*this->seq, alfa, this->trace);
    }
};

#endif