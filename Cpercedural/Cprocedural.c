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


double findP(struct Shop s, char* name)
{
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(name, s.stock[i].product.name) == 0){
			return s.stock[i].product.price;
		}
	}
	return -1;
}

int findQ(struct Shop s, char* name)
{
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(name, s.stock[i].product.name) == 0){
			return s.stock[i].quantity;
		}
	}
	return -1;
}

int findI(struct Shop s, char* name)
{
	for (int i = 0; i < s.index; i++)
	{
		if (strcmp(name, s.stock[i].product.name) == 0){
			return i;
		}
	}
	return -1;
}

void buyingCSV(char CustDir[80]){
    //printf("Bought stuff\n");
    //printf("%s - passed customer dir",CustDir);
    struct Customer c = read_customer(CustDir);
    printCustomer(c);
    struct Shop shop = createAndStockShop();
    double cash = getCash();
    double totalC = 0;
    int flag = 0;
   
	for(int i=0; i < c.index; i++){
		struct Product p = c.shoppingList[i].product;
		double price= findP(shop, p.name);
        int q = findQ(shop, p.name);
        int index = findI(shop, p.name);
        //printf("index = %d\n",index);
		//printf("The price of %s in the shop is %.2f\n", p.name, price);
		double totalI = c.shoppingList[i].quantity * price;
		//printf("You want %d of %s, that will cost you %.2f\n", c.shoppingList[i].quantity, p.name, totalI);
        //printf("C quan %d, S quan %d\n",c.shoppingList[i].quantity,q );
        if(q == -1 ){
           printf("No request\n");
        }else if (c.shoppingList[i].quantity > q)
        {  flag = 1;}
        else{

            //printf("Stock before change = %d\n",shop.stock[index].quantity);
            shop.stock[index].quantity = shop.stock[index].quantity - c.shoppingList[i].quantity;
            //printf("Stock  after change = %d\n",shop.stock[index].quantity);
            totalC += totalI;
        }
		
	}

    if (totalC > c.budget){flag = 2;}

    if (flag == 0){
        printf("The total cost for %s will be %.2f\n",c.name, totalC);
        c.budget = c.budget - totalC;
        printf("%s new balance = E%.2f\n",c.name,c.budget);
        printf("shop cash before: %.2f\n",cash);
        cash = cash + totalC;
        printf("shop cash after: %.2f\n",cash);
        //https://dev.to/arepp23/how-to-write-to-a-csv-file-in-c-1l5b
        FILE *fpt;
        fpt = fopen("stock.csv", "w+");
        fprintf(fpt,"cash,%.2f\n",cash);
        for (int i = 1;i<shop.index;i++)
        {
             fprintf(fpt,"%s,%.2f,%d\n",shop.stock[i].product.name,shop.stock[i].product.price,shop.stock[i].quantity);
        };
        fclose(fpt);

    }
    else if (flag ==1){
        printf("sorry there is not enough stock to complete the tansaction, This order will be terminated\n");
    } else if (flag == 2){
         printf("%s did not have enough cash for this tansaction, This order will be terminated\n",c.name);
    }
	


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



void LiveBuy(){ 
    char c[15];
    char money[15];
    char ItemBuy[20];
    char BuyQuan[5];
    int buyInt;
    float cusBudget;
    int BuyIndex=0;
    struct Customer liveCustomer = {};
    struct Shop shop = createAndStockShop();
    printShop(shop);
    double cash = getCash();
    printf("CASH IS %.2f\n",cash);
    
    
    printf("Enter your Name: \n");
    scanf(" %s",c);
    liveCustomer.name = c;
    printf("Cus name: %s", liveCustomer.name);
    printf("\nEnter your Budget: \n");
    scanf(" %s",money);
    double cusBudgetF = atof(money);
    liveCustomer.budget = cusBudgetF;
    printf("Cus budget: %.2f\n", liveCustomer.budget);
    printf("Please enter the itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
    //https://cboard.cprogramming.com/c-programming/131665-strcmp-fails-spaces.html
    //https://www.scaler.com/topics/fgets-function-c/
    while(1){
         fgets(ItemBuy, 20, stdin);
        if(strcmp("Coke Can\n", ItemBuy) == 0){
            printf("enter quantity: \n");
            fgets(BuyQuan, 5, stdin);
            liveCustomer.shoppingList[BuyIndex].product.name = "Coke Can";
            buyInt = atoi(BuyQuan);
            liveCustomer.shoppingList[BuyIndex].quantity = buyInt;
            printf("%d of %s",liveCustomer.shoppingList[BuyIndex].quantity,liveCustomer.shoppingList[BuyIndex].product.name);
            BuyIndex++;
            printf("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
        }else if(strcmp("Bread\n", ItemBuy) == 0){
            printf("enter quantity: \n");
            fgets(BuyQuan, 5, stdin);
            liveCustomer.shoppingList[BuyIndex].product.name = "Bread";
            buyInt = atoi(BuyQuan);
            liveCustomer.shoppingList[BuyIndex].quantity = buyInt;
            BuyIndex++;
            printf("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
        }else if(strcmp("Spaghetti\n", ItemBuy) == 0){
            printf("enter quantity: \n");
            fgets(BuyQuan, 5, stdin);
            liveCustomer.shoppingList[BuyIndex].product.name = "Spaghetti";
            buyInt = atoi(BuyQuan);
            liveCustomer.shoppingList[BuyIndex].quantity = buyInt;
            BuyIndex++;
            printf("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
        }else if(strcmp("Tomato Sauce\n", ItemBuy) == 0){
            printf("enter quantity: \n");
            fgets(BuyQuan, 5, stdin);
            liveCustomer.shoppingList[BuyIndex].product.name = "Tomato Sauce";
            buyInt = atoi(BuyQuan);
            liveCustomer.shoppingList[BuyIndex].quantity = buyInt;
            BuyIndex++;
            printf("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
        }else if(strcmp("Bin Bags\n", ItemBuy) == 0){
            printf("enter quantity: \n");
            fgets(BuyQuan, 5, stdin);
            liveCustomer.shoppingList[BuyIndex].product.name = "Bin Bags";
            buyInt = atoi(BuyQuan);
            liveCustomer.shoppingList[BuyIndex].quantity = buyInt;
            BuyIndex++;
            printf("\nPlease enter additional itmes you would like to buy, when ready to submit order enter y, or x to exit\n");
        }else if(strcmp("y\n", ItemBuy) == 0){
            printf("buying items");
            printf("Cus name: %s", liveCustomer.name);
            FILE *fpt;
            fpt = fopen("LiveBasket.csv", "w+");
            fprintf(fpt,"%s,%.2f\n",liveCustomer.name,liveCustomer.budget);
            for (int i = 0;i<BuyIndex;i++)
        {
             fprintf(fpt,"%s,%d\n",liveCustomer.shoppingList[i].product.name,liveCustomer.shoppingList[i].quantity);
        };
        fclose(fpt);
            buyingCSV("LiveBasket.csv");
            break;
        }else if(strcmp("x\n", ItemBuy) == 0){
            printf("Returning to main menu");
            break;
        }else{
            printf("Item not in shop list\n");
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
            LiveBuy();
            }else if (c=='3') {
            struct Shop shop = createAndStockShop();
            printShop(shop);
            }else if (c=='4') {
                cash = getCash();
                printf("CASH IS %.2f\n",cash);
            }else if (c=='x') {
            printf("Closing app"); 
                break; // breaks loop and closes the program
            } else {
            // block of code to be executed if the condition1 is false and condition2 is false
            }
    }

    return 0;
}