n = int(input("Enter a Number: "))
count = 1
x = 0
if(n!=17):
    while (count <= n):
        x = x + count
        count = count + 1
else:
    while (count <= n):
        if ((count%5)==0) or ((count%3)==0):
            x = x + count
            count = count + 1
        else:
            count = count +1
print (x)
