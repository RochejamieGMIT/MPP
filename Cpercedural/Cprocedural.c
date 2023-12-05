#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product {
    char* name;
    double price;
};

struct ProductStock {
    struct Product product;
    int quantity;
};

struct Customer {
    char* name;
    double budget;
    struct ProductStock shoppingList[20];
    int index; 
};


struct Shop{
    double cash;
    struct ProductStock stock[20];
    int index; 
};

void printProduct(struct Product p){
    printf("Product Name: %s\nProduct Price: %.2f\n",p.name,p.price);
    printf("_______________________\n");
};

void printCustomer(struct Customer c){
    printf("Customer name:%s\n",c.name);
    printf("Customer Budget: %.2f\n",c.budget);
    printf("_______________________\n");
    for(int i =0; i<c.index;i++)
    {
        printProduct(c.shoppingList[i].product);
        printf("%s Orders %d of the %s\n",c.name,c.shoppingList[i].quantity,c.shoppingList[i].product.name);
        double cost = c.shoppingList[i].product.price*c.shoppingList[i].quantity;
        printf("The cost to %s will be E%.2f\n",c.name,cost);
    };

}

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
    //set to 1 to skip cash for now
    for (int i = 1;i<s.index;i++)
    {
        printProduct(s.stock[i].product);
        printf("The shop has %d of %s\n",s.stock[i].quantity,s.stock[i].product.name);
        printf("-------------\n");
    };

};

int main(void)
{
    struct Customer Jamie = {"Jamie",100.0};
    //printf("Customer name is %s\n",Jamie.name);

    struct Product coke = {"Can Coke", 1.10};
    struct Product bread = {"Bread",0.7};
    
    //printf("The %s costs %.2f\n",coke.name,coke.price);

    struct ProductStock cokeStock = {coke,20};
    struct ProductStock breadStock = {bread,2};
    printf("The shop has %d of the product %s\n",cokeStock.quantity,cokeStock.product.name);

    
    

    Jamie.shoppingList[Jamie.index++] = cokeStock;
    Jamie.shoppingList[Jamie.index++] = breadStock;
    printCustomer(Jamie);
    //printProduct(coke);

    struct Shop shop = createAndStockShop();
    printShop(shop);
    char c;
    scanf("%c",&c);
    return 0;
}