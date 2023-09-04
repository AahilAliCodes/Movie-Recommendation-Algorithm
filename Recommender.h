#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "UserDatabase.h"
#include "MovieDatabase.h"

//class UserDatabase;
//class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {
    }
    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database) : m_user_database(&user_database), m_movie_database(&movie_database)
    {
    
    }
    ~Recommender();
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;
  private:
   const UserDatabase* m_user_database; //create pointer to databases to avoid malloc error (free a pointer that was already freed, or if you are trying to free a pointer that was not allocated dynamically.)
   const MovieDatabase* m_movie_database;
};

#endif // RECOMMENDER_INCLUDED
