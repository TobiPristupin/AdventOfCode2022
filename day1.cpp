#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void part2(){
    int currentCals = 0;
    std::vector<int> maxCals = {0, 0, 0};
    std::string line;
    while (std::getline(std::cin, line)){
        if (line.empty()){
            auto it = std::min_element(maxCals.begin(), maxCals.end());
            if (currentCals > *it){
                *it = currentCals;
            }

            currentCals = 0;
            continue;
        }

        currentCals += std::stoi(line);
    }


    std::cout << maxCals[0] + maxCals[1] + maxCals[2] << "\n";
}

void part1(){
    int currentCals = 0;
    int maxCals = 0;
    std::string line;
    while (std::getline(std::cin, line)){
        if (line.empty()){
            maxCals = std::max(maxCals, currentCals);
            currentCals = 0;
            continue;
        }

        currentCals += std::stoi(line);
    }


    std::cout << maxCals << "\n";
}

int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}
