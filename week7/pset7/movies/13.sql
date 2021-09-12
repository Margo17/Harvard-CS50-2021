-- SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

SELECT DISTINCT(name)
FROM stars
JOIN people ON people.id = stars.person_id
WHERE movie_id IN
(SELECT movie_id
FROM people
JOIN stars ON stars.person_id = people.id
WHERE name = "Kevin Bacon" AND birth = 1958)
AND name != "Kevin Bacon";