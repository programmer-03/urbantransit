#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_TRAINS 5

typedef struct Ticket {
    int ticketNo;
    char name[50];
    char time[10];
    char from[20];
    char destination[20];
    char date[12];
    int distance;
    int fare;
    struct Ticket* next;
} Ticket;

typedef struct TrainSchedule {
    char from[20];
    char destination[20];
    char departureTime[10];
    char arrivalTime[10];
} TrainSchedule;

int calculateFare(int distance) {
    return 5 * distance;
}

Ticket* createTicket(int ticketNo, char* name, char* from, char* destination, int distance, char* departureTime) {
    Ticket* newTicket = (Ticket*)malloc(sizeof(Ticket));
    newTicket->ticketNo = ticketNo;
    strcpy(newTicket->name, name);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(newTicket->time, "%02d:%02d", tm.tm_hour, tm.tm_min);
    strcpy(newTicket->from, from);
    strcpy(newTicket->destination, destination);
    sprintf(newTicket->date, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    newTicket->distance = distance;
    newTicket->fare = calculateFare(distance);
    newTicket->next = NULL;
    return newTicket;
}

void enqueueTicket(Ticket** head, Ticket* newTicket) {
    if (*head == NULL) {
        *head = newTicket;
    } else {
        Ticket* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTicket;
    }
}

Ticket* dequeueTicket(Ticket** head) {
    if (*head == NULL) {
        return NULL;
    }
    Ticket* dequeuedTicket = *head;
    *head = (*head)->next;
    dequeuedTicket->next = NULL;
    return dequeuedTicket;
}

void initializeTrainSchedule(TrainSchedule* schedule) {
    // Initially, there are no scheduled trains by admin.
    // Admin can schedule trains during the program.
    for (int i = 0; i < MAX_TRAINS; i++) {
        strcpy(schedule[i].from, "");
        strcpy(schedule[i].destination, "");
        strcpy(schedule[i].departureTime, "");
        strcpy(schedule[i].arrivalTime, "");
    }
}

void printStations(char* stations[], int count) {
    printf("Available Stations:\n");
    for (int i = 0; i < count; i++) {
        printf("%d) %s\n", i + 1, stations[i]);
    }
}

void generateQRCode() {
    int opt;
    printf("Scan the below QRCODE for payment!\n");
    printf(" ▄▄▄▄▄▄▄ ▄▄▄▄▄ ▄▄▄▄▄▄▄ \n");
    printf(" █ ▄▄▄ █ █▄▀ █ ▄▄▄ █ \n");
    printf(" █ ███ █ ▀█▀▄ █ ███ █ \n");
    printf(" █▄▄▄▄▄█ ▄ ▄▀█ █▄▄▄▄▄█ \n");
    printf(" ▄▄ ▄▄ ▄ ▀██▀█ ▄ ▄ \n");
    printf(" ██▀█ █▄ ▄ ▀ ▀██▀ ▀██▄ \n");
    printf(" ▀▀▄ ▀▄▄▀ ▄▀▀ █ ▄▄▀██ \n");
    printf(" ▄▄▄▄▄▄▄ ▀▄█▀█▄ █▄▀ ▀ \n");
    printf(" █ ▄▄▄ █ ▄▀ ██▀▀█ █▀ \n");
    printf(" █ ███ █ ▀█▀▀▀██▀▄▀▀▄▄ \n");
    printf(" █▄▄▄▄▄█ █▄▀▄ █▀▀▄▀▀▀▀ \n");

    printf("1. Payment Done!\n2. Cancel\nEnter Your Choice: ");
    scanf("%d", &opt);

    switch(opt){
    case 1:
    printf("Payment Successfull!\n");
    break;
    case 2:
    printf("Cancelled Successfully!!");
    break;

}
}
int main() {
    Ticket* ticketQueue = NULL;
    char name[50];
    int from, to, ticketNo = 1;
    int choice;
    int trainCount = 0;

    int distances[5][5] = {
        {0, 200, 150, 250, 200},
        {200, 0, 80, 0, 0},
        {150, 80, 0, 0, 0},
        {250, 0, 0, 0, 0},
        {200, 0, 0, 0, 0}
    };
    char* stations[5] = {"Pune", "Mumbai", "Thane", "Nashik", "Nagpur"};

    TrainSchedule schedule[MAX_TRAINS];
    initializeTrainSchedule(schedule);

    int attempts = 3;
    char adminUsername[50];
    char adminPassword[50];

    while (1) {
              printf("\nMENU:\n");
        printf("1. Schedule a train (Admin)\n");
        printf("2. Book a ticket (User)\n");
        printf("0. Exit & Print Tickets\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting the program...\n");
                break;
            case 1:
                if (attempts > 0) {
                    char inputUsername[50];
                    char inputPassword[50];

                    printf("\nEnter Admin Username: ");
                    scanf("%s", inputUsername);
                    printf("Enter Admin Password: ");
                    scanf("%s", inputPassword);

         if ((strcmp(inputUsername, "202202230") == 0 || strcmp(inputUsername, "202202251") == 0) &&
    (strcmp(inputPassword, "202202230") == 0 || strcmp(inputPassword, "202202251") == 0)) {
    attempts = 3; // Reset attempts on successful login
} else {
    attempts--;
    printf("Invalid credentials. %d attempts remaining.\n", attempts);
    if (attempts == 0) {
        printf("Too many incorrect attempts. Press 3 for 'Forgot Password' option.\n");
    }
    break;
}


                } else {
                    printf("Too many incorrect attempts. Press 3 for 'Forgot Password' option.\n");
                }

                if (trainCount < MAX_TRAINS) {
                    printStations(stations, 5);

                    printf("Enter the number for departure station: ");
                    scanf("%d", &from);
                    from--;

                    printf("Enter the number for destination station: ");
                    scanf("%d", &to);
                    to--;

                    printf("Enter departure time (hh:mm): ");
                    char departureTime[10];
                    scanf("%s", departureTime);


                    printf("Enter arrival time (hh:mm): ");
                    char arrivalTime[10];
                    scanf("%s", arrivalTime);

                    strcpy(schedule[trainCount].from, stations[from]);
                    strcpy(schedule[trainCount].destination, stations[to]);
                    strcpy(schedule[trainCount].departureTime, departureTime);
                    strcpy(schedule[trainCount].arrivalTime, arrivalTime);

                    printf("Train scheduled from %s to %s at %s - %s\n", stations[from], stations[to], schedule[trainCount].departureTime, schedule[trainCount].arrivalTime);
                    trainCount++;
                } else {
                    printf("All train schedules are full. Admin can't schedule more trains.\n");
                }
                break;
            case 2:
                if (trainCount == 0) {
                    printf("Sorry for the inconvenience. No trains are scheduled. Admin needs to schedule a train first.\n");
                } else {
                    printf("Enter your name: ");
                    scanf("%s", name);

                    printStations(stations, 5);

                    printf("Enter the number for departure station: ");
                    scanf("%d", &from);
                    from--;

                    printf("Enter the number for destination station: ");
                    scanf("%d", &to);
                    to--;

                    char departureStation[20];
                    char destinationStation[20];
                    strcpy(departureStation, stations[from]);
                    strcpy(destinationStation, stations[to]);

                    int distance = distances[from][to];

                    int foundMatchingSchedule = 0;
                    for (int i = 0; i < MAX_TRAINS; i++) {
                        if (strcmp(schedule[i].from, departureStation) == 0 && strcmp(schedule[i].destination, destinationStation) == 0) {
                            foundMatchingSchedule = 1;
                            char departureTime[10];
                            strcpy(departureTime, schedule[i].departureTime);
                            char arrivalTime[10];
                            strcpy(arrivalTime, schedule[i].arrivalTime);
                            Ticket* newTicket = createTicket(ticketNo++, name, departureStation, destinationStation, distance, departureTime);
                            enqueueTicket(&ticketQueue, newTicket);

                            // Generate and display QR code
                            char qrData[100]; // You may need to adjust the size based on your data
                            sprintf(qrData, "Ticket No.: %02d\nName: %s\nFrom: %s\nTo: %s\nDate: %s\nTime: %s\nDistance: %d Km\nFare: $%d", newTicket->ticketNo, newTicket->name, newTicket->from, newTicket->destination, newTicket->date, newTicket->time, newTicket->distance, newTicket->fare);
                            generateQRCode(qrData);

                            printf("Ticket generated and added to the queue.\n");
                            break;
                        }
                    }

                    if (!foundMatchingSchedule) {
                        printf("Sorry, there is no matching schedule for your selected stations.\n");
                    }
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        if (choice == 0) {
            break;
        }
    }

    printf("\n\n");

    while (ticketQueue != NULL) {
        Ticket* processingTicket = dequeueTicket(&ticketQueue);
        if (processingTicket != NULL) {
            printf("************************************\n");
            printf(" METRO TICKET\n");
            printf("************************************\n");
            printf("Ticket No.: %02d\n", processingTicket->ticketNo);
            printf("Name: %s\n", processingTicket->name);
            printf("From: %s\n", processingTicket->from);
            printf("To: %s\n", processingTicket->destination);
            printf("Date: %s\n", processingTicket->date);
            printf("Time: %s\n", processingTicket->time);
            printf("Distance: %d Km\n", processingTicket->distance);
            printf("Fare: ₹%d\n", processingTicket->fare);
            printf("************************************\n");
            free(processingTicket);
        }
    }

    return 0;
}