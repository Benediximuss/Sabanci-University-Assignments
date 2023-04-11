q=float(input("Please enter your internet quota (GB): "))
v=float(input("Please enter your total video viewing time in minutes: "))
m=int(input("Please enter the number of messages you send: "))

q2_mb=q*1024-(v*7.7+m*1.7/1024)
q2=round(q2_mb/1024, 2)
totmin=q2_mb/7.7
remhour=totmin//60
remmin=(totmin-remhour*60)//1
remsec=round((totmin*60)-(remhour*3600+remmin*60), 2)

print("Your remaining internet quota is {} GB(s).".format(q2))
print("You can watch video for {0} hour(s), {1} minute(s) and {2} second(s).".format(int(remhour),int(remmin),remsec))