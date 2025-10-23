-- Lists the names of songs that are by Post Malone

-- Using nested SELECTs
SELECT name FROM songs WHERE artist_id = ( SELECT id FROM artists WHERE name = 'Post Malone' );

-- Using JOIN
SELECT songs.name FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'Post Malone';