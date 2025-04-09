#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

// La clase persona representa una persona con un ID, nombre y dos apellidos.
// El ID se compone de un prefijo (alu, prof o pas) y 7 dígitos.
// Se comparan primero los números; si son iguales, se comparan los prefijos de forma
// que el orden sea: "alu" < "prof" < "pas" (alfabéticamente o mediante un criterio definido).
class persona {
private:
    std::string tipo;   // Prefijo: "alu", "prof" o "pas"
    int numero;         // Parte numérica (de 0 a 9999999, se formatea a 7 dígitos)
    std::string nombre;  
    std::string apellido1;
    std::string apellido2;
public:
    // Constructor por defecto (puede generar valores de prueba)
    persona() : tipo("alu"), numero(0), nombre("Nombre"), apellido1("Apellido1"), apellido2("Apellido2") {}

    // Constructor con parámetros
    persona(const std::string &t, int num, const std::string &n, const std::string &a1, const std::string &a2)
        : tipo(t), numero(num), nombre(n), apellido1(a1), apellido2(a2) {}

    // Métodos de acceso
    std::string getTipo() const { return tipo; }
    int getNumero() const { return numero; }
    std::string getNombre() const { return nombre; }
    std::string getApellido1() const { return apellido1; }
    std::string getApellido2() const { return apellido2; }

    // Método para obtener el id completo en formato "tipo"+"7 dígitos"
    std::string getID() const {
        std::ostringstream oss;
        oss << tipo << std::setfill('0') << std::setw(7) << numero;
        return oss.str();
    }

    // Se definen los operadores de comparación.
    // Se comparan primeramente los números; si son iguales, se compara el tipo.
    bool operator<(const persona &other) const {
        if (numero != other.numero)
            return numero < other.numero;
        // Si los números son iguales, se ordena por el tipo.
        return tipo < other.tipo;
    }
    bool operator>(const persona &other) const {
        return other < *this;
    }
    bool operator==(const persona &other) const {
        return (numero == other.numero) && (tipo == other.tipo);
    }
    bool operator!=(const persona &other) const {
        return !(*this == other);
    }

    // Operador de salida: muestra el ID y también el nombre completo.
    friend std::ostream & operator<<(std::ostream &os, const persona &p) {
        os << p.getID() << " (" << p.nombre << " " << p.apellido1 << " " << p.apellido2 << ")";
        return os;
    }
};

#endif
