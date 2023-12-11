import csv 
import time
import os


class Product:

    def __init__(self, name, price=0):
        self.name = name
        self.price = price
    
    def __repr__(self):
        return f'Name: {self.name}, Price: {self.price},'

class ProductStock:
    
    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity
    
    def name(self):
        return self.product.name;
    
    def unit_price(self):
        return self.product.price;
        
    def cost(self):
        return self.unit_price() * self.quantity
        
    def __repr__(self):
        return f"{self.product} Quantity: {self.quantity}"

class Customer:

    def __init__(self, path):
        self.shopping_list = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                p = Product(name)
                ps = ProductStock(p, quantity)
                self.shopping_list.append(ps) 
                
    def calculate_costs(self, price_list):
        for shop_item in price_list:
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()
    
    def order_cost(self):
        cost = 0
        
        for list_item in self.shopping_list:
            cost += list_item.cost()
        
        return cost
    
    def __repr__(self):
        
        str = f"Shopping list for {self.name}"
        for item in self.shopping_list:
            cost = item.cost()
            str += "\nName: "
            str += f"{item.product.name}"
            str += f",Quantity: {item.quantity}"
            if (cost != 0):
                str += f" COST: {cost}"
                        
        return str 
    
    def CbuyingCSV(self,s):
        total = 0
        flag = 0                
        #s = Shop("stock.csv")
        self.order_cost()
        print(self)
        for Cproduct in self.shopping_list:
            for Sproduct in s.stock:
                if Sproduct.product.name == Cproduct.product.name:
                    #print(f'Item {Cproduct.product.name} found')
                    #print(Cproduct.quantity)

                    if Cproduct.quantity > Sproduct.quantity:
                        #print("sorry there is not enough stock to complete the tansaction, This order will be terminated")
                        flag = 1
                        break
                    else:
                        Sproduct.quantity = Sproduct.quantity - Cproduct.quantity
        self.calculate_costs(s.stock)
        orderCost = round(self.order_cost(),2)
        if orderCost > self.budget:
            flag = 2
        if flag == 0:
            print(f'Total cost to {self.name} = {orderCost}')
            with open("stock.csv", 'w',newline='') as file:
                writer1 = csv.writer(file)
                # https://www.programiz.com/python-programming/methods/built-in/round
                #keep cash in csv to max 2 decimal places
                writer1.writerow(['cash',round(s.cash+orderCost,2)])
                fieldnames = ["name","price","quantity"]
                for Sproduct in s.stock:
                    writer1.writerow([Sproduct.product.name,Sproduct.product.price,Sproduct.quantity])
                file.close()

        elif flag == 1:
            print("sorry there is not enough stock to complete the tansaction, This order will be terminated")
        elif flag == 2:
            print(f' {self.name} did not have enough cash for this tansaction, This order will be terminated')
        else:
            print("Error occured")   
        
class Shop:
    
    def __init__(self, path):
        self.stock = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[1])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = ProductStock(p, float(row[2]))
                self.stock.append(ps)
    
    def __repr__(self):
        str = ""
        #str += f'Shop has {self.cash} in cash\n'
        for item in self.stock:
            str += f"{item}\n"
        return str
    
    def getCash(self):
        str = ""
        str += f'Shop has {self.cash} in cash\n'
        return str
    
    def SLiveBuy(self):
        print("Menu\n=========================")
        print(self)
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
                c = Customer("LiveBasket.csv") 
                c.CbuyingCSV(self)
                break # breaks loop and closes the program
            elif (option == "x"):
                print("Returning to menu") 
                time.sleep(1)
                break # breaks loop and closes the program
            else:
                print("Item not in shop list") # any other option is invalid 

    def existingCustS(self):
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
                    c = Customer(CustDir) 
                    c.CbuyingCSV(self)
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


def main():
    while True:
        s = Shop("stock.csv")
        
        display_menu() # Calls function to display method options 
        # https://stackoverflow.com/questions/40056747/print-a-list-of-dictionaries-in-table-form
        option = input("Select: ") # take input from user 
        if (option == "1"):
            s.existingCustS()
        elif (option == "2"):
            s.SLiveBuy()
        elif (option == "3"):
            print("Current Stock in Shop \n")
            print(s)
            pass
            time.sleep(1)

        elif (option == "4"):
           cash = s.getCash()
           print(cash)
           
            
        elif (option == "x"):
            print("Closing app") 
            break # breaks loop and closes the program
        else:
             print("Invalid Option") # any other option is invalid 

def display_menu(): # display menu 
    print("Welcome to the python OOP shop \n----------\n")
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