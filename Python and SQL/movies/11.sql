SELECT title, rating FROM movies
INNER JOIN ratings ON id = movie_id
WHERE id in
(SELECT movie_id FROM stars WHERE person_id in
(SELECT id FROM people WHERE name = "Chadwick Boseman"))
ORDER by rating DESC LIMIT 5