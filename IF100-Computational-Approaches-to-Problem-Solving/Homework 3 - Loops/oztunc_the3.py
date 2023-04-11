a1 = str(input("Please enter movie names and remaining quota: "))
a2 = a1.replace(":", ",")
a3 = a2.split(",")

a = a3[0::3]
b = a3[1::3]
c = a3[2::3]

movies = []
seats = []
genres = []

for film in a:
  if movies.count(film) == 0:   
    if a.count(film) > 1:
      pp = []
      for i in range(len(a)):
        if a[i] == film:
          pp.append(a.index(film, i))
      pp2 = []
      for k in pp:
        pp2.append(int(b[k]))
      seats_temp = sum(pp2)
      movies.append(film)
      seats.append(seats_temp)  
    elif a.count(film) == 1:
      movies.append(film)      
      seats.append(int(b[a.index(film)]))
    genres.append(c[a.index(film)])

movie_check = str(input("Please enter the movie you want to watch: "))

if movies.count(movie_check) == 0:
  print("There is no such movie in the theater.") # output 1
else:
  seat_check = int(input("Please enter the number of tickets you want to buy: "))
  if seats[movies.index(movie_check)] >= seat_check:
    print("The reservation is done!") # output 2
  elif seats[movies.index(movie_check)] < seat_check:
    same_genre_movies = []
    for i in range(len(genres)):
      if genres[i] == genres[movies.index(movie_check)]:
        if seats[i] >= seat_check:
          same_genre_movies.append(movies[i])
    if len(same_genre_movies) == 0:
     print("There are not enough seats for", movie_check, "and any other movie with the genre", genres[movies.index(movie_check)] + "!") #output3
    else:
      print("There are not enough seats for", movie_check + "! But you can watch one of the following movies from the genre", genres[movies.index(movie_check)] + ":") #output4
      for i in sorted(same_genre_movies):
        print("*", i)