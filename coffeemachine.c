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
#define low_water 30
#define low_milk 70
#define low_syrup 30

int total_amount = 0;
int coffee_beans, water, milk, syrup, price;

int selection = 0;

int main()
{

}

int main_menu()
{
    printf("1. Order a coffee\n");
    printf("2. Admin mode\n");
    printf("3. Exit\n");

    while (selection != 1 || selection != 2 || selection !=3)
    {
        printf("Enter your chosen field's number from 1-3: ");
        scanf("%d", &selection);
    }
    return 0;
}
