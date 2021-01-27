SELECT title from movies
WHERE id in
(SELECT stars.movie_id from stars join people on stars.person_id = people.id where people.name = "Johnny Depp")
AND
id in
(SELECT stars.movie_id from stars join people on stars.person_id = people.id where people.name = "Helena Bonham Carter");