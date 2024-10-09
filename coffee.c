#include <stdio.h>
#include <string.h>

#define CoffeeBeans 8

#define EspWater 30
#define CappWater 30
#define MochaWater 39

#define CappMilk 70
#define MochaMilk 160

#define EspSyrup 0
#define CappSyrup 0
#define MochaSyrup 30

float EspPrice = 3.5;
float CappPrice = 4.5;
float MochaPrice = 5.5;

#define password 987654

#define low_beans 8
#define low_water 39
#define low_milk 160
#define low_syrup 30

float total_amount = 0;
int coffee_beans = 100;
int water = 100;
int milk = 100;
int syrup = 100;

float price;

int selection = 0;
int order = 0;
int true;
int confirm = 0;

//Function prototypes
int coffee_order();
int ing_check(int a);
int payment(int a);
int ing_count(int a);
int admin_mode();
int display();
int change_ing();

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
        coffee_order();
    }
    if (selection == 2)
    {
        admin_mode();
    }
        
}
    

int coffee_order()
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
 
                if (confirm == 1)
                {
                    payment(order);
                    ing_count(order);
                }
                else
                {
                    return 0;
                }
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

int payment(int a)
{
    float to_be_paid;
    float amount = 0;
    float coin = 0;

    if (a == 1)
    {
        to_be_paid = EspPrice;
    }
    else if (a == 2)
    {
        to_be_paid = CappPrice;
    }
    else if (a == 3)
    {
        to_be_paid = MochaPrice;
    }

    while (amount < to_be_paid)
    {
        printf("Enter 1 to insert 1 dhs and 0.5 to insert 0.5 dhs: ");
        scanf("%f", &coin);
        if (coin == 1)
        {
            amount ++;
        }
        else if (coin == 0.5)
        {
            amount = amount + 0.5;
        }
        else
        {
            printf("Invalid coin.\n");
        }
    }

    if (amount > to_be_paid)
    {
        float change = amount - to_be_paid;
        printf("Your change is %.2f\n", change);
    }

    printf("Thank you. Enjoy!\n");
    total_amount += to_be_paid;
    amount = 0;
    return 0;
}

int ing_count(int a)
{
    if (a == 1)
    {
        coffee_beans = coffee_beans - CoffeeBeans;
        water = water - EspWater;
        syrup = syrup - EspSyrup;
    }
    else if (a == 2)
    {
        coffee_beans = coffee_beans - CoffeeBeans;
        water = water - CappWater;
        milk = milk - CappMilk;
        syrup = syrup - CappSyrup;
    }
    else 
    {
        coffee_beans = coffee_beans - CoffeeBeans;
        water = water - MochaWater;
        milk = milk - MochaMilk;
        syrup = syrup - MochaSyrup; 
    }

    if (coffee_beans <= low_beans)
    {
        printf("Error: Machine out of CoffeeBeans\n");
    }

    if (water <= low_water)
    {
        printf("Error: Machine out of Water\n");
    }

    if(milk <= low_milk)
    {
        printf("Error: Machine out of Milk\n");
    }

    if(syrup <= low_syrup)
    {
        printf("Error: Machine out of Syrup\n");
    }
}

int admin_mode()
{
    int pass;
    int choice = 0;

    printf("Enter the admin password: ");
    scanf("%d", &pass);

    if (password == pass)
    {
        printf("1. Display the quantity of each ingredient in the machine and the total sale amount \n");
        printf("2. Replenish ingredients in the machine \n");
        printf("3. Change coffee price \n");
        printf("0. Exit the Admin Mode function \n");

        printf("Enter a number from 1-3 to perform a task. Enter 0 to exit: ");
        scanf("%d", &choice);

        while (choice != 0 && choice != 1 && choice != 2 && choice != 3)
        {
            printf("Wrong Input\n");
            printf("Enter a number from 1-3 to perform a task. Enter 0 to exit: ");
            scanf("%d", &choice);
        }

        if (choice == 1)
        {
            display();
        }
        else if (choice == 2)
        {
            change_ing();
        }
        else if (choice == 3)
        {
            change_price();
        }

    }
    return 0;
}

int display()
{
    printf("The quantity of coffee beans is %d\n", coffee_beans);
    printf("The quantity of water is %d\n", water);
    printf("The quantity of milk is %d\n", milk);
    printf("The quantity of chocolate syrup is %d\n", syrup);
    printf("The total sale amount is %d\n", total_amount);
}

int change_ing()
{
    int number;
    printf("1. Coffee beans\n");
    printf("2. Water\n");
    printf("3. Milk\n");
    printf("4. Chocolate syrup\n");
    printf("Enter the ingredient's number from 1-4 to change the quantity: ");
    scanf("%d", &number);

    while (number != 1 && number != 2 && number != 3 && number !=4)
    {
        printf("Invalid input\n");
        printf("Enter the ingredient's number from 1-4 to change the quantity: ");
        scanf("%d", &number);
    }

    if (number == 1)
    {
        printf("The quantity of Coffee Beans in the machine is %d\n", coffee_beans);
        printf("Enter the changed quantity: ");
        scanf("%d", &coffee_beans);
        printf("The new quantity of Coffee Beans in the machine is %d\n", coffee_beans);
    }
    else if (number == 2)
    {
        printf("The quantity of Water in the machine is %d\n", water);
        printf("Enter the changed quantity: ");
        scanf("%d", &water);
        printf("The new quantity of Water in the machine is %d\n", water);
    }
    else if (number == 3)
    {
        printf("The quantity of Milk in the machine is %d\n", milk);
        printf("Enter the changed quantity: ");
        scanf("%d", &milk);
        printf("The new quantity of Milk in the machine is %d\n", milk);
    }
    else if (number == 4)
    {
        printf("The quantity of Chocolate Syrup in the machine is %d\n", syrup);
        printf("Enter the changed quantity: ");
        scanf("%d", &syrup);
        printf("The new quantity of Syrup in the machine is %d\n", syrup);
    }
}

int change_price()
{
    int number;
    printf("1. Espresso AED 3.5\n");
    printf("2. Cappucino AED 4.5\n");
    printf("3. Mocha AED 5.5\n");
   
    printf("Enter the coffee's number from 1-3 to change the price: ");
    scanf("%d", &number);

    while (number != 1 && number != 2 && number != 3)
    {
        printf("Invalid input\n");
        printf("Enter the ingredient's number from 1-3 to change the quantity: ");
        scanf("%d", &number);
    }

    if (number == 1)
    {
        printf("The price of Espresso is %f\n", EspPrice);
        printf("Enter the new price: ");
        scanf("%f", &EspPrice);
        printf("The new price of Espresso is %f\n", EspPrice);
    }
    else if (number == 2)
    {
        printf("The price of Cappucino is %f\n", CappPrice);
        printf("Enter the new price: ");
        scanf("%f", &CappPrice);
        printf("The new price of Cappucino is %f\n", CappPrice);
    }
    else if (number == 3)
    {
        printf("The price of Mocha is %f\n", MochaPrice);
        printf("Enter the new price: ");
        scanf("%f", &MochaPrice);
        printf("The new price of Mocha is %f\n", MochaPrice);
    }

}