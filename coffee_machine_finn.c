#include <stdio.h>
#include <stdlib.h>

#define CoffeeBeans 8

//Water Constants
#define EspWater 30
#define CappWater 30
#define MochaWater 39

//Milk Constants
#define CappMilk 70
#define MochaMilk 160

//Syrup Constants
#define EspSyrup 0
#define CappSyrup 0
#define MochaSyrup 30

//Password for admin mode
#define password 987654

//Low ingredient constants
#define low_beans 8
#define low_water 30
#define low_milk 70
#define low_syrup 30

//Initialising Coffee Prices Variables
float EspPrice = 3.5;
float CappPrice = 4.5;
float MochaPrice = 5.5;

//Initialising variables
float total_amount;
int coffee_beans = 200;
int water = 200;
int milk = 200;
int syrup = 200;
float price;

//General global variables
int selection = 0;
int order = 0;
int true = 0;
int confirm = 0;

//Function prototypes
int coffee_order();
int ing_check(int a);
int payment(int a);
void thankyou (int a);
int ing_count(int a);
int admin_mode();
int display();
int change_ing();
int change_price();

// Main Function
int main(void)
{
    while (1) // Infinite loop for the main menu
    {
        printf("\n1. Order a coffee\n"); // Displays the main menu
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
            coffee_order(); // Function that directs to coffee menu
        }
        else if (selection == 2)
        {
            admin_mode(); // Function that directs to admin menu
        }
        else 
        break; // Exits the main function
    }  
}
    
int coffee_order() // Coffee menu function
{
    while (1)
    {
        printf("\n1. Espresso AED %.2f\n", EspPrice); // Prints coffee menu and price
        printf("2. Cappucino AED %.2f\n", CappPrice);
        printf("3. Mocha AED %.2f\n", MochaPrice); 

        printf("To place your order, enter a number from 1 to 3. To exit, enter 0: "); // Inputs coffee order from user
        scanf("%d", &order);

        while (order != 1 && order != 2 && order !=3 && order != 0)
        {
            printf("Wrong Input\n");
            printf("Enter a number from 1-3: ");
            scanf("%d", &order);
        }

        if(order == 0)
        {
            return 0; // Exits the coffee function
        }
        else if(order == 1 || order == 2 || order == 3)
        {        
            ing_check(order); // calls function that checks if ingredients are available for the coffee ordered
            if (true == 1)
            {
                printf("Unavailable due to temporarily insufficient ingredients\n");
                return 0;
            }
            else
            {
                // Confirmation of order
                if (order == 1) 
                {
                    printf("\nCoffee Type: Espresso\n");
                    printf("Coffee Price: %.2f\n", EspPrice);
                    printf("Enter 1 to confirm your order or enter 0 to exit: ");
                    scanf("%d", &confirm);
                    printf("\n");
                }
                else if (order == 2)
                {
                    printf("\nCoffee Type: Cappucino\n");
                    printf("Coffee Price: %.2f\n", CappPrice);
                    printf("Enter 1 to confirm your order or enter 0 to exit: ");
                    scanf("%d", &confirm);
                    printf("\n");
                }
                else if (order == 3)
                {
                    printf("\nCoffee Type: Mocha\n");
                    printf("Coffee Price: %.2f\n", MochaPrice);
                    printf("Enter 1 to confirm your order or enter 0 to exit: ");
                    scanf("%d", &confirm);
                    printf("\n\n");
                }
                
                if (confirm == 1)
                {
                    payment(order); // Calls function that completes the payment of the order
                    ing_count(order); // Calls a function that updates the ingredients
                }
                else
                {
                    continue; // goes back to the coffee menu
                }
            }
        }
    }
}

int ing_check(int a) // Ingredient check function 
{
    if (a == 1)
    {
        if (coffee_beans < CoffeeBeans || water < EspWater || syrup < EspSyrup)
        {
            true = 1;
        }
        else{
            true = 0;
        }
    }
    else if (a == 2)
    {
        if (coffee_beans < CoffeeBeans || water < CappWater || syrup < CappSyrup || milk < CappMilk)
        {
            true = 1;
        }
        else{
            true = 0;
        }
    }
    else if (a == 3)
    {
        if (coffee_beans < CoffeeBeans || water < MochaWater || syrup < MochaSyrup || milk < MochaMilk)
        {
            true = 1;
        }
        else{
            true = 0;
        }
    }
}

int payment(int a) // Payment function
{
    float to_be_paid;
    float coin = 0;
    float amount = 0;

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
    thankyou(a);
    total_amount = total_amount + to_be_paid; // updates total amount
    return 0;
}

void thankyou (int a)
{
    if (a == 1)
    {
        printf("Thankyou for ordering an Espresso. Your total was %.2f. Enjoy!\n", EspPrice);
    }
    else if (a == 2)
    {
        printf("Thankyou for ordering a Cappucino. Your total was %.2f. Enjoy!\n", CappPrice);
    }
    else if (a == 3)
    {
        printf("Thankyou for ordering a Mocha. Your total was %.2f. Enjoy!\n", MochaPrice);
    }
}

int ing_count(int a) // Updates ingredients in the machine
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

    // Sends out alerts if the ingredients run low
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

int admin_mode() //Admin function
{
    int pass;
    int choice = 0;

    printf("Enter the admin password: "); // Asks the user for password
    scanf("%d", &pass);

    if (password == pass) //Checks if the password is correct
    {
        while (1) // Infinite loop for the admin function
        {
            printf("\n1. Display the quantity of each ingredient in the machine and the total sale amount \n");
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
                display(); //Calls a function that displays quantites and asks if total amount needs to be reset
            }
            else if (choice == 2)
            {
                change_ing(); //Calls a function that replenishes ingredients
            }
            else if (choice == 3)
            {
                change_price(); //Calls a function that can change price of any coffee
            }
            else if (choice == 0)
            {
                break; //Exits admin mode
            }
        }
    }
    else{
        printf("Incorrect Password!\n"); //If password is incorrect, it informs the user 
    }
    return 0;
}

int display() // Displays the quantities and total amount and also prompts the user to reset total sales
{
    int change = 0;
    printf("\nThe quantity of coffee beans is %d\n", coffee_beans);
    printf("The quantity of water is %d\n", water);
    printf("The quantity of milk is %d\n", milk);
    printf("The quantity of chocolate syrup is %d\n", syrup);
    printf("The total sale amount is %.2f\n\n", total_amount);
    printf("Do you want to reset the total sale amount to 0? Enter 1 if yes, Enter 0 if no: \n"); //Prompts the user to reset total sale amount
    scanf("%d", &change);

    if (change == 1)
    {
        total_amount = 0; //resets total_amount
        printf("Don't forget to collect the money from the machine!\n\n");
        change = 0;
    } 
}

int change_ing() //Replenishes ingredients
{
    int number;
    printf("\n1. Coffee beans\n");
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
        printf("\nThe old quantity of Coffee Beans in the machine was %d\n", coffee_beans);
        coffee_beans = coffee_beans + ((rand() % 1991) + low_beans);
        printf("The new quantity of Coffee Beans in the machine is %d\n", coffee_beans);
    }
    else if (number == 2)
    {
        printf("\nThe old quantity of Water in the machine was %d\n", water);
        water = water + ((rand() % 1960) + low_water);
        printf("The new quantity of Water in the machine is %d\n", water);
    }
    else if (number == 3)
    {
        printf("\nThe old quantity of Milk in the machine was %d\n", milk);
        milk = milk + ((rand() % 1839) + low_milk);
        printf("The new quantity of Milk in the machine is %d\n", milk);
    }
    else if (number == 4)
    {
        printf("\nThe old quantity of Chocolate Syrup in the machine was %d\n", syrup);
        syrup = syrup + ((rand() % 2969) + low_syrup);
        printf("The new quantity of Syrup in the machine is %d\n", syrup);
    }
}

int change_price() //Changes prices
{
    int number;
    printf("\n1. Espresso AED %.2f\n", EspPrice);
    printf("2. Cappucino AED %.2f\n", CappPrice);
    printf("3. Mocha AED %.2f\n", MochaPrice);
   
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
        printf("The price of Espresso is %.2f\n", EspPrice);
        printf("Enter the new price: ");
        scanf("%f", &EspPrice);
        printf("The new price of Espresso is %.2f\n", EspPrice);
    }
    else if (number == 2)
    {
        printf("The price of Cappucino is %.2f\n", CappPrice);
        printf("Enter the new price: ");
        scanf("%f", &CappPrice);
        printf("The new price of Cappucino is %.2f\n", CappPrice);
    }
    else if (number == 3)
    {
        printf("The price of Mocha is %.2f\n", MochaPrice);
        printf("Enter the new price: ");
        scanf("%f", &MochaPrice);
        printf("The new price of Mocha is %.2f\n", MochaPrice);
    }
}