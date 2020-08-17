SELECT name FROM people JOIN stars ON (id = person_id) WHERE movie_id in 
(SELECT movie_id from stars JOIN people ON (id = person_id) WHERE name = "Kevin Bacon") 
AND name != "Kevin Bacon"