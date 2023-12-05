#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Product
{
    char* name;
    double price;
};

struct ProductStock{
    struct Product product;
    int quantity;
};

struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};

struct Shop{
    double cash;
    struct ProductStock stock[20];
    int index;

};

void printProduct(struct Product p){
    printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);

};

void printCustomer(struct Customer c){

    printf("CUSTOMER NAME: %s \nCusotmer Budget: %.2f\n", c.name, c.budget);
	printf("-------------\n");
    for (int i =0;i <c.index ;i++){
        printProduct(c.shoppingList[i].product);
        printf("%s orders %d of %s\n",c.name,c.shoppingList[i].quantity,c.shoppingList[i].product.name);
        double cost = c.shoppingList[i].product.price*c.shoppingList[i].quantity;
        printf("Cost to %s will be E%.2f\n",c.name,cost);
    }
};

struct Shop createAndStockShop(){
   	struct Shop shop = { 200 };
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE", line);
		char *n = strtok(line,",");
        char *p = strtok(NULL,",");
        char *q = strtok(NULL,",");
        int quantity = atoi(q);
		double price = atof(p);
        char *name = malloc(sizeof(char) * 50);
        strcpy(name, n);
        struct Product product = {name,price};
        struct ProductStock stockItem = {product,quantity};
        shop.stock[shop.index++] = stockItem;
        //printf("Name of product %s price %.2f quanity %i\n", name,price,quantity);
        }

    return shop;
};

void printShop(struct Shop s){
    printf("\nShop has %.2f in cash\n",s.cash);
    printf("-------------\n");

    for (int i = 1;i<s.index;i++)
    {
        printProduct(s.stock[i].product);
        printf("The shop has %d of %s\n",s.stock[i].quantity,s.stock[i].product.name);
        printf("-------------\n");
    };

};

int main(void){
    struct Customer Jamie = {"Jamie",100.0};
    //printf("Customer jamie is %s\n",Jamie.name);
    struct Product coke ={"Can of Coke",1.10};
    struct Product bread = {"Bread",0.7};
    
    //printf("Item name %s, item price %.2f\n",coke.name,coke.price);

    struct ProductStock cokeStock = {coke,20};
    struct ProductStock breadStock = {bread,2};
    //printf("Shop has %d of %s",cokeStock.quantity,cokeStock.product.name);

    //printf("\n*****************************\n");
    Jamie.shoppingList[Jamie.index++] = cokeStock;
    Jamie.shoppingList[Jamie.index++] = breadStock;
    //printCustomer(Jamie);
    //printProduct(coke);

    struct Shop shoppy = createAndStockShop();
    printShop(shoppy);


    
    return 0;
}