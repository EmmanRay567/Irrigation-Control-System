#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#define buffer 80
#define SIZE 100
//Author: Emmanuel Ray
//Course: COP2220C
//Teacher: Najib Saylani
//date: 04-13-2025
//Description: This Project simulates the design of a Irrigation control system. The User
//Will select from a variety of options for the system and will be able to control certain aspects of this program.

// This structure declares A structure Controller, and in it the structure Zone.
// The controller will be able to control the aspects of the zone, and act on them
//Right now, this is just initializing the values/variables for each structure
 struct Controller {
    time_t CurrentDate;
    time_t Current_Time;
    time_t OperationDate_Current;
    int RainSensorVal;
    int ZoneNums;
//-----------------------------------------
struct Zone {
    int Sequence;
    time_t StartTime;
    time_t EndTime;
    int minutes;
    int Skip;
    int state;
    }; struct Zone zone;

} typedef Controller;  //Declares New names for these structures instead of having to declare struct for every variable.



//prototypes:
int MakeMenu(struct Controller* pController);
void ClearScreenAndDisplayTime(struct Controller*pController);
void ActivateRainsSensor(int selection, int ZoneCount, struct Controller*pController);
void DisplayStates(int ZoneCount, struct Controller*pController, int selection);
void SystemReset(struct Controller*pController);


int main(){
  //Declarations:
//------------------------------------------
  srand(time(NULL)); // call the time/Random Function
  int ZoneCount = 0; // Sets zoneCount to be used for user input and malloc
  int Create = 0;
  int Delete = 0;
  int selection = 0;
  int CreateZones = 0; // Used for the Set zones function
  int ActivationLength = 0; // Activates amount of time the sensor will be on for
  int CountZones = 0;

  Controller*pController = malloc(ZoneCount*sizeof(Controller)); // What this is doing is we are first Making a pointer to the structure/typedef Controller
  //and storing it in memory. The malloc(sizeof(Controller) stores or analyzes how much memory is need or sees it can hole enough memory Size that will work for Controller.
    if(pController == NULL) { // if This memory Allocation fails, Then the user will know that it was not suzzessful
        printf("Sorry Could not Allocate Memory");
        exit(1);
    }

 pController->Sequence; // What this is doing is pointing to the sequence Structure in zone using the pointer pController.
 pController->StartTime;// What this is doing is pointing to the StartTime Structure in zone using the pointer pController.
 pController->EndTime; // What this is doing is pointing to the End Time Structure in zone using the pointer pController.
 pController->minutes; // What this is doing is pointing to the Minutes Structure in zone using the pointer pController.
 pController->Skip; // What this is doing is pointing to the Skip Structure in zone using the pointer pController.
 pController->state; // What this is doing is pointing to the State Structure in zone using the pointer pController.
 //Input:-----------------------------------------------------------------------------------------------------------------
    char input[buffer] = " "; // makes space for 80 characters maximum and stores user input.
    char *pinput = NULL; // pointer pinput points to a value of nothing. However this pointer takes the rule of input.
      printf("Welcome! Please select 1 start, or 0 to end the program :).");
      pinput = fgets(input, buffer, stdin); // gets user input
      selection = atoi(pinput); // converts character string input to integers.

         //As long as the Selection is not 1 or 0, keep asking the user to enter 1 for yes, or 0 for no.
         while(selection != 1 && selection != 0) {
         printf("Sorry, but please 1 for yes or 0 for no: ");
         pinput = fgets(input, buffer, stdin); // Gets user input again
        selection = atoi(pinput); // converts selection that was a string to integer input.
}
//Case Statements:------------------------------------------------------------------------------
          if(selection == 0){
         printf("Thank you for interacting with this program! have a wonderful day!\n");
           }else{
             while(selection != 6) { // As long as the user does not press 6, the program will run
            selection = MakeMenu(pController); //takes the user's selection value and creates the menu
             switch(selection) {
           case 1: ClearScreenAndDisplayTime(pController); //if the user selects 1, this will clear the screen, display time, and exit the program.
                   exit(1);
                   break;

           case 2:   ZoneCount = SetZones(ZoneCount); // This Assigns Zone Count to the User's Input
                     pController->ZoneNums = ZoneCount;// This Assigns the pController From memory to the ZoneNums Structure
                                                        // And takes thee value of ZoneCount.
                       break;
           case 3:  GenerateOrInput(pController,selection,ZoneCount); // Generates or inputs Values
                     exit(1);
                     break;
           case 4:   ActivateRainsSensor(selection,ZoneCount,pController); //Activates Rain Sensor
                       exit(1);
                        break;
           case 5: DisplayStates(ZoneCount,pController,selection); //Displays Conditions
                      break;
           case 6: SystemReset(pController); //Resets System.
                     break;
                     default: exit(1); // if user selects An option other than 1-6, the Program will End.


              }//End Switch
             }//End While
           }// end else
free(pController);
return 0;



} // End Main

//This Function Creates the menu and Displays the Current Date and Time.
int MakeMenu(struct Controller* pController) {
   struct tm* local_time; // Declares a struct tm for the local time to be used
   time(&pController->Current_Time); //Points the pController to the Current_Time Var in the struct Controller
   local_time = localtime(&pController->Current_Time);
printf("\nToday's date and Current time: %s\n", asctime(local_time)); // displays current date and time
 int selection = 0;
  char input[buffer] = " "; // declares space for 80 characters
  char* pinput = NULL; // pointer to nowhere
   printf("\n-1-Set Date and Time\n"
          "\n-2-Select Number of Zones\n"
          "\n-3-Configure operation of all zones (start date, start time, end time)\n"
          "\n-4-Set the rain sensor limits to increments of .5 inches to a max of 2 inches\n"
          "\n-5-Schedule the operation\n"
          "\n-6-Reset System\n"
          "\t\tEnter option 1-6:\n "); // menu
         pinput = fgets(input, buffer, stdin); // gets user input
         strtok(pinput, "\n"); // removes the new line.
selection = atoi(pinput); // converts the user input into an integer.
return selection; // returns user input.

}

 void ClearScreenAndDisplayTime(struct Controller*pController) {
     system("cls"); // Tells the system to clear screen. (cls stands for clear screen);
     struct tm* local_time; // Declares struct tm for time.
   time(&pController->Current_Time); //points to the Current_Time in struct
   local_time = localtime(&pController->Current_Time); //Assigns Local time to The Current Timee
printf("Today's date and Current time: %s\n", asctime(local_time));

 }

//This Function Takes the User's Input for the Amount of zones they would like to be created.
int SetZones(int ZoneCount) {
   printf("Please enter the Number of zones you would like to Create.");
   char input[buffer] = " "; // declares space for 80 characters
   char* pinput = NULL; // pointer to nowhere
   pinput = fgets(input, buffer, stdin); // gets user Input
   strtok(pinput, "\n"); // removes new line
   ZoneCount = atoi(pinput); // assigns user's zone number value to an integer.
 return ZoneCount; // returns the user's value to main.
 }

 //This Function Allows the user to choose whether they want to generate zone values manually or randomly
 void GenerateOrInput(struct Controller*pController, int selection, int ZoneCount) {
    int choice = 0;
    int random = 0;
    int i = 0;
    printf("How would you like to generate values for each attribute? Press 0 for manual, 1 for random generated.");
    scanf("%d", &selection);
     if(selection != 0 && selection != 1){ // Validation to prevent the User from continuing the program if they enter the wrong value.
       printf("Sorry I did not get that. Please Restart.");
       exit(1); // quits program.
     }
      switch(selection) {
       case 0: printf("Please enter values for: \nDate \nTime \nOperation Date \nRain Sensor Value \n These are for your chosen Zones: ");
         for(int i = 0; i < ZoneCount; i++) {
             printf("\nPlease enter Zone/Sequence %d", i + 1);
             char input[buffer] = " ";
             char* pinput = NULL;
              pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].Sequence = atoi(pinput); // points to an i element that pController assigns from Sequence to the users input

             printf("\nPlease enter the Start Time for this zone: ");
              pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].StartTime = atoi(pinput);// points to an i element that pController assigns for Start Time to the users input



             printf("\nPlease enter the End Time: ");
              pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].EndTime = atoi(pinput); // points to an i element that pController assigns for End Time to the users input

             printf("\nPlease enter the Minutes: ");

             pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].minutes = atoi(pinput);// points to an i element that pController assigns for minutes to the users input

             printf("\nPlease Enter the Skip: ");
             pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].Skip = atoi(pinput);// points to an i element that pController assigns for Skip to the users input

             printf("\nPlease enter the State: ");
              pinput = fgets(input, buffer, stdin);
             strtok(pinput, "\n");
             pController[i].state = atoi(pinput);// points to an i element that pController assigns for State to the users input

              for(int i = 0; i < ZoneCount; i++) {
                 printf("\nUser Created Zone:", pController[i].Sequence); //PController Displays The Value from the Sequence in the structure Zone
                 printf("\nStart Time: %d",pController->StartTime);//PController Displays The Value from the Start Time in the structure Zone
                 printf("\nEnd Time: %d",pController->EndTime);//PController Displays The Value from the End Time in the structure Zone
                 printf("\nMinutes: %d",pController->minutes);//PController Displays The Value from the Minutes in the structure zone
                 printf("\nSkip: %d",pController->Skip);//PController Displays The Value from the Sequence in the structure Zone
                 printf("\nState: %d",pController->state);//PController Displays The Value from the Sequence in the structure Zone
                 printf("\n-----------------------------------------------------");
              }

         }
                break;

           case 1: for(int i = 0; i < ZoneCount; i++) {
                 pController[i].Sequence = rand() % 6+1; //Assigns pController in the i-th element from sSequence a random Number from 1-6
                 pController[i].StartTime = rand() % 100 + 50; //Assigns pController in the i-th element from sSequence a random Number 50 - 249
                 pController[i].EndTime = rand() % 200 + 80;//Assigns pController in the i-th element from sSequence a random Number 80 -279
                 pController[i].minutes = rand() % 100 + 20;//Assigns pController in the i-th element from sSequence a random Number from 20 - 119
                 pController[i].Skip = rand() % 2;//Assigns pController in the i-th element from sSequence a random Number from 0-2
                 pController[i].state = rand()% 2;//Assigns pController in the i-th element from sSequence a random Number. Assigns values from 0 - 2
//-------------------------------------------------------------------------
                 printf("\nZone: %d", pController[i].Sequence); // displays Value from i-th elemment for Sequence
                 printf("\nStart Time: %d",pController[i].StartTime); // displays Value from i-th elemment for StartTime
                 printf("\nEnd Time: %d",pController[i].EndTime);// displays Value from i-th elemment for EndTime
                 printf("\nMinutes: %d",pController[i].minutes);// displays Value from i-th elemment for Minutes
                 printf("\nSkip: %d",pController[i].Skip); // displays Value from i-th elemment for Skip
                 printf("\nState: %d",pController[i].state);// displays Value from i-th elemment for State
                 printf("\n-----------------------------------------------------");

           }
                   break;

 }

 }

// This Function Activates the Rain Sensor according to the user's selection
  void ActivateRainsSensor(int selection, int ZoneCount, struct Controller*pController) {
      int ActivationLength = 0;
      int ActivationPoint = 0;
      int RainSensorValue = 0;
    for(int i = 0; i < ZoneCount; i++ ) {
         RainSensorValue = rand() % 2; // Assigns random value from 0 - 2
         ActivationPoint = rand() % 2 + 4; // assigns numbers from 4 - 5;
         ActivationLength = rand()% 5 + 10; // generates Numbers from 10 - 14.
    }
    printf("\nPlease enter the threshold to increment between 0 and 2 inches.");
       scanf("%d",&selection);
         if(selection == 0 || selection < RainSensorValue){
            printf("\nYour selection is %d\nSENSOR: OFF: STATUS: ALL ACTIVITY IS DEACTIVATED"
                   "\nSensor will be on %d minutes", selection, ActivationLength);
         }else{
               if(selection != 0 && selection != 1 && selection != 2){ // Checks and tells the user to restart the program if they do not enter a value between 0 -2.
                 printf("Sorry, You were supposed to enter a number between either 0 and 2. Goodbye!");
                      exit(1);
             }else{
                if(selection == 1 || selection < RainSensorValue){ // if user selections 1 then it activates in at least 1 value
                     printf("\nYour selection is %d\nSENSOR: ON: STATUS: least 1 zone has been ACTIVATED"
                            "\nSensor will be on for %d minutes", selection, ActivationLength);
                     }else{
                     if(selection == 2) {
                           printf("\nYour selection is %d\nSENSOR: ON: STATUS: least 2 zones have been ACTIVATED:"
                                  "\nSensor will be on for %d minutes", selection, ActivationLength);

                     }
                }
             }
//-------------------------------------------------------------------------------------------------------------------------
}
  }

// Displays  The state of the Zones, and the current time

//Processing:
void DisplayStates(int ZoneCount, struct Controller*pController, int selection) {
    int i = 0;
    int ZoneStatus = 0;
    system("cls");
    struct tm* local_time;
   time(&pController->Current_Time);
   local_time = localtime(&pController->Current_Time);
printf("\nToday's date and Current time: %s\n", asctime(local_time)); // prints todays current day and time
//------------------------------------------------------------------------------------------------------
printf("Rain Sensor: %d: (Note: if rain Sensor is 0 or less, the sensor is off)", pController->RainSensorVal);
        for(int i = 0; i < ZoneCount; i++) {
        printf("\nZone: %d", pController->Sequence);
                 printf("\nStart Time: %d",pController->StartTime); // Displays Start Time
                 printf("\nEnd Time: %d",pController->EndTime);  // Displays End TIme
                 printf("\nMinutes: %d",pController->minutes); // Displays Minutes
                 printf("\nSkip: %d",pController->Skip); //Displays Skip
                 printf("\nState: %d (Tells you if the Zone is on or off)",pController->state);
        }
}

//resets the system, and uses getchar to display the date and time again.
void SystemReset(struct Controller*pController) {
      system("cls");
     printf("You have Decided to Reset the system. Please press any key to reset the time. After you set the time, please restart the program to go back to options 1 - 6.");getchar();
     struct tm* local_time;
   time(&pController->Current_Time);
   local_time = localtime(&pController->Current_Time);
printf("\nToday's date and Current time: %s\n", asctime(local_time)); // displays date and time



}



