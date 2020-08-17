SELECT title from movies WHERE id in
	(SELECT movie_id FROM stars JOIN people ON (person_id = id) 
	WHERE name = "Johnny Depp")
INTERSECT
SELECT title from movies WHERE id in 
	(SELECT movie_id FROM stars JOIN people ON (person_id = id) 
	WHERE name = "Helena Bonham Carter")