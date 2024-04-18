#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream inFile;
    inFile.open("C:\\DSAProject3/movies.csv", ios::in);

    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }

    string movieId;
    vector<string> movieElements;
    string line, name, date, tag, description, min, rating;


    for(int i=0; i<10; i++){
        getline(inFile, line);
        istringstream s(line);


        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');

        cout<<movieId<<" "<<name<<" "<<rating<<endl;
        movieElements.push_back(movieId);
        movieElements.push_back(name);
        movieElements.push_back(rating);

    }

    return 0;
}
