#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
using namespace std;

Recommender::~Recommender()
{
//    m_user_database = nullptr;
//    m_movie_database = nullptr;
}
vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const {
    vector<MovieAndRank> movie_scores; //
    User* user = m_user_database->get_user_from_email(user_email);

    if (!user) { //if null
        return movie_scores;
    }

    const vector<string> watched_movie_ids = user->get_watch_history(); // store users watch history in this vector
    unordered_set<string> watched_movie_ids_set(watched_movie_ids.begin(), watched_movie_ids.end()); // convert to hash table for O(1) lookup functionality
    unordered_map<string, int> compatibility_scores; // store scores in this unordered map for quick lookup
    for (const string& movie_id : watched_movie_ids) {
        const Movie* movie_ptr = m_movie_database->get_movie_from_id(movie_id);
        for (const string& director : movie_ptr->get_directors()) {
            for (const Movie* other_movie : m_movie_database->get_movies_with_director(director)) { // I have a pointer another movies with same director and while they arent in watched ids, we count them
                const string& other_movie_id = other_movie->get_id();
                if (watched_movie_ids_set.count(other_movie_id) == 0) {
                    compatibility_scores[other_movie_id] += 20; //I add 20 points for directors
                }
            }
        }
        for (const string& actor : movie_ptr->get_actors()) {
            for (const Movie* other_movie : m_movie_database->get_movies_with_actor(actor)) { // I have a pointer another movies with same actor and while they arent in watched ids, we count them
                const string& other_movie_id = other_movie->get_id();
                if (watched_movie_ids_set.count(other_movie_id) == 0) {
                    compatibility_scores[other_movie_id] += 30; //I add 30 points for actors
                }
            }
        }
        for (const string& genre : movie_ptr->get_genres()) {
            for (const Movie* other_movie : m_movie_database->get_movies_with_genre(genre)) {
                const string& other_movie_id = other_movie->get_id(); // I have a pointer another movies with same genre and while they arent in watched ids, we count them
                if (watched_movie_ids_set.count(other_movie_id) == 0) {
                    compatibility_scores[other_movie_id] += 1; //I add1 point for genre
                }
            }
        }
    }

    vector<MovieAndRank> movies; //place unsorted potential movies in this vector as long as greater than 1 score
    for (const pair<string, int> compatibility_score : compatibility_scores) {
        if (compatibility_score.second >= 1) { //check if greater than or equal to 1
            movies.emplace_back(compatibility_score.first, compatibility_score.second);
        }
    }

    sort(movies.begin(), movies.end(), [&](const MovieAndRank& a, const MovieAndRank& b) { // use sort function in STL vector class to sort based on precidence
        const Movie* movie_a = m_movie_database->get_movie_from_id(a.movie_id);
        const Movie* movie_b = m_movie_database->get_movie_from_id(b.movie_id);

        if (a.compatibility_score != b.compatibility_score) {
            return a.compatibility_score > b.compatibility_score;
        } else if (movie_a->get_rating() != movie_b->get_rating()) {
            return movie_a->get_rating() > movie_b->get_rating();
        } else {
            return movie_a->get_title() < movie_b->get_title();
        }
    });

    vector<MovieAndRank> recommended_movies; // final vector WITH sorted movies and I make sure to cut the vector down to the desired size.
    for (int i = 0; i < min(movie_count, static_cast<int>(movies.size())); ++i) {
        recommended_movies.emplace_back(movies[i]);
    }

    return recommended_movies;
}
