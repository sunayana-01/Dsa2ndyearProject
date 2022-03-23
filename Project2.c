//Program in c language for online shopping mart

//Header files
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define MALLOC(p,s,t)\
    p=(t)malloc(s);\
    if(p==NULL){\
        printf("insufficient memory");\
        exit(1);\
        }

//Cart of customer
struct purchase{
    char purchase[30];
    int price;
    int tprice;
    int number;
};
typedef struct purchase* purch;

//User account
struct account{
    int cust_key; 
    char cust_name[30];
    char password[30];
    char address[40];
    int pin;
    int mobno;
    int points;
    int admin;
    purch purchase[30];
    struct account* left;
    struct account* right;
};

//Item node
struct item{
    int item_key;
    char item_name[30];
    int price;
    int stock;
    struct item* left;
    struct item* right;
};

typedef struct account* cust_NODE;
typedef struct item* item_NODE;
int cart=0, val=0;
cust_NODE current = NULL;
int ind = 0;

//Functions Defination Section
int getid();
void display();
cust_NODE createc(cust_NODE, int);
item_NODE createi(item_NODE, int);
int searchi(item_NODE, int);
int searchc(cust_NODE, int);
void viewitems(item_NODE);
void payable();


int main(){
    int option, j, flag, done=0, pay, fdone=0;
    cust_NODE member = NULL;
    item_NODE item = NULL;
    int itemkey, memberkey;
    while(!fdone){
        done=0;
        ind = 0;
        val = 0;
        printf("*--------------------------------------------------------------------------------------------------------------*\n");
        printf("                                  WELCOME TO ONLINE SHOPPING MART\n");
        printf("                                                                          Cart=%d\n", cart);
        printf("\n");
        printf("Enter the following key: \n1.Signup\n2.Login\n3.Exit\nKey:\t");
        scanf("%d", &option);
        switch(option){
            case 1: printf("Enter the following details:");
                    member = createc(member, getid());
                    printf("Account created successfully.\n\n");
                    chcc:
                        if(current->admin==1){
                            while(!done){
                                printf("Enter the key for the following operations:\n");
                                printf("1.Profile\n2.Add Item\n3.View Items\n4.Logout\nKey:\t");
                                scanf("%d",&j);
                                switch (j){
                                    case 1: printf("\nDetails:\n");
                                            display();
                                            break;
                                    case 2: 
                                            item = createi(item, getid());
                                            if(item!=NULL)
                                                printf("item added successfully\n\n");
                                            break;
                                    case 3: printf("Key\t\tItem Name\t\tStock\t\tPrice Value\n");
                                            viewitems(item);
                                            break;
                                    case 4: done = 1;
                                            printf("\e[1;1H\e[2J");
                                            break;
                                    default: printf("Invalid Option.\n");
                                }
                            }
                        }
                        else{
                            while(!done){
                                printf("Enter the key for the following operations:\n");
                                printf("1.Profile\n2.View Items\n3.View your cart\n4.Add Item\n5.Proceed to pay\n6.Logout\nKey:\t");
                                scanf("%d",&j);
                                switch(j){
                                    case 1: printf("\nDetails:\n");
                                            display();
                                            break;
                                    case 2: printf("Item Name\t\tItem Key\t\tStock\t\tPrice Value\n");
                                            viewitems(item);
                                            printf("\n");
                                            printf("\n\n");
                                            break;
                                    case 3: printf("Items in your cart:\n");
                                            printf("Item Name\t\tQuantity\t\tPrice Value per product\tTotal price\n");
                                            for(int k=0; k<val; k++){
                                                purch temp = current->purchase[k];
                                                printf("%s\t\t%d\t\t%d\t\t%d\n",temp->purchase, temp->number, temp->price, temp->tprice);
                                            }
                                            printf("End of cart.\n");
                                            break;
                                    case 4: printf("Enter the item key of the product you want to buy:\n");
                                            scanf("%d", &itemkey);
                                            flag = searchi(item, itemkey);
                                            if(flag!=1)
                                                printf("Invalid item key or item not available.\n\n");
                                            else
                                                printf("Item Successfully added to cart\n\n");
                                            break;
                                    case 5: printf("Total amount payable");{
                                            int total = 0;
                                            printf("Item Name\t\tQuantity\t\tPrice Value per product\tTotal price\n");
                                            for(int k=0; k<val; k++){
                                                purch temp = current->purchase[k];
                                                printf("%s\t%d\t\t%d\t\t%d\n",temp->purchase, temp->number, temp->price, temp->tprice);
                                                total += temp->tprice;
                                            }
                                            printf("Total cost: %d\n",total);}
                                            payable();
                                            break;
                                    case 6: done = 1;
                                            printf("\e[1;1H\e[2J");
                                            break;
                                    default: printf("Invalid Option.\n");
                                }
                            }
                        }
                    break;
                    //}

            case 2: printf("Enter your security key:\n");
                    scanf("%d", &memberkey);
                    flag = searchc(member, memberkey);
                    if(flag!=1)
                        printf("Invalid credentials\n");
                    else
                        goto chcc;
                    break;

            case 3: fdone=1;
                    break;

            default: printf("Wrong choice. Please enter again.\n"); 
        }
    }
    return 0;
}

//Function to display useer profile
void display(){
    printf("Name:%s\nSecurity Key:%d\nAddress:%s\nPin:%d\nMobile no:%d\nPoints:%d\n\n",current->cust_name,
                                            current->cust_key, current->address, current->pin, current->mobno, current->points);
}

//Function to generate random key
int getid(){
    return rand();
}

//Function to proceed payment
void payable(){
    int op;
    printf("Enter your payment method:\n");
    printf("1.COD\t2.Debit/Credit Card\n");
    scanf("%d",&op);
    if(op==1)
        printf("Placed order successfully.\n");
    else{
        char temp[30];
        int cvv;
        printf("Enter your card details.\n");
        printf("Enter your card number(16 digits):\t");
        scanf("%s", temp);
        printf("Enter cvv:\t");
        scanf("%d", &cvv);
        printf("Completing transaction....\n");
        printf("Placed order successfully.\n");
    }
}

//Function to create a customer node
cust_NODE createc(cust_NODE mem, int r){
    if(mem==NULL){
        MALLOC(mem, sizeof(struct account), cust_NODE);
        printf("\nEnter the data:\n");
        printf("Enter your name:\t");
        scanf("%s",mem->cust_name);
        printf("Enter your password:\t");
        scanf("%s", mem->password);
        printf("Enter your address:\n");
        scanf("%s", mem->address);
        printf("Enter your pin:\t");
        scanf("%d",&mem->pin);
        printf("Enter your mobile no.:\t");
        scanf("%d",&mem->mobno);
        printf("Are you admin? Type 1 if you are\t");
        scanf("%d",&mem->admin);
        mem->cust_key = r;
        printf("This is your security key. Do not share it with anyone.\nSecurity key:%d\n",mem->cust_key);
        mem->points=0;
        mem->right = mem->left = NULL;
        if(ind == 0){
            current = mem;
            ind = 1;
        }
    }
    else if(r==mem->cust_key){
        r=rand();
        createc(mem, r);
    }
    else if(r<mem->cust_key){
        mem->left=createc(mem->left,r);
    }
    else{
        mem->right=createc(mem->right, r);
    }
    return mem;
}

//Function to create item node
item_NODE createi(item_NODE ite, int rr){
    if(ite==NULL){
        MALLOC(ite, sizeof(struct item), item_NODE);
        printf("Enter the data:\n");
        printf("Enter item name:\t");
        scanf("%s",ite->item_name);
        printf("Enter item's price:\t");
        scanf("%d", &ite->price);
        printf("Enter item's stock:\t");
        scanf("%d", &ite->stock);
        ite->item_key = rr;
        printf("This is item's security key.\nSecurity key:%d\n",ite->item_key);
        ite->right = ite->left = NULL;
    }
    else if(rr==ite->item_key){
        rr=rand();
        createi(ite, rr);
    }
    else if(rr<ite->item_key)
        ite->left=createi(ite->left,rr);
    else
        ite->right=createi(ite->right, rr);
    return ite;
}

//Function to search for an item
int searchi(item_NODE ite, int key){
    int q;
    if(ite==NULL)
        return 0;
    else if(key == ite->item_key){
        printf("Enter number of items you want to buy?\t");
        printf("In stock: %d\n",ite->stock);
        scanf("%d",&q);
        if(q<=ite->stock){
            MALLOC(current->purchase[val], sizeof(struct purchase), purch);
            ite->stock-=q;
            cart+=q;
            current->purchase[val]->number=q;
            strcpy(current->purchase[val]->purchase ,ite->item_name);
            current->purchase[val]->price=ite->price;
            current->purchase[val]->tprice = q*ite->price;
            val++;
            return 1;
        }
        else
            return 0;
    }
    else if(key < ite->item_key)
        return searchi(ite->left, key);
    else
        return searchi(ite->right, key);
}

//Function to check for login credentials
int searchc(cust_NODE cust, int key){
    if(cust==NULL)
        return 0;
    else if(key == cust->cust_key){
        char name[30], password[30];
            printf("Enter your username:\t");
            scanf("%s", name);
            printf("Eneter your password:\t");
            scanf("%s", password);
            if(strcmp(cust->cust_name, name)==0 && strcmp(cust->password, password)==0){
                printf("Successfully logged in.\n");
                return 1;
            }
            else
                return 0;
    }
    else if(key < cust->cust_key)
        return searchc(cust->left, key);
    else
        return searchc(cust->right, key);
}

//Function to view all items in cart
void viewitems(item_NODE ite){
    if(ite!=NULL){
        printf("%s\t\t\t%d\t\t\t%d\t\t\t%d\n",ite->item_name, ite->item_key, ite->stock, ite->price);
        viewitems(ite->left);
        viewitems(ite->right);
    }
}