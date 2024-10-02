#include <stdio.h>

#define CoffeeBeans 8

#define EspWater 30
#define CappWater 30
#define MochaWater 39

#define CappMilk 70
#define MochaMilk 160

#define EspSyrup 0
#define CappSyrup 0
#define MochaSyrup 30

#define EspPrice 3.5
#define CappPrice 4.5
#define MochaPrice 5.5

#define password admin000

#define low_beans 8
#define low_water 39
#define low_milk 160
#define low_syrup 30

int total_amount = 0;
int coffee_beans = 100;
int water = 100;
int milk = 100;
int syrup = 100;

float price;

int selection = 0;
int order = 0;
int true;
int confirm = 0;

int coffee_type();
int ing_check(int a);

int main(void)
{
    printf("1. Order a coffee\n");
    printf("2. Admin mode\n");
    printf("3. Exit\n");

    printf("Enter your chosen field's number from 1-3: ");
    scanf("%d", &selection);

    while (selection != 1 && selection != 2 && selection !=3)
    {
        printf("Wrong Input\n");
        printf("Enter your chosen field's number from 1-3: ");
        scanf("%d", &selection);
    }

    if (selection == 1)
    {
        coffee_type();
    }
   
}

int coffee_type()
{
    printf("1. Espresso\n");
    printf("2. Cappucino\n");
    printf("3. Mocha\n"); 

    printf("To place your order, enter a number from 1 to 3. To exit, enter 0: ");
    scanf("%d", &order);


    while (order != 1 && order != 2 && order !=3 && order != 0)
    {
        printf("Wrong Input\n");
        printf("Enter a number from 1-3: ");
        scanf("%d", &order);
    }

    if(order == 0)
    {
        return 0;
    }
    else if(order == 1 || order == 2 || order == 3)
    {
    
        ing_check(order);
        if (true == 1)
        {
            printf("Unavailable due to temporarily insufficient ingredients\n");
        }
        else
        {
            if (order == 1)
            {
                printf("Coffee Type: Espresso\n");
                printf("Coffee Price: %.2f\n", EspPrice);
                printf("Enter 1 to confirm your order or enter 0 to exit: ");
                scanf("%d", &confirm);
            }
            else if (order == 2)
            {
                printf("Coffee Type: Cappucino\n");
                printf("Coffee Price: %.2f\n", CappPrice);
                printf("Enter 1 to confirm your order or enter 0 to exit: ");
                scanf("%d", &confirm);
            }
            else if (order == 3)
            {
                printf("Coffee Type: Mocha\n");
                printf("Coffee Price: %.2f\n", MochaPrice);
                printf("Enter 1 to confirm your order or enter 0 to exit: ");
                scanf("%d", &confirm);
            }
            
        }
        
    }
}

int ing_check(int a)
{
    if (a == 1)
    {
        if (coffee_beans < CoffeeBeans || water < EspWater || syrup < EspSyrup)
        {
            true = 1;
        }
    }
    else if (a == 2)
    {
        if (coffee_beans < CoffeeBeans || water < CappWater || syrup < CappSyrup || milk < CappMilk)
        {
            true = 1;
        }
    }
    else if (a == 3)
    {
        if (coffee_beans < CoffeeBeans || water < MochaWater || syrup < MochaSyrup || milk < MochaMilk)
        {
            true = 1;
        }
    }
}