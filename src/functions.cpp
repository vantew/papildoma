#include "Mylib.h"

wstring cleanWord(const wstring& word) {
    wstring cleaned;
    for (wchar_t c : word) {
        if (iswalpha(c)) {
            cleaned += towlower(c);
        }
    }
    return cleaned;
}

void printCrossReferenceTable(wofstream& outputFile,
                              const unordered_map<wstring, vector<int>>& wordLines,
                              const unordered_map<wstring, int>& wordCount,
                              int maxWidth) {
    const int leftMargin = 20;
    outputFile << setw(leftMargin) << L"Word" << L" | " << L"Line Number" << endl;
    outputFile << wstring(50, L'-') << endl;

    for (const auto& pair : wordLines) {
        if (wordCount.at(pair.first) > 1) { // includint tik zodzius kurie pasikartoj daugiau nei 1 karta
            outputFile << setw(leftMargin) << pair.first << L" | ";
            int currentWidth = leftMargin + 3;
            for (size_t i = 0; i < pair.second.size(); ++i) {
                wstring num = to_wstring(pair.second[i]);
                if (currentWidth + num.length() + 2 > maxWidth) { // +2 for ", "
                    outputFile << endl << setw(leftMargin + 3) << L"";
                    currentWidth = leftMargin + 3;
                }
                outputFile << num;
                currentWidth += num.length() + 2;
                if (i < pair.second.size() - 1) {
                    outputFile << L", ";
                }
            }
            outputFile << endl;
        }
    }
}
