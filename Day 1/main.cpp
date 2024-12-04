#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;
vector<int> v1;
vector<int> v2;

void loadFile() {
    string line;
    ifstream myfile ("puzzle.txt");

    int index = 0;

    if (myfile.is_open())
    {
        while(getline(myfile, line)) {
            stringstream ss(line);  
            int word;
            while (ss >> word) {
                if (index % 2 == 0) {
                    v1.push_back(word);
                } else {
                    v2.push_back(word);
                }
                index++;
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
}

int main(int argc, char const *argv[])
{
    loadFile();
    vector<int> results;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    
    for (int i = 0; i < v1.size(); i++) {
        results.push_back(abs(v1.at(i) - v2.at(i)));
    }

    int sum = 0;
    for (int i : results) {
        sum += i;
    }

    cout << "Result: " << sum << endl;

    return 0;
}