#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

void makeMap(map<int, vector<string>> &m){

    ifstream inFile;
    inFile.open("C:\\DSAProject3/movies.csv", ios::in);

    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }

    string movieId;
    vector<string> movieElements;
    string line, name, date, tag, description, min, rating;

    getline(inFile, line);
    istringstream s(line);


    getline(s, movieId, ',');
    getline(s, name, ',');
    getline(s, rating, ',');

    for(int i=0; i<10; i++){
        getline(inFile, line);
        istringstream s(line);


        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');

        //cout<<movieId<<" "<<name<<" "<<rating<<endl;
        //movieElements.push_back(movieId);
        movieElements.push_back(name);
        movieElements.push_back(rating);

        m.insert({stoi(movieId), movieElements});

        movieElements.clear();
    }

    inFile.close();

    inFile.open("C:\\DSAProject3/genres.csv", ios::in);

    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }

    string id, genre;

    getline(inFile, line);
    istringstream b(line);

    getline(b, id, ',');
    getline(b, genre, ',');

    for(int i=0; i<10; i++){
        getline(inFile, line);
        istringstream b(line);


        getline(b, id, ',');
        getline(b, genre, ',');

        //cout<<id<<" "<<genre<<endl;

        int newId = stoi(id);

        auto it = m.find(newId);
        if(it != m.end()){
            it->second.push_back(genre);
        }

    }

    map<int, vector<string>>::iterator it;
    for(it = m.begin(); it != m.end(); it++){
        //cout<<it->first<<" ";
        for(int i=0; i<it->second.size(); i++){
            //cout<<it->second[i]<<" ";
        }
        //cout<<endl;
    }
}

int main() {
    map<int, vector<string>> m;

    makeMap(m);

    cout<<"Enter two desired genres: ";

    string genre1, genre2;

    cin >> genre1;
    cin >> genre2;

    cout<<endl;

    cout<<genre1<<" "<<genre2<<endl;


    return 0;
}
