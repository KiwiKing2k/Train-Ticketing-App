#include "Encryption.h"
#include <bits/stdc++.h>
using namespace std;

// This function generates the key in
// a cyclic manner until it's length isn't
// equal to the length of original text
string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0;; i++) {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}

// This function returns the encrypted text
// generated with the help of the key
string cipherText(string str, string key) {
    string cipher_text;
    for (int i = 0; i < str.size(); i++) {
        char x = (str[i] + key[i] - 2 * 32) % 95 + 32; // 95 printable ASCII characters
        cipher_text.push_back(x);
    }
    return cipher_text;
}

// This function decrypts the encrypted text
// and returns the original text
string originalText(string cipher_text, string key) {
    string orig_text;
    for (int i = 0; i < cipher_text.size(); i++) {
        char x = (cipher_text[i] - key[i] + 95) % 95 + 32; // 95 printable ASCII characters
        orig_text.push_back(x);
    }
    return orig_text;
}

int get_password_security_level(string password) {
    /// 0 weak, 1 ok , 2 good

    bool has_upper = false, has_lower = false, has_digit = false, has_punct = false;
    for (char c : password) {
        if (isupper(c)) {
            has_upper = true;
        }
        if (islower(c)) {
            has_lower = true;
        }
        if (isdigit(c)) {
            has_digit = true;
        }
        if (ispunct(c)) {
            has_punct = true;
        }
    }
    int security_level = 0;
    (has_lower)? security_level++ : security_level;
    (has_upper)? security_level++ : security_level;
    (has_digit)? security_level++ : security_level;
    (has_punct)? security_level++ : security_level;
    (password.length() >= 8)? security_level++ : security_level;
    if (security_level == 5) {
        cout << "Password is good" << endl;
        return 2;
    }
    if (security_level >= 3) {
        cout << "Password is ok" << endl;
        return 1;
    }
    throw invalid_argument("Password is weak");
    return 0;
}