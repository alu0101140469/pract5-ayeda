#ifndef NIF_HPP
#define NIF_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

// Daniel Palenzuela Álvarez alu0101140469

// Clase nif: representa un número de 8 dígitos y define sobrecargas para comparación e impresión.
/*class nif {
private:
    long number;  // Almacena el número (8 dígitos)
public:
    // Constructor por defecto, que genera aleatoriamente un número de 8 dígitos.
    nif() {
        number = 10000000 + rand() % 90000000;
    }
    // Constructor que inicializa el objeto con el número dado.
    nif(long n) : number(n) {}

    // Conversión al tipo long, que permite usar objetos nif en operaciones numéricas.
    operator long() const { return number; }

    // Sobrecarga del operador de igualdad
    bool operator==(const nif &other) const { return number == other.number; }
    // Sobrecarga del operador de desigualdad
    bool operator!=(const nif &other) const { return number != other.number; }
    // Sobrecarga del operador menor que
    bool operator<(const nif &other) const { return number < other.number; }
    // Sobrecarga del operador mayor que
    bool operator>(const nif &other) const { return number > other.number; }

    // Sobrecarga del operador de salida, para facilitar la impresión
    friend std::ostream& operator<<(std::ostream &os, const nif &n) {
        os << n.number;
        return os;
    }
}; */

// Clase persona que representa una persona con un ID, nombre y dos apellidos.
class persona {
    private:
        std::string tipo;   // Prefijo alu, prof, pas
        int numero;         // Parte numérica de 7 dígitos
        std::string nombre;  
        std::string apellido1;
        std::string apellido2;

    public:
    // Constructor por defecto
    persona() : tipo("alu"), numero(0), nombre("Nombre"), apellido1("Apellido1"), apellido2("Apellido2") {}

    // Constructor con parámetros
    persona(const std::string &t, int num, const std::string &n, const std::string &a1, const std::string &a2)
        : tipo(t), numero(num), nombre(n), apellido1(a1), apellido2(a2) {}

    // Getters
    std::string getTipo() const { return tipo; }
    int getNumero() const { return numero; }
    std::string getNombre() const { return nombre; }
    std::string getApellido1() const { return apellido1; }
    std::string getApellido2() const { return apellido2; }

    // Para obtener el id completo tipo+dígitos
    std::string getID() const {
        std::ostringstream oss;
        oss << tipo << std::setfill('0') << std::setw(7) << numero;
        return oss.str();
    }

    // Operadores de comparación.
    // Se comparan los números y si son iguales, se compara el tipo.
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

    // Operador de salida, muestra el ID y el nombre con los 2 apellidos
    friend std::ostream & operator<<(std::ostream &os, const persona &p) {
        os << p.getID() << " (" << p.nombre << " " << p.apellido1 << " " << p.apellido2 << ")";
        return os;
    }
};

#endif