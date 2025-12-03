#include <stdio.h> //for input output fncs printf, scanf, fopen...
#include <stdlib.h> //for memory related fncs
#include <string.h> //for strings 
#include <time.h> //for current date and time

struct Journal {
    char datetime[50]; //stores current date and time 
    char text[500]; //stores the journal entry
};

//some functions that are defined below
void addEntry();
void viewEntries();
void deleteEntry();


void addEntry() {
    struct Journal j;
    FILE *fp = fopen("journal.dat", "ab"); //opens the file in append binary mode, ab writes new entry without overwriting 
    if(fp == NULL)
    {
        printf("File error.\n");
        return;
    }
    time_t now; // time_t is a data type used by c to store calendar time
    time(&now); //gets current time time() gets filled by now time
    strcpy/*copies the datetime string into structure's datetime*/(j.datetime, ctime(&now)/*converts in readable*/);

    printf("Write your journal entry:\n");
    fgets(j.text/*destination*/, sizeof(j.text)/*ensures no buffer overflow*/, stdin/*standard input*/);
    fwrite(&j/*address of structure*/, sizeof(struct Journal)/*size of one entry*/, 1/*wirte the struc*/, fp);

    fclose(fp);
    printf("Entry added successfully!\n");
}

void viewEntries() {
    struct Journal j;
    FILE *fp = fopen("journal.dat", "rb");//read binary mode  
    if(fp == NULL) {
        printf("No entries found.\n");
        return;
    }

    printf("\n------ YOUR ENTRIES ------\n");

    int count = 1;

    while(fread(&j, sizeof(struct Journal), 1, fp)) {
        printf("\n%d.\n", count);
        printf("Time: %s", j.datetime);
        printf("Entry: %s\n", j.text);
        count++;
    }

    fclose(fp);
}

void deleteEntry() {
    struct Journal j;
    FILE *fp = fopen("journal.dat"/*file to open*/, "rb");
    if (!fp/*file doesnot exsists*/) {
        printf("No entries to delete.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb"/*opens file in binary formate for writing */);
    int del, count = 1;

    printf("Enter entry number to delete: ");
    scanf("%d", &del);
    getchar();

    while (fread(&j, sizeof(struct Journal), 1, fp)) {
        if (count != del)
            fwrite(&j, sizeof(struct Journal), 1, temp);
        count++;
    }

    fclose(fp);
    fclose(temp);

    remove("journal.dat");
    rename("temp.dat", "journal.dat");

    printf("Entry deleted successfully!\n");
}

int main() {
    int choice;

    while(1) {
        printf("\n------ DIGITAL JOURNAL ------\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Delete entry\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addEntry(); break;
            case 2: viewEntries(); break;
            case 3: deleteEntry(); break;
            case 4: 
                printf("Goodbye! Take care of your thoughts <3\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
