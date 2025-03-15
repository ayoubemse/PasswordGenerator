//
//  encryptionModule.hpp
//  MyPasswordGenerator
//
//  Created by Ayoub Touibi on 08/02/2025.
//

#ifndef encryptionModule_hpp
#define encryptionModule_hpp

#include <stdio.h>
#include <vector>
#include <cstring>
std::vector<unsigned char> aes256PasswordEncryption(
    const std::string& plaintext,
    std::vector<unsigned char>& key,
    std::vector<unsigned char>& iv);

std::string aes256PasswordDecryption(
        const std::vector<unsigned char>& ciphertext,
        const std::vector<unsigned char>& key,
        const std::vector<unsigned char>& iv);
#endif /* encryptionModule_hpp */
