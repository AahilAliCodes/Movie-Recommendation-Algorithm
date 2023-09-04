# Movie Recommendation Algorithm

The other day, I recommended Cocomelon on my Netflix home page. Despite finishing all 5 seasons of Breaking Bad and 8 seasons of Game of Thrones, I was flustered to see a kids' show on my recommendations page as an outlier to the hardcore TV-MA rated dramas. As I looked online for why this outlier was recommended to me, I read this Reddit thread of people complaining about the same thing. So naturally, I made my own recommendation algorithm.

## My algorithm:

The `recommend_movies` method is responsible for:

```plaintext
- Taking as parameters:
  - An email address for a user.
  - A maximum count of how many movies to recommend to the user based on the user's watching history.
  
- Using the provided email address to find all of the movies the user has watched in the past.

- For each movie `m` the user has previously watched, determining a compatibility score based on:
  - For each director `d` associated with `m`, each movie in the movie database that has `d` in its list of directors contributes 20 points to the compatibility score.
  - For each actor `a` associated with `m`, each movie in the movie database that has `a` in its list of actors contributes 30 points to the compatibility score.
  - For each genre `g` associated with `m`, each movie in the movie database that has `g` in its list of genres contributes 1 point to the compatibility score.

- For the movies that have a compatibility score of at least 1, filter out the movies that the user has already watched (so you don't recommend them).

- Rank ordering all candidate movies that have a compatibility score of at least 1, breaking ties as follows:
  - Movies with a higher compatibility score must be ordered higher on the recommendation list than movies with a lower compatibility score.
  - If two or more movies have the same compatibility score, they must be further ordered based on:
    - The movie's rating; a movie with a higher 5-star rating must be ordered higher on the recommendation list than a movie with a lower 5-star rating.
    - If two or more movies have the same compatibility score and the same 5-star rating, then they must be further ordered based on the movie's name, alphabetically, in ascending order (e.g., Avalanche comes before The Matrix).

- Returning a vector with the requested number of the most highly ranked movie recommendations, ordered as described above. If fewer compatible movies were found than the requested number, then the vector must have all movies with a compatibility score of at least 1, ordered as described above. (If the `movie_count` parameter is negative, act as if it were 0, returning an empty vector.)

Each recommendation (using the `MovieAndRank` struct) has the movie's ID (which can be used to look up the movie's details), and the compatibility score.

```

## Example Output:

```plaintext             
Enter a user's email for recommendations: KabiL@aol.com
     Enter number of recommendations to provide: 8
     User Kabir Luna has watched the following movies:
 							
      Notes On Blindness
      Lana: Queen of the Amazons
      The Big Bang
      Homefront
      For Ellen
      Hitch			
... the rest of the movies are omitted for this example			
Here are the recommendations:

1. The Blues Brothers (1980)
Rating: 3.79643
Compatibility Score: 390
					
2. The Player (1992)
   Rating: 3.92309
   Compatibility Score: 281
					
3. Trust the Man (2005)
   Rating: 2.82645
   Compatibility Score: 250
					
4. Never So Few (1959)
   Rating: 3.11111
   Compatibility Score: 234
					
5. Knocked Up (2007)
   Rating: 3.40438
   Compatibility Score: 230
		
6. The Ghost Comes Home (1940)
   Rating: 2
   Compatibility Score: 230
			
7. Hot Fuzz (2007)
   Rating: 3.86654
   Compatibility Score: 227
			
8. Filth (2013)
   Rating: 3.64121
   Compatibility Score: 221
```
