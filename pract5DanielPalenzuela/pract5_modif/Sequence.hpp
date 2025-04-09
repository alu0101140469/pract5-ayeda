#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

// Daniel Palenzuela Álvarez alu0101140469

// Clase base abstracta Sequence, que define el interfaz para una secuencia de elementos.
template<typename Key>
class Sequence {
public:
    // Operador de acceso (lectura), método puro.
    virtual Key operator[](unsigned idx) const = 0;
    // Operador de acceso (escritura), método puro.
    virtual Key& operator[](unsigned idx) = 0;
    // Método que devuelve el tamaño de la secuencia.
    virtual unsigned getSize() const = 0;
    virtual ~Sequence() {}
};

// Clase staticSequence, que implementa una secuencia de tamaño fijo usando un vector.
template<typename Key>
class staticSequence : public Sequence<Key> {
private:
    std::vector<Key> data;   // Vector donde se almacenan los elementos.
public:
    // Constructor que reserva espacio para s elementos.
    staticSequence(unsigned s) : data(s) {}

    // Acceso para lectura que verifica el índice y devuelve el elemento.
    Key operator[](unsigned idx) const override {
        if (idx >= data.size())
            throw std::out_of_range("Índice fuera de rango");
        return data[idx];
    }

    // Acceso para escritura que verifica el índice y devuelve una referencia al elemento.
    Key& operator[](unsigned idx) override {
        if (idx >= data.size())
            throw std::out_of_range("Índice fuera de rango");
        return data[idx];
    }

    // Método que devuelve el tamaño de la secuencia.
    unsigned getSize() const override {
        return data.size();
    }

    // Función auxiliar para imprimir la secuencia completa.
    void print() const {
        for (unsigned i = 0; i < data.size(); i++) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

#endif