

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Booking {
    int guestID;
    char guestName[50];
    int roomNo;
    int days;
    float amount;
    int rating;
    char review[100];
};

struct Booking b[MAX];
int count = 0;


void loadData();
void saveData();
void bookRoom();
void viewBookings();
void addReview();

int main() {
    int choice;
    loadData();

    do {
        printf("\n===== HOTEL MANAGEMENT SYSTEM =====\n");
        printf("1. Book Room\n");
        printf("2. View Bookings\n");
        printf("3. Guest Review & Rating\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookRoom(); break;
            case 2: viewBookings(); break;
            case 3: addReview(); break;
            case 4: saveData(); printf("Data saved. Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}


void loadData() {
    FILE *fp = fopen("hotel.dat", "rb");
    if (fp != NULL) {
        fread(&count, sizeof(int), 1, fp);
        fread(b, sizeof(struct Booking), count, fp);
        fclose(fp);
    }
}


void saveData() {
    FILE *fp = fopen("hotel.dat", "wb");
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(b, sizeof(struct Booking), count, fp);
    fclose(fp);

void bookRoom() {
    float rate;

    b[count].guestID = 1000 + count + 1;

    printf("Enter guest name: ");
    scanf(" %[^\n]", b[count].guestName);

    printf("Enter room number: ");
    scanf("%d", &b[count].roomNo);

    printf("Enter number of days: ");
    scanf("%d", &b[count].days);

    printf("Enter room rate per day: ");
    scanf("%f", &rate);

    b[count].amount = b[count].days * rate;
    b[count].rating = 0;
    strcpy(b[count].review, "Not given");

    printf("\n--- BOOKING CONFIRMED ---\n");
    printf("Guest ID: %d\n", b[count].guestID);
    printf("Room No: %d\n", b[count].roomNo);
    printf("Total Payment: %.2f\n", b[count].amount);

    count++;
}

// View all bookings
void viewBookings() {
    if (count == 0) {
        printf("No bookings available.\n");
        return;
    }

    printf("\nID\tName\tRoom\tDays\tAmount\tRating\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%d\t%.2f\t%d\n",
               b[i].guestID,
               b[i].guestName,
               b[i].roomNo,
               b[i].days,
               b[i].amount,
               b[i].rating);
    }
}

// Add guest review and rating
void addReview() {
    int id;
    printf("Enter Guest ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (b[i].guestID == id) {
            printf("Enter rating (1 to 5): ");
            scanf("%d", &b[i].rating);

            printf("Enter review: ");
            scanf(" %[^\n]", b[i].review);

            printf("Thank you for your feedback!\n");
            return;
        }
    }
    printf("Guest ID not found!\n");
}

