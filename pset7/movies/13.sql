SELECT name from people
where id in
(SELECT person_id from stars where movie_id in
(SELECT stars.movie_id from stars join people on stars.person_id = people.id where people.name = "Kevin Bacon" and people.birth = 1958))
and name <> "Kevin Bacon";