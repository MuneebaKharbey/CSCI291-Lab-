#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 
#include <stdbool.h>

// Global Defined variables
#define NUM_TEAMS 5  
#define SQUAD_SIZE 11

// Structure to store player's age
typedef struct{
    int day; // date
    int month; // month
    int year; // year
} age;

// Structure to store player's details
typedef struct{
    char full_name[26]; // Player's full name
    int kit_number; // Player's kit number from 1 to 99
    char club[40]; // Club name 
    age dob; // Player's date of birth
    char position[20]; // Position of the player ex: Goalkeeper, Mid-fielder, Forward etc.
} player_t;

// Structure to store the details of the club
typedef struct{
    char name[21]; // Club name
    player_t players[SQUAD_SIZE]; // Array of players 
    int ActiveSize; // Number of players in the team currently
} team_t;

team_t teams[NUM_TEAMS]; // Array of teams 
int num_enrolled_clubs = 0; // Counter to track the number of clubs 

void display_menu();
void enroll_club();
void add_player();
int check_player_name(int team_num, char* full_name);
int check_kit_no(int team_num, int kit_number);
void search_update();
void update_player(int team_num, int player_num);
void display_club_statistics();
int get_current_year(); // Function to calculate the year 
double calculate_average_age(int team_num); // Function to calculate the average age
void handle_error(const char *message);

int main(){
    int choice;

    // Setting each team to have 0 players at the start
    for(int i = 0; i < NUM_TEAMS; i++){
        teams[i].ActiveSize = 0;
    }

    while (1)
    {
        display_menu();
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        if (choice == 1)
        {
            enroll_club();
        }
        else if (choice == 2)
        {
            add_player();
        }
        else if (choice == 3)
        {
            search_update();
        }
        else if (choice == 4)
        {
            display_club_statistics();
        }
        else
        {
            printf("Invalid Input. Program Exited.\n");
            break;
        }  
    }
}

// Function to display the menu
void display_menu()
{
   printf("\n1. Enroll a Club\n");
   printf("2. Add a player\n");
   printf("3. Search and update a player\n");
   printf("4. Club Statistics\n");
   printf("Enter your choice from 1-4. Input any other value to exit: ");
}

// Function to enroll a club
void enroll_club()
{
    if(num_enrolled_clubs >= NUM_TEAMS){ // Checking if the maximum number of clubs have been enrolled
        printf("Maximum number of clubs enrolled.\n"); // Error message to be displayed when max number of clubs reached
        return;
    }

    char club_name[21];
    printf("Enter club name: ");
    if(fgets(club_name, sizeof(club_name), stdin) == NULL){ // Reads team name
        printf("Error reading club name.\n");
        return;
    }
    club_name[strcspn(club_name, "\n")] = '\0'; // Remove newline character
    if(strlen(club_name) == 0){ // Check if club name is empty
        printf("You must enter a club name.\n"); // Error message to be displayed when club name is empty
        return;
    }
    for(int i = 0; i < num_enrolled_clubs; i++){
        if(strcasecmp(teams[i].name, club_name) == 0){ // Checks if the club name already exists
            printf("A club with the same name already exists.\n"); // Error message displayed when there is already an existing club name
            return;
        }
    }

    // Stores the club's name if no errors
    strcpy(teams[num_enrolled_clubs].name, club_name);
    teams[num_enrolled_clubs].ActiveSize = 0;
    num_enrolled_clubs++;
    printf("Club %s has been enrolled.\n", club_name);
}

// Function to add a player to a club
void add_player() {
    if (num_enrolled_clubs == 0) { // Ensure at least one club exists
        handle_error("No clubs are created yet.\n");
        return;
    }

    printf("Choose a team to add a player:\n");
    for (int i = 0; i < num_enrolled_clubs; i++) {
        printf("%d. %s\n", i + 1, teams[i].name); // Display enrolled teams
    }

    int team_number;
    printf("Enter the team number: ");
    scanf("%d", &team_number);
    getchar(); // Handle newline

    // Ensure valid team number
    if (team_number < 1 || team_number > num_enrolled_clubs) {
        handle_error("Invalid team number.\n");
        return;
    }

    // Adjust team index (1-based input to 0-based array index)
    int team_index = team_number - 1;

    if (teams[team_index].ActiveSize >= SQUAD_SIZE) { // Check for squad size limit
        handle_error("The team already has the maximum number of players.\n");
        return;
    }

    player_t new_player; // Create new player instance

    printf("Enter player's full name (max 25 characters): ");
    if (fgets(new_player.full_name, sizeof(new_player.full_name), stdin) == NULL) {
        handle_error("Error reading name.\n");
        return;
    }
    new_player.full_name[strcspn(new_player.full_name, "\n")] = '\0'; // Remove newline

    // Check for duplicate player name
    if (check_player_name(team_index, new_player.full_name)) {
        handle_error("A player with this name already exists in the team.\n");
        return;
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    getchar(); // Handle newline

    // Check for valid kit number
    if (!check_kit_no(team_index, new_player.kit_number)) {
        return; // Error already handled in check_kit_no
    }

    printf("Enter birth date (DD MM YYYY): ");
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year);
    getchar(); // Handle newline

    printf("Enter player's position: ");
    if (fgets(new_player.position, sizeof(new_player.position), stdin) == NULL) {
        handle_error("Error reading position.\n");
        return;
    }
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; // Remove newline

    // Add new player to the team's players array
    teams[team_index].players[teams[team_index].ActiveSize++] = new_player;

    printf("Player %s has been added to team %s.\n", new_player.full_name, teams[team_index].name);
}

// Function to check for duplicate player name
int check_player_name(int team_num, char* full_name){
    for(int i=0; i<teams[team_num].ActiveSize;i++){
        if(strcasecmp(teams[team_num].players[i].full_name, full_name)==0){
            return 1; // 1 is returned if there is a duplicate
        }
    }
    return 0; // 0 is returned if there isn't a duplicate
}

// Function to check for valid and unique kit number
int check_kit_no(int team_num, int kit_number){
    if (kit_number<1 || kit_number>99)
    {
        handle_error("Invalid kit number. Enter number between 1 and 99.\n"); // Error message to be displayed when outside the range 1-99
        return 0;
    }
    
    for(int i=0; i<teams[team_num].ActiveSize;i++){
        if(teams[team_num].players[i].kit_number==kit_number){
            handle_error("A player with this number is already there\n"); // Error message to be displayed when there are same kit numbers
            return 0;
        }
    }
    return 1; // Kit number is valid
}

// Function to search and update player details
void search_update(){
    if (num_enrolled_clubs==0){ // Ensures that a club is enrolled first
        handle_error("Enroll Teams First"); // Error message to be displayed if no clubs enrolled
        return;
    }
    
    int search_choice;
    printf("Search for a player by:\n1. Kit Number\n2. Name\n");
    scanf("%d",&search_choice);
    getchar();

    int x=0; // To keep track of the player searched
    if (search_choice == 1){ // User decides to search by kit number
        int kit_number;
        printf("Enter the kit number: ");
        scanf("%d", &kit_number);
        getchar();

        for (int i = 0; i < num_enrolled_clubs && !x; i++){
            for (int j = 0; j < teams[i].ActiveSize; j++){
                if (teams[i].players[j].kit_number == kit_number){ // Checking the structure for the same kit number
                   printf("Player found!\n"); 
                    
                    printf("Team: %s\n", teams[i].name);
                    printf("Player Name: %s\n", teams[i].players[j].full_name);
                    printf("Kit Number: %d\n", teams[i].players[j].kit_number);
                    printf("Position: %s\n", teams[i].players[j].position);
                    printf("Date of Birth: %d/%d/%d\n", teams[i].players[j].dob.day,teams[i].players[j].dob.month,teams[i].players[j].dob.year);

                    printf("Do you want to update player details\n1. Yes\n2. No:\n"); // Prompts the user to want to update player details or not
                    int update_choice;
                    scanf("%d", &update_choice);
                    getchar();
                    if (update_choice == 1){
                        update_player(i, j); // Calls the update_player function to update details
                    }
                    x = 1;
                    break;
                }
            }
        }
    }else if (search_choice == 2){ // User decides to search by player name
        char player_name[50];
        printf("Enter the player's name: ");
        if (fgets(player_name, sizeof(player_name), stdin) == NULL){ // Reads the player name entered
            handle_error("Error reading player name.\n"); // Error message to be displayed
            return;
        }
        player_name[strcspn(player_name, "\n")] = '\0'; // Removes new line character

        for (int i = 0; i < num_enrolled_clubs && !x; i++){
            for (int j = 0; j < teams[i].ActiveSize; j++){
                if (strcasecmp(teams[i].players[j].full_name, player_name) == 0){ // Checking the structure for same name
                    printf("Player found!\n"); 
                    
                    printf("Team: %s\n", teams[i].name);
                    printf("Player Name: %s\n", teams[i].players[j].full_name);
                    printf("Kit Number: %d\n", teams[i].players[j].kit_number);
                    printf("Position: %s\n", teams[i].players[j].position);
                    printf("Date of Birth: %d/%d/%d\n", teams[i].players[j].dob.day,teams[i].players[j].dob.month,teams[i].players[j].dob.year);
                    
                    printf("Do you want to update player details\n1. Yes\n2. No: \n"); // Prompts the user to want to update player details or not
                    int update_choice;
                    scanf("%d", &update_choice);
                    getchar();
                    if (update_choice == 1){
                        update_player(i, j); // Calls the update_player function to update details
                    }
                    x = 1;
                    break;
                }
            }
        }
    }else{
        handle_error("Wrong input\n"); // Error message to be displayed
        return;
    }
    if(!x){
        handle_error("Player not found\n"); // Error message to be displayed
    }
}

// Function to update player details
void update_player(int team_num, int player_num){
    int choice;
    printf("1. Update Name\n2. Update Kit Number\n3. Update DOB\n4. Update Position\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1){ // Updating name
        printf("Enter new name: ");
        if (fgets(teams[team_num].players[player_num].full_name, sizeof(teams[team_num].players[player_num].full_name), stdin) == NULL){
            handle_error("Error reading name.\n");
            return;
        }
        teams[team_num].players[player_num].full_name[strcspn(teams[team_num].players[player_num].full_name, "\n")] = '\0';
        printf("Player name updated.\n");
    }else if (choice == 2){ // Updating kit number
        printf("Enter new kit number: ");
        int new_kit_no;
        scanf("%d", &new_kit_no);
        getchar();
        if (!check_kit_no(team_num, new_kit_no)){ // Checking if the new kit number matches the criteria
            handle_error("Invalid or duplicate kit number.\n");
            return;
        }
        teams[team_num].players[player_num].kit_number = new_kit_no;
        printf("Kit number updated\n");
    }else if (choice == 3){ // Updating date of birth
        printf("Enter new DOB (DD MM YYYY): ");
        int day, month, year;
        scanf("%d %d %d", &day, &month, &year);
        getchar();

        // Storing the new DoB in the structure
        teams[team_num].players[player_num].dob.day = day;
        teams[team_num].players[player_num].dob.month = month;
        teams[team_num].players[player_num].dob.year = year;
        printf("DOB updated to %02d/%02d/%04d.\n", day, month, year);
    }else if (choice == 4){ // Updating the position
        printf("Enter new position: ");
        if (fgets(teams[team_num].players[player_num].position, sizeof(teams[team_num].players[player_num].position), stdin) == NULL) {
            handle_error("Error reading position.\n");
            return;
        }
        teams[team_num].players[player_num].position[strcspn(teams[team_num].players[player_num].position, "\n")] = '\0';
        printf("Position updated.\n");
    } 
    else {
        handle_error("Invalid choice."); // Error message to be displayed
    }
}

// Function to display club statistics
void display_club_statistics() {
    printf("\nClub Statistics\n");
    printf("Number of Enrolled Teams: %d\n\n", num_enrolled_clubs);

    for (int i = 0; i < num_enrolled_clubs; i++) {
        printf("Team %d: %s\n", i + 1, teams[i].name);
        printf("Number of Players: %d\n", teams[i].ActiveSize);

        if (teams[i].ActiveSize == 0) {
            printf("No players in this team.\n\n");
            continue;
        }

        printf("Players:\n");
        for (int j = 0; j < teams[i].ActiveSize; j++) {
            player_t player = teams[i].players[j];
            printf("  Name: %s\n", player.full_name);
            printf("  Kit Number: %d\n", player.kit_number);
            printf("  Position: %s\n", player.position);
            printf("  Date of Birth: %02d/%02d/%04d\n\n", player.dob.day, player.dob.month, player.dob.year);
        }
        // Calculate and print the average age of the team.
        double avg_age = calculate_average_age(i);
        printf("Average age of the team: %.2f years\n", avg_age);
    }
}

// Function to get the current year for calculating the average age
int get_current_year(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

// Function to calculate the current average age
double calculate_average_age(int team_num){
    if (teams[team_num].ActiveSize == 0){
        return 0.0; // Return 0 if there are no players in the team
    }

    int total_age = 0;
    int current_year = get_current_year(); // Get the current year

    for (int i = 0; i < teams[team_num].ActiveSize; i++){
        total_age += (current_year - teams[team_num].players[i].dob.year); // Calculate the age of each player and add to total_age
    }

    return (double) total_age / teams[team_num].ActiveSize; // Calculate and return the average age
}

// Function that prints and handles all the error messages
void handle_error(const char *message){
    printf("Error: %s\n", message);
}