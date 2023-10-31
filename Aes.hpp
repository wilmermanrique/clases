#ifndef AES256GCM_HPP
#define AES256GCM_HPP

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <cmath>
#include "stdio.h"


class Aes {
    private:
        void handleErrors(void);

        int cstrlen(const char * u);
        void ccharconcat(char * a, char b, int s = 1);
        void cstrconcat(char * a, const char * b);
        void cstrclean(char * a);
        int cfindindex(const char * a, char b);

        int pow(int num, int exp);
        int prevMult(int div, int size);
        int nextMult(float div, float size);

        void toBin(char * a, char b, int n = 8);
        void toBin(char * a, const char * b);
        int toDec(const char * c);
    public:
        Aes();
        void encodeb64(char * a, const char * b);
        void decodeb64(char * a, const char * b);

        void encrypt(const char * plaintext, const char * key, char * ciphertext);
        void decrypt(const char * ciphertext, const char * key, char * plaintext);
};

#endif
