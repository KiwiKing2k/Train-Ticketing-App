#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

std::string generateKey(std::string str, std::string key);
std::string cipherText(std::string str, std::string key);
std::string originalText(std::string cipher_text, std::string key);

#endif // ENCRYPTION_H
