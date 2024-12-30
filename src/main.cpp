#include "Mylib.h"

int main() {
    cout << "Choose output type (1 for word count, 2 for cross-reference table, 3 for URL extraction): ";
    int choice;
    cin >> choice;

    if (choice == 3) {
        ifstream inputFile("urlai.txt");
        if (!inputFile) {
            cerr << "Error: Could not open file urlai.txt" << endl;
            system("pause");
            return 1;
        }

        ofstream outputFile("outputas.txt");
        if (!outputFile) {
            cerr << "Error: Could not open file outputas.txt for writing" << endl;
            system("pause");
            return 1;
        }

        regex urlRegex(R"((https?://[^\s]+|www\.[^\s]+|[a-zA-Z0-9\-]+\.[a-zA-Z]{2,}))");
        string line;
        while (getline(inputFile, line)) {
            sregex_iterator begin(line.begin(), line.end(), urlRegex), end;
            for (auto it = begin; it != end; ++it) {
                string url = it->str();
                while (!url.empty() && ispunct(url.back())) {
                    url.pop_back();
                }
                outputFile << url << endl;
            }
        }

        inputFile.close();
        outputFile.close();
        cout << "URLs extracted and written to outputas.txt" << endl;

    } else if (choice == 1 || choice == 2) {
        wifstream inputFile("tekstas.txt");
        if (!inputFile) {
            wcerr << L"Error: Could not open file tekstas.txt" << endl;
            system("pause");
            return 1;
        }

        wofstream outputFile("outputas.txt");
        if (!outputFile) {
            wcerr << L"Error: Could not open file outputas.txt for writing" << endl;
            system("pause");
            return 1;
        }

        unordered_map<wstring, int> wordCount;
        unordered_map<wstring, vector<int>> wordLines;

        wstring line;
        int lineNumber = 0;

        while (getline(inputFile, line)) {
            ++lineNumber;
            wstringstream stream(line);
            wstring word;

            while (stream >> word) {
                wstring cleanedWord = cleanWord(word);
                if (!cleanedWord.empty()) {
                    ++wordCount[cleanedWord];
                    wordLines[cleanedWord].push_back(lineNumber);
                }
            }
        }

        inputFile.close();

        if (choice == 1) {
            outputFile << setw(20) << L"Word" << L" | " << L"Count" << endl;
            outputFile << wstring(30, L'-') << endl;

            for (const auto& pair : wordCount) {
                if (pair.second > 1) {
                    outputFile << setw(20) << pair.first << L" | " << pair.second << endl;
                }
            }
        } else if (choice == 2) {
            const int maxWidth = 100;
            printCrossReferenceTable(outputFile, wordLines, wordCount, maxWidth);
        }

        outputFile.close();
        wcout << L"Output written to outputas.txt" << endl;
    } else {
        cout << "Invalid choice. No output generated." << endl;
    }

    system("pause");
    return 0;
}
