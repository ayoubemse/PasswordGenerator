//
//  passwordGenerator.hpp
//  Password generator
//
//  Created by Ayoub Touibi on 27/12/2024.
//

#ifndef passwordGenerator_hpp
#define passwordGenerator_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <boost/program_options.hpp>

using namespace std;

enum class StrenghLevel
{
    WEAK,
    FAIR,
    STRONG,
    VERY_STRONG
};

inline std::unordered_map<StrenghLevel, string> strengthToString={
    {StrenghLevel::WEAK, "WEAK"},
    {StrenghLevel::FAIR, "FAIR"},
    {StrenghLevel::STRONG, "STRONG"},
    {StrenghLevel::VERY_STRONG, "VERY_STRONG"}
};

class PasswordGenerator
{
    public:
    
    PasswordGenerator() : password{}, charSet{}, charSetDiversity(0) {};
    ~PasswordGenerator()=default;
    void generate(unsigned int pwdLength, unsigned int minLength=8, unsigned int maxLength=128, bool lowerCase=true, bool upperCase=true, bool _specialChars=true, bool _digits=true);
    string getPassword() const;
    size_t getPasswordLength() const;
    StrenghLevel getPasswordStrength();
    friend double passwordEntropy(const PasswordGenerator& pwdGenerator);
    friend bool hasrepeatedPattern(const PasswordGenerator& pwdGenerator);

private:
    string password;
    string charSet;
    int charSetDiversity;
};
#endif /* passwordGenerator_hpp */
