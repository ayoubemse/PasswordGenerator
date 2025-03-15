//
//  main.cpp
//  Password generator
//
//  Created by Ayoub Touibi on 27/12/2024.
//

#include <iostream>
#include <string>
#include <vector>
#include "passwordGenerator.hpp"
#include "encryptionModule.hpp"

int main(int argc, const char * argv[]) {
    
   PasswordGenerator pwdTest;
   namespace po = boost::program_options;

        try {
           po::options_description desc("Allowed options");
           desc.add_options()
               ("help,h", "Show help message")
               ("pwdLen", po::value<unsigned int>()->default_value(8), "Password length")
               ("minLen", po::value<unsigned int>()->default_value(6), "Minimum password length")
               ("maxLen", po::value<unsigned int>()->default_value(128), "Maximum password length")
               ("lowercase,lc", po::value<bool>()->default_value(true)->implicit_value(true), "Include lowercase characters")
               ("uppercase,uc", po::value<bool>()->default_value(true)->implicit_value(true), "Include uppercase characters")
               ("specialchar,sc", po::value<bool>()->default_value(true)->implicit_value(true), "Include special characters")
               ("digits,d", po::value<bool>()->default_value(true)->implicit_value(true), "Include digits");

           po::variables_map vm;
           po::store(po::parse_command_line(argc, argv, desc), vm);
           po::notify(vm);

           if (vm.count("help")) {
               std::cout << desc << "\n";
               return 0;
           }

           unsigned int pwdLength = vm["pwdLen"].as<unsigned int>();
           unsigned int minLength = vm["minLen"].as<unsigned int>();
           unsigned int maxLength = vm["maxLen"].as<unsigned int>();
           bool lowerCase = vm["lowercase"].as<bool>();
           bool upperCase = vm["uppercase"].as<bool>();
           bool specialChars = vm["specialchar"].as<bool>();
           bool digits = vm["digits"].as<bool>();

           pwdTest.generate(pwdLength, minLength, maxLength, lowerCase, upperCase, specialChars, digits);
       } catch (const std::exception& e) {
           std::cerr << "Error: " << e.what() << "\n";
           return 1;
       }

    std::cout << "generaed password = " << pwdTest.getPassword() << endl;
    try{
        std::vector<unsigned char> key;
        std::vector<unsigned char> iv;
        auto res = aes256PasswordEncryption(pwdTest.getPassword(), key, iv);
        std::cout<<"encrypted password : "<< std::endl;
        for (auto c : res)
        {
            std::cout << std::hex << (int)c << " ";
        }
        std::cout<< std::endl;
        
        std::cout << "decrypted password = " << aes256PasswordDecryption(res, key, iv)<< endl;
    }
    catch(const std::exception& e){
        std::cerr<< "Exception occured : " << e.what()<<std::endl;
    }
    std::cout << "password entropy = " << passwordEntropy(pwdTest)<< endl;
    return 0;
}
