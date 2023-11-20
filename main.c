#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define structures for bus schedule and booking
typedef struct {
    int bus_id;
    char source[50];
    char destination[50];
    char departure_time[10];
    int available_seats;
} BusSchedule;

typedef struct {
    int booking_id;
    int bus_id;
    char customer_name[50];
    int seats_booked;
} Booking;

int loggedIn = 0; // Variable to track employee login status

// Function to display a menu and return the user's choice
int menu() {
    int choice;
    printf("\n-----* Bus Booking System *------\n");
    printf("|1. Employee Login                 |\n");
    printf("|2. Bus Information Management     |\n");
    printf("|3. Booking Management             |\n");
    printf("|4. Booking History                |\n");
    printf("|5. Exit                           |\n");
    printf("|__________________________________|\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to add a new bus schedule
void addBusSchedule(BusSchedule* schedules, int* schedule_count) {
    if (*schedule_count < 100) {
        BusSchedule newSchedule;
        newSchedule.bus_id = *schedule_count + 1;
        printf("-----------------------------------\n");
        printf("|Enter bus id:                     |\n");
        scanf("%d", &newSchedule.bus_id);
        printf("|Enter source:                     |\n");
        scanf("%s", newSchedule.source);
        printf("|Enter destination:                |\n");
        scanf("%s", newSchedule.destination);
        printf("|Enter departure time:             |\n");
        scanf("%s", newSchedule.departure_time);
        printf("|Enter available seats:            |\n");
        scanf("%d", &newSchedule.available_seats);
        printf("|__________________________________|\n");

        schedules[*schedule_count] = newSchedule;
        (*schedule_count)++;

        printf("Bus schedule added successfully!\n");
    } else {
        printf("Maximum schedule limit reached. Cannot add more schedules.\n");
    }
}

// Function to delete a bus schedule
void deleteBusSchedule(BusSchedule* schedules, int* schedule_count) {
    int busIdToDelete;
    printf(" ----------------------------\n");
    printf("|Enter the Bus ID to delete: |\n");
    scanf("%d", &busIdToDelete);
    printf("|____________________________|\n");

    int found = 0;
    for (int i = 0; i < *schedule_count; i++) {
        if (schedules[i].bus_id == busIdToDelete) {
            // Move all schedules after the deleted schedule up one index to maintain continuity
            for (int j = i; j < (*schedule_count - 1); j++) {
                schedules[j] = schedules[j + 1];
            }
            (*schedule_count)--;
            found = 1;
            break;
        }
    }

    if (found) {
       printf(" ----------------------------------------------\n");
        printf("|Bus schedule with Bus ID %d has been deleted.|\n", busIdToDelete);
        printf("|_____________________________________________|\n");
    } else {
        printf(" -------------------------------------\n");
        printf("|Bus schedule with Bus ID %d not found.|\n", busIdToDelete);
        printf("|______________________________________|\n");
    }
}

// Function to search for buses
void searchBuses(BusSchedule* schedules, int schedule_count) {
    char source[50];
    char destination[50];
    printf(" ---------------------\n");
    printf("|Enter source:        |\n");
    scanf("%s", source);
    printf("|Enter destination:   |\n");
    scanf("%s", destination);
    printf("|_____________________|\n");

    printf("Matching Bus Schedules:\n");
    printf("Bus ID | Source | Destination | Departure Time | Available Seats\n");

    for (int i = 0; i < schedule_count; i++) {
        if (strcmp(schedules[i].source, source) == 0 && strcmp(schedules[i].destination, destination) == 0) {
    printf("%6d    | %-6s   | %-11s       | %-13s           | %d\n", schedules[i].bus_id, schedules[i].source, schedules[i].destination, schedules[i].departure_time, schedules[i].available_seats);
        }
    }
}

// Function to book seats
void bookSeats(BusSchedule* schedules, int schedule_count, Booking* bookings, int* booking_count) {
    int busId, seatsToBook;
    char customerName[50];
    printf(" -----------------------------------\n");
    printf("|Enter your name:                   |\n");
    scanf("%s", customerName);
    printf("|Enter the Bus ID you want to book: |\n");
    scanf("%d", &busId);
    printf("|___________________________________|\n");
    int found = 0;
    for (int i = 0; i < schedule_count; i++) {
        if (schedules[i].bus_id == busId) {
             printf(" --------------------\n");
            printf("|Bus schedule found:  |\n");
            printf("|Bus ID: %d           |\n", schedules[i].bus_id);
            printf("|Source: %s           |\n", schedules[i].source);
            printf("|Destination: %s      |\n", schedules[i].destination);
            printf("|Departure Time: %s   |\n", schedules[i].departure_time);
            printf("|Available Seats: %d  |\n", schedules[i].available_seats);
            printf("|_____________________|\n");

            printf("Enter the number of seats you want to book: ");
            scanf("%d", &seatsToBook);

            if (seatsToBook <= schedules[i].available_seats) {
                // Update available seats in the schedule
                schedules[i].available_seats -= seatsToBook;

                // Record the booking
                Booking newBooking;
                newBooking.booking_id = (*booking_count) + 1;
                newBooking.bus_id = busId;
                strcpy(newBooking.customer_name, customerName);
                newBooking.seats_booked = seatsToBook;

                bookings[(*booking_count)] = newBooking;
                (*booking_count)++;
                printf("---------------------------------------\n");
                printf("|%d seat(s) booked for %s on Bus ID %d.|\n", seatsToBook, customerName, busId);
                printf("|______________________________________|\n");
            } else {
                printf("---------------------------------------------\n");
                printf("|Not enough available seats for your request.|\n");
                printf("|____________________________________________|\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("---------------------------------------\n");
        printf("|Bus schedule with Bus ID %d not found.|\n", busId);
        printf("|______________________________________|\n");
    }
}

// Function to cancel a booking
void cancelBooking(Booking* bookings, int* booking_count, BusSchedule* schedules, int schedule_count) {
    int bookingId;
    char customerName[50];

    printf("Enter your name: ");
    scanf("%s", customerName);
    printf("Enter the Booking ID you want to cancel: ");
    scanf("%d", &bookingId);

    int bookingIndex = -1;

    // Find the booking based on the provided Booking ID and customer name
    for (int i = 0; i < *booking_count; i++) {
        if (bookings[i].booking_id == bookingId && strcmp(bookings[i].customer_name, customerName) == 0) {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1) {
        printf("-------------------------------------------------------------\n");
        printf("|Booking with Booking ID %d and customer name '%s' not found.|\n", bookingId, customerName);
        printf("|____________________________________________________________|\n");
        return;
    }

    // Retrieve the bus ID and seats booked from the booking
    int busId = bookings[bookingIndex].bus_id;
    int seatsBooked = bookings[bookingIndex].seats_booked;

    // Find the corresponding bus schedule
    int scheduleIndex = -1;

    for (int i = 0; i < schedule_count; i++) {
        if (schedules[i].bus_id == busId) {
            scheduleIndex = i;
            break;
        }
    }

    if (scheduleIndex == -1) {
        printf("--------------------------------------\n");
        printf("|Bus schedule for Bus ID %d not found.|\n", busId);
        printf("|_____________________________________|\n");
        return;
    }

    // Restore the available seats in the schedule
    schedules[scheduleIndex].available_seats += seatsBooked;

    // Remove the canceled booking
    for (int i = bookingIndex; i < *booking_count - 1; i++) {
        bookings[i] = bookings[i + 1];
    }
    (*booking_count)--;
    printf("---------------------------------------------------------------------\n");
    printf("|Booking with Booking ID %d and customer name '%s' has been canceled.|\n", bookingId, customerName);
    printf("|____________________________________________________________________|\n");
}

// Function to view booking history
void viewBookingHistory(Booking* bookings, int booking_count, BusSchedule* schedules, int schedule_count) {
    if (booking_count == 0) {
        printf("---------------------------------\n");
        printf("|No booking history available.   |\n");
        printf("|________________________________|\n");
        return;
    }

    printf("----------------Booking History---------------------\n");
    printf("|Booking ID | Bus ID | Customer Name | Seats Booked |\n");
    printf("|___________|________|_______________|______________|\n");


    for (int i = 0; i < booking_count; i++) {
    printf("|%10d       | %6d    | %-13s         | %d           |\n", bookings[i].booking_id, bookings[i].bus_id, bookings[i].customer_name, bookings[i].seats_booked);
    printf("|___________|________|_______________|______________|\n");


    }
}
// Function to view all bus schedules
void viewAllBusSchedules(BusSchedule* schedules, int schedule_count) {
    if (schedule_count == 0) {
        printf("-----------------------------------\n");
        printf("|SORRY!No bus schedules available. |\n");
        printf("|__________________________________|\n");
    } else {
        printf("-------------------All Bus Schedules------------------------------\n");
        printf("|Bus ID | Source | Destination | Departure Time | Available Seats |\n");
        printf("|_______|________|_____________|________________|_________________|\n");
        for (int i = 0; i < schedule_count; i++) {
        printf("|%6d    | %-6s   | %-11s       | %-13s          | %d              |\n", schedules[i].bus_id, schedules[i].source, schedules[i].departure_time, schedules[i].available_seats);
        printf("|_______|________|_____________|________________|_________________|\n");
        }

    }
}


// Function for employee login

int employeeLogin() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, "Maxwell") == 0 && strcmp(password, "Scout") == 0) {

        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}


int main() {
    BusSchedule schedules[100];
    int schedule_count = 0;
    Booking bookings[100];
    int booking_count = 0;
    int loggedIn = 0;

    int choice;
    do {
        choice = menu();
        switch (choice) {
            case 1:
                loggedIn = employeeLogin();
                if (loggedIn) {
                    printf(" -------------------------------------------\n");
                    printf("|Employee login successful. Access granted. |\n");
                    printf("|___________________________________________|\n");
                } else {
                    printf(" ----------------------------------------\n");
                    printf("|Employee login failed. Access denied.   |\n");
                    printf("|________________________________________|\n");
                }
                break;
            case 2:
                if (loggedIn) {
                    int subChoice;
                    printf("\n----Bus Information Management-------\n");
                    printf("|1. Add new bus schedule               |\n");
                    printf("|2. Delete bus schedule                |\n");
                    printf("|3. View all bus schedules             |\n");
                    printf("|______________________________________|\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    switch (subChoice) {
                        case 1:
                            addBusSchedule(schedules, &schedule_count);
                            break;
                        case 2:
                            deleteBusSchedule(schedules, &schedule_count);
                            break;
                        case 3:
                              viewAllBusSchedules(schedules, schedule_count);
                            break;
                        default:
                printf(" ----------------------------------------------\n");
                printf("|Invalid choice for bus information management.|\n");
                printf("|______________________________________________|\n");
                    }
                } else {
                    printf(" -------------------------------------------------\n");
                    printf("|Access denied. Please login as an employee first.|\n");
                    printf("|_________________________________________________|\n");
                }
                break;
            case 3:
                if (loggedIn) {
                    int subChoice;

                  printf("\n-----Booking Management------\n");
                    printf("|1. Search for buses         |\n");
                    printf("|2. Book seats               |\n");
                    printf("|3. Cancel booking           |\n");
                    printf("|____________________________|\n");
                    printf("Enter your choice:");
                    scanf("%d", &subChoice);

                    switch (subChoice) {
                        case 1:
                            searchBuses(schedules, schedule_count);
                            break;
                        case 2:
                            bookSeats(schedules, schedule_count, bookings, &booking_count);
                            break;
                        case 3:
                            cancelBooking(bookings, &booking_count, schedules, schedule_count);
                            break;
                        default:
                printf(" --------------------------------------\n");
                printf("|Invalid choice for booking management.|\n");
                printf("|______________________________________|\n");
                    }
                } else {
                    printf(" -------------------------------------------------\n");
                    printf("|Access denied. Please login as an employee first.|\n");
                    printf("|_________________________________________________|\n");
                }
                break;
            case 4:
                if (loggedIn) {
                    viewBookingHistory(bookings, booking_count, schedules, schedule_count);
                } else {
                    printf(" -------------------------------------------------\n");
                    printf("|Access denied. Please login as an employee first.|\n");
                    printf("|_________________________________________________|\n");
                }
                break;
            case 5:
                printf(" ---------------------------------\n");
                printf("|Exiting the system.              |\n");
                printf("|_________________________________|\n");
                break;
            default:
                printf(" ---------------------------------\n");
                printf("|Invalid choice. Please try again.|\n");
                printf("|_________________________________|\n");

        }
    } while (choice != 5);

    return 0;
}

