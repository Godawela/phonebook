#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 20
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_PHONEBOOK_ENTRIES 100
#define PHONEBOOK_FILE "phonebook.txt"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
} PhonebookEntry;

void login();
void addPhoneNumber();
void listPhoneNumbers();
void deletePhoneNumber();
void savePhonebookToFile();
void loadPhonebookFromFile();
void interface();

PhonebookEntry phonebook[MAX_PHONEBOOK_ENTRIES];
int phonebookSize = 0;
char password[MAX_PASSWORD_LENGTH] = "1234";
char p;

int main() {
    interface();
    login();
    loadPhonebookFromFile();

    int choice;
    do {
        system("color DF");
        system("cls");
        printf("\nPhonebook Menu\n");
        printf("1. Add Phone Number\n");
        printf("2. List Phone Numbers\n");
        printf("3. Delete Phone Number\n");
        printf("4. Exit and save the numbers in the text file\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPhoneNumber();
                break;
            case 2:
                listPhoneNumbers();
                break;
            case 3:
                deletePhoneNumber();
                break;
            case 4:
                savePhonebookToFile();
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                system("pause");
                break;
        }
    } while (choice != 4);

    return 0;
}
void interface()
{
	system("color 5F");
	printf("\n\n\n\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~\n\n");
	printf("\t\t\t\t\tWELCOME TO the Phone Book APP \n\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~~~~~~~~~~~~~~~"
		"~~~~~~~~~~\n");


	// Pausing screen until user
	// presses any key
	system("pause");
}

void login() {
    system("cls");
    char enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter the password: ");
    scanf("%s", enteredPassword);

    int count=0;
    for(int i=0;i<=2;i++){
        while (strcmp(enteredPassword, password) != 0) {
            printf("Incorrect password.\nPlease try again: \n");
            scanf("%s", enteredPassword);
        }
        count++;
    }

    if(count==2){
        printf("Did you forget your password?\n");
        printf("Enter 'y' or 'n'");
        scanf("%c",&p);
    }
/*
    if(p=='y'){
        printf("Enter your NIC for the verification: ");
        scanf("%d",&enternic);

        if(nic==enternic){
            printf("Enter a new password");

        }
    }
*/
    printf("Password accepted. Access granted.\n");
    printf("\n\n\n");
	system("pause");
}

void addPhoneNumber() {
    system("cls");
    if (phonebookSize >= MAX_PHONEBOOK_ENTRIES) {
        printf("Phonebook is full. Cannot add more entries.\n");
        return;
    }

    PhonebookEntry entry;

    printf("Enter the ID number: ");
    scanf("%d", &entry.id);

    printf("Enter the name: ");
    scanf(" %[^\n]s", entry.name);

    printf("Enter the phone number: ");
    scanf(" %[^\n]s", entry.phoneNumber);

    phonebook[phonebookSize++] = entry;

    printf("Phone number added successfully.\n");
    printf("\n\n\n");
	system("pause");
}

void listPhoneNumbers() {
    system("cls");
    if (phonebookSize == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    printf("Phonebook Entries:\n");
    printf("ID\tName\t\tPhone Number\n");

    for (int i = 0; i < phonebookSize; i++) {
        PhonebookEntry entry = phonebook[i];
        printf("%d\t%s\t\t%s\n", entry.id, entry.name, entry.phoneNumber);
    }
    printf("\n\n\n");
	system("pause");
}

void deletePhoneNumber() {
    system("cls");
    if (phonebookSize == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    int idToDelete;
    printf("Enter the ID number of the phone number to delete: ");
    scanf("%d", &idToDelete);

    int indexToDelete = -1;

    for (int i = 0; i < phonebookSize; i++) {
        if (phonebook[i].id == idToDelete) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        printf("Phone number with ID %d not found.\n", idToDelete);
        return;
    }

    for (int i = indexToDelete; i < phonebookSize - 1; i++) {
        phonebook[i] = phonebook[i + 1];
    }

    phonebookSize--;

    printf("Phone number with ID %d deleted successfully.\n", idToDelete);
    printf("\n\n\n");
	system("pause");
}

void savePhonebookToFile() {
    system("cls");
    FILE *file = fopen(PHONEBOOK_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");

        printf("\n\n\n");
        system("pause");
        return;
    }
    else{
        for (int i = 0; i < phonebookSize; i++) {
            PhonebookEntry entry = phonebook[i];
            fprintf(file, "ID: %d  Name: %s  Number: %s\n", entry.id, entry.name, entry.phoneNumber);
        }

        fclose(file);
        printf("Phonebook saved to file.\n");
        printf("\n\n\n");
	    system("pause");
    }
}

void loadPhonebookFromFile() {
    system("cls");
    FILE *file = fopen(PHONEBOOK_FILE, "r");
    if (file == NULL) {
        printf("No phonebook file found.\n");

        printf("\n\n\n");
        system("pause");
        return;
    }
    else{
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            PhonebookEntry entry;
            sscanf(line, "ID: %d Name: %s Number: %s", &entry.id, entry.name, entry.phoneNumber);
            phonebook[phonebookSize++] = entry;
        }

        fclose(file);
        printf("Phonebook loaded from file.\n");
        printf("\n\n\n");
	    system("pause");
    }
}
