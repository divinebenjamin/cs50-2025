-- Returns the average energy of songs that are by Drake

-- Using nested SELECTs
SELECT AVG(energy) FROM songs WHERE artist_id = ( SELECT id FROM artists WHERE name = 'Drake' );


-- Using JOIN
SELECT AVG(songs.energy) FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'Drake';