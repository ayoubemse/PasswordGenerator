//
//  encryptionModule.cpp
//  MyPasswordGenerator
//
//  Created by Ayoub Touibi on 08/02/2025.
//

#include "encryptionModule.hpp"

#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <cstring>

void handleErrors(const std::string& context) {
    unsigned long errCode;
    while ((errCode = ERR_get_error())) {
        char errBuffer[256];
        ERR_error_string_n(errCode, errBuffer, sizeof(errBuffer));
        std::cerr << "Error in " << context << ": " << errBuffer << std::endl;
    }
    exit(EXIT_FAILURE);
}

std::vector<unsigned char> aes256PasswordEncryption(
    const std::string& plaintext,
    std::vector<unsigned char>& key,
    std::vector<unsigned char>& iv) {

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors("EVP_CIPHER_CTX_new");

    key.resize(32);
    iv.resize(16);
    if (!RAND_bytes(key.data(), key.size()) || !RAND_bytes(iv.data(), iv.size()))
        handleErrors("RAND_bytes");

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data()) != 1)
        handleErrors("EVP_EncryptInit_ex");

    std::vector<unsigned char> ciphertext(plaintext.size() + 16); // Add space for padding
    int len = 0, ciphertext_len = 0;

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, (unsigned char*)plaintext.data(), plaintext.size()) != 1)
        handleErrors("EVP_EncryptUpdate");
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1)
        handleErrors("EVP_EncryptFinal_ex");
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);
    return ciphertext;
}

std::string aes256PasswordDecryption(
    const std::vector<unsigned char>& ciphertext,
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& iv) {

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleErrors("EVP_CIPHER_CTX_new");

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv.data()) != 1)
        handleErrors("EVP_DecryptInit_ex");

    std::vector<unsigned char> plaintext(ciphertext.size());
    int len = 0, plaintext_len = 0;

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1)
        handleErrors("EVP_DecryptUpdate");
    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) != 1)
        handleErrors("EVP_DecryptFinal_ex");
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(plaintext_len);
    return std::string(plaintext.begin(), plaintext.end());
}
