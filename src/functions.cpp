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

void sortResults(unordered_map<wstring, int>& wordCount, vector<pair<wstring, int>>& sortedResults, bool sortByAlphabet, bool ascending) {
    sortedResults.assign(wordCount.begin(), wordCount.end());

    if (sortByAlphabet) {
        sort(sortedResults.begin(), sortedResults.end(), [ascending](const auto& a, const auto& b) {
            return ascending ? a.first < b.first : a.first > b.first;
        });
    } else {
        sort(sortedResults.begin(), sortedResults.end(), [ascending](const auto& a, const auto& b) {
            return ascending ? a.second < b.second : a.second > b.second;
        });
    }
}

void printCrossReferenceTable(wofstream& outputFile,
                              const unordered_map<wstring, vector<int>>& wordLines,
                              const unordered_map<wstring, int>& wordCount,
                              int maxWidth) {
    const int leftMargin = 20;
    outputFile << setw(leftMargin) << L"Word" << L" | " << L"Line Number" << endl;
    outputFile << wstring(50, L'-') << endl;

    for (const auto& pair : wordLines) {
        if (wordCount.at(pair.first) > 1) { // Include only words appearing more than once
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
