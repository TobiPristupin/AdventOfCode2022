#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

//A rock
//B paper
//C scissors
int beats(const std::string& a, const std::string& b){
    if (b == "X"){
        if (a == "C"){
            return 1;
        } else if (a == "B"){
            return -1;
        }
        return 0;
    }

    if (b == "Y"){
        if (a == "A") {
            return 1;
        } else if (a == "C"){
            return  -1;
        }
        return 0;
    }

    if (b == "Z"){
        if (a == "B"){
            return 1;
        } else if (a == "A"){
            return -1;
        }
        return 0;
    }
}

void part1(){
    std::unordered_map<std::string, int> shapeValue= {{"X", 1}, {"Y", 2}, {"Z", 3}};

    std::string a, b;
    int score = 0;
    while (std::cin >> a >> b){
        score += shapeValue[b];
        int beat = beats(a, b);
        if (beat == 0){
            score += 3;
        } else if (beat > 0){
            score += 6;
        }
    }

    std::cout << score << "\n";
}

void part2(){
    std::unordered_map<std::string, std::string> win = {{"A", "B"}, {"B", "C"}, {"C", "A"}};
    std::unordered_map<std::string, std::string> lose = {{"A", "C"}, {"B", "A"}, {"C", "B"}};
    std::unordered_map<std::string, int> shapeValue= {{"A", 1}, {"B", 2}, {"C", 3}};

    std::string a, b;
    int score = 0;
    while (std::cin >> a >> b){
        if (b == "X"){
            score += shapeValue[lose[a]];
        } else if (b == "Y"){
            score += shapeValue[a] + 3;
        } else {
            score += shapeValue[win[a]] + 6;
        }
    }

    std::cout << score << "\n";
}

int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}
