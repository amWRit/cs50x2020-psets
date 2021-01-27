SELECT title, rating from ratings
join
(SELECT id, title from movies where year = 2010 ORDER BY title ASC) as movies_temp
on ratings.movie_id = movies_temp.id
ORDER by rating DESC;