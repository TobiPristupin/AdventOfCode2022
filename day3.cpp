#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

int getPriority(char c){
    int upperCorrection = isupper(c) ? 26 : 0;
    return tolower(c) - (int) 'a' + 1 + upperCorrection;
}

void part1(){
    std::string items;
    int score = 0;
    while (std::cin >> items){
        std::unordered_set<char> seen;
        int i = 0;
        for (i; i < items.size() / 2; i++){
            seen.insert(items[i]);
        }
        for (i; i < items.size(); i++){
            if (seen.find(items[i]) != seen.end()){
                score += getPriority(items[i]);
                break;
            }
        }
    }

    std::cout << score << "\n";
}

void part2(){
    std::string line1, line2, line3;
    int score = 0;
    while (std::cin >> line1 >> line2 >> line3){
        std::unordered_map<char, int> count;
        for (char c : line1){
            if (count[c] == 0){
                count[c] += 1;
            }
        }
        for (char c : line2){
            if (count[c] == 1){
                count[c] += 1;
            }
        }
        for (char c : line3){
            if (count[c] == 2){
                score += getPriority(c);
                break;
            }
        }
    }

    std::cout << score << "\n";
}

int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}