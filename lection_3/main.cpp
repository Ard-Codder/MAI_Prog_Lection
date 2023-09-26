#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string convertToGift(const string& inputText) {
    stringstream ss(inputText);
    string line;
    vector<string> options;

    getline(ss, line); // Считываем строку вопроса

    while (getline(ss, line)) { // Считываем строки с вариантами ответов
        options.push_back(line);
    }

    // Формируем строку в формате gift
    string giftFormat = line + " {\n";

    for (const string& option : options) {
        if (option[0] == '-')
            giftFormat += "~ " + option.substr(2) + "\n";
        else if (option[0] == '+')
            giftFormat += "= " + option.substr(2) + "\n";
    }

    giftFormat += "}";

    return giftFormat;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./converter <input_file.txt>\n";
        return 1;
    }

    string inputFilename = argv[1];
    string outputFilename = inputFilename.substr(0, inputFilename.find_last_of(".")) + ".gift";

    ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cout << "Error opening input file.\n";
        return 1;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cout << "Error opening output file.\n";
        return 1;
    }

    string line;
    while (std::getline(inputFile, line)) {
        string giftQuestion = convertToGiftFormat(line);
        outputFile << giftQuestion << "\n";
    }

    inputFile.close();
    outputFile.close();

    cout << outputFilename << " created.\n";

    return 0;
}
