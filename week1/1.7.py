for i in range(2,101):
    if (i == 2) or (i == 3) or (i == 5) or (i == 7):
        print(str(i) +",")
    
    elif ((i%2) == 0) or ((i%3) == 0) or ((i%5) == 0) or ((i%7) == 0):
        x = 1
    else:
        print(str(i)+",")