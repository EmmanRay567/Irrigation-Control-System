#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define BUFFER 80

// Author: Emmanuel Edward Ray
// Course: COP2220C
// Instructor: Najib Saylani
// Date: 04/13/2025
// Description: 
// Simulates an irrigation control system that manages multiple zones, 
// activates rain sensors, sets operation schedules, and displays system status.

typedef struct Zone {
    int Sequence;
    time_t StartTime;
    time_t EndTime;
    int minutes;
    int Skip;
    int state;
} Zone;

typedef struct Controller {
    time_t CurrentDate;
    time_t CurrentTime;
    time_t OperationDate_Current;
    int RainSensorVal;
    int ZoneNums;
    Zone zone;
} Controller;

// Function prototypes
int MakeMenu(Controller *pController);
void ClearScreenAndDisplayTime(Controller *pController);
void ActivateRainSensor(int selection, int ZoneCount, Controller *pController);
void DisplayStates(int ZoneCount, Controller *pController, int selection);
void SystemReset(Controller *pController);
int SetZones(int ZoneCount);
void GenerateOrInput(Controller *pController, int selection, int ZoneCount);

int main() {
    srand(time(NULL));

    int ZoneCount = 0;
    int selection = 0;

    Controller *pController = malloc(sizeof(Controller));
    if (pController == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Welcome! Please select 1 to start, or 0 to end the program.\n");
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    selection = atoi(input);

    while (selection != 1 && selection != 0) {
        printf("Invalid input. Please enter 1 for yes or 0 for no: ");
        fgets(input, BUFFER, stdin);
        selection = atoi(input);
    }

    if (selection == 0) {
        printf("Thank you for using this program! Have a great day.\n");
    } else {
        while (selection != 6) {
            selection = MakeMenu(pController);
            switch (selection) {
                case 1:
                    ClearScreenAndDisplayTime(pController);
                    exit(0);
                case 2:
                    ZoneCount = SetZones(ZoneCount);
                    pController->ZoneNums = ZoneCount;
                    break;
                case 3:
                    GenerateOrInput(pController, selection, ZoneCount);
                    break;
                case 4:
                    ActivateRainSensor(selection, ZoneCount, pController);
                    break;
                case 5:
                    DisplayStates(ZoneCount, pController, selection);
                    break;
                case 6:
                    SystemReset(pController);
                    break;
                default:
                    printf("Invalid option. Please select between 1–6.\n");
            }
        }
    }

    free(pController);
    return 0;
}

// Displays the main menu
int MakeMenu(Controller *pController) {
    struct tm *local_time;
    time(&pController->CurrentTime);
    local_time = localtime(&pController->CurrentTime);
    printf("\nToday's Date and Time: %s", asctime(local_time));

    char input[BUFFER];
    printf("\n--- IRRIGATION CONTROL MENU ---\n"
           "1 - Display Current Time\n"
           "2 - Select Number of Zones\n"
           "3 - Configure Zone Operations\n"
           "4 - Set Rain Sensor Limits\n"
           "5 - Display System States\n"
           "6 - Reset System\n"
           "Enter your choice (1–6): ");
    fgets(input, BUFFER, stdin);
    return atoi(input);
}

// Clears screen and displays the current time
void ClearScreenAndDisplayTime(Controller *pController) {
    system("cls");
    struct tm *local_time;
    time(&pController->CurrentTime);
    local_time = localtime(&pController->CurrentTime);
    printf("Current Date and Time: %s\n", asctime(local_time));
}

// Sets the number of irrigation zones
int SetZones(int ZoneCount) {
    printf("Enter the number of zones to create: ");
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    ZoneCount = atoi(input);
    return ZoneCount;
}

// Generates or manually inputs zone data
void GenerateOrInput(Controller *pController, int selection, int ZoneCount) {
    printf("Generate values automatically (1) or enter manually (0)? ");
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    selection = atoi(input);

    if (selection != 0 && selection != 1) {
        printf("Invalid input. Please restart.\n");
        exit(1);
    }

    for (int i = 0; i < ZoneCount; i++) {
        if (selection == 0) {
            printf("\nEnter details for Zone %d:\n", i + 1);
            printf("Sequence Number: ");
            fgets(input, BUFFER, stdin);
            pController->zone.Sequence = atoi(input);

            printf("Start Time (integer): ");
            fgets(input, BUFFER, stdin);
            pController->zone.StartTime = atoi(input);

            printf("End Time (integer): ");
            fgets(input, BUFFER, stdin);
            pController->zone.EndTime = atoi(input);

            printf("Minutes Active: ");
            fgets(input, BUFFER, stdin);
            pController->zone.minutes = atoi(input);

            printf("Skip (0 or 1): ");
            fgets(input, BUFFER, stdin);
            pController->zone.Skip = atoi(input);

            printf("State (0 = off, 1 = on): ");
            fgets(input, BUFFER, stdin);
            pController->zone.state = atoi(input);

        } else {
            // Random generation
            pController->zone.Sequence = rand() % 6 + 1;
            pController->zone.StartTime = rand() % 100 + 50;
            pController->zone.EndTime = rand() % 200 + 80;
            pController->zone.minutes = rand() % 100 + 20;
            pController->zone.Skip = rand() % 2;
            pController->zone.state = rand() % 2;

            printf("\nGenerated Zone %d:\n", i + 1);
            printf("Start Time: %lld | End Time: %lld | Minutes: %d | Skip: %d | State: %d\n",
                   (long long)pController->zone.StartTime,
                   (long long)pController->zone.EndTime,
                   pController->zone.minutes,
                   pController->zone.Skip,
                   pController->zone.state);
        }
    }
}

// Activates the rain sensor based on user input
void ActivateRainSensor(int selection, int ZoneCount, Controller *pController) {
    int ActivationLength = 0;
    int RainSensorValue = 0;

    RainSensorValue = rand() % 2;
    ActivationLength = rand() % 5 + 10;

    printf("Enter threshold between 0 and 2 inches: ");
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    selection = atoi(input);

    if (selection == 0 || selection < RainSensorValue) {
        printf("\nSENSOR: OFF | All activity deactivated\nDuration: %d minutes\n", ActivationLength);
    } else if (selection >= 1 && selection <= 2) {
        printf("\nSENSOR: ON | %d zone(s) activated\nDuration: %d minutes\n", selection, ActivationLength);
    } else {
        printf("Invalid input. Please restart.\n");
        exit(1);
    }
}

// Displays the current states of zones
void DisplayStates(int ZoneCount, Controller *pController, int selection) {
    system("cls");
    struct tm *local_time;
    time(&pController->CurrentTime);
    local_time = localtime(&pController->CurrentTime);
    printf("\nDate and Time: %s\n", asctime(local_time));
    printf("Rain Sensor: %d (0 = off, 1 = on)\n", pController->RainSensorVal);

    for (int i = 0; i < ZoneCount; i++) {
        printf("\nZone %d\nStart Time: %lld\nEnd Time: %lld\nMinutes: %d\nSkip: %d\nState: %d\n",
               i + 1,
               (long long)pController->zone.StartTime,
               (long long)pController->zone.EndTime,
               pController->zone.minutes,
               pController->zone.Skip,
               pController->zone.state);
    }
}

// Resets the system
void SystemReset(Controller *pController) {
    system("cls");
    printf("System resetting... Press any key to confirm.\n");
    getchar();
    struct tm *local_time;
    time(&pController->CurrentTime);
    local_time = localtime(&pController->CurrentTime);
    printf("\nSystem time has been reset to: %s\n", asctime(local_time));
}
