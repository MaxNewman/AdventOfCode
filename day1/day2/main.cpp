#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> getDepths();
int getThreeDepthIncreases(std::vector<int>& depths);

int main() {
    std::vector<int> depths = getDepths();

    std::cout << "count: " << getThreeDepthIncreases(depths) << std::endl;

    return 0;
}

int getThreeDepthIncreases(std::vector<int>& depths) {
    int prevDepth = depths[2] + depths[1] + depths[0];
    int currDepth;
    int count = 0;
    for(int left=1, right=3; right < depths.size(); ++left, ++right) {
        currDepth = prevDepth - depths[left-1] + depths[right];
        if(prevDepth < currDepth) {
            ++count;
        }
    }
    return count;
}

std::vector<int> getDepths() {
    std::ifstream input("input.txt");

    std::string line;
    std::vector<int> depths;

    while(!input.fail()) {
        std::getline(input, line);

        if(input.fail()) {
            break;
        }

        int num = std::stoi(line);
        depths.push_back(num);
    }

    return depths;
}