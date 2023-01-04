#include <cstdio>
#include <string>
#include <iostream>
#include <stack>
#include <vector>


std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

int parseNumStacks(const std::vector<std::string> &lines){
    std::string lastLine = lines.back();
    rtrim(lastLine);
    return stoi(lastLine.substr(lastLine.find_last_of(' ')));
}

std::vector<std::stack<char>> parseStacks(){
    std::vector<std::string> lines;
    std::string line;
    std::getline(std::cin, line);
    while (!line.empty()){
        lines.push_back(line);
        std::getline(std::cin, line);
    }

    std::vector<std::stack<char>> stacks(parseNumStacks(lines), std::stack<char>());
    for (int i = lines.size() - 2; i >= 0; i--){
        for (int c = 0; c < stacks.size(); c++){
            if (1 + 4*c < lines[i].size() && lines[i][1 + 4*c] != ' '){
                stacks[c].push(lines[i][1 + 4*c]);
            }
        }
    }

    return stacks;
}

void part1(){
    std::vector<std::stack<char>> stacks = parseStacks();
    std::string line;
    while (std::getline(std::cin, line)){
        int quantity, to, from;
        sscanf(line.c_str(), "%*s %d %*s %d %*s %d", &quantity, &from, &to);
        while (quantity--){
            stacks[to-1].push(stacks[from-1].top());
            stacks[from-1].pop();
        }
    }

    for (auto stack : stacks){
        std::cout << stack.top();
    }
    std::cout << "\n";
}

void part2(){
    std::vector<std::stack<char>> stacks = parseStacks();
    std::string line;
    while (std::getline(std::cin, line)){
        int quantity, to, from;
        sscanf(line.c_str(), "%*s %d %*s %d %*s %d", &quantity, &from, &to);
        std::vector<char> popped;
        while (quantity--){
            popped.push_back(stacks[from-1].top());
            stacks[from-1].pop();
        }

        for (int i = popped.size() - 1; i >= 0; i--){
            stacks[to - 1].push(popped[i]);
        }
    }

    for (auto stack : stacks){
        std::cout << stack.top();
    }
    std::cout << "\n";
}


int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}