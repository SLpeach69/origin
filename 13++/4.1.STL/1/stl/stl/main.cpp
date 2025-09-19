#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::string input;
    std::cout << "Enter text ";
    std::getline(std::cin, input);

    std::map<char, int> frequency;
    for (char c : input) {
        frequency[c]++;
    }

    std::vector<std::pair<char, int>> sorted(frequency.begin(), frequency.end());
    std::sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });

    std::cout << "Result \n";
    for (const auto& [character, count] : sorted) {
        std::cout << character << ": " << count << std::endl;
    }

    return 0;
}