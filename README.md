# 🔐 Password Generator

## 📌 Description
This project is a secure password generator that uses AES-256 encryption to generate and store passwords safely.

## 🚀 Features
✅ **Random Password Generation** – Creates strong, unpredictable passwords  
✅ **AES-256 Encryption** – Encrypts stored passwords for security
✅ **Boost Program Options** – Command-line customization 
✅ **Configurable Length & Complexity** – User-defined settings  
✅ **Cross-Platform** – Works on Linux, macOS, and Windows  
✅ **Secure Key & IV Management** – Uses OpenSSL for cryptographic operations  

## 🔧 Installation

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/yourusername/PasswordGenerator.git
```

### 2️⃣ Install dependencies
  - Install OpenSsl
```bash
sudo apt install libssl-dev  # Ubuntu/Debian
brew install openssl         # macOS
vcpkg install openssl        # windows
```
  - Install Boost libraries
```bash
sudo apt install libboost-program-options-dev  # Ubuntu/Debian
brew install boost                             # macOS
vcpkg install boost-program-options            # windows
```

3️⃣ Compile the Project
```bash
g++ -std=c++17 -lssl -lcrypto -lboost_program_options main.cpp passwordGenerator.cpp encryptionModule.cpp -o main && ./main
```
This will generate a password with default settings : 
(8 characters, includes lowercase, uppercase, digits, and special characters)

- Example for custom generation :
```bash
./main --pwdLen 16 --uppercase false --digits true --specialchar false
``


