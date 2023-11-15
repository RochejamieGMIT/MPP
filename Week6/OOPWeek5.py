import csv 

def create_and_stock_shop():
    shop = {}
    with open("stock.csv") as csv_file:
        csv_reader = csv.reader(csv_file,delimiter=",")
        first_row = next(csv_reader)
        #shop["cash"] = float(first_row)
        #shop["products"]={}
        for row in csv_reader:
            product = {}

            product["name"] = row[0]
            product["price"] = row[1]
            product["quantity"] = row[2]
            #shop["products"].append(product)
            print_product(product)


def read_customer():
    pass

def print_product(product):
    print(f'Product: {product["name"]}, Price: {product["price"]}, Quantity: {product["quantity"]}')

def print_customer(c):
    pass

def print_shop(s):
    pass


create_and_stock_shop()