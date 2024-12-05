#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

using namespace std;

int handleMul(string instruction) {
    std::regex rgx("(0|[1-9]{1}[0-9]{0,2}),(0|[1-9]{1}[0-9]{0,2})");
    std::smatch match;

    if (std::regex_search(instruction, match, rgx))
    {
        string first_op = match[1];
        string second_op = match[2];
        return atoi(first_op.c_str()) * atoi(second_op.c_str());

    }

    return 0;
}

int main(int argc, char const *argv[])
{
    std::ifstream t("puzzle.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    const std::string s = buffer.str();
    std::regex rgx("(don't\\(\\)|do\\(\\))|((mul)\\b\\((0|[1-9]{1}[0-9]{0,2}),(0|[1-9]{1}[0-9]{0,2})\\))");
    std::smatch match;

    string::const_iterator searchStart( s.cbegin() );

    int runningSum = 0;

    bool instructionEnabled = true;

    while (std::regex_search(searchStart, s.cend(), match, rgx))
    {
        string instruction = match[0];

        bool isEnabler = instruction == "don't()" || instruction == "do()";
        instructionEnabled = (isEnabler) ? (instruction == "do()") : instructionEnabled; 

        if (!isEnabler && instructionEnabled) {
            runningSum += handleMul(instruction);
        }
        searchStart = match.suffix().first;
    }

    cout << "Result: " << runningSum;
}