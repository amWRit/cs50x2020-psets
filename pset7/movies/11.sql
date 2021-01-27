SELECT title from movies join
(SELECT ratings.movie_id, ratings.rating from ratings JOIN
	(SELECT stars.movie_id from
	stars join people
	on stars.person_id = people.id
	WHERE people.name = "Chadwick Boseman") as temp
	on ratings.movie_id = temp.movie_id ORDER BY rating DESC
	) as temp_ratings
on movies.id = temp_ratings.movie_id
LIMIT 5;