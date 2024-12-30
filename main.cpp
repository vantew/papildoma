#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <iomanip>

std::wstring cleanWord(const std::wstring& word) {
    std::wstring cleaned;
    for (wchar_t c : word) {
        if (std::iswalpha(c)) {
            cleaned += std::towlower(c);
        }
    }
    return cleaned;
}

void printCrossReferenceTable(std::wofstream& outputFile,
                              const std::unordered_map<std::wstring, std::vector<int>>& wordLines,
                              const std::unordered_map<std::wstring, int>& wordCount,
                              int maxWidth) {
    const int leftMargin = 20;
    outputFile << std::setw(leftMargin) << L"Word" << L" | " << L"Line Number" << std::endl;
    outputFile << std::wstring(50, L'-') << std::endl;

    for (const auto& pair : wordLines) {
        if (wordCount.at(pair.first) > 1) { // includint tik zodzius kurie pasikartoj daugiau nei 1 karta
            outputFile << std::setw(leftMargin) << pair.first << L" | ";
            int currentWidth = leftMargin + 3;
            for (size_t i = 0; i < pair.second.size(); ++i) {
                std::wstring num = std::to_wstring(pair.second[i]);
                if (currentWidth + num.length() + 2 > maxWidth) { // +2 for ", "
                    outputFile << std::endl << std::setw(leftMargin + 3) << L"";
                    currentWidth = leftMargin + 3;
                }
                outputFile << num;
                currentWidth += num.length() + 2;
                if (i < pair.second.size() - 1) {
                    outputFile << L", ";
                }
            }
            outputFile << std::endl;
        }
    }
}

int main() {
    std::cout << "Choose output type (1 for word count, 2 for cross-reference table, 3 for URL extraction): ";
    int choice;
    std::cin >> choice;

    if (choice == 3) {
        std::ifstream inputFile("urlai.txt");
        if (!inputFile) {
            std::cerr << "Error: Could not open file urlai.txt" << std::endl;
            return 1;
        }

        std::ofstream outputFile("outputas.txt");
        if (!outputFile) {
            std::cerr << "Error: Could not open file outputas.txt for writing" << std::endl;
            return 1;
        }

        std::regex urlRegex(R"((https?://[^\s]+|www\.[^\s]+|[a-zA-Z0-9\-]+\.[a-zA-Z]{2,}))");
        std::string line;
        while (std::getline(inputFile, line)) {
            std::sregex_iterator begin(line.begin(), line.end(), urlRegex), end;
            for (auto it = begin; it != end; ++it) {
                std::string url = it->str();
                while (!url.empty() && std::ispunct(url.back())) {
                    url.pop_back();
                }
                outputFile << url << std::endl;
            }
        }

        inputFile.close();
        outputFile.close();
        std::cout << "URLs extracted and written to outputas.txt" << std::endl;

    } else if (choice == 1 || choice == 2) {
        std::wifstream inputFile("tekstas.txt");
        if (!inputFile) {
            std::wcerr << L"Error: Could not open file tekstas.txt" << std::endl;
            return 1;
        }

        std::wofstream outputFile("outputas.txt");
        if (!outputFile) {
            std::wcerr << L"Error: Could not open file outputas.txt for writing" << std::endl;
            return 1;
        }

        std::unordered_map<std::wstring, int> wordCount;
        std::unordered_map<std::wstring, std::vector<int>> wordLines;

        std::wstring line;
        int lineNumber = 0;

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

        if (choice == 1) {
            outputFile << std::setw(20) << L"Word" << L" | " << L"Count" << std::endl;
            outputFile << std::wstring(30, L'-') << std::endl;

            for (const auto& pair : wordCount) {
                if (pair.second > 1) {
                    outputFile << std::setw(20) << pair.first << L" | " << pair.second << std::endl;
                }
            }
        } else if (choice == 2) {
            const int maxWidth = 100;
            printCrossReferenceTable(outputFile, wordLines, wordCount, maxWidth);
        }

        outputFile.close();
        std::wcout << L"Output written to outputas.txt" << std::endl;
    } else {
        std::cout << "Invalid choice. No output generated." << std::endl;
    }

    return 0;
}
