#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

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


double getCash(){
    double cash = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (i == 0) {
        read = getline(&line, &len, fp);
        // printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE", line);
		char *n = strtok(line,",");
        char *c = strtok(NULL,",");
		cash = atof(c);
        //printf("%.2f CASH IN LOOP",cash);
        i++;
        }
    fclose(fp);
    return cash;
};

void printProduct(struct Product p){
    printf("Product Name: %s\nProduct Price: %.2f\n",p.name,p.price);
    printf("_______________________\n");
};

void printCustomer(struct Customer c){
     printf("Name: %s Cash: %.2f\n",c.name,c.budget);
    printf("ShoppingList for %s\n",c.name);
   for(int i=0; i < c.index; i++){
		printf("%s %d\n",c.shoppingList[i].product.name,c.shoppingList[i].quantity);
	}

}

struct Shop createAndStockShop(){
   	struct Shop shop = {};
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
    //printf("\nShop has %.2f in cash\n",s.cash);
    printf("-------------\n");
    //set to 1 to skip cash for now
    for (int i = 1;i<s.index;i++)
    {
        printProduct(s.stock[i].product);
        printf("The shop has %d of %s\n",s.stock[i].quantity,s.stock[i].product.name);
        printf("-------------\n");
    };

};


void displayMenu(){
    printf("Welcome to the C procedural shop \n----------\n");
    printf("Menu\n====\n");
    printf("1 - Buy With Shopping List (CSV)\n");
    printf("2 - Buy Live\n");
    printf("3 - Check Shop Stock\n");
    printf("4 - Check Shop Cash Balance\n");
    printf("x - Exit application\n");


}


struct Customer read_customer(char CustDir[80]){
    struct Customer c = {};
    double cash;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    fp = fopen(CustDir, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);


     while (i == 0) {
        read = getline(&line, &len, fp);
        // printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE", line);
		char *n = strtok(line,",");
        char *b = strtok(NULL,",");
        char *name = malloc(sizeof(char) * 50);
        strcpy(name, n);
        //printf("name of cust %s",name);
        c.name = name;
		c.budget = atof(b);
        //printf("%.2f CASH IN LOOP",c.budget);
        i++;
        }
    int index=0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        //printf("%s IS A LINE", line);
		char *n = strtok(line,",");
        //*p = strtok(NULL,",");
        char *q = strtok(NULL,",");
        int quantity = atoi(q);
		double price = 0;
        char *name = malloc(sizeof(char) * 50);
        strcpy(name, n);
        struct Product product = {name,price};
        struct ProductStock shoppingList = {product,quantity};
        c.shoppingList[c.index++] = shoppingList;
        //printf("Name of product %s price %.2f quanity %i\n", name,price,quantity);
        }

    return c;




}

void buyingCSV(char CustDir[80]){
    //printf("Bought stuff\n");
    //printf("%s - passed customer dir",CustDir);
    struct Customer c = read_customer(CustDir);
    printCustomer(c);
    struct Shop shop = createAndStockShop();
    double cash = getCash();
    double total = 0;
    int flag = 0;


}

void existingCustomer(){
    printf("Are you an existing customer with a shopping list?\n");
    printf("Type 1 for yes, 2 for no\n");
    char c;
    char * token = "";
    int count=0;
    char *s = "";
    char CustDir[80];
    //https://www.geeksforgeeks.org/array-of-strings-in-c/
    char name[10][20] = {};
    char check[20];
    while(1){
        scanf(" %c",&c);
        //https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
        if (c=='1') {
            DIR *d;
        struct dirent *dir;
            d = opendir(".\\Customers");
        if (d) {
                while ((dir = readdir(d)) != NULL) {
                    //https://www.educative.io/answers/splitting-a-string-using-strtok-in-c
                    //https://www.geeksforgeeks.org/different-ways-to-copy-a-string-in-c-c/
                    token = strtok(dir->d_name, ".");
                    //printf("%s\n", token); // Print the tokenized part
                    if (token != NULL) {
                        //https://www.geeksforgeeks.org/array-of-strings-in-c/
                        strcpy(name[count], token); // Store token in the array
                        printf("%s\n", name[count]); // Print the stored token
                        count++;
                    }
                }
                closedir(d);
            }
           int len = sizeof(name)/sizeof(name[0]);
           int foundFlag =0;
           scanf("%s",check);
           //https://stackoverflow.com/questions/13677890/how-to-check-if-a-string-is-in-an-array-of-strings-in-c
            for(count = 0; count < len; ++count)
                {
                    if(!strcmp(name[count], check))
                    {
                       strcpy(CustDir, "Customers\\");
                       strcat(CustDir, check);
                       strcat(CustDir, ".csv");
                       //printf("%s", CustDir);
                        buyingCSV(CustDir);
                        foundFlag=1;
                        
                    }
                }
            if (foundFlag == 1)
            {
                break;
            }
            else{
                printf("Does not Exist, Try again\n");
                printf("Are you an existing customer with a shopping list?\n");
                printf("Type 1 for yes, 2 for no\n");

            }

            } else if (c=='2') {
            printf("Sorry, Shopping with a list is for exisitng customers only\n You will be sent back to the main menu\n");
            break; // Send back to main menu
            }else{
             printf("Invalid Option");
            }
    }

}




int main(void)
{
    //struct Customer Jamie = {"Jamie",100.0};
    //printf("Customer name is %s\n",Jamie.name);

    //struct Product coke = {"Can Coke", 1.10};
    //struct Product bread = {"Bread",0.7};
    
    //printf("The %s costs %.2f\n",coke.name,coke.price);

    //struct ProductStock cokeStock = {coke,20};
    //struct ProductStock breadStock = {bread,2};
    //printf("The shop has %d of the product %s\n",cokeStock.quantity,cokeStock.product.name);

    
    

    //Jamie.shoppingList[Jamie.index++] = cokeStock;
    //Jamie.shoppingList[Jamie.index++] = breadStock;
    //printCustomer(Jamie);
    //printProduct(coke);
    double cash = getCash();
    printf("CASH IS %.2f\n",cash);


    struct Shop shop = createAndStockShop();
    printShop(shop);
    char c;
    while(1){
            displayMenu();
            scanf("%c",&c);
            if (c=='1') {
            existingCustomer();
            } else if (c=='2') {
            // block of code to be executed if the condition1 is false and condition2 is true
            }else if (c=='3') {
            // block of code to be executed if the condition1 is false and condition2 is true
            }else if (c=='4') {
            // block of code to be executed if the condition1 is false and condition2 is true
            }else if (c=='x') {
            printf("Closing app"); 
                break; // breaks loop and closes the program
            } else {
            // block of code to be executed if the condition1 is false and condition2 is false
            }
    }

    return 0;
}