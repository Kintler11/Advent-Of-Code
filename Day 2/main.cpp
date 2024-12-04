#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int SAFE_RANGE = 3;

bool isSafe(vector<int> numbers) {
    bool isDecreasing = numbers[1] - numbers[0] < 0;
    int lastNumber = numbers[0];
    
    for (int i = 1; i < numbers.size(); i++) {
        int difference = lastNumber - numbers[i];

        bool isSafe = (
            difference != 0 && 
            abs(difference) <= SAFE_RANGE &&
            ((difference < 0 && !isDecreasing) || (difference > 0 && isDecreasing))
        );

        if (!isSafe) {
            return false;
        }
        
        lastNumber = numbers[i];
    }

    return true;
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

            if (isSafe(lineNumbers)) {
                safeReportCount++;
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "Result: " << safeReportCount << endl;
}