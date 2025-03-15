//
//  passwordGenerator.cpp
//  Password generator
//
//  Created by Ayoub Touibi on 27/12/2024.
//

#include "passwordGenerator.hpp"
#include "encryptionModule.hpp"
#include <random>
#include <cmath>
#include <iostream>
#include <regex>

double passwordEntropy(const PasswordGenerator& pwdGenerator)
{
    return pwdGenerator.getPasswordLength() * log2(pwdGenerator.charSet.size());
}

bool hasrepeatedPattern(const PasswordGenerator& pwdGenerator)
{
    
    std::regex repeatedPattern("(.)\\1{2,}");
    return std::regex_search(pwdGenerator.getPassword(), repeatedPattern);
}


StrenghLevel PasswordGenerator::getPasswordStrength()
{

    if (getPasswordLength() > 15 && passwordEntropy(*this)>=60 && (charSetDiversity == 4) && !hasrepeatedPattern(*this))
        return StrenghLevel::VERY_STRONG;
    
    else if (getPasswordLength() >= 12 && passwordEntropy(*this)>=37 && (charSetDiversity >= 3) && !hasrepeatedPattern(*this))
        return StrenghLevel::STRONG;
    
    else if (getPasswordLength() >= 8 && passwordEntropy(*this)>=28 && (charSetDiversity >= 2))
        return StrenghLevel::FAIR;
    
    else
        return StrenghLevel::WEAK;

}

string PasswordGenerator::getPassword() const
{
    return password;
}

size_t PasswordGenerator::getPasswordLength() const
{
    return password.size();
}

void PasswordGenerator::generate(unsigned int pwdLength, unsigned int minLength, unsigned int maxLength, bool lowerCase, bool upperCase, bool _specialChars, bool _digits)
{
    string upperLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowerLetters = "abcdefghijklmnopqrstuvwxyz";
    string digits = "0123456789";
    string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    
    
    if(lowerCase)
    {
        charSet+=lowerLetters;
        charSetDiversity+=lowerCase;
    }
        
    if (upperCase)
    {
        charSet+=upperLetters;
        charSetDiversity+=upperCase;
    }
    if(_digits)
    {
        charSet+=digits;
        charSetDiversity+=_digits;
    }
    if (_specialChars)
    {
        charSet+=specialChars;
        charSetDiversity+=_specialChars;
    }

    if (charSet.empty())
        throw std::invalid_argument("No character set was selected for this password.");
    if (pwdLength < minLength || pwdLength > maxLength)
        throw std::invalid_argument("password length must be contained between " + std::to_string(minLength) + " and " + std::to_string(maxLength));
    
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, (int)charSet.size() - 1);
    
    for (int i=0; i<pwdLength; i++)
    {
        password+=charSet[dist(generator)];
    }
}

