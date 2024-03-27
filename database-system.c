#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// Global Variable
FILE *pFile;

// Function prototypes
void addProfile();
void profileRecords();
void findProfile();
void deleteProfile();

typedef struct{
    char firstName[30];
    char lastName[30];
    int age;
    char sex[20];
} information;

void addProfile(){
    information profile;
    char another;
    do {
        system("cls");
        printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t|\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\t\t                             |\n");
        printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t    ADDING NEW PROFILE\t\t                             \n");
        pFile = fopen("database.txt", "a");
        printf("\t\t\t\tENTER FIRST NAME\t: ");
        scanf("%29s", profile.firstName);
        printf("\t\t\t\tENTER LAST NAME\t\t: ");
        scanf("%29s", profile.lastName);
        printf("\t\t\t\tENTER AGE\t\t: ");
        scanf("%d", &profile.age);
        printf("\t\t\t\tENTER SEX\t\t: ");
        scanf("%s", profile.sex);

        if(pFile == NULL){
            fprintf(stderr, "\t\t\t\t\t\t\t\t\t    CAN'T OPEN FILE\t\t                             \n");
        } else {
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t| NAME\t: %s %s\t\t\t\t\t\t\t\t                             |\n", profile.firstName, profile.lastName);
            printf("\t\t\t\t| AGE\t: %d\t\t\t\t\t\t\t\t\t                             |\n", profile.age);
            printf("\t\t\t\t| SEX\t: %s\t\t\t\t\t\t\t\t\t                             |\n", profile.sex);
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");

            printf("\t\t\t\t SAVE? (Y/N): ");
            getchar();

            if(getchar() == 'y' || getchar() == 'Y'){
                printf("\t\t\t\tINFORMATION STORED SUCCESSFULLY.\n");
                fwrite(&profile, sizeof(information), 1, pFile);
            }
            fclose(pFile);
        }
        printf("\t\t\t\tADD ANOTHER PROFILE? (Y/N): ");
        scanf(" %c", &another);
    } while(another == 'y' || another == 'Y');
}

void profileRecords(){
    system("cls");
    information profile;
    pFile = fopen("database.txt", "r");
    // Header
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t|\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\t\t                             |\n");
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t    PROFILE RECORDS\t\t                             \n");

    if(pFile == NULL){
            fprintf(stderr, "\t\t\t\t\t\t\t\t\t    CAN'T OPEN FILE\t\t                             \n");
    }

    while(fread(&profile, sizeof(information), 1, pFile)){
        printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t NAME\t: %s %s \t\t\t\t\t\t\t\t                             \n", profile.firstName, profile.lastName);
        printf("\t\t\t\t AGE\t: %d \t\t\t\t\t\t\t\t\t                             \n", profile.age);
        printf("\t\t\t\t SEX\t: %s \t\t\t\t\t\t\t\t\t                             \n", profile.sex);
    }
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    fclose(pFile);
    getch();
}

void findProfile(){
    system("cls");
    char lastName[30];

    information profile;
    pFile = fopen("database.txt", "r");
    // Header
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t|\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\t\t                             |\n");
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t    SEARCH PROFILE\t\t                             \n");
    printf("\t\t\t\t ENTER LAST NAME: ");
    scanf("%s", &lastName);

    if(pFile == NULL){
            fprintf(stderr, "\t\t\t\t\t\t\t\t\t    CAN'T OPEN FILE\t\t                             \n");
    }
    while (fread(&profile, sizeof(information), 1, pFile)) {
        if (strcmp(profile.lastName, lastName) == 0) {
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t NAME\t: %s %s \t\t\t\t\t\t\t\t                             \n", profile.firstName, profile.lastName);
            printf("\t\t\t\t AGE\t: %d \t\t\t\t\t\t\t\t\t                             \n", profile.age);
            printf("\t\t\t\t SEX\t: %s \t\t\t\t\t\t\t\t\t                             \n", profile.sex);
        }
    }
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    fclose(pFile);
    getch();
}

void deleteProfile(){
    system("cls");

    char firstName[30];
    char lastName[30];
    FILE *pFile, *pFile1;

    information profile;
    pFile = fopen("database.txt", "r");
    pFile1 = fopen("temp.txt", "w"); // Open temporary file for writing

    // Header
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t|\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\t\t                             |\n");
    printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t\t    DELETE PROFILE\t\t                             \n");
    printf("\t\t\t\t ENTER FIRST NAME: ");
    scanf("%s", firstName);
    printf("\t\t\t\t ENTER LAST NAME: ");
    scanf("%s", lastName);

    if (pFile == NULL || pFile1 == NULL) {
        fprintf(stderr, "\t\t\t\t\t\t\t\t\t    CAN'T OPEN FILE\t\t                             \n");
        return;
    }

    int profileDeleted = 0; // Flag to track if profile has been deleted

    while (fread(&profile, sizeof(information), 1, pFile)) {
        if (strcmp(profile.firstName, firstName) == 0 && strcmp(profile.lastName, lastName) == 0) {
            profileDeleted = 1; // Set flag indicating profile is deleted
            printf("\t\t\t\t\t\t\t\t    PROFILE DELETED SUCCESSFULLY\t\t                             \n");
        } else {
            fwrite(&profile, sizeof(information), 1, pFile1); // Write profiles other than the one to be deleted to the temporary file
        }
    }

    fclose(pFile);
    fclose(pFile1);

    if (profileDeleted) {
        remove("database.txt"); // Remove original file
        rename("temp.txt", "database.txt"); // Rename temporary file to original file
    } else {
        printf("\t\t\t\t\t\t\t\t    PROFILE NOT FOUND\t\t                             \n");
        remove("temp.txt"); // If profile is not found, remove the temporary file
    }

    printf("\t\t\t\t DELETE ANOTHER PROFILE? (Y/N): ");
    getchar();

    if(getchar() == 'y' || getchar() == 'Y'){
        deleteProfile();
    }
}

void exitSystem(){
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t    THANK YOU FOR USING THE SYSTEM!\t\t                             \n");
    printf("\n\n\n\n");
    exit(0);
}

int main(){
    int choice;
    int loop = 1;
    while(loop == 1){
        do{
            // HEADER DESIGN
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t|\t\t\t\t\tDATABASE MANAGEMENT SYSTEM\t\t                             |\n");
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");
            // Options
            printf("\t\t\t\t| 1. ADD NEW PROFILE\t\t\t\t\t\t\t\t                             |\n");
            printf("\t\t\t\t| 2. PROFILE RECORDS\t\t\t\t\t\t\t\t                             |\n");
            printf("\t\t\t\t| 3. FIND PROFILE\t\t\t\t\t\t\t\t                             |\n");
            printf("\t\t\t\t| 4. DELETE PROFILE\t\t\t\t\t\t\t\t                             |\n");
            printf("\t\t\t\t| 5. EXIT PROGRAM\t\t\t\t\t\t\t\t                             |\n");
            printf("\t\t\t\t--------------------------------------------------------------------------------------------------------------\n");


            printf("\t\t\t\t ENTER CHOICE: ");
            scanf("%d", &choice);
            if (choice <= 0 || choice >= 6) {
                system("cls");
                printf("\t\t\t\tInvalid Choice.\n");
            }

        } while (choice <= 0 || choice >= 6);

        switch(choice){
            case 1:
                addProfile();
                system("cls");
                break;
            case 2:
                profileRecords();
                system("cls");
                break;
            case 3:
                findProfile();
                system("cls");
                break;
            case 4:
                deleteProfile();
                system("cls");
                break;
            case 5:
                exitSystem();
                loop = 0;
                break;
        }

    }
}
