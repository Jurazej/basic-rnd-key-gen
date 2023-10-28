#include <iostream>
#include <fstream>
#include <random>
#include <string>

// Function to generate a random key
std::string generateRandomKey(int length) {
    std::string keyCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // You can modify the characters based on your specification
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, keyCharacters.size() - 1);

    std::string key;
    for (int i = 0; i < length; ++i) {
        key += keyCharacters[distribution(gen)];
    }

    return key;
}

int main() {
    int numKeys;
    int keyLength;
    std::string format;

    std::cout << "Enter the number of keys to generate: ";
    std::cin >> numKeys;

    std::cout << "Enter the key length: ";
    std::cin >> keyLength;

    std::cout << "Enter the key format (e.g., 'XXXX-XXXX' for 8 characters with two dashes): ";
    std::cin >> format;

    std::ofstream outputFile("keys.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1;
    }

    for (int i = 0; i < numKeys; ++i) {
        std::string key = generateRandomKey(keyLength);

        // If a format is specified, modify the key accordingly
        if (format.size() > 0) {
            int formatIndex = 0;
            for (int j = 0; j < keyLength; ++j) {
                if (formatIndex < format.size() && format[formatIndex] == 'X') {
                    key[j] = format[formatIndex];
                    formatIndex++;
                }
            }
        }

        outputFile << key << "\n";
    }

    outputFile.close();

    std::cout << numKeys << " keys have been generated and saved to the 'keys.txt' file." << std::endl;

    return 0;
}
