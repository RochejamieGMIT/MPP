import math 

n = int(input("Enter a Number: "))
s = input("Type S for Sum or P for Product")
x = 0
count = 1

if(s =="S") or (s=="s"):
    while (count <= n):
        x = x + count
        count = count + 1
elif(s =="P") or (s=="p"):
    x = math.factorial(n)
else:
    print("Incorrect input")
print(x)

