#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

class unorderedMap{
private:
    vector<vector<string>> map;
    vector<string> keys;
public:
    void insert(string key, vector<string> values){
        bool unique = true;
        for(int i=0; i<keys.size(); i++){
            if(keys[i]==key){
                unique = false;
            }
        }

        if(unique){
            values.insert(values.begin(), key);
            map.push_back(values);
        }
        else{
            cout<<"Key not unique"<<endl;
        }
    }

    vector<vector<string>>::iterator begin(){
        return map.begin();
    }

    vector<vector<string>>::iterator end(){
        return map.end();
    }

    vector<vector<string>>::iterator find(string key){
        vector<vector<string>>::iterator it;
        for(it=map.begin(); it!=map.end(); it++){
            if((*it)[0] == key){
                return it;
            }
        }
        return map.end();
    }

    int bucket(string key){
        for(int i=0; i<map.size(); i++) {
            if (map[i][0] == key) {
                return i+1;
            }
        }
        return -1;
    }

    int bucketCount(){
        return map.size();
    }

    bool empty(){
        if(map.size()==0){
            return true;
        }
        return false;
    }

    void erase(string key){
        for(int i=0; i<map.size(); i++){
            if(map[i][0]==key){
                map[i].clear();
            }
        }
    }

    vector<vector<string>> returnMap(){
        return map;
    }

    void printMap(){
        for(int i=0; i<map.size(); i++){
            for(int j=0; j<map[i].size(); j++){
                cout<<map[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

class Movies {
private:
    int id;
    string name;
    float rating;
public:
    Movies(int id, string name, float rating) {
        this->id = id;
        this->name = name;
        this->rating = rating;
    }

    int getId() {
        return id;
    }
};

vector<string> findBestMovieMap(map<string,vector<string>> m, string genre1){
    vector<pair<float, string>> ratingVector;
    vector<string> topMovies;
    map<string, vector<string>>::iterator it;
    for(it=m.begin(); it != m.end(); it++){
        try{
            // Saves rating
            float rating = stof(it->second[1]);
            // Iterates through genres of movie id
            for(int i=2; i<it->second.size(); i++){
                //cout<<rating<<endl;
                if(it->second[i]== genre1){
                    ratingVector.emplace_back(rating, it->first);
                }
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
        cout << ratingVector[i].second << endl;
        topMovies.push_back(ratingVector[i].second);
    }
    return topMovies;
}
void makeMap(map<string, vector<string>> &m){
    ifstream inFile;
    inFile.open("C:\\DSAProject3/movies.csv", ios::in);
    if (!inFile.is_open()) {
        cout<<"unopened"<<endl;
    }
    string movieId;
    vector<string> movieElements;
    string line, name, rating;
    getline(inFile, line);
    istringstream s(line);
    getline(s, movieId, ',');
    getline(s, name, ',');
    getline(s, rating, ',');
    for(int i=0; i<10000; i++){
        movieElements.clear();
        getline(inFile, line);
        istringstream s(line);
        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');
        //cout<<movieId<<" "<<name<<" "<<rating<<endl;
        //movieElements.push_back(movieId);
        movieElements.push_back(name);
        movieElements.push_back(rating);
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
    for(int i=0; i<10000; i++){
        getline(inFile, line);
        istringstream b(line);
        getline(b, id, ',');
        getline(b, genre, ',');
        //cout<<id<<" "<<genre<<endl;
        auto it = m.find(id);
        if(it != m.end()){
            it->second.push_back(genre);
        }
        genre = "";
    }
    inFile.close();
//    map<string, vector<string>>::iterator it;
//    for(it = m.begin(); it != m.end(); it++){
//        cout<<it->first<<" ";
//        for(int i=0; i<it->second.size(); i++){
//            cout<<it->second[i]<<" ";
//        }
//        cout<<endl;
//    }
}
int main() {
    map<string, vector<string>> m;
    makeMap(m);
    cout << " _______________________________________" << endl;
    cout << "|         Welcome to Show-Intel!        |" << endl;
    cout << "|           You Tell, We Show           |" << endl;
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
    cout<<"Enter desired genre: ";
    string genre1;


    cin >> genre1;


    cout<<endl;


    cout<<genre1<<endl;


    vector<string> bestMovieId = findBestMovieMap(m, genre1);
    cout << "        Your top five recommended movies:\n" << endl;
    cout << "Name(Year)          Rating            Duration" << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < bestMovieId.size(); i++)
    {
        auto it = m.find(bestMovieId[i]);
        cout << i << ". " << it->second[0] << it->second[1] << endl;
        cout << "Description: " << "\n"<< endl;
    }

    return 0;
}