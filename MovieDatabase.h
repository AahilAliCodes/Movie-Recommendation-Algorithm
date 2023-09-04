#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::vector<Movie*> m_movies;
    TreeMultimap<std::string, Movie*> m_directors_tree;
    TreeMultimap<std::string, Movie*> m_actors_tree;
    TreeMultimap<std::string, Movie*> m_genres_tree;
    TreeMultimap<std::string, Movie*> m_ids_tree;
    std::vector<std::string> splitCommas(const std::string line);
    std::string make_lowercase(const std::string& str) const;
};

#endif // MOVIEDATABASE_INCLUDED
