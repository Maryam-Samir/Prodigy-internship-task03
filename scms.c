#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define FILENAME "contacts.txt"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

Contact contacts[MAX_CONTACTS];
int num_contacts = 0;

void load_contacts() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        return;
    }

    num_contacts = 0;
    while (fscanf(fp, "%49s %19s %49s", contacts[num_contacts].name, contacts[num_contacts].phone, contacts[num_contacts].email) == 3) {
        num_contacts++;
        if (num_contacts >= MAX_CONTACTS) {
            break;
        }
    }

    fclose(fp);
}

void save_contacts() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error saving contacts.\n");
        return;
    }

    for (int i = 0; i < num_contacts; i++) {
        fprintf(fp, "%s %s %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved successfully.\n");
}

void add_contact() {
    if (num_contacts >= MAX_CONTACTS) {
        printf("Maximum number of contacts reached.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", contacts[num_contacts].name);
    printf("Enter phone number: ");
    scanf("%s", contacts[num_contacts].phone);
    printf("Enter email address: ");
    scanf("%s", contacts[num_contacts].email);
    num_contacts++;
    save_contacts();
    printf("Contact added successfully.\n");
}

void view_contacts() {
    if (num_contacts == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("Contact List:\n");
    for (int i = 0; i < num_contacts; i++) {
        printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void edit_contact() {
    int index;
    printf("Enter the index of the contact to edit: ");
    scanf("%d", &index);
    if (index < 1 || index > num_contacts) {
        printf("Invalid index.\n");
        return;
    }

    index--;
    printf("Current information:\nName: %s, Phone: %s, Email: %s\n", contacts[index].name, contacts[index].phone, contacts[index].email);

    printf("Enter new name: ");
    scanf("%s", contacts[index].name);
    printf("Enter new phone number: ");
    scanf("%s", contacts[index].phone);
    printf("Enter new email address: ");
    scanf("%s", contacts[index].email);
    save_contacts();
    printf("Contact updated successfully.\n");
}

void delete_contact() {
    int index;
    printf("Enter the index of the contact to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > num_contacts) {
        printf("Invalid index.\n");
        return;
    }

    index--;
    for (int i = index; i < num_contacts - 1; i++) {
        strcpy(contacts[i].name, contacts[i + 1].name);
        strcpy(contacts[i].phone, contacts[i + 1].phone);
        strcpy(contacts[i].email, contacts[i + 1].email);
    }
    num_contacts--;
    save_contacts();
    printf("Contact deleted successfully.\n");
}

int main() {
    load_contacts();
    int choice;
    while (1) {
        printf("\nContact Management System:\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                view_contacts();
                break;
            case 3:
                edit_contact();
                break;
            case 4:
                delete_contact();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}