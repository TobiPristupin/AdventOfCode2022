#include <cstdio>
#include <string>
#include <iostream>
#include <map>

void part1(){
    std::string packet;
    std::cin >> packet;

    if (packet.size() < 4){
        return;
    }

    std::map<char, int> last4;
    last4[packet[0]]++;
    last4[packet[1]]++;
    last4[packet[2]]++;
    last4[packet[3]]++;

    /*
     * bvwbj plbgvbhsrlpgdmjqwftvncz
     * b:1, v:1, w:1, j:1
     */

    for (int c = 4; c < packet.size(); c++){
        int distinctChars = 0;
        for (const auto& [ch, count] : last4){
            if (count > 0){
                distinctChars++;
            }
        }

        if (distinctChars == 4){
            std::cout << c << "\n";
            return;
        }

        last4[packet[c]]++;
        last4[packet[c-4]]--;
    }
}

void part2(){
    std::string packet;
    std::cin >> packet;

    if (packet.size() < 14){
        return;
    }

    std::map<char, int> last14;
    for (int i = 0; i < 14; i++){
        last14[packet[i]]++;
    }

    /*
     * bvwbj plbgvbhsrlpgdmjqwftvncz
     * b:1, v:1, w:1, j:1
     */

    for (int c = 14; c < packet.size(); c++){
        int distinctChars = 0;
        for (const auto& [ch, count] : last14){
            if (count > 0){
                distinctChars++;
            }
        }

        if (distinctChars == 14){
            std::cout << c << "\n";
            return;
        }

        last14[packet[c]]++;
        last14[packet[c-14]]--;
    }
}

int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part2();
    return 0;
}