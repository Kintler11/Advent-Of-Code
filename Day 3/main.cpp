#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char const *argv[])
{
    std::ifstream t("puzzle.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    const std::string s = buffer.str();
    std::regex rgx("(mul)\\b\\((0|[1-9]{1}[0-9]{0,2}),(0|[1-9]{1}[0-9]{0,2})\\)");
    std::smatch match;

    string::const_iterator searchStart( s.cbegin() );

    int runningSum = 0;
    int runningCount = 0;
    while (std::regex_search(searchStart, s.cend(), match, rgx))
    {
        if (is_number(match[2]) && is_number(match[3])) {
            string first_op = match[2];
            string second_op = match[3];
            runningSum += atoi(first_op.c_str()) * atoi(second_op.c_str());
            cout << match[2] << " " << match[3] << endl;  
            runningCount++;
        }
        searchStart = match.suffix().first;
    }

    cout << "Results: " << runningCount << endl;
    cout << "Result: " << runningSum;
}