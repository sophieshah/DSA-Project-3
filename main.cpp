#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

//unordered map class made from scratch --> made as map<string, vector<string>>
class unorderedMap{
private:
    vector<vector<string>> map;
    vector<string> keys;
public:
    //inserts a key, value pair into map making sure the key is unique and then inserting the key as the 0th index and the values as the rest of the vector
    void insert(string key, vector<string> values){
        bool unique = true;
        for(int i=0; i<keys.size(); i++){
            if(keys[i]==key){
                unique = false;
            }
        }

        if(unique){
            keys.push_back(key);
            values.insert(values.begin(), key);
            map.push_back(values);
        }
        else{
            cout<<"Key not unique"<<endl;
        }
    }

    //returns iterator to the beginning of the map
    vector<vector<string>>::iterator begin(){
        return map.begin();
    }

    //returns iterator to the end of the map
    vector<vector<string>>::iterator end(){
        return map.end();
    }

    //returns iterator to the element in the map with the given key
    vector<vector<string>>::iterator find(string key){
        vector<vector<string>>::iterator it;
        for(it=map.begin(); it!=map.end(); it++){
            if((*it)[0] == key){
                return it;
            }
        }
        return map.end();
    }

    //erases the key, value pair in the map given a key to erase
    void erase(string key){
        for(int i=0; i<map.size(); i++){
            if(map[i][0]==key){
                map[i].clear();
            }
        }
    }

    //returns the map vector
    vector<vector<string>> returnMap(){
        return map;
    }

    //prints every element held in the map
    void printMap(int num){
        for(int i=0; i<num; i++){
            for(int j=0; j<map[i].size(); j++){
                cout<<map[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

//movie class that stores the movie id number, name, rating, duration, and description
//only has constructor and return functions
class Movies {
private:
    int id;
    string name;
    float rating;
    int date;
    int duration;
    string description;
public:
    Movies(int id, string name, float rating, int date, int duration, string description) {
        this->id = id;
        this->name = name;
        this->rating = rating;
        this->date = date;
        this->duration = duration;
        this->description = description;
    }

    int getId() {
        return id;
    }
    string getName(){
        return name;
    }
    float getRating(){
        return rating;
    }
    int getDate() {
        return date;
    }
    int getDuration() {
        return duration;
    }
    string getDescription(){
        return description;
    }
};

//iterates through the unordered map to find the top five highest ranked movies with the given genre, year, and duration
//returns a vector of keys to the movies
vector<string> findBestMovieUnordered(unorderedMap um, string genre, string year, string duration){
    vector<string> topRanked;
    vector<pair<float, string>> topFive;
    vector<vector<string>>::iterator it;
    int timing = stof(duration)*60;
    for(it = um.begin(); it != um.end(); it++){
        bool genre1 = false;
        bool date = false;
        bool length = false;
        float rating = stof((*it)[2]);
        if(stoi((*it)[3]) == stoi(year)){
            date = true;
        }
        if(stof((*it)[4]) <= timing){
            length = true;
        }
        for(int i=6; i<(*it).size(); i++){
            if((*it)[i] == genre){
                genre1 = true;
            }
        }
        if(genre1 && date && length){
            pair<float,string> p1 = make_pair(stof((*it)[2]), (*it)[0]);
            topFive.push_back(p1);
        }
    }
    std::sort(topFive.begin(), topFive.end());

    for(auto iter=topFive.end()-1; iter!=topFive.end()-6; iter--){
        topRanked.push_back(iter->second);
    }
    return topRanked;
}

//goes through the movies and genres in the csv data files and adds them to the unordered map
void makeUnorderedMap(unorderedMap &um, vector<Movies> movieVect){
    for(int i=0; i<movieVect.size(); i++){
        int id = movieVect[i].getId();
        string name = movieVect[i].getName();
        float rating = movieVect[i].getRating();
        int date = movieVect[i].getDate();
        int duration = movieVect[i].getDuration();
        string description = movieVect[i].getDescription();

        vector<string> values = {name, to_string(rating), to_string(date), to_string(duration), description};
        um.insert(to_string(id), values);
    }

    ifstream inFile;
    inFile.open("C:\\DSAProject3/genres.csv", ios::in);

    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }

    string id, line, genre;

    getline(inFile, line);
    istringstream l(line);

    getline(l, id, ',');
    getline(l, genre, ',');

    for(int i=0; i<100000; i++){
        getline(inFile, line);
        istringstream l(line);


        getline(l, id, ',');
        getline(l, genre, ',');

        auto it = um.find(id);
        if(it != um.end()){
            it->push_back(genre);
        }

        genre = "";

    }
    inFile.close();

}

//goes through the movies and genres in the csv data files, creates a movie object with the data, adds them to vector of movie objects
void readMovies(vector<Movies> &movieVect){
    ifstream inFile;

    inFile.open("C:\\DSAProject3/movies.csv", ios::in);
    if (!inFile.is_open()) {
        cout << "unopened" << endl;
    }
    string line, movieId, name, rating, date, minute, description;
    getline(inFile, line);
    istringstream s(line);


    getline(s, movieId, ',');
    getline(s, name, ',');
    getline(s, rating, ',');
    getline(s, date, ',');
    getline(s, minute, ',');
    getline(s, description);


    for(int i=0; i<100000; i++){
        getline(inFile, line);
        istringstream s(line);

        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');
        getline(s, date, ',');
        getline(s, minute, ',');
        getline(s, description);


        try{
            Movies m1(stoi(movieId), name, stof(rating), stoi(date), stoi(minute), description);
            movieVect.push_back(m1);
        }
        catch(const std::invalid_argument &e){
            cout<<"invalid stoi with "<<movieId<<endl;
            continue;
        }
    }
    inFile.close();
}

//iterates through the map to find the top five highest ranked movies with the given genre, year, and duration
//returns a vector of keys to the movies
vector<string> findBestMovieMap(map<string,vector<string>> m, string genre1, string year, string duration){
    vector<pair<float, string>> ratingVector;
    vector<string> topMovies;
    map<string, vector<string>>::iterator it;
    for(it=m.begin(); it != m.end(); it++){
        bool genre = false, date = false, length = false;
        try{
            // Saves rating
            float rating = stof(it->second[1]);
            // Iterates through genres of movie id
            if(stoi(it->second[2]) == stoi(year)){
                date = true;
            }
            if(stof(it->second[3]) <= stof(duration)*60.0){
                length = true;
            }
            for(int i=5; i<it->second.size(); i++){
                if(it->second[i]== genre1){
                    genre = true;
                }
            }
            if(date && length && genre){
                ratingVector.emplace_back(rating, it->first);
            }
        }
        catch(const std::invalid_argument &e){
            cout<<"invalid stof "<<it->second[1]<<" "<<it->first<<endl;
            continue;
        }
    }
    sort(ratingVector.begin(), ratingVector.end());
    for(int i = ratingVector.size() - 1; i > ratingVector.size() - 6; i--)
    {
        topMovies.push_back(ratingVector[i].second);
    }
    return topMovies;
}

//goes through the movies and genres in the csv data files and adds them to the unordered map
void makeMap(map<string, vector<string>> &m){


    ifstream inFile;
    inFile.open("C:\\DSAProject3/movies.csv", ios::in);


    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }


    string movieId;
    vector<string> movieElements;
    string line, name, rating, date, minute, description;


    getline(inFile, line);
    istringstream s(line);




    getline(s, movieId, ',');
    getline(s, name, ',');
    getline(s, rating, ',');
    getline(s, date, ',');
    getline(s, minute, ',');
    getline(s, description);


    for(int i=0; i<100000; i++){
        movieElements.clear();


        getline(inFile, line);
        istringstream s(line);




        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');
        getline(s, date, ',');
        getline(s, minute, ',');
        getline(s, description);

        movieElements.push_back(name);
        movieElements.push_back(rating);
        movieElements.push_back(date);
        movieElements.push_back(minute);
        movieElements.push_back(description);


        m.insert({movieId, movieElements});
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


    for(int i=0; i<100000; i++){
        getline(inFile, line);
        istringstream b(line);




        getline(b, id, ',');
        getline(b, genre, ',');


        auto it = m.find(id);
        if(it != m.end()){
            it->second.push_back(genre);
        }


        genre = "";


    }
    inFile.close();
}


int main() {
    map<string, vector<string>> m;
    unorderedMap um;
    vector<Movies> movieVect;

    cout << " _______________________________________" << endl;
    cout << "|         Welcome to Show-Intel!        |" << endl;
    cout << "|---------------------------------------|" << endl;
    cout << "|      Action              Adventure    |" << endl;
    cout << "|      Animation           Comedy       |" << endl;
    cout << "|      Crime               Documentary  | " << endl;
    cout << "|      Drama               Family       |" << endl;
    cout << "|      Fantasy             History      |" << endl;
    cout << "|      Horror              Music        |" << endl;
    cout << "|      Mystery             Romance      |" << endl;
    cout << "|      Science Fiction     Thriller     |" << endl;
    cout << "|      TV Movie            War          |" << endl;
    cout << "|      Western                          |" << endl;
    cout << "-----------------------------------------" << endl;

    cout<<endl;
    string genre1, date, duration;

    cout<<"Enter desired genre: ";
    cin >> genre1;
    cout<<endl;

    cout<<"Enter desired year: ";
    cin >> date;
    cout<<endl;

    cout<<"Enter maximum duration (in hours): ";
    cin >> duration;
    cout<<endl<<endl<<endl;


    //auto start = high_resolution_clock ::now();
    readMovies(movieVect);
    makeUnorderedMap(um, movieVect);
//    auto stop = high_resolution_clock ::now();
//    auto difference = duration_cast<microseconds>(stop - start);
//    cout << difference.count() << endl;
//
    vector<string> bestUmMovies = findBestMovieUnordered(um, genre1, date, duration);
    if(bestUmMovies.size()<5){
        cout<<"Sorry, there are only "<<bestUmMovies.size()<<" to match your search: "<<endl;
    }
    cout << "Your top five recommended movies with unordered map:\n" << endl;
    cout << "Name(Year)          Rating            Duration" << endl;
    cout<<endl;

    for(int i=0; i<bestUmMovies.size(); i++){
        auto it = um.find(bestUmMovies[i]);
        if(it != um.end()){
            cout << i+1 << ". " << (*it)[1]<<"("<<(*it)[3]<<")    Rating: " << (*it)[2] <<"    Duration: "<<(*it)[4]<<" minutes"<< endl;
            cout << "Description: " << (*it)[5]<< "\n";
            cout<<endl;
        }
    }

    cout<<endl<<endl<<endl;

//    auto start = high_resolution_clock ::now();
    makeMap(m);
    vector<string> bestMovieId = findBestMovieMap(m, genre1, date, duration);
//    auto stop = high_resolution_clock ::now();
//    auto difference = duration_cast<microseconds>(stop - start);
//    cout << difference.count() << endl;

    cout << " Your top five recommended movies with map:\n" << endl;
    cout << "Name(Year)          Rating            Duration" << endl;
    cout<<endl;

    if(bestMovieId.size()<5){
        cout<<"Sorry, there are only "<<bestMovieId.size()<<" to match your search: "<<endl;
    }
    for(int i = 0; i < bestMovieId.size(); i++)
    {
        auto it = m.find(bestMovieId[i]);
        cout << i+1 << ". " << it->second[0]<<"("<<it->second[2]<<")    Rating: " << it->second[1] <<"    Duration: "<<it->second[3]<<" minutes"<< endl;
        cout << "Description: " << it->second[4]<< "\n";
        cout<< endl;
    }


    return 0;
}