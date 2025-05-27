#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ROOMS 5
#define MAX_NAME 20
#define MAX_FOOD_ITEMS 113

typedef struct {
    int number;
    char type[7];
    int charge;
    int advance;
    char customer[MAX_NAME];
    char city[MAX_NAME];
    char nationality[MAX_NAME];
    int members;
    int period;
    char available;
    int total_bill;
    int arrival_day, arrival_month, arrival_year;
} Room;

typedef struct {
    char name[30];
    int price;
} Food;

// Global data
Room rooms[MAX_ROOMS] = {
    {1, "Sup.Del", 15000, 7500, "N.A", "", "", 0, 0, 'Y', 0, 0, 0, 0},
    {2, "Deluxe", 10000, 5000, "N.A", "", "", 0, 0, 'Y', 0, 0, 0, 0},
    {3, "General", 7500 , 4000, "N.A", "", "", 0, 0, 'Y', 0, 0, 0, 0},
    {4, "Couple", 10000, 5000, "N.A", "", "", 0, 0, 'Y', 0, 0, 0, 0},
    {5, "Cpl.Del", 15000, 7500, "N.A", "", "", 0, 0, 'Y', 0, 0, 0, 0}
};

Food menu[MAX_FOOD_ITEMS] = {
    {"Chicken Koththu", 1000}, {"Biriyani", 800}, {"Rice & Curry", 900},
    // Add other food items as needed (abbreviated for brevity)
    {"Fried Rice", 1000}
};

// Function prototypes
void display_header();
void display_intro();
void display_availability();
void display_features();
void allocate_room();
void display_customer();
void restaurant();
void cancel_reservation();
void deallocate_room();

// Utility function for safe string input
void get_safe_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
}

// Validate date
int is_valid_date(int day, int month, int year) {
    if (year < 1900 || year > 9999 || month < 1 || month > 12 || day < 1) return 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) days_in_month[1] = 29;
    return day <= days_in_month[month - 1];
}

void display_header() {
    printf("\n------HOTEL Lakiya Inn-------\n");
}

void display_intro() {
    display_header();
    printf("\nNo.40/3,Near the temple, Kapuwaththa, Dambulla, Sri Lanka");
    printf("\nContact No.: 066 2565127\n");
    printf("Hotel \"Lakiya Inn\" is one of the newest hotels in Dambulla, equipped with modern amenities.\n");
    printf("Amenities:\n* 100%% Power backup\n* Automatic lift\n* Ample parking\n* 24/7 security\n");
    printf("* Running hot/cold water\n* Free internet\n* 24-hour room service\n* Laundry service\n");
    printf("\nWelcome to Hotel Lakiya Inn\n");
    printf("\nPress Enter to continue...");
    getchar();
}

void display_availability() {
    display_header();
    printf("\nROOM AVAILABILITY\n");
    printf("Room |     Type     |  Charge |  Available  |  Customer |  Period\n");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("%-4d |  %-10s  |  %-6d |  %-9c  |  %-8s |  %-6d  \n",
               rooms[i].number, rooms[i].type, rooms[i].charge,
               rooms[i].available, rooms[i].customer, rooms[i].period);
    }
    printf("\nPress Enter to continue...");
    getchar();
}

void display_features() {
    int type;
    display_header();
    printf("\nChoose room type:\n1. Super Deluxe\n2. Deluxe\n3. General\n4. Couple\n5. Couple Delux\n");
    scanf("%d", &type);
    getchar(); // Clear newline
    if (type < 1 || type > 5) {
        printf("Invalid choice! Please select 1-5.\n");
        display_features();
        return;
    }
    display_header();
    printf("\nRoom Number: %d\nAdvance: %d\n", rooms[type - 1].number, rooms[type - 1].advance);
    printf("\nFEATURES OF THIS ROOM\n");
    printf("--------------------------------\n");
    printf("Room Type: %s\nCharges: Rs.%d/day\n", rooms[type - 1].type, rooms[type - 1].charge);
    printf("Beds: %d\nCapacity: %d\n", (type == 4 || type == 5) ? 1 : 2, (type == 4 || type == 5) ? 2 : 5);
    if (type == 1) printf("Balcony: Yes\n");
    printf("\nADDITIONAL FEATURES\n");
    printf("--------------------------------\n");
    if (type == 1 || type == 2 || type == 5) printf("A/C: Yes\n");
    if (type != 3) printf("TV: Yes\n");
    printf("Geyser: Yes\n");
    printf("Note: Extra bed costs Rs.1500\n");
    printf("\nPress Enter to continue...");
    getchar();
}

void allocate_room() {
    int room_no, members, period, day, month, year;
    char name[MAX_NAME], city[MAX_NAME], nationality[MAX_NAME];
    display_header();
    display_availability();
    printf("\nEnter room number (1-5): ");
    scanf("%d", &room_no);
    getchar();
    if (room_no < 1 || room_no > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }
    if (rooms[room_no - 1].available == 'N') {
        printf("Room is not available!\n");
        return;
    }
    printf("Enter customer name: ");
    get_safe_string(name, MAX_NAME);
    printf("Enter city: ");
    get_safe_string(city, MAX_NAME);
    printf("Enter nationality: ");
    get_safe_string(nationality, MAX_NAME);
    printf("Enter number of days: ");
    scanf("%d", &period);
    printf("Enter number of members: ");
    scanf("%d", &members);
    if ((room_no == 1 || room_no == 2 || room_no == 3) && (members < 1 || members > 5)) {
        printf("Invalid number of members (1-5 allowed)!\n");
        return;
    }
    if ((room_no == 4 || room_no == 5) && (members < 1 || members > 2)) {
        printf("Invalid number of members (1-2 allowed)!\n");
        return;
    }
    printf("Enter arrival date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    getchar();
    if (!is_valid_date(day, month, year)) {
        printf("Invalid date!\n");
        return;
    }
    strcpy(rooms[room_no - 1].customer, name);
    strcpy(rooms[room_no - 1].city, city);
    strcpy(rooms[room_no - 1].nationality, nationality);
    rooms[room_no - 1].members = members;
    rooms[room_no - 1].period = period;
    rooms[room_no - 1].available = 'N';
    rooms[room_no - 1].arrival_day = day;
    rooms[room_no - 1].arrival_month = month;
    rooms[room_no - 1].arrival_year = year;
    printf("Room %d allocated to %s for %d days.\n", room_no, name, period);
    printf("Press Enter to continue...");
    getchar();
}

void display_customer() {
    int room_no;
    display_header();
    printf("\nEnter room number (1-5): ");
    scanf("%d", &room_no);
    getchar();
    if (room_no < 1 || room_no > MAX_ROOMS || strcmp(rooms[room_no - 1].customer, "N.A") == 0) {
        printf("No customer data available!\n");
        return;
    }
    printf("\nRoom Number: %d\n", rooms[room_no - 1].number);
    printf("Customer Name: %s\n", rooms[room_no - 1].customer);
    printf("Period: %d days\n", rooms[room_no - 1].period);
    printf("City: %s\n", rooms[room_no - 1].city);
    printf("Nationality: %s\n", rooms[room_no - 1].nationality);
    printf("Members: %d\n", rooms[room_no - 1].members);
    printf("Arrival Date: %d/%d/%d\n", rooms[room_no - 1].arrival_day,
           rooms[room_no - 1].arrival_month, rooms[room_no - 1].arrival_year);
    printf("\nPress Enter to continue...");
    getchar();
}

void restaurant() {
    int room_no, food_code, total = 0;
    char name[MAX_NAME], choice;
    display_header();
    printf("\nMENU CARD\n");
    printf("--------------------------------\n");
    for (int i = 0; i < 10; i++) { // Display first 10 items for brevity
        printf("%2d. %-20s Rs.%d\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("--------------------------------\n");
    do {
        printf("Enter food code (1-%d, 0 to finish): ", MAX_FOOD_ITEMS);
        scanf("%d", &food_code);
        getchar();
        if (food_code == 0) break;
        if (food_code < 1 || food_code > MAX_FOOD_ITEMS) {
            printf("Invalid food code!\n");
            continue;
        }
        total += menu[food_code - 1].price;
        printf("Added %s (Rs.%d)\n", menu[food_code - 1].name, menu[food_code - 1].price);
        printf("More items? (y/n): ");
        scanf("%c", &choice);
        getchar();
    } while (tolower(choice) == 'y');
    printf("Enter room number (1-5): ");
    scanf("%d", &room_no);
    getchar();
    if (room_no < 1 || room_no > MAX_ROOMS) {
        printf("Invalid room number!\n");
        return;
    }
    printf("Enter customer name: ");
    get_safe_string(name, MAX_NAME);
    if (strcasecmp(name, rooms[room_no - 1].customer) != 0) {
        printf("Name does not match room records!\n");
        return;
    }
    rooms[room_no - 1].total_bill += total;
    printf("\nOrder Summary:\n");
    printf("Total: Rs.%d\n", rooms[room_no - 1].total_bill);
    printf("Press Enter to continue...");
    getchar();
}

void cancel_reservation() {
    int room_no;
    char name[MAX_NAME];
    display_header();
    printf("\nEnter room number (1-5): ");
    scanf("%d", &room_no);
    getchar();
    if (room_no < 1 || room_no > MAX_ROOMS || strcmp(rooms[room_no - 1].customer, "N.A") == 0) {
        printf("Room is empty!\n");
        return;
    }
    printf("Enter customer name: ");
    get_safe_string(name, MAX_NAME);
    if (strcasecmp(name, rooms[room_no - 1].customer) != 0) {
        printf("Invalid name!\n");
        return;
    }
    printf("Reservation for room %d cancelled.\n", room_no);
    printf("Total bill (advance): Rs.%d\n", rooms[room_no - 1].advance);
    strcpy(rooms[room_no - 1].customer, "N.A");
    rooms[room_no - 1].available = 'Y';
    rooms[room_no - 1].period = 0;
    rooms[room_no - 1].members = 0;
    rooms[room_no - 1].total_bill = 0;
    printf("Press Enter to continue...");
    getchar();
}

void deallocate_room() {
    int room_no, total;
    char name[MAX_NAME];
    display_header();
    printf("\nEnter room number (1-5): ");
    scanf("%d", &room_no);
    getchar();
    if (room_no < 1 || room_no > MAX_ROOMS || strcmp(rooms[room_no - 1].customer, "N.A") == 0) {
        printf("Room is empty!\n");
        return;
    }
    printf("Enter customer name: ");
    get_safe_string(name, MAX_NAME);
    if (strcasecmp(name, rooms[room_no - 1].customer) != 0) {
        printf("Invalid name!\n");
        return;
    }
    total = (rooms[room_no - 1].period * rooms[room_no - 1].charge) - rooms[room_no - 1].advance + rooms[room_no - 1].total_bill;
    printf("Room %d deallocated.\n", room_no);
    printf("Total bill: Rs.%d\n", total);
    strcpy(rooms[room_no - 1].customer, "N.A");
    rooms[room_no - 1].available = 'Y';
    rooms[room_no - 1].period = 0;
    rooms[room_no - 1].members = 0;
    rooms[room_no - 1].total_bill = 0;
    printf("Thanks for staying!\n");
    printf("Press Enter to continue...");
    getchar();
}

int main() {
    char choice;
    int option;
    display_intro();
    do {
        printf("\nMENU:\n1. Room Availability\n2. Room Features\n3. Room Allocation\n");
        printf("4. Customer Details\n5. Restaurant\n6. Cancel Reservation\n");
        printf("7. Room Deallocation\n8. Exit\n");
        printf("Enter choice (1-8): ");
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1: display_availability(); break;
            case 2: display_features(); break;
            case 3: allocate_room(); break;
            case 4: display_customer(); break;
            case 5: restaurant(); break;
            case 6: cancel_reservation(); break;
            case 7: deallocate_room(); break;
            case 8: exit(0);
            default: printf("Invalid choice! Choose 1-8.\n");
        }
        printf("\nContinue? (y/n): ");
        scanf("%c", &choice);
        getchar();
    } while (tolower(choice) == 'y');
    return 0;
}
