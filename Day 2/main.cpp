#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int SAFE_RANGE = 3;

int main(int argc, char const *argv[]) {
    int safeReportCount = 0;

    string line;
    ifstream myfile ("puzzle.txt");
    if (myfile.is_open())
    {
        while(getline(myfile, line)) {
            stringstream ss(line); 
            bool hasChecked = false;
            bool isDecreasing = NULL;
            int lastNumber = NULL;

            int number;
            bool isSafe = true;

            while (ss >> number) {
                if (!isSafe) {
                    break;
                }
                if (lastNumber == NULL) {
                    lastNumber = number;
                    continue;
                }

                if (!hasChecked) {
                    isDecreasing = lastNumber > number;
                    hasChecked = true;
                }

                int difference = lastNumber - number;

                isSafe = (
                    difference != 0 && 
                    abs(difference) <= SAFE_RANGE &&
                    ((difference < 0 && !isDecreasing) || (difference > 0 && isDecreasing))
                );
                
                lastNumber = number;
            }

            if (isSafe) {
                safeReportCount++;
            }

            cout << line << endl;
            cout << (isSafe ? "Safe" : "UnSafe") << endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout << "Result: " << safeReportCount << endl;
}