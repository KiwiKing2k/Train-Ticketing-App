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