#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>

// Helper function to remove punctuation and numbers from a word
std::wstring cleanWord(const std::wstring& word) {
    std::wstring cleaned;
    for (wchar_t c : word) {
        if (std::iswalpha(c)) {
            cleaned += std::towlower(c);
        }
    }
    return cleaned;
}

// Function to print a cross-reference table with proper wrapping
void printCrossReferenceTable(std::wofstream& outputFile,
                              const std::unordered_map<std::wstring, std::vector<int>>& wordLines,
                              const std::unordered_map<std::wstring, int>& wordCount,
                              int maxWidth) {
    const int leftMargin = 20; // Width of the first column (word column)
    outputFile << std::setw(leftMargin) << L"Word" << L" | " << L"Line Numbers" << std::endl;
    outputFile << std::wstring(50, L'-') << std::endl;

    for (const auto& pair : wordLines) {
        if (wordCount.at(pair.first) > 1) { // Only include words with a count greater than 1
            outputFile << std::setw(leftMargin) << pair.first << L" | ";

            int currentWidth = leftMargin + 3; // Account for " | "
            for (size_t i = 0; i < pair.second.size(); ++i) {
                std::wstring num = std::to_wstring(pair.second[i]);
                if (currentWidth + num.length() + 2 > maxWidth) { // +2 for ", "
                    outputFile << std::endl << std::setw(leftMargin + 3) << L"";
                    currentWidth = leftMargin + 3;
                }
                outputFile << num;
                currentWidth += num.length() + 2; // Update width
                if (i < pair.second.size() - 1) {
                    outputFile << L", ";
                }
            }
            outputFile << std::endl;
        }
    }
}

int main() {
    // Open input file
    std::wifstream inputFile("tekstas.txt");
    if (!inputFile) {
        std::wcerr << L"Error: Could not open file tekstas.txt" << std::endl;
        return 1;
    }

    // Open output file
    std::wofstream outputFile("outputas.txt");
    if (!outputFile) {
        std::wcerr << L"Error: Could not open file outputas.txt for writing" << std::endl;
        return 1;
    }

    // Word count and cross-reference tables
    std::unordered_map<std::wstring, int> wordCount;
    std::unordered_map<std::wstring, std::vector<int>> wordLines;

    std::wstring line;
    int lineNumber = 0;

    // Process input file line by line
    while (std::getline(inputFile, line)) {
        ++lineNumber;
        std::wstringstream stream(line);
        std::wstring word;

        while (stream >> word) {
            std::wstring cleanedWord = cleanWord(word);
            if (!cleanedWord.empty()) {
                ++wordCount[cleanedWord];
                wordLines[cleanedWord].push_back(lineNumber);
            }
        }
    }

    inputFile.close();

    // Ask user for output choice
    std::wcout << L"Choose output type (1 for word count, 2 for cross-reference table): ";
    int choice;
    std::wcin >> choice;

    if (choice == 1) {
        // Print word count
        outputFile << std::setw(20) << L"Word" << L" | " << L"Count" << std::endl;
        outputFile << std::wstring(30, L'-') << std::endl;

        for (const auto& pair : wordCount) {
            if (pair.second > 1) { // Only include words with a count greater than 1
                outputFile << std::setw(20) << pair.first << L" | " << pair.second << std::endl;
            }
        }
    } else if (choice == 2) {
        const int maxWidth = 80; // Set maximum line width
        printCrossReferenceTable(outputFile, wordLines, wordCount, maxWidth);
    } else {
        std::wcout << L"Invalid choice. No output generated." << std::endl;
    }

    outputFile.close();
    std::wcout << L"Output written to outputas.txt" << std::endl;

    return 0;
}
