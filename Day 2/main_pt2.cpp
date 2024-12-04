#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int SAFE_RANGE = 3;

int isSafe(vector<int> numbers) {
    bool isDecreasing = numbers[numbers.size() - 1] - numbers[0] < 0;
    int lastNumber = numbers[0];
    
    for (int i = 1; i < numbers.size(); i++) {
        int difference = lastNumber - numbers[i];

        bool isSafe = (
            difference != 0 && 
            abs(difference) <= SAFE_RANGE &&
            ((difference < 0 && !isDecreasing) || (difference > 0 && isDecreasing))
        );

        if (!isSafe) {
            return i;
        }
        
        lastNumber = numbers[i];
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    int safeReportCount = 0;

    string line;
    ifstream myfile ("puzzle.txt");
    if (myfile.is_open()) {
        while(getline(myfile, line)) {
            stringstream ss(line); 
            vector<int> lineNumbers;
            int number;

            while (ss >> number) {
                lineNumbers.push_back(number);
            }

            int index = isSafe(lineNumbers);

            if (index == 0 ) {
                safeReportCount++;
                continue;
            }

            bool allowed = false;
            vector<int> one = lineNumbers;

            lineNumbers.erase(next(lineNumbers.begin(), index));
            one.erase(next(one.begin(), index - 1));

            if (isSafe(lineNumbers) == 0 || isSafe(one) == 0 ) {
                allowed = true;
            }

            if (allowed) {
                safeReportCount++;
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "Result: " << safeReportCount << endl;
}