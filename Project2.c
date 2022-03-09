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

struct purchase{
    char purchase[30];
    int price;
    int tprice;
    int number;
};
typedef struct purchase* purch;

struct account{
    int cust_key; 
    char cust_name[30];
    char address[40];
    int pin;
    int mobno;
    int points;
    int admin;
    purch purchase[30];
    struct account* left;
    struct account* right;
};

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

//Defination Section
cust_NODE createc(cust_NODE mem, int r){
    if(mem==NULL){
        MALLOC(mem, sizeof(struct account), cust_NODE);
        printf("Enter the data:\n");
        printf("Enter your name:\t");
        scanf("%s",mem->cust_name);
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

int searchi(item_NODE ite, int key){
    int q;
    if(ite==NULL)
        return 0;
    else if(key == ite->item_key){
        printf("Enter number of items you want to buy?\t");
        printf("In stock: %d\n",ite->stock);
        scanf("%d",&q);
        if(q<=ite->stock){
            purch temp = current->purchase[val];
            ite->stock-=q;
            cart+=q;
            printf("1");
            temp->number=q;
            printf("1");
            strcpy(temp->purchase ,ite->item_name);
            printf("1");
            current->purchase[val]->number=q;
            printf("1");
            current->purchase[val]->price=ite->price;
            printf("1");
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

int searchc(cust_NODE cust, int key){
    if(cust==NULL)
        return 0;
    else if(key == cust->cust_key){
            printf("Logged in Successully!.\n");
            return 1;
    }
    else if(key < cust->cust_key)
        return searchc(cust->left, key);
    else
        return searchc(cust->right, key);
}

void preorderi(item_NODE ite){
    if(ite!=NULL){
        printf("%s\t\t%d\t\t%d\t\t%d\n",ite->item_name, ite->item_key, ite->stock, ite->price);
        preorderi(ite->left);
        preorderi(ite->right);
    }
}

int main(){
    int i, j, flag, done=0, pay, fdone=0;
    cust_NODE member = NULL;
    item_NODE item = NULL;
    int itemkey, memberkey;
    printf("*--------------------------------------------------------------------------------------------------------------*\n");
    printf("                                  WELCOME TO ONLINE SHOPPING MART\n");
    printf("                                                                          Cart=%d\n", cart);
    while(!fdone){
        done=0;
        ind = 0;
        val = 0;
        printf("Enter the following key: \n1.Signup\n2.Login\n3.Exit\n");
        scanf("%d", &i);
        switch(i){
            case 1: printf("Enter the following details:");
                    member = createc(member, 5467);
                    printf("Account created successfully.\n");
                    printf("dgshja\n");
                        if(current->admin==1){
                            while(!done){
                                printf("Enter the key for the following operations:\n");
                                printf("1.Profile\n2.Add Item\n3.Modify Price\n4.View Items\n5.Logout\n");
                                scanf("%d",&j);
                                switch (j){
                                    case 1: printf("Details:\n");
                                            printf("Name:%s\nSecurity Key:%d\nAddress:%s\nPin:%d\nMobile no:%d\nPoints:%d\nadmin:%d\n\n",current->cust_name,
                                            current->cust_key, current->address, current->pin, current->mobno, current->points, current->admin);
                                            break;
                                    case 2: item = createi(item, 5467);
                                            if(item!=NULL)
                                                printf("item added successfully\n\n");
                                            break;
                                    case 4: printf("Key\t\tItem Name\t\tStock\t\tPrice Value\n");
                                            preorderi(item);
                                            break;
                                    case 5: done = 1;
                                            system("clear");
                                            break;
                                    default: printf("Invalid Option.\n");
                                }
                            }
                        }
                        else{
                            while(!done){
                                printf("Enter the key for the following operations:\n");
                                printf("1.Profile\n2.View Items\n3.View your cart\n4.Add Item\n5.Proceed to pay\n6.Logout\n");
                                scanf("%d",&j);
                                switch(j){
                                    case 1: printf("Details:\n");
                                            printf("Name:%s\nSecurity Key:%d\nAddress:%s\nPin:%d\nMobile no:%d\nPoints:%d\n\n",current->cust_name,
                                            current->cust_key, current->address, current->pin, current->mobno, current->points);
                                            break;
                                    case 2: printf("Item Name\t\tItem Key\t\tStock\t\tPrice Value\n");
                                            preorderi(item);
                                            printf("\n\n");
                                            break;
                                    case 3: printf("Items in your cart:\n");
                                            printf("Item Name\t\tQuantity\t\tPrice Value per product\tTotal price\n");
                                            for(int k=0; k<=val; k++){
                                                printf("%s\t\t%d\t\t%d\t\t%d\n",current->purchase[k]->purchase, current->purchase[k]->number,
                                                current->purchase[k]->price, current->purchase[k]->tprice);
                                            }
                                            printf("End of cart.\n");
                                            break;
                                    case 4: printf("Enter the item key of the product you want to buy:\n");
                                            scanf("%d", &itemkey);
                                            flag = searchi(item, itemkey);
                                            if(flag!=1)
                                                printf("Invalid item key or item not available.\n");
                                            else
                                                printf("Item Successfully added to cart");
                                            break;
                                    case 5: printf("Total amount payable");
                                            int total = 0;
                                            printf("Item Name\t\tQuantity\t\tPrice Value per product\tTotal price\n");
                                            for(int k=0; k<=val; k++){
                                                printf("%s\t\t%d\t\t%d\t\t%d\n",current->purchase[k]->purchase, current->purchase[k]->number,
                                                current->purchase[k]->price, current->purchase[k]->tprice);
                                                total += current->purchase[k]->tprice;
                                            }
                                            printf("Total cost: %d\n",total);
                                            printf("Enter your payment method:\n");
                                            printf("1.COD\t2.Debit/Credit Card\n");
                                            scanf("%d",&pay);
                                            if(pay==1)
                                                printf("Placed order successfully.\n");
                                            else
                                                printf("Enter your card details.\n");
                                            break;
                                    case 6: done = 1;
                                            system("clear");
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
                    break;

            case 3: {
                fdone=1;
            }

            default: printf("Wrong choice. Please enter again.\n"); 
        }
    }
    return 0;
}