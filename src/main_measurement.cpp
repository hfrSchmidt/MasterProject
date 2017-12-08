#include "../include/crypto_diffieHellman.h"


int main(int argc, char** argv) {
    
    Crypto::CDiffieHellman dh = Crypto::CDiffieHellman();
    dh.profileExchange();
    
    return 0;
}