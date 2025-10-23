-- Determine the average rating of all movies released in 2012.

-- Using SELECTs
SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012); 

-- Using JOIN
SELECT AVG(ratings.rating) FROM ratings JOIN movies ON ratings.movie_id = movies.id WHERE movies.year = 2012;