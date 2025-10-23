-- List the names of all people who starred in Toy Story.

-- Using JOIN
SELECT name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id WHERE title = 'Toy story';

-- Using SELECTs
select name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE title = 'Toy Story'));