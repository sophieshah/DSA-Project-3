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

    void printMap(int num){
        for(int i=0; i<num; i++){
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

vector<string> findBestMovieUnordered(unorderedMap um, string genre){
    vector<string> topRanked;
    vector<pair<float, string>> topFive;
    vector<vector<string>>::iterator it;
    //cout<<"about to start loop"<<endl;
    for(it = um.begin(); it != um.end(); it++){
        //cout<<(*it).size()<<endl;
        for(int i=6; i<(*it).size(); it++){
            if((*it)[i] == genre){
                //cout<<"found movie with genre "<<genre<<endl;
                pair p1 = make_pair(stof((*it)[2]), (*it)[0]);
                topFive.push_back(p1);
            }
        }
    }
    //cout<<"made it to end of top5"<<endl;
    std::sort(topFive.begin(), topFive.end());
    for(auto iter=topFive.end(); iter!=topFive.end()-6; iter--){
        topRanked.push_back(iter->second);
        //cout<<iter->second<<" "<<iter->first<<" ";
    }
    //cout<<endl;
    topRanked.erase(topRanked.begin());
    //cout<<topRanked.size();
    return topRanked;
}

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

    for(int i=0; i<10000; i++){
        getline(inFile, line);
        istringstream l(line);


        getline(l, id, ',');
        getline(l, genre, ',');

        //cout<<id<<" "<<genre<<endl;

        auto it = um.find(id);
        if(it != um.end()){
            it->push_back(genre);
        }

        genre = "";

    }
    inFile.close();

}

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


    for(int i=0; i<10000; i++){
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

vector<string> findBestMovieMap(map<string,vector<string>> m, string genre1){
    vector<pair<float, string>> ratingVector;
    vector<string> topMovies;
    map<string, vector<string>>::iterator it;
    for(it=m.begin(); it != m.end(); it++){
        try{
            // Saves rating
            float rating = stof(it->second[1]);
            // Iterates through genres of movie id
            for(int i=5; i<it->second.size(); i++){
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
        //cout << ratingVector[i].second << endl;
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
    string line, name, rating, date, minute, description;


    getline(inFile, line);
    istringstream s(line);




    getline(s, movieId, ',');
    getline(s, name, ',');
    getline(s, rating, ',');
    getline(s, date, ',');
    getline(s, minute, ',');
    getline(s, description);


    for(int i=0; i<10000; i++){
        movieElements.clear();


        getline(inFile, line);
        istringstream s(line);




        getline(s, movieId, ',');
        getline(s, name, ',');
        getline(s, rating, ',');
        getline(s, date, ',');
        getline(s, minute, ',');
        getline(s, description);


        //cout<<movieId<<" "<<name<<" "<<rating<<endl;
        //movieElements.push_back(movieId);
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
    unorderedMap um;
    vector<Movies> movieVect;


    makeMap(m);
    readMovies(movieVect);
    makeUnorderedMap(um, movieVect);

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
    cout<<"Enter desired genre: ";
    string genre1;


    cin >> genre1;
    cout<<endl<<endl<<endl;
    //cout<<genre1<<endl;


    findBestMovieUnordered(um, genre1);
    vector<string> bestUmMovies = findBestMovieUnordered(um, genre1);
    cout << "        Your top five recommended movies:\n" << endl;
    cout << "Name(Year)          Rating            Duration" << endl;
    cout << "-----------------------------------------------" << endl;
    cout<<endl;

    for(int i=0; i<5; i++){
        auto it = um.find(bestUmMovies[i]);
        if(it != um.end()){
            cout << i+1 << ". " << (*it)[1]<<"("<<(*it)[3]<<")    Rating: " << (*it)[2] <<"    Duration: "<<(*it)[4]<< endl;
            cout << "Description: " << (*it)[5]<< "\n";
            cout<<endl;
        }
    }


   vector<string> bestMovieId = findBestMovieMap(m, genre1);
    cout << "        Your top five recommended movies:\n" << endl;
    cout << "Name(Year)          Rating            Duration" << endl;
    cout << "-----------------------------------------------" << endl;
    cout<<endl;

    for(int i = 0; i < bestMovieId.size(); i++)
    {
        auto it = m.find(bestMovieId[i]);
        cout << i+1 << ". " << it->second[0]<<"("<<it->second[2]<<")    Rating: " << it->second[1] <<"    Duration: "<<it->second[3]<< endl;
        cout << "Description: " << it->second[4]<< "\n";
        cout<< endl;
    }


    return 0;
}