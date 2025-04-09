#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

// Clase abstracta Sequence: define la interfaz para una secuencia de elementos.
template<typename Key>
class Sequence {
public:
    // Operador de acceso para lectura (método virtual puro).
    virtual Key operator[](unsigned idx) const = 0;
    // Operador de acceso para escritura (método virtual puro).
    virtual Key& operator[](unsigned idx) = 0;
    // Método para obtener el tamaño de la secuencia.
    virtual unsigned getSize() const = 0;
    virtual ~Sequence() {}
};

// Implementación de secuencia de tamaño fijo usando un vector.
template<typename Key>
class staticSequence : public Sequence<Key> {
private:
    std::vector<Key> data;   // Almacena los elementos en un vector.
public:
    // El constructor reserva espacio para 's' elementos.
    staticSequence(unsigned s) : data(s) {}

    // Operador de acceso para lectura: verifica el índice.
    Key operator[](unsigned idx) const override {
        if (idx >= data.size())
            throw std::out_of_range("Índice fuera de rango");
        return data[idx];
    }

    // Operador de acceso para escritura.
    Key& operator[](unsigned idx) override {
        if (idx >= data.size())
            throw std::out_of_range("Índice fuera de rango");
        return data[idx];
    }

    // Retorna el tamaño de la secuencia.
    unsigned getSize() const override {
        return data.size();
    }

    // Imprime todos los elementos de la secuencia.
    void print() const {
        for (unsigned i = 0; i < data.size(); i++) {
            std::cout << data[i] << "\n";
        }
        std::cout << std::endl;
    }
};

#endif
