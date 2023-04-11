semester1courses_raw = str(input("Please enter the courses you have taken previously with letter grades: "))

colons1 = semester1courses_raw.count(":")
semis1 = semester1courses_raw.count(";")

if colons1 == semis1 + 1 :

  semester2courses_raw = str(input("Please enter the courses you have taken this semester with letter grades: "))

  colons2 = semester2courses_raw.count(":")
  semis2 = semester2courses_raw.count(";")
  
  if colons2 == semis2 +1 :

    x = str(input("Please enter the course you want to check: "))

    q1 = semester1courses_raw.replace(";", ":")
    s1 = q1.split(":")
    q2 = semester2courses_raw.replace(";", ":")
    s2 = q2.split(":")


    if s2.count(x) != 0 :

      x_grade2 = s2[s2.index(x) + 1].upper()
  
      if x_grade2 != "F" :
        print("You can choose between S and", x_grade2,  "for", x + ".")
      else:
       if s1.count(x) == 0 :
          print("Your grade for", x, "is U.")
       else:
          x_grade1 = s1[s1.index(x) + 1].upper()
          if x_grade1 == "U" :
           print("Your grade for", x, "is U.")
          else:
           print("Your grade for", x, "is F.")

    else:
        print("You didn't take", x, "this semester.")

  else:
    print("Invalid input")

else:
  print("Invalid input")