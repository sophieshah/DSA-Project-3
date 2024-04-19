#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>


using namespace std;


string findBestMovieMap(map<string,vector<string>> m, string genre1, string genre2){
    bool g1 = false , g2 = false;
    float highestRating = 0.0;
    string bestMovieId;


    map<string, vector<string>>::iterator it;
    for(it=m.begin(); it != m.end(); it++){
        try{
            float rating = std::stof(it->second[1]);
            for(int i=2; i<it->second.size(); i++){
                //cout<<rating<<endl;
                g1, g2 = false;


                if(it->second[i]== genre1){
                    g1 = true;
                }
                if(it->second[i] == genre2){
                    g2 = true;
                }


                if(g1 && g2 && rating > highestRating){
                    highestRating  = std::stof(it->second[1]);
                    bestMovieId = it->first;
                }
            }
        }
        catch(const std::invalid_argument &e){
            cout<<"invalid stof "<<it->second[1]<<" "<<it->first<<endl;
            continue;
        }




    }
    cout<<bestMovieId<<endl;
    return bestMovieId;
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


    cout<<"Enter two desired genres: ";


    string genre1, genre2;


    cin >> genre1;
    cin >> genre2;


    cout<<endl;


    cout<<genre1<<" "<<genre2<<endl;




    string bestMovieId = findBestMovieMap(m,genre1, genre2);
    auto it = m.find(bestMovieId);
    if(it != m.end()){
        cout<<"Your recommended movie is "<<it->second[0]<<endl;
    }
    else{
        cout<<"No movies match the search :("<<endl;
    }


    return 0;
}



