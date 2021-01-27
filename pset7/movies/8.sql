SELECT name from
people where id
in (SELECT stars.person_id from movies
join stars
on movies.id = stars.movie_id
where movies.title = "Toy Story") ;