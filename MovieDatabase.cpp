#include "MovieDatabase.h"
#include "Movie.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "treemm.h"
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}
MovieDatabase::~MovieDatabase() //delete dynamically allocated movies in the vector
{
    for (auto movie : m_movies) {
                delete movie;
            }
        m_movies.clear();
    }

    bool MovieDatabase::load(const string& filename)
    {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error: cannot open file " << filename << endl;
            return false;
        }

        string id;
        string id2;
        string line;
        string title;
        string releaseYear;
        vector<string> directors;
        vector<string> actors;
        vector<string> genres;
        float rating;
        
        while (getline(infile, id)) {
            id2 = id;
            id2 = make_lowercase(id2);
//            cout << id << endl;
            getline(infile, title);
//           cout << title << endl;
            getline(infile, releaseYear);
//            cout << releaseYear << endl;
            getline(infile, line);
            vector<string> temp;
            temp = splitCommas(line);
            for(string director : temp){ // make all lowercase
//                cout << director << endl;
                director = make_lowercase(director);
                directors.push_back(director);
            }
            getline(infile, line);
            temp = splitCommas(line);
            for(string actor : temp){
//                cout << actor << endl;
                actor = make_lowercase(actor);
                actors.push_back(actor);
            }
            getline(infile, line);
            temp = splitCommas(line);
            for(string genre : temp){
//                cout << genre << endl;
                genre = make_lowercase(genre);
                genres.push_back(genre);
            }
            infile >> rating;
//            cout << rating << endl;
            infile.ignore(10000, '\n'); // ignore blank line
            infile.ignore(10000, '\n');
            
            Movie* movie = new Movie(id2, title, releaseYear, directors, actors, genres, rating); // dynamically allocate a NEW Movie
            m_movies.push_back(movie); // push into vector

            m_ids_tree.insert(id2, movie);
            for (const std::string& director : directors) {
                m_directors_tree.insert(director, movie);
            }
            for (const std::string& actor : actors) {
                m_actors_tree.insert(actor, movie);
            }
            for (const std::string& genre : genres) {
                m_genres_tree.insert(genre, movie);
            }

            directors.clear(); // clear and restart
            actors.clear();
            genres.clear();
//            id = "";
//            id2 = "";
        }

//         cerr << "got here" << endl;
//        infile.close();
        return true;
    }


Movie* MovieDatabase::get_movie_from_id(const string& id) const {
    string id2 = make_lowercase(id); //make lowercase so that case INSENSITIVE
    auto it = m_ids_tree.find(id2);
    if (!it.is_valid()) {
        return nullptr;
    } else {
        return it.get_value();
    }
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> movies;
    string director2 = make_lowercase(director);
    TreeMultimap<string, Movie*>::Iterator it = m_directors_tree.find(director2);
    while (it.is_valid()) {
        Movie* movie = get_movie_from_id(it.get_value()->get_id());
        if (movie != nullptr) {
            movies.push_back(movie);
        }
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> movies;
    string actor2 = make_lowercase(actor);
    TreeMultimap<string, Movie*>::Iterator it = m_actors_tree.find(actor2);
    while (it.is_valid()) {
        Movie* movie = get_movie_from_id(it.get_value()->get_id());
        if (movie != nullptr) {
            movies.push_back(movie);
        }
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> movies;
    string genre2 = make_lowercase(genre);
    TreeMultimap<string, Movie*>::Iterator it = m_genres_tree.find(genre2);
    while (it.is_valid()) {
        Movie* movie = get_movie_from_id(it.get_value()->get_id());
        if (movie != nullptr) {
            movies.push_back(movie);
        }
        it.advance();
    }
    return movies;
}
vector<string> MovieDatabase::splitCommas(const std::string line) {
    vector<string> result;
    stringstream comma(line);

    for (std::string actor; std::getline(comma, actor, ','); ) {
        result.push_back(actor);
    }
    return result;
}

string MovieDatabase::make_lowercase(const string& str) const {
    string lowercase_str;
    for (char c : str) {
        lowercase_str += tolower(c);
    }
    return lowercase_str;
}
