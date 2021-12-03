#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");

    int prevLine = -1;
    int count = 0;
    std::string line;
    while(!input.fail()) {
        std::getline(input, line);

        if(input.fail()) {
            break;
        }

        int num = std::stoi(line);
        if(prevLine != -1 && prevLine < num) {
            ++count;
        }
        prevLine = num;
    }

    std::cout << "count: " << count << std::endl;

    return 0;
}

