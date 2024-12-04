#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string generateKey(std::string str, std::string key);
std::string cipherText(std::string str, std::string key);
std::string originalText(std::string cipher_text, std::string key);
int get_password_security_level(std::string password);

#endif // ENCRYPTION_H
