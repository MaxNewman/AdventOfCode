#include <iostream>
#include <fstream>
#include <sstream>

struct position {
    int depth;
    int horizontal;
    int aim;

    position() {
        depth = 0;
        horizontal = 0;
        aim = 0;
    }
};

position processLine(std::string& line, position currPos);

int main() {
    std::ifstream input("input.txt");

    std::string line;
    position pos;

    while(!input.fail()) {
        std::getline(input, line);
        if(input.fail()) {
            break;
        }
        pos = processLine(line, pos);
    }

    std::cout << "depth: " << pos.depth << std::endl;
    std::cout << "horizontal: " << pos.horizontal << std::endl;
    std::cout << "multiply: " << pos.depth * pos.horizontal << std::endl;

    return 0;
}

position processLine(std::string& line, position currPos) {
    std::stringstream ss(line);
    std::string op, dist;
    ss >> op >> dist;

    int distInt = std::stoi(dist);
    if(op == "forward") {
        currPos.horizontal += distInt;
        currPos.depth += distInt * currPos.aim;
    } else if(op == "up") {
        currPos.aim -= distInt;
    } else if(op == "down") {
        currPos.aim += distInt;
    }
    return currPos;
}
