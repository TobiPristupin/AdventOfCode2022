#include <cstdio>
#include <string>
#include <iostream>

void part1(){
    std::string line;
    int score = 0;
    while (std::cin >> line){
        int a, b, c, d;
        sscanf(line.c_str(), "%d-%d,%d-%d", &a, &b, &c, &d);
        score += (c >= a && d <= b) || (a >= c && b <= d);
    }

    std::cout << score << "\n";
}

void part2(){
    std::string line;
    int score = 0;
    while (std::cin >> line){
        int a, b, c, d;
        sscanf(line.c_str(), "%d-%d,%d-%d", &a, &b, &c, &d);
        score += (c >= a && c <= b) || (a >= c && a <= d);
    }

    std::cout << score << "\n";
}

int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}