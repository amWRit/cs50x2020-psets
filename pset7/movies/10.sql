SELECT name from
people where id
in (SELECT directors.person_id from directors
join ratings
on directors.movie_id = ratings.movie_id
where ratings.rating >= 9.0);