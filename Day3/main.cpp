#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> parseFile();
std::pair<std::string, std::string> getBits(std::vector<std::string>& vec);
std::pair<int,int> getGammaAndEpsilon(std::vector<std::string>& vec);

int main() {
    std::vector<std::string> vec = parseFile();
    std::pair<std::string, std::string> strs = getBits(vec);

    std::pair<int,int> vals = getGammaAndEpsilon(vec);
    std::cout << "gamma: " << vals.first << std::endl;
    std::cout << "epsilon: " << vals.second << std::endl;
    std::cout << "product: " << vals.first * vals.second << std::endl;

    return 0;
}

std::pair<int,int> getOneAndTwoCount(std::vector<std::string>& vec, int column) {
    int count = 0;
    for(int i=0; i<vec.size(); ++i) {
        if(vec[i][column] == '1') {
            ++count;
        }
    }
    return { count, vec.size() - count };
}

std::vector<std::string> filterVals(std::vector<std::string>& vec, char filterVal, int column) {
    std::vector<std::string> newVec;
    for(int i=0; i<vec.size(); ++i) {
        if(vec[i][column] == filterVal) {
            newVec.push_back(vec[i]);
        }
    }

    return newVec;
}

std::pair<int,int> getGammaAndEpsilon(std::vector<std::string>& vec) {
    std::vector<std::string> gammaVals = vec, epsilonVals = vec;
    for(int i=0; i<vec[0].size(); ++i) {
       std::pair<int,int> counts = getOneAndTwoCount(gammaVals, i);
       std::pair<int,int> eCounts = getOneAndTwoCount(epsilonVals, i);

       char gammaChar = '1';
       if(counts.second > counts.first) {
           gammaChar = '0';
       }

       char epsilonChar = '0';
       if(eCounts.first < eCounts.second) {
          epsilonChar = '1';
       }

       if(gammaVals.size() != 1) {
           gammaVals = filterVals(gammaVals, gammaChar, i);
       }
       if(epsilonVals.size() != 1) {
           epsilonVals = filterVals(epsilonVals, epsilonChar, i);
       }
    }
    return { std::stoi(gammaVals[0], 0, 2), std::stoi(epsilonVals[0], 0, 2) };
}

std::pair<std::string, std::string> getBits(std::vector<std::string>& vec) {
    std::string gamma;
    std::string epsilon;
    for(int i=0; i<vec[0].size(); ++i) {
        int oneCount = 0;
        for(int j=0; j<vec.size(); ++j) {
            if(vec[j][i] == '1') {
                ++oneCount;
            }
        }

        if(oneCount > vec.size() - oneCount) {
            gamma += '1';
            epsilon += '0';
        } else {
            gamma += '0';
            epsilon += '1';
        }
    }

    return { gamma, epsilon };
}

std::vector<std::string> parseFile() {
    std::ifstream input("input.txt");

    std::vector<std::string> vec;
    std::string line;
    for(;;) {
        std::getline(input, line);
        if(input.fail()) {
            break;
        }
        vec.push_back(line);
    }

    return vec;
}