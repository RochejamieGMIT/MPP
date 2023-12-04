import csv 
import time
import os




def main():
    cash = getCash("stock.csv")
    shop = readInShopCSV("stock.csv")
    #print("Available cash in Shop: " + str(cash))
    while True:
        display_menu() # Calls function to display method options 
        # https://stackoverflow.com/questions/40056747/print-a-list-of-dictionaries-in-table-form
        option = input("Select: ") # take input from user 
        if (option == "1"):
            existingCust()
        elif (option == "2"):
            LiveBuy()
        elif (option == "3"):
            print("Current Stock in Shop \n")
            for product in shop:  # Iterate through each product in the shop list
                print_product(product)
            time.sleep(1)

        elif (option == "4"):
           cash = round(float(getCash("stock.csv")),2)
           print(f'Shop Current Balance is €{cash}')
            
        elif (option == "x"):
            print("Closing app") 
            break # breaks loop and closes the program
        else:
             print("Invalid Option") # any other option is invalid 



def print_product(product):
        print(f"Name: {product['name']}, Price: {product['price']}, Quantity: {product['quantity']}")


def read_customer(cust):
    customer = {}
    with open(cust) as csv_file:
        csv_reader = csv.reader(csv_file,delimiter=",")
        first_row = next(csv_reader)
        customer["name"] = first_row[0]
        customer["cash"] = float(first_row[1])
        customer["products"] = []
        for row in csv_reader:
            product = {}
            product["name"] = row[0]
            product["quantity"] = int(row[1])
            customer["products"].append(product)
        return customer

def print_cust(customer):
    print(f'Name: {customer["name"]} cash: {customer["cash"]}')
    print(f'\nShopping list for {customer["name"]}')
    for product in customer["products"]:
        print(f"Name: {product['name']}, Quantity: {product['quantity']}")

# https://stackoverflow.com/questions/17262256/how-to-read-one-single-line-of-csv-data-in-python 
def getCash(filename):
    cash = 0
    with open(filename, mode ='r') as file:   
        csv_reader = csv.reader(file)
        cashLine = next(csv_reader)
    #print (cashLine)
    cash = cashLine[1]
    #print(cash)
    return cash

def readInShopCSV(filename):
    shop = {}
    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file,delimiter=",")
        next(csv_reader)
        shop["products"]=[]
        for row in csv_reader:
            product = {}
            product["name"] = row[0]
            product["price"] = float(row[1])
            product["quantity"] = int(row[2])
            shop["products"].append(product)
            #print_product(product)
        return shop["products"]

def existingCust():
    print("Are you an existing customer with a shopping list?")
    print("Type 1 for yes, 2 for no")
    while True:
       
        # https://stackoverflow.com/questions/40056747/print-a-list-of-dictionaries-in-table-form
        option = input("Select: ") # take input from user 
        if (option == "1"):
            # https://builtin.com/data-science/python-list-files-in-directory
            exist = os.listdir("Customers")
            print("Existing Customers \n------------------- \n")
            for x in exist:
                print(x[:-4])
            option2 = input("\nWhat is your name from the list above?")
            option2 = option2.lower()+ ".csv"
            
            if option2 in exist:
                CustDir = ("Customers\\" + option2)
                buyingCSV(CustDir)
                break

            else: 
                print("Does not Exist, Try again")
                print("Are you an existing customer with a shopping list?")
                print("Type 1 for yes, 2 for no")
                
        elif (option == "2"):
            print("Sorry, Shopping with a list is for exisitng customers only\n You will be sent back to the main menu")
            break # Send back to main menu
        else:
             print("Invalid Option") # any other option is invalid 

def buyingCSV(CustDir):
    c = read_customer(CustDir)
    print_cust(c)
    shop = readInShopCSV("stock.csv")
    Cash = float(getCash("stock.csv"))
    total = 0
    flag = 0
    stockout={}
    stockout["products"]=shop
    for Cproduct in c["products"]:
        n = Cproduct['name']
        q = Cproduct['quantity']
        for Sproduct in shop:
            if Sproduct['name'] == n:
                #print(product)
                if q > Sproduct["quantity"]:
                    #print("sorry there is not enough stock to complete the tansaction, This order will be terminated")
                    flag = 1
                    break
                else:
                    Sproduct["quantity"] = Sproduct["quantity"] - q
                    #print(Sproduct["quantity"])
                    total = total + q*Sproduct["price"]
                    #print(total)
                    # PRINTING MULITPLE TIMES for each item in persons basket 
                    #stockout["products"].append(Sproduct)      
    if total > c["cash"]:
        flag = 2
                
    if flag == 0:
        print(f'Total cost to {c["name"]} = {total}')
        c["cash"] = c["cash"] - total
        print(f'{c["name"]} new balance = {c["cash"]}')

        #https://stackoverflow.com/questions/9427163/remove-duplicate-dict-in-list-in-python 
        # remove duplicates in output to stock file
                
        [i for n, i in enumerate(stockout["products"]) if i not in stockout["products"][n + 1:]]
        #https://www.geeksforgeeks.org/reading-and-writing-csv-files-in-python/
        # https://ioflood.com/blog/python-write-to-csv/#:~:text=Python's%20CSV%20Module%20Uncovered,-Python's%20csv%20module&text=It%20defines%20the%20writer%20and,rows%20to%20the%20CSV%20file.
        with open("stock.csv", 'w',newline='') as file:
            writer1 = csv.writer(file)
            # https://www.programiz.com/python-programming/methods/built-in/round
            #keep cash in csv to max 2 decimal places
            writer1.writerow(['cash',round(Cash+total,2)])
            fieldnames = ["name","price","quantity"]
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writerows(stockout["products"])
            file.close()


                           
    elif flag == 1:
        print("sorry there is not enough stock to complete the tansaction, This order will be terminated")
    elif flag == 2:
        print(f' {c["name"]} did not have enough cash for this tansaction, This order will be terminated')
    else:
        print("Error occured")       
        
def LiveBuy():
    print("Menu\n=========================")
    shop = readInShopCSV("stock.csv")
    for product in shop:  # Iterate through each product in the shop list
                print_product(product)
    print("\n=========================")
    stockout={}
    stockout["name"]=[]
    stockout["products"]=[]
    name = input("Enter Your name: ") # take input from user 
    budget = input("Enter your budget: ") # take input from user
    stockout["products"].append({"name":name,"quantity":budget})
    print("Please enter the itmes you would like to buy, when ready to submit order enter y, or x to exit\n")
    while True:
        option = input("Select: ") # take input from user 
        if (option == "Coke Can"):
            option2 = input("enter quantity: ")
            stockout["products"].append({"name":option,"quantity":option2})
            print("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n")
        elif (option == "Bread"):
            option2 = input("enter quantity: ")
            stockout["products"].append({"name":option,"quantity":option2})
            print("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n")
        elif (option == "Spaghetti"):
            option2 = input("enter quantity: ")
            stockout["products"].append({"name":option,"quantity":option2})
            print("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n")
        elif (option == "Tomato Sauce"):
            option2 = input("enter quantity: ")
            stockout["products"].append({"name":option,"quantity":option2})
            print("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n")    
        elif (option == "Bin Bags"):
            option2 = input("enter quantity: ")
            stockout["products"].append({"name":option,"quantity":option2})
            print("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n")
        elif (option == "y"):
            #print(stockout["products"])
            [i for n, i in enumerate(stockout["products"]) if i not in stockout["products"][n + 1:]]
        #https://www.geeksforgeeks.org/reading-and-writing-csv-files-in-python/
        # https://ioflood.com/blog/python-write-to-csv/#:~:text=Python's%20CSV%20Module%20Uncovered,-Python's%20csv%20module&text=It%20defines%20the%20writer%20and,rows%20to%20the%20CSV%20file.
            with open("LiveBasket.csv", 'w',newline='') as file:
                # https://www.programiz.com/python-programming/methods/built-in/round
                #keep cash in csv to max 2 decimal places
                fieldnames = ["name","quantity"]
                writer = csv.DictWriter(file, fieldnames=fieldnames)
                writer.writerows(stockout["products"])
                file.close()
            buyingCSV("LiveBasket.csv")
            break # breaks loop and closes the program
        elif (option == "x"):
            print("Returning to menu") 
            time.sleep(1)
            break # breaks loop and closes the program
        else:
             print("Item not in shop list") # any other option is invalid 




def display_menu(): # display menu 
    print("Welcome to the python procedural shop \n----------\n")
    print("Menu\n====")
    print("1 - Buy With Shopping List (CSV)")
    print("2 - Buy Live")
    print("3 - Check Shop Stock")
    print("4 - Check Shop Cash Balance")
    print("x - Exit application")

    #existingCust()
    #customer = read_customer()
    #print_cust(customer)


if __name__ == "__main__":
    main()




    
