#include "Aes.hpp"

Aes::Aes() {}

void Aes::handleErrors(void) {
	ERR_print_errors_fp(stderr);
	abort();
}

// Obtiene el numero de caracteres en un arreglo de char
int Aes::cstrlen(const char * u) {
    int s = 0;
    while(u[s] != '\0') s++;
    return s;
}

// Agrega n caracteres al final del arreglo
void Aes::ccharconcat(char * a, char b, int n) {
    if(n < 1) return;

    int i = cstrlen(a);
    int j = i + n;

    for(;i < j; i++) a[i] = b;
}

// Concatenea una cadena en otra
void Aes::cstrconcat(char * a, const char * b) {
    int i = 0;
    int j = cstrlen(a);
    int s = cstrlen(b);

    for(;i < s; i++) {
        if(j > -1) {
            a[j] = b[i];
            j++;
        }
    }
}

// Limpia el arreglo con nulos
void Aes::cstrclean(char * a) {
    int i = 0;
    while(a[i] != 0) {
        a[i] = 0;
        i++;
    }
}

// Busca la posicion donde se encuentra el char
int Aes::cfindindex(const char * a, char b) {
    int i = 0;
    int s = cstrlen(a);

    for(;i < s; i++) {
        if(a[i] == b) return i;
    }

    return -1;
}

// Eleva el numero al exponente ingresado
int Aes::pow(int num, int exp) {
    int result = 1;

    for(int i = 0; i < exp; i++) result *= num;

    return result;
}

int Aes::prevMult(int div, int size) {
    return (size / div) * div;
}

// Obtiene el residuo obtenido de la resta entre el numero divisor mas cercano hacia arriba
// ejemplo res(2, 5) el numero mas cercano divisible va a ser 6, entonces el residuo va a ser 1
int Aes::nextMult(float div, float size) {
    double f = 0; 
    int mul = 0;    
    if(div != 0){
        f = ceil(size / div);
        mul = (int)f * div;
    }

    return mul - size;
}

// Convierte un char, que a su vez es un numero, en un binario
// ejemplo toBin(c, 'a', 8) va a regresar 01100001, porque 'a' es igual a 97
void Aes::toBin(char * a, char b, int n) {
    if(n < 1) return;

    int base = 0x80;
    int i = 0;
    int j = 8 - n;

    for(;i < j + 1; i++) {
        if(i > 0) base /= 2;
    }

    i = 0;

    for(;i < n; i++) {
        if(i > 0) base /= 2;
        a[i] = b & base ? '1' : '0';
    }
}

// Convierte una cadena de char en binario
void Aes::toBin(char * a, const char * b) {
    int len = cstrlen(b);
    int i = 0;
    int j = 0;
    int index = 0;
    char aux[9] = {0};

    for(;i < len; i++) {
        toBin(aux, b[i]);

        for(;j < 8; j++) {
            if(index > -1) {
                a[index] = aux[j];
                index++;
            }
        }

        j = 0;
        aux[0] = '\0';
    }
}

// Convierte un binario a decimal
int Aes::toDec(const char * c) {
    int result = 0;
    int aux = 0;
    int con = 0;
    int size = cstrlen(c) - 1;

    while(size > -1) {
        aux = c[size] - 48;
        result += aux == 1 ? pow(2, con) : 0;
        size--;
        con++;
    }

    return result;
}

// Codifica a base 64
void Aes::encodeb64(char * a, const char * b) {
    const char * b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int s = cstrlen(b);
    int len = s * 8;
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 0;
    int ix1 = 0;
    int ix2 = 0;
    int r = nextMult(3, s);

    char aux[7] = {0};
    char * bin = new char[len + 1];

    toBin(bin, b);

    for(; i < len; i++) {
        aux[ix1++] = bin[i];

        if((ix1 > 0 && ix1 % 6 == 0) || i == len - 1) {
            for(;k < 6; k++) {
                if(aux[k] == '\0') aux[k] = '0';
            }

            k = 0;
            n = toDec(aux);
            if(ix2 > -1) a[ix2] = b64[n];
            ix1 = 0;
            ix2++;

            for(;k < 6; k++) aux[k] = '\0';
            k = 0;
        }
    }

    i = 0;
    for(;i < r; i++) ccharconcat(a, 61);

    delete [] bin;
}

void Aes::decodeb64(char * a, const char * b) {
    const char * b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int len = cstrlen(b);
    int i = 0;
    int j = 0;
    int s = 0;
    int x = 0;
    char aux[9] = {0};

    while(b[len - 1] == 61) len--;

    s = len * 6;
    char c[2148] = {0};
    i = 0;

    for(;i < len; i++) {
        j = cfindindex(b64, b[i]);
        toBin(aux, j, 6);
        cstrconcat(c, aux);
        aux[0] = '\0';
    }

    i = 0;
    j = 0;
    x = 0;
    s = prevMult(8, s);
    aux[0] = '\0';

    for(;i < s; i++) {
        if(j > -1) aux[j] = c[i];
        j++;

        if((i > 0 && (i + 1) % 8 == 0) || i == s -1) {
            if(x > -1) a[x] = toDec(aux);
            aux[0] = '\0';
            j = 0;
            x++;
        }
    }

    //delete [] c;
}