#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#include <ctype.h>
#include <limits.h>


struct student{
    int roll;
    char name[20];
    int class;
    char f_name[20];
    char g_num[20];
    char m_name[20];
    int age;
    char gender[20];
    char pre_address[20];
    char per_address[20];
    char pass[100];

    char payble_amount[8];
    char m_Percent[8];
    char payment_info[8];
}s;

typedef struct {
    int id;
    char name[50];
    char designation[50];
    char subject[50];
    char phone[15];
    char email[50];
    char address[100];
    char qualification[50];
    char joining_date[11];
} Teacher;


struct admin{
    char pass[100];
    char pass2[100];
    char c1[8], c2[8], c3[8], c4[8], c5[8];
    char c6[8], c7[8], c8[8], c9[8], c10[8];
}a;

struct NoticeEvent {
    char title[100];
    char description[500];
    char date[20];
    char type[10];
} ne;

struct member{
    int id;
    int roll;
    char name[20];
    int age;
    int class;
    char g_num[20];
    char t1[100],t2[100],t3[100],t4[100],t5[100];
    char a1[40],a2[40],a3[40],a4[40],a5[40];
    char d1[20], d2[20], d3[20], d4[20], d5[20];
    int c1,c2,c3,c4,c5;
}m;

struct book{
    int code;
    char title[100];
    char author[40];
    int amount;
}b;

FILE *file;
FILE *libf;
FILE *adminf;
FILE *bookf;



int int_input() {

    char str[100];
    int num = -1;

    if (fgets(str, sizeof(str), stdin) == NULL) {
        return -1; // Handle input error
    }
    str[strcspn(str, "\n")] = '\0';
    if (str[0] == '\0') {
        return -1;
    }
    int i = 0;
    if (str[i] == '-') {
        i++;
    }
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return -1;
        }
    }
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return -1;
    }
    num = (int)val;
    return num;
}


//====================================================================================== Student Portal ==========================================================================================================================


void student_Portal() {
    start:
    system("cls");
    printf("\t\t\t\t~Student Portal~\n\n\n");

    int class_num, roll;
    char pass[60];

    // Class input with back option
    class_input:
    printf("\nEnter Class (1-10): ");
    class_num=int_input();
    if(class_num < 1 || class_num > 10) {
        printf("\n\nInvalid class! Please enter between 1-10.\n\n");

        back_option_class:
        printf("1. Try Again\n");
        printf("2. Back to Main Menu\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto class_input;
        else if(opt == '2') return;
        else {

            printf("\n\nInvalid choice!\n");

            goto back_option_class;
        }
    }


    // Roll number input with back option
    roll_input:
    printf("\nEnter Roll Number: ");

    roll=int_input();
    if(roll<1) {
        printf("\n\nInvalid roll number! Please enter numbers only.\n\n");

        back_option_roll:
        printf("1. Try Again\n");
        printf("2. Back to Class Input\n");
        printf("3. Back to Main Menu\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto roll_input;
        else if(opt == '2') {
            goto class_input;
        }
        else if(opt == '3') return;
        else {
            printf("\nInvalid choice!\n");
            goto back_option_roll;
        }
    }


    // Open student file
    file = fopen("student.txt", "rb");
    if(file == NULL) {
        printf("\nError opening student database!\n");
        fclose(file);
        file=fopen("student.txt","wb");
        fclose(file);
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        goto start;
    }

    // Search for student
    int found = 0;
    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(class_num == s.class && roll == s.roll) {
            found = 1;

            // Password attempt
            password_input:
            printf("Enter Password: ");
            fgets(pass, sizeof(pass), stdin);
            pass[strcspn(pass, "\n")] = '\0';

            if(strcmp(pass, s.pass) == 0) {  // Correct password check
                fclose(file);
                system("cls");
                printf("\n\n\t\t\t\tLogin Successful!\n\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                Portal_page(pass, roll,class_num);
                return;
            }
            else {
                system("cls");
                printf("\t\t\t\t~Student Portal~\n\n\n");
                printf("Class: %d | Roll: %d\n", class_num, roll);
                printf("\n\n\t\t\t\tWrong Password!\n\n");

                back_option_pass:
                printf("1. Try Again\n");
                printf("2. Back to Roll Input\n");
                printf("3. Back to Class Input\n");
                printf("4. Back to Main Menu\n\n");
                printf("Enter Choice: ");

                char opt = getch();
                if(opt == '1') {
                    system("cls");
                    printf("\t\t\t\t~Student Portal~\n\n\n");
                    printf("Class: %d | Roll: %d\n", class_num, roll);
                    goto password_input;
                }
                else if(opt == '2') {
                    fclose(file);
                    system("cls");
                    goto roll_input;
                }
                else if(opt == '3') {
                    fclose(file);
                    system("cls");
                    goto class_input;
                }
                else if(opt == '4') {
                    fclose(file);
                    return;
                }
                else {
                    printf("\nInvalid choice!\n");
                    goto back_option_pass;
                }
            }
        }
    }

    if(!found) {
        int count=0;
        back_option_notfound:

        system("cls");
        printf("\n\nStudent with Class %d and Roll %d not found!\n\n", class_num, roll);
        fclose(file);

        printf("1. Try Again\n");
        printf("2. Back to Class Input\n");
        printf("3. Back to Main Menu\n\n");
        if(count==1) printf("\n\nPlease Press 1-3\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto start;
        else if(opt == '2') goto class_input;
        else if(opt == '3') return;
        else {
            printf("\nInvalid choice!\n");
            count=1;
            goto back_option_notfound;
        }
    }
}



void Portal_page(char pass[100], int i, int class) {                                        // Student portal Page
    start:
    system("cls");

    file = fopen("student.txt", "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }


    int found = 0;
    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(i == s.roll && class == s.class) {
            found = 1;
            printf("\t\t\t\t~Your Student Portal~\n\n\n");
            printf("ID                    : %d\n", s.roll);
            printf("Name                  : %s\n", s.name);
            printf("Class                 : %d\n", s.class);
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Student not found!\n");
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        student_Portal();
        return;
    }


    printf("\n\n\n\n1. Student Information \n");
    printf("2. Notice / Event \n");
    printf("3. Library Info \n");
    printf("4. Payment Info\n");
    printf("5. Change Password \n");
    printf("6. Teachers \n");
    printf("7. Back \n");

    char b;
    printf("\n\n\n\nEnter Choice :--");
    b = getch();

    if(b < '1' || b > '7') {
        system("cls");
        printf("\t\t\t\t~Your Student Portal~");
        printf("\n\n\n\t\t\t\t===Invalid Input. Please Press 1-6 Key===\n\n");
        printf("\t\t\t\t\tPress Any Key");
        getch();
        goto start;
    }

    switch(b) {
        case '1':
            student_Info(pass, i, class);
            break;
        case '2':
            student_view_notices();
            goto start;
            break;
        case '3':
            stud_lib(i,class);
            break;
        case '4':
            payment(pass,i,class);
            break;
        case '5':

            change_Pass(pass, i, class);
            break;
        case '6':
            view_teachers();
            break;
        case '7':
            return 0;
            break;
    }
}



void stud_lib(char pass[100],int i,int class){
    start:

    system("cls");
    struct member currentMember;
    printf("\t\t\t\t~Library Info~\n\n\n");
    libf=fopen("library.txt","rb");
    if(libf==NULL){
        printf("\n\nFile is not opening\n\n");
        printf("1. Try Again\n");
        printf("2. Back to Portal\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }
    int found=0;
    while(fread(&currentMember,sizeof(currentMember),1,libf)==1){
        if(i==currentMember.roll && class==currentMember.class){
            found=1;

        // Display member info
        printf("Member Information:\n");
        printf("Member ID     : %d\n", currentMember.id);
        printf("Name          : %s\n", currentMember.name);
        printf("Roll          : %d\n", currentMember.roll);
        printf("Class         : %d\n\n", currentMember.class);

        // Current books display with serial numbers
        printf("Borrowed Books:\n");
        int bookCount = 0;
        int bookIndices[5] = {0}; // Tracks which slots have books (1-5)

        // Check each book slot and display if borrowed
        if(currentMember.c1 != 0) {
            printf("1. %-30s (%-20s) Due: %s\n",
                   currentMember.t1, currentMember.a1, currentMember.d1);
            bookCount++;
            bookIndices[0] = 1;
        } else {
            printf("1. [Empty Slot]\n");
        }

        if(currentMember.c2 != 0) {
            printf("2. %-30s (%-20s) Due: %s\n",
                   currentMember.t2, currentMember.a2, currentMember.d2);
            bookCount++;
            bookIndices[1] = 1;
        } else {
            printf("2. [Empty Slot]\n");
        }

        if(currentMember.c3 != 0) {
            printf("3. %-30s (%-20s) Due: %s\n",
                   currentMember.t3, currentMember.a3, currentMember.d3);
            bookCount++;
            bookIndices[2] = 1;
        } else {
            printf("3. [Empty Slot]\n");
        }

        if(currentMember.c4 != 0) {
            printf("4. %-30s (%-20s) Due: %s\n",
                   currentMember.t4, currentMember.a4, currentMember.d4);
            bookCount++;
            bookIndices[3] = 1;
        } else {
            printf("4. [Empty Slot]\n");
        }

        if(currentMember.c5 != 0) {
            printf("5. %-30s (%-20s) Due: %s\n",
                   currentMember.t5, currentMember.a5, currentMember.d5);
            bookCount++;
            bookIndices[4] = 1;
        } else {
            printf("5. [Empty Slot]\n");
        }
        printf("\n\nPress any key for go back");
        break;
        }

    }
    if(!found){
        system("cls");
        printf("\n\nYou Are Not A Member Of Library");
        printf("\n\nPress Any Key TO Go Back");
    }
    getch();
    Portal_page(pass, i, class);
    return;
}





void student_view_notices() {                                                                               // Student View Notice
    start:
    system("cls");
    printf("\t\t\t\t~Notices & Events~\n\n\n");

    FILE *noticeFile = fopen("notices.txt", "rb");
    if(noticeFile == NULL) {
        printf("\n\nNo notices or events available at this time.\n\n");
        printf("1. Try Again\n");
        printf("2. Back to Portal\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }

    int count = 0;
    printf("List of Notices & Events:\n\n");
    while(fread(&ne, sizeof(ne), 1, noticeFile) == 1) {
        printf("%d. %s - %s [%s]\n", ++count, ne.type, ne.title, ne.date);
    }

    if(count == 0) {
        printf("\n\nNo notices or events available!\n\n");
        fclose(noticeFile);
        printf("1. Try Again\n");
        printf("2. Back to Portal\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }

    printf("\n\nEnter Notice/Event number to view (1-%d)\n", count);
    printf("0. Back to Portal\n\n");
    printf("Enter Choice: ");

    int choice=int_input();
    if(choice<0) {
            printf("\nInvalid input! Please enter Number.\n");
            printf("\nPress any key to try again...");
            printf("\nPress <0> key to return ");
            int a=getch();
            if(a=='0') return;
            goto start;
    }

    if(choice == 0) {
        fclose(noticeFile);
        return;
    }

    if(choice < 1 || choice > count) {
        printf("\n\nInvalid selection!\n\n");
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        fclose(noticeFile);
        goto start;
    }


    fseek(noticeFile, (choice-1)*sizeof(ne), SEEK_SET);
    fread(&ne, sizeof(ne), 1, noticeFile);

    details:
    system("cls");
    printf("\t\t\t\t~Notice Details~\n\n\n");
    printf("Type: %s\n", ne.type);
    printf("Date: %s\n", ne.date);
    printf("Title: %s\n", ne.title);
    printf("\nDescription:\n%s\n\n", ne.description);
    printf("------------------------------\n\n");

    printf("1. Back to List\n");
    printf("2. Back to Portal\n\n");
    printf("Enter Choice: ");

    char option = getch();
    printf("%c\n", option);

    fclose(noticeFile);

    switch(option) {
        case '1':
            goto start;
        case '2':
            return;
        default:
            printf("\nInvalid choice!\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            goto details;
    }
}


void student_Info(char pass[100],int i,int class){                                                                      // Student Info
    int count=0;
    file=fopen("student.txt","rb");
    if (file == NULL) {
    printf("Error opening file\n");
    return;
    }
    int found=0;
    while(fread(&s,sizeof(s),1,file)==1){
        if(i==s.roll && class==s.class){
                start:
                system("cls");
                printf("\t\t\t\t\t\t~Student Portal~\n\n\n");
                printf("ID                    : %d\n",s.roll);
                printf("Name                  : %s\n",s.name);
                printf("Age                   : %d\n",s.age);
                printf("Class                 : %d\n",s.class);
                printf("Gender                : %s\n",s.gender);
                printf("Father Name           : %s\n",s.f_name);
                printf("Mother Name           : %s\n",s.m_name);
                printf("Gaurdian Phone number : %s\n",s.g_num);
                printf("Present Address       : %s\n",s.pre_address);
                printf("Permanent Address     : %s\n",s.per_address);

                found=1;
                break;
        }
    }
    if(found==0){
        printf("This ID is not found !!");
    }
    fclose(file);

    printf("\n\n\nBack (Enter Key) ");

    if(count==1){
        printf("\n\nYou Didn't Press Enter. Please Press Enter For Back");
    }
    char c;

    c=getch();
    if(c!='\r'){
        count=1;
        system("cls");
        printf("\n\nYou Didn't Press Enter. Please Press Enter For Back");
        getch();
        goto start;
    }else{Portal_page(pass,i,class);}

}


void payment(char pass[100],int i, int class) {
    int count=0;
    start:
    system("cls");
    file = fopen("student.txt", "rb");
    if (file == NULL) {
        printf("Error opening student records!\n");
        printf("Press any key to continue...");
        getch();
        return;
    }


    int found = 0;
    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(i == s.roll && class == s.class) {
            found = 1;

            printf("\t\t\t\t~Payment Information~\n\n");
            printf("Roll Number         : %d\n", s.roll);
            printf("Name                : %s\n", s.name);
            printf("Class               : %d\n\n\n", s.class);
            printf("Total Payable Amount: %s\n", s.payble_amount);
            printf("10%% of Payable      : %s\n\n", s.m_Percent);

            float total= atof(s.payble_amount);
            float paid= atof(s.payment_info);
            float balance=total-paid;
            printf("\nPaid                : %s\n", s.payment_info);
            printf("Remaining Balance   : %.2f\n", balance);

            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("\nStudent with Roll %d in Class %d not found!\n", i, class);
    }


    printf("\n1. Back\n");
    printf("Enter choice: ");
    if(count==1){
    printf("\n\n\nWrong Choice. Please Enter 1 to go Back");}
    if(getch() == '1') {
        Portal_page(pass,i,class);
    } else {
        count=1;
        goto start;
    }
}


void view_teachers() {
    system("cls");
    printf("\t\t\t\t~~ All Teachers ~~\n\n\n");

    FILE *file = fopen("teachers.txt", "rb");
    if (file == NULL) {
        printf("\t\t\t\tNo teachers found!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
        return;
    }

    // Display basic list
    printf("%-6s %-20s %-15s %-15s\n", "ID", "Name", "Designation", "Subject");
    printf("--------------------------------------------------\n");

    Teacher t;
    int found = 0;
    while (fread(&t, sizeof(Teacher), 1, file) == 1) {
        found = 1;
        printf("%-6d %-20s %-15s %-15s\n", t.id, t.name, t.designation, t.subject);
    }

    if (found) {
        printf("\nPress [D] for detailed view or any key to return...");
        char choice = getch();
        if (tolower(choice) == 'd') {
            system("cls");
            printf("\t\t\t\t~~ Teachers Details ~~\n\n\n");
            rewind(file);
            while (fread(&t, sizeof(Teacher), 1, file) == 1) {
                printf("ID            : %d\n", t.id);
                printf("Name          : %s\n", t.name);
                printf("Designation   : %s\n", t.designation);
                printf("Subject       : %s\n", t.subject);
                printf("Phone         : %s\n", t.phone);
                printf("Email         : %s\n", t.email);
                printf("Address       : %s\n", t.address);
                printf("Qualification : %s\n", t.qualification);
                printf("Joining Date  : %s\n", t.joining_date);
                printf("--------------------------------------------\n");
            }
            printf("\nPress any key to return...");
            getch();
        }
    } else {
        printf("\n\t\t\t\tNo teachers found!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
    }

    fclose(file);
}




void change_Pass(char p[100], int i, int class) {                                                                    // Change Password
    system("cls");


    char pass[60];
    char new_pass[60];
    int found = 0;

    file = fopen("student.txt", "rb+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }


    printf("Enter Current Password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;


    while (fread(&s, sizeof(s), 1, file) == 1) {
        if(i==s.roll && class==s.class){
        if (strcmp(pass, s.pass) == 0) {
            found = 1;

            printf("Enter New Password : ");
            fgets(new_pass, sizeof(new_pass), stdin);
            new_pass[strcspn(new_pass, "\n")] = 0;

            strcpy(s.pass, new_pass);

            fseek(file, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, file);

            printf("======= Password Has Been Changed =======");
            break;
        }
        }
    }

    if (found==0) {
        start1:
        system("cls");
        printf("======= Wrong Password ======= \n\n");
        printf("1. Try Again\n");
        printf("2. Back\n");

        char c;
        c=getch();
        if(c<'1' || c>'2'){
            printf("\nPlease Press 1 Or 2");
            printf("\nPress Any Key");
            getch();
            goto start1;
        }

        switch (c) {
            case '1':
                fclose(file);
                change_Pass(p,i,class);
                break;
            case '2':
                fclose(file);
                Portal_page(p,i,class);
                break;
            default:
                fclose(file);
                change_Pass(p,i,class);
                break;
        }
    }

    fclose(file);
    printf("\n\nPress Any Key To Go Main Page");
    getch();
}



//========================================================================================Teacher Management====================================================================================================================



void tm(){
    while (1) {
        system("cls");
        printf("\t\t\t\t~~ TEACHER MANAGEMENT SYSTEM ~~\n\n\n");
        printf("\t\t\t\t1. Add New Teacher\n");
        printf("\t\t\t\t2. View All Teachers\n");
        printf("\t\t\t\t3. Remove Teacher\n");
        printf("\t\t\t\t4. Back\n\n");
        printf("\t\t\t\tEnter Your Choice: ");

        char choice = getch();
        printf("%c\n", choice);

        switch (choice) {
            case '1':
                addTeacher();
                break;
            case '2':
                viewAllTeachers();
                break;
            case '3':
                removeTeacher();
                break;
            case '4':
                return 0;
                break;
            default:
                printf("\n\t\t\t\tInvalid choice! Please try again.\n");
                getch();
        }
    }
}

int getMaxTeacherId() {
    FILE *file = fopen("teachers.txt", "rb");
    int maxId = 0;

    if (file != NULL) {
        Teacher temp;
        while (fread(&temp, sizeof(Teacher), 1, file) == 1) {
            if (temp.id > maxId) {
                maxId = temp.id;
            }
        }
        fclose(file);
    }
    return maxId;
}

void addTeacher() {
    system("cls");
    printf("\t\t\t\t~~ Add New Teacher ~~\n\n\n");

    Teacher newTeacher;
    memset(&newTeacher, 0, sizeof(newTeacher));
    newTeacher.id = getMaxTeacherId() + 1;

    FILE *file = fopen("teachers.txt", "ab");
    if (file == NULL) {
        printf("\n\n\t\t\t\tError opening teacher file!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    int currentField = 0;
    while (1) {
        system("cls");
        printf("\t\t\t\t~~ Add New Teacher ~~\n\n\n");
        printf("Teacher ID: %d (Auto-generated)\n\n", newTeacher.id);
        printf("Current Information:\n");
        printf("1. Name                  : %s\n", newTeacher.name[0] ? newTeacher.name : "[Not entered]");
        printf("2. Designation           : %s\n", newTeacher.designation[0] ? newTeacher.designation : "[Not entered]");
        printf("3. Subject               : %s\n", newTeacher.subject[0] ? newTeacher.subject : "[Not entered]");
        printf("4. Phone Number          : %s\n", newTeacher.phone[0] ? newTeacher.phone : "[Not entered]");
        printf("5. Email                 : %s\n", newTeacher.email[0] ? newTeacher.email : "[Not entered]");
        printf("6. Address               : %s\n", newTeacher.address[0] ? newTeacher.address : "[Not entered]");
        printf("7. Qualification         : %s\n", newTeacher.qualification[0] ? newTeacher.qualification : "[Not entered]");
        printf("8. Joining Date (DD/MM/YYYY): %s\n", newTeacher.joining_date[0] ? newTeacher.joining_date : "[Not entered]");
        printf("\n0. Save and Complete\n");
        printf("9. Back to Menu\n\n");
        printf("Enter field number to edit (%d/8): ", currentField);

        char choice = getch();
        printf("%c\n", choice);

        if (choice == '0') {
            if (!newTeacher.name[0] || !newTeacher.designation[0] || !newTeacher.subject[0] ||
                !newTeacher.phone[0] || !newTeacher.qualification[0] || !newTeacher.joining_date[0]) {
                printf("\n\nError: Required fields must be completed before saving!\n");
                printf("Required fields: Name, Designation, Subject, Phone, Qualification, Joining Date\n\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }

            fwrite(&newTeacher, sizeof(newTeacher), 1, file);
            fclose(file);

            system("cls");
            printf("\t\t\t\t~~ Teacher Added Successfully ~~\n\n\n");
            printf("Teacher ID      : %d\n", newTeacher.id);
            printf("Name            : %s\n", newTeacher.name);
            printf("Designation     : %s\n", newTeacher.designation);
            printf("Subject         : %s\n", newTeacher.subject);
            printf("\n\t\t\t\tPress Any Key to Return to Menu");
            getch();
            return;
        }
        else if (choice == '9') {
            fclose(file);
            printf("\nTeacher addition cancelled! Returning to menu...\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            return;
        }
        else if (choice >= '1' && choice <= '8') {
            currentField = choice - '0';
            printf("\nEnter %s: ",
                currentField == 1 ? "Name" :
                currentField == 2 ? "Designation" :
                currentField == 3 ? "Subject" :
                currentField == 4 ? "Phone Number" :
                currentField == 5 ? "Email" :
                currentField == 6 ? "Address" :
                currentField == 7 ? "Qualification" : "Joining Date (DD/MM/YYYY)");

            switch (currentField) {
                case 1:
                    fgets(newTeacher.name, sizeof(newTeacher.name), stdin);
                    newTeacher.name[strcspn(newTeacher.name, "\n")] = '\0';
                    break;
                case 2:
                    fgets(newTeacher.designation, sizeof(newTeacher.designation), stdin);
                    newTeacher.designation[strcspn(newTeacher.designation, "\n")] = '\0';
                    break;
                case 3:
                    fgets(newTeacher.subject, sizeof(newTeacher.subject), stdin);
                    newTeacher.subject[strcspn(newTeacher.subject, "\n")] = '\0';
                    break;
                case 4:
                    fgets(newTeacher.phone, sizeof(newTeacher.phone), stdin);
                    newTeacher.phone[strcspn(newTeacher.phone, "\n")] = '\0';
                    break;
                case 5:
                    fgets(newTeacher.email, sizeof(newTeacher.email), stdin);
                    newTeacher.email[strcspn(newTeacher.email, "\n")] = '\0';
                    break;
                case 6:
                    fgets(newTeacher.address, sizeof(newTeacher.address), stdin);
                    newTeacher.address[strcspn(newTeacher.address, "\n")] = '\0';
                    break;
                case 7:
                    fgets(newTeacher.qualification, sizeof(newTeacher.qualification), stdin);
                    newTeacher.qualification[strcspn(newTeacher.qualification, "\n")] = '\0';
                    break;
                case 8:
                    fgets(newTeacher.joining_date, sizeof(newTeacher.joining_date), stdin);
                    newTeacher.joining_date[strcspn(newTeacher.joining_date, "\n")] = '\0';
                    break;
            }
        }
        else {
            printf("\nInvalid choice! Please select 0-9.\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
        }
    }
}

void viewAllTeachers() {
    system("cls");
    printf("\t\t\t\t~~ All Teachers ~~\n\n\n");

    FILE *file = fopen("teachers.txt", "rb");
    if (file == NULL) {
        printf("\t\t\t\tNo teachers found!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
        return;
    }

    // Display basic list
    printf("%-6s %-20s %-15s %-15s\n", "ID", "Name", "Designation", "Subject");
    printf("--------------------------------------------------\n");

    Teacher t;
    int found = 0;
    while (fread(&t, sizeof(Teacher), 1, file) == 1) {
        found = 1;
        printf("%-6d %-20s %-15s %-15s\n", t.id, t.name, t.designation, t.subject);
    }

    if (found) {
        printf("\nPress [D] for detailed view or any key to return...");
        char choice = getch();
        if (tolower(choice) == 'd') {
            system("cls");
            printf("\t\t\t\t~~ Teachers Details ~~\n\n\n");
            rewind(file);
            while (fread(&t, sizeof(Teacher), 1, file) == 1) {
                printf("ID            : %d\n", t.id);
                printf("Name          : %s\n", t.name);
                printf("Designation   : %s\n", t.designation);
                printf("Subject       : %s\n", t.subject);
                printf("Phone         : %s\n", t.phone);
                printf("Email         : %s\n", t.email);
                printf("Address       : %s\n", t.address);
                printf("Qualification : %s\n", t.qualification);
                printf("Joining Date  : %s\n", t.joining_date);
                printf("--------------------------------------------\n");
            }
            printf("\nPress any key to return...");
            getch();
        }
    } else {
        printf("\n\t\t\t\tNo teachers found!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
    }

    fclose(file);
}

void removeTeacher() {
    system("cls");
    printf("\t\t\t\t~~ Remove Teacher ~~\n\n\n");

    FILE *file = fopen("teachers.txt", "rb");
    if (file == NULL) {
        printf("\t\t\t\tNo teachers found to remove!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
        return;
    }

    // Load all teachers into memory
    Teacher teachers[100];
    int count = 0;
    while (fread(&teachers[count], sizeof(Teacher), 1, file) == 1) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("\t\t\t\tNo teachers found to remove!\n");
        printf("\n\t\t\t\tPress Any Key to Return to Menu");
        getch();
        return;
    }

    // Display teachers for selection
    printf("%-6s %-20s %-15s\n", "ID", "Name", "Designation");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-20s %-15s\n", teachers[i].id, teachers[i].name, teachers[i].designation);
    }

    int idToRemove;
    printf("\nEnter Teacher ID to remove: ");
    scanf("%d", &idToRemove);
    getchar(); // Consume newline

    int found = 0;
    FILE *tempFile = fopen("temp.txt", "wb");
    for (int i = 0; i < count; i++) {
        if (teachers[i].id != idToRemove) {
            fwrite(&teachers[i], sizeof(Teacher), 1, tempFile);
        } else {
            found = 1;
        }
    }
    fclose(tempFile);

    if (found) {
        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");
        printf("\n\t\t\t\tTeacher removed successfully!\n");
    } else {
        remove("temp.txt");
        printf("\n\t\t\t\tTeacher with ID %d not found!\n", idToRemove);
    }

    printf("\n\t\t\t\tPress Any Key to Return to Menu");
    getch();
}




//======================================================================================== Admission ==============================================================================================================================



void admit(){                                                      // Admission System

    start:
    system("cls");
    printf("\t\t\t\t~Admission System~\n\n\n");
    printf("1. Student Admission \n");
    printf("2. Show All Students \n");
    printf("3. Search Student By Data \n");
    printf("4. Remove Student \n");
    printf("5. back \n\n");
    char c=getch();
    if(c<'1' || c>'5'){
        system("cls");
        printf("Wrong Choice. Please Enter 1-4");
        getch();
        goto start;
    }
    switch(c){
    case '1':
        admission();
        break;
    case '2':
        viewStudents();
        break;
    case '3':
        Search_Student();
        break;
    case '4':
        remStu();
        break;
    case '5':
        return;
        break;
    default:
        printf("Wrong choice");
    }
}


void Search_Student() {
    start:
    system("cls");
    printf("\t\t\t\t~Search Student~\n\n\n");

    int c, r;
    int found = 0;

    printf("Enter Class (1-10): ");
    c=int_input();
    if(c < 1 || c > 10) {
        printf("\n\nInvalid class! Please enter between 1-10.\n\n");
        printf("\t\t\t\tPress Any Key to Try Again\n");
        printf("\t\t\t\tPress <0> Key to go Back");
        int a=getch();
        if(a=='0'){
            admit();
            return 0;
        }
        goto start;
    }
    start1:
    printf("\nEnter Roll: ");
    r=int_input();
    if(r<1) {
        printf("\n\nInvalid roll number! Please enter numbers only.\n\n");
        printf("Press Any Key to Try Again");
        printf("\nPress <0> Key to go Back");
        int a=getch();
        if(a=='0'){
            admit();
            return 0;
        };
        goto start1;
    }


    file = fopen("student.txt", "rb");
    if(file == NULL) {
        printf("\n\nError opening student file!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    system("cls");
    printf("\t\t\t\t~Student Details~\n\n\n");

    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(c == s.class && r == s.roll) {
            found = 1;
            printf("\nName                : %s\n", s.name);
            printf("Class               : %d\n", s.class);
            printf("Student ID          : %d\n", s.roll);
            printf("Age                 : %d\n", s.age);
            printf("Gender              : %s\n", s.gender);
            printf("Father              : %s\n", s.f_name);
            printf("Mother              : %s\n", s.m_name);
            printf("Guardian Phone      : %s\n", s.g_num);
            printf("Present Address     : %s\n", s.pre_address);
            printf("Permanent Address   : %s\n", s.per_address);
            printf("Payable Amount      : %s\n", s.payble_amount);
            printf("10%%- of Payable      : %s\n", s.m_Percent);
            printf("Total Paid          : %s\n", s.payment_info);
            printf("Password            : %s\n", s.pass);
            printf("------------------------------------------------\n");
            break;
        }
    }

    fclose(file);

    if(!found) {
        printf("\n\nStudent with Roll %d in Class %d not found!\n\n", r, c);
    }

    printf("\n\n1. Search Again\n");
    printf("2. Back \n\n");
    printf("Enter Choice: ");

    char option = getch();
    switch(option) {
        case '1':
            goto start;
        case '2':
            admit();
            return 0;
        default:
            printf("\n\nInvalid choice! Returning to menu...\n\n");
            getch();
            return;
    }
}


void admission(){                                                                                               // Student Admission
    start:
    system("cls");
    printf("\t\t\t\t~Admission System~\n\n\n");
    printf("1. Add Student\n");
    printf("2. Edit Student Information\n");
    printf("3. Back\n");
    char c=getch();
    if(c<'1' || c>'3'){
        system("cls");
        printf("\t\t\t\t Invalid Choice. Please Press 1-4 ");
        getch();
        goto start;
    }
    switch(c){
    case '1':
        addStudent();
        break;
    case '2':
        edit_Sinfo();
        break;
    case '3':
        admit();
        break;
    default:
        break;
    }
}


void addStudent(){
    start:
    system("cls");
    printf("\t\t\t\t~Admission System~\n\n\n");
    printf("  CLass \n");
    printf("--------\n");
    printf("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n\n\n");
    printf("11. Back \n\n");
    printf("Enroll Class :  ");
    int c=int_input();

    if(c<1 || c>11){
        printf("\n\n\n\t\t\t\t=== Wrong Input. Press Key From 1-11 ===");
        getch();
        goto start;
    }

    if(c==11){
        admission();
        return 0;
    }else{addStudent_info(c);}

}


void addStudent_info(int c) {                                                                   // Student Form
    start:
    system("cls");
    printf("\t\t\t\t~~ New Admission - Class %d ~~\n\n\n", c);

    struct student newStudent;
    memset(&newStudent, 0, sizeof(newStudent));
    newStudent.class = c;

    int maxRoll = 0;
    file = fopen("student.txt", "rb");
    if (file != NULL) {
        while (fread(&s, sizeof(s), 1, file) == 1) {
            if (c == s.class && s.roll > maxRoll) {
                maxRoll = s.roll;
            }
        }
        fclose(file);
    }
    newStudent.roll = maxRoll + 1;

    system("cls");
    printf("\t\t\t\t~~ New Admission - Class %d ~~\n\n\n", c);
    printf("Automatically Generated Roll Number: %d\n\n", newStudent.roll);
    printf("\t\t\t\tPress Any Key to Continue");
    getch();

    file = fopen("student.txt", "ab");
    if (file == NULL) {
        printf("\n\nError opening student file!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    int currentField = 0;
    while (1) {
        system("cls");
        printf("\t\t\t\t~~ New Admission (Class %d) ~~\n\n\n", c);
        printf("Roll Number: %d (Auto-generated)\n\n", newStudent.roll);
        printf("Current Information:\n");
        printf("1. Name                  : %s\n", newStudent.name[0] ? newStudent.name : "[Not entered]");
        printf("2. Father's Name         : %s\n", newStudent.f_name[0] ? newStudent.f_name : "[Not entered]");
        printf("3. Mother's Name         : %s\n", newStudent.m_name[0] ? newStudent.m_name : "[Not entered]");
        printf("4. Guardian Phone        : %s\n", newStudent.g_num[0] ? newStudent.g_num : "[Not entered]");
        printf("5. Age                   : %d\n", newStudent.age);
        printf("6. Gender                : %s\n", newStudent.gender[0] ? newStudent.gender : "[Not entered]");
        printf("7. Present Address       : %s\n", newStudent.pre_address[0] ? newStudent.pre_address : "[Not entered]");
        printf("8. Permanent Address     : %s\n", newStudent.per_address[0] ? newStudent.per_address : "[Not entered]");
        printf("\n0. Save and Complete\n");
        printf("9. Back to Menu\n\n");
        printf("Enter field number to edit (%d/8): ", currentField);

        char choice = getch();
        printf("%c\n", choice);

        if (choice == '0') {

            if (!newStudent.name[0] || !newStudent.f_name[0] || !newStudent.m_name[0] ||
                !newStudent.g_num[0] || !newStudent.age || !newStudent.gender[0] ||
                !newStudent.pre_address[0] || !newStudent.per_address[0]) {
                printf("\n\nError: All fields must be completed before saving!\n\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }


            sprintf(newStudent.pass, "%d%s%d", newStudent.roll, newStudent.name, newStudent.class);
            strcpy(newStudent.payment_info, "0");

            adminf = fopen("adminPass.txt", "rb");
            if (adminf != NULL) {
                while (fread(&a, sizeof(a), 1, adminf) == 1) {
                    const char* amount = NULL;
                    switch (c) {
                        case 1: amount = a.c1; break;
                        case 2: amount = a.c2; break;
                        case 3: amount = a.c3; break;
                        case 4: amount = a.c4; break;
                        case 5: amount = a.c5; break;
                        case 6: amount = a.c6; break;
                        case 7: amount = a.c7; break;
                        case 8: amount = a.c8; break;
                        case 9: amount = a.c9; break;
                        case 10: amount = a.c10; break;
                    }
                    if (amount != NULL) {
                        strncpy(newStudent.payble_amount, amount, sizeof(newStudent.payble_amount));
                        break;
                    }
                }
                fclose(adminf);
            }


            float amount = atof(newStudent.payble_amount);
            snprintf(newStudent.m_Percent, sizeof(newStudent.m_Percent), "%.2f", amount * 0.1f);

            fwrite(&newStudent, sizeof(newStudent), 1, file);
            fclose(file);

            system("cls");
            printf("\t\t\t\t~~ Admission Successful ~~\n\n\n");
            printf("Student Roll Number: %d\n", newStudent.roll);
            printf("Name              : %s\n", newStudent.name);
            printf("Class             : %d\n", newStudent.class);
            printf("\nGenerated Password: %s\n", newStudent.pass);
            printf("\n\t\t\t\tPress Any Key to Return to Menu");
            getch();
            admit();
            return;
        }
        else if (choice == '9') {
            fclose(file);
            printf("\nAdmission cancelled! Returning to menu...\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            admit();
            return;
        }
        else if (choice >= '1' && choice <= '8') {
            int count=0;
            currentField = choice - '0';
            printf("\nEnter %s: ",
                currentField == 1 ? "Name" :
                currentField == 2 ? "Father's Name" :
                currentField == 3 ? "Mother's Name" :
                currentField == 4 ? "Guardian Phone" :
                currentField == 5 ? "Age" :
                currentField == 6 ? "Gender" :
                currentField == 7 ? "Present Address" : "Permanent Address");

            switch (currentField) {
                case 1:
                    fgets(newStudent.name, sizeof(newStudent.name), stdin);
                    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
                    break;
                case 2:
                    fgets(newStudent.f_name, sizeof(newStudent.f_name), stdin);
                    newStudent.f_name[strcspn(newStudent.f_name, "\n")] = '\0';
                    break;
                case 3:
                    fgets(newStudent.m_name, sizeof(newStudent.m_name), stdin);
                    newStudent.m_name[strcspn(newStudent.m_name, "\n")] = '\0';
                    break;
                case 4:
                    fgets(newStudent.g_num, sizeof(newStudent.g_num), stdin);
                    newStudent.g_num[strcspn(newStudent.g_num, "\n")] = '\0';
                    break;
                case 5:
                    while (1) {
                        if(count==1){printf("\nEnter Age : ");}
                        if (scanf("%d", &newStudent.age) != 1) {
                            printf("\nInvalid age! Please enter numbers only.\n");
                            while (getchar() != '\n');
                            printf("Press any key to try again...");
                            count=1;
                            getch();
                            continue;
                        }
                        while (getchar() != '\n');
                        break;
                    }
                    break;
                case 6:
                    fgets(newStudent.gender, sizeof(newStudent.gender), stdin);
                    newStudent.gender[strcspn(newStudent.gender, "\n")] = '\0';
                    break;
                case 7:
                    fgets(newStudent.pre_address, sizeof(newStudent.pre_address), stdin);
                    newStudent.pre_address[strcspn(newStudent.pre_address, "\n")] = '\0';
                    break;
                case 8:
                    fgets(newStudent.per_address, sizeof(newStudent.per_address), stdin);
                    newStudent.per_address[strcspn(newStudent.per_address, "\n")] = '\0';
                    break;
            }
//            if (currentField < 8) currentField++;
        }
        else {
            printf("\nInvalid choice! Please select 0-9.\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
        }
    }
}

void edit_Sinfo() {
    start:

    system("cls");
    printf("\t\t\t\t~Edit Student Information~\n\n\n");

    int c, r;
    int found = 0;

    // Get class input
    class_input:
    printf("Enter Class (1-10)       : ");
    c=int_input();
    if(c < 1 || c > 10) {
        printf("\n\nInvalid class! Please enter between 1-10.\n\n");

        printf("1. Try Again\n");
        printf("2. Back\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') {
            system("cls");
            goto class_input;
        }
        else if(opt == '2') {
            admit();
            return;
        }
        else {
            printf("\nInvalid choice! Returning...\n");
            getch();
            admit();
            return;
        }
    }
    roll_input:
    printf("Enter Roll Number        : ");
    r=int_input();
    if(r<1) {
        printf("\n\nInvalid roll number! Please enter numbers only.\n\n");
        printf("1. Try Again\n");
        printf("2. Back\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') {
            system("cls");
            goto roll_input;
        }
        else if(opt == '2') {
            admit();
            return 0;
        }
        else {
            printf("\nInvalid choice! Returning...\n");
            getch();
            admit();
            return 0;
        }
    }

    FILE *temp = fopen("temp.txt", "wb");
    file = fopen("student.txt", "rb");

    if(file == NULL || temp == NULL) {
        printf("\n\nError opening files!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        if(file) fclose(file);
        if(temp) fclose(temp);
        getch();
        admit();
        return;
    }
    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(c == s.class && r == s.roll) {
            found = 1;
            edit_menu:
            system("cls");
            printf("\t\t\t\t~Edit Student %d Class %d~\n\n\n", r, c);
            printf("1. Name                  : %s\n", s.name);
            printf("2. Age                   : %d\n", s.age);
            printf("3. Gender                : %s\n", s.gender);
            printf("4. Father's Name         : %s\n", s.f_name);
            printf("5. Mother's Name         : %s\n", s.m_name);
            printf("6. Guardian Phone        : %s\n", s.g_num);
            printf("7. Present Address       : %s\n", s.pre_address);
            printf("8. Permanent Address     : %s\n", s.per_address);
            printf("0. Save and Exit\n\n\n");
            printf("Enter Field Number to Edit: ");

            char field = getch();
            printf("%c\n", field);

            if(field<'0' || field>'8'){
                    printf("\nInvalid Input. Press Valid Input\n");
                    printf("\t\t\t\tPress Any Key to Try Again\n");
                    printf("\t\t\t\tPress <0> Key to go Back");
                    int a=getch();
                    if(a=='0'){
                        admission();
                        return 0;
                    }
                    goto edit_menu;
            }

            if(field == '0') {
                fwrite(&s, sizeof(s), 1, temp);
                break;
            }
            printf("Enter New Value: ");
            switch(field) {
                case '1':
                    fgets(s.name, sizeof(s.name), stdin);
                    s.name[strcspn(s.name, "\n")] = 0;
                    break;
                case '2':
                    scanf("%d", &s.age);
                    while(getchar() != '\n');
                    break;
                case '3':
                    fgets(s.gender, sizeof(s.gender), stdin);
                    s.gender[strcspn(s.gender, "\n")] = 0;
                    break;
                case '4':
                    fgets(s.f_name, sizeof(s.f_name), stdin);
                    s.f_name[strcspn(s.f_name, "\n")] = 0;
                    break;
                case '5':
                    fgets(s.m_name, sizeof(s.m_name), stdin);
                    s.m_name[strcspn(s.m_name, "\n")] = 0;
                    break;
                case '6':
                    fgets(s.g_num, sizeof(s.g_num), stdin);
                    s.g_num[strcspn(s.g_num, "\n")] = 0;
                    break;
                case '7':
                    fgets(s.pre_address, sizeof(s.pre_address), stdin);
                    s.pre_address[strcspn(s.pre_address, "\n")] = 0;
                    break;
                case '8':
                    fgets(s.per_address, sizeof(s.per_address), stdin);
                    s.per_address[strcspn(s.per_address, "\n")] = 0;
                    break;
                default:
                    printf("\n\nInvalid choice!\n\n");
                    printf("1. Try Again\n");
                    printf("2. Back\n\n");
                    printf("Enter Choice: ");
                    char opt = getch();
                    if(opt == '1') {
                        goto edit_menu;
                    }
                    else {
                        fwrite(&s, sizeof(s), 1, temp);
                        goto finish_edit;
                    }
            }
            goto edit_menu;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    finish_edit:

    while(fread(&s, sizeof(s), 1, file) == 1) {
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if(!found) {
        printf("\n\nStudent not found!\n\n");
        printf("1. Try Again\n");
        printf("Press Any Key To Back\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') {
            goto start;
        }
        else {
            admit();
            return;
        }
    }
    else {
        printf("\n\nStudent information updated successfully!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        admit();
    }
}


void viewStudents() {
    int c;
    int found = 0;
    int studentCount = 0;
    char choice;
    while (1) {
        system("cls");
        printf("\t\t\t\t~View Students~\n\n");
        printf("Show All Students Of Class (1-10): ");

        c=int_input();
        if (c < 1 || c > 10) {
            printf("\nInvalid input! Please enter a number between 1-10.\n");
            printf("\nPress any key to try again...");
            printf("\nPress <0> key to return ");
            int a=getch();
            if(a=='0') goto start;
            continue;
        }
        break;
    }

    file = fopen("student.txt", "rb");
    if (file == NULL) {
        printf("\nError: Student database not found!\n");
        printf("Press any key to return...");
        getch();
        return;
    }
    system("cls");
    printf("\t\t\t\t~Students of Class %d~\n\n", c);
    printf("%-10s%-20s%-10s%-10s\n", "Roll", "Name", "Age", "Gender");
    printf("------------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, file) == 1) {
        if (c == s.class) {
            found = 1;
            studentCount++;
            printf("%-10d%-20s%-10d%-10s\n", s.roll, s.name, s.age, s.gender);
        }
    }
    if (found) {
        printf("\nTotal Students: %d\n", studentCount);
        printf("\nPress [D] for detailed view or any other key to continue...");
        choice = getch();
        if (tolower(choice) == 'd') {
            system("cls");
            printf("\t\t\t~Detailed View - Class %d~\n\n", c);
            rewind(file);
            while (fread(&s, sizeof(s), 1, file) == 1) {
                if (c == s.class) {
                    printf("\nStudent ID: %d\n", s.roll);
                    printf("Name                : %s\n", s.name);
                    printf("Age                 : %d\n", s.age);
                    printf("Gender              : %s\n", s.gender);
                    printf("Father              : %s\n", s.f_name);
                    printf("Mother              : %s\n", s.m_name);
                    printf("Guardian Phone      : %s\n", s.g_num);
                    printf("Present Address     : %s\n", s.pre_address);
                    printf("Permanent Address   : %s\n", s.per_address);
                    printf("Payable Amount      : %s\n", s.payble_amount);
                    printf("10%% of Payable      : %s\n", s.m_Percent);
                    printf("Total Paid          : %s\n", s.payment_info);
                    printf("Password            : %s\n", s.pass);
                    printf("------------------------------------------------\n");
                }
            }
        }
    } else {
        printf("\nNo students found in class %d\n", c);
    }
    fclose(file);
    printf("\nPress any key to return to menu...");
    getch();
    start:
    admit();
}


void remStu(){
    start:
    system("cls");
    printf("1. Remove One (1) Student \n");
    printf("2. Remove All Students \n");
    printf("3. Back \n\n");
    printf("Enter your choice :- ");
    char c=getch();
    if(c<'1' || c>'3'){
        system("cls");
        printf("Wrong Choice. Press key From 1-3");
        getch();
        goto start;
    }
    switch(c){
    case '1':
        removeStudent();
        break;
    case '2':
        removeAllStudents();
        break;
    case '3':
        admit();
        break;
    default:
        break;
    }
}


void removeStudent(){                                                                   // One Student Remove

    FILE *temp=fopen("temp.txt","w");
    int c;
    int i;
    int found=0;
    start:
    system("cls");
    printf("Enter Class :");
    c=int_input();
    if(c<1 || c>10){
            printf("\nInvalid choice. Please Enter CLass Number 1-10\n");
            printf("Press any key to try again\n");
            printf("Press <0> key  to go Back\n");
            char b=getch();
            if(b=='0'){
            remStu();
            return 0;
            }else{
            goto start;
            }
    }
    start1:
    printf("Enter Roll :");
    i=int_input();
    if(i<1 || i>10){
            printf("\nInvalid choice. Please Enter CLass Number 1-10\n");
            printf("Press any key to try again\n");
            printf("Press <0> key  to go Back\n");
            char a=getch();
            if(a=='0'){
            remStu();
            return 0;
            }
            goto start1;
    }
    file=fopen("student.txt","rb");
    while(fread(&s,sizeof(s),1,file)==1){
        if(i==s.roll && c==s.class){
                found=1;
                printf("Roll  : %d\n",s.roll);
                printf("Name  : %s\n",s.name);
                printf("Class : %d\n",s.class);

                printf("\nPress <Enter> To Delete This Student Data");
                printf("\nPress Any Key TO Go Back ");
                char r=getch();
                if(r=='\r'){
                    continue;
                }else{remStu();}
        }else{
            fwrite(&s,sizeof(s),1,temp);
            }
        }
    if(found==0){
        printf("The ID is not found to delete !!");
    }
    fclose(file);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt","student.txt");
    system("cls");
    printf("The student with ID %d deleted successfully !!",i);
    getch();
}


void removeAllStudents(){                                                               // All Student Remove
    start2:
    system("cls");
    int found=0;
    printf("\t\t\t\t~Delete All Students Of A Class~");
    printf("\n1. Class 1");
    printf("\n2. Class 2");
    printf("\n3. Class 3");
    printf("\n4. Class 4");
    printf("\n5. Class 5");
    printf("\n6. Class 6");
    printf("\n7. Class 7");
    printf("\n8. Class 8");
    printf("\n9. Class 9");
    printf("\n10. Class 0");
    printf("\n\nPress Class Number TO Delete : ");
    int c=int_input();
    if(c<1 || c>10){
            printf("\nInvalid choice. Please Enter CLass Number 1-10\n");
            printf("Press any key to try again\n");
            printf("Press <0> key  to go Back\n");
            char a=getch();
            if(a=='0'){
            remStu();
            return 0;
            }else {goto start2;}
    }

    FILE *temp=fopen("temp.txt","w");
    file=fopen("student.txt","rb");
    while(fread(&s,sizeof(s),1,file)==1){
        if(c==s.class){
                found=1;
        }else{
            fwrite(&s,sizeof(s),1,temp);
            }
        }
    if(found==0){
        system("cls");
        printf("The Class No Data to delete !!");
        goto start;
    }
    fclose(file);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt","student.txt");
    system("cls");
    if(found==1){printf("Delete All Students Data Of Class %d",c);}
    start:
    printf("\n\nPress any Key To Go Back");
    getch();
    start3:
    remStu();
    return 0;
}


//============================================================================== Transaction ================================================================================================



void transaction(){

    char c;
    while(1){                                                                   // Transaction
    system("cls");
    printf("\t\t\t\t~Transaction~");
    printf("\n\n\n\n1. Admin \n");
    printf("2. Payment\n");
    printf("Press <Enter> Back\n");
    c=getch();
    if(c=='\r'){
        return 0;
    }
    if (c < '1' || c > '9') {
        system("cls");
        printf("\n\n\n\t\t\t\tInvalid input! Please enter a number.\n\n\n");
        printf("\t\t\t\t\tPress Any Key ");
        getch();
        continue;
    }else{break;}
    }
    switch(c){
    case '1':
        log_in();
        break;
    case '2':

            system("cls");
            adminf=fopen("adminPass.txt","rb");
            printf("\nEnter Password : ");
            char pass[100];
            int found=0;
            fgets(pass, sizeof(pass), stdin);
            pass[strcspn(pass, "\n")] = 0;
            while(fread(&a,sizeof(a),1,adminf)==1){
            if(strcmp(pass, a.pass2)==0){
                found=1;
                fclose(adminf);
                printf("\n\n\n\t\t\t\t~Log In Successful~");
                printf("\n\t\t\t\t=== Press Any Key ===");
                break;
            }
            }
            if(!found){
                printf("\n\nWrong Password\n\n");
                printf("Press any key to go back\n");
                getch();
                break;
            }

        pay();
        break;
    default:
        system("cls");
        printf("================Wrong Choice=============");
        printf("===============Press Any Key============");
        getch();
        transaction();
    }
}



void log_in(){                                                              // Admin log in
    system("cls");

    adminf=fopen("adminPass.txt","rb");
    int found=0;
    char pass[60];
    printf("\t\t\t~Admin Log In Page~");
    printf("\n\n\nEnter Admin Password : ");
    fgets(pass,sizeof(pass),stdin);
    pass[strcspn(pass, "\n")] = 0;
    rewind(adminf);
    while(fread(&a,sizeof(a),1,adminf)==1){
    if(strcmp(pass, a.pass)==0){
        found=1;
        fclose(adminf);
        printf("\n\n\n\t\t\t\t~Log In Successful~");
        printf("\n\t\t\t\t=== Press Any Key ===");
        getch();
        admin_profile(pass);
        break;
    }
    }
    if(found==0){
        fclose(adminf);
        char c;
        while(1){
        printf("\n\n\n\t\t\t\t=====Wrong Admin Pass======\n\n\n");
        printf("1. Try Again  \n");
        printf("2. Back \n\n\n");
        printf("Enter Choice : ");
        c=getch();
        if (c < '1' || c > '2') {
            system("cls");
            printf("\n\n\n\t\t\t\tInvalid input! Please enter 1 or 2.\n\n\n");
            printf("\t\t\t\t\tPress Any Key ");
            getch();
            continue;
        }else{break;}
        }
        switch(c){
        case '1':
            log_in();
            break;
        case '2':
           transaction();
            return;
        default:
            log_in();
            break;
        }
    }
}


void admin_profile(char pass[100]){                                                         // Admin Profile
    system("cls");
    adminf = fopen("adminPass.txt", "rb");
    if (adminf == NULL) {
        printf("Error opening file\n");
        return;
    }
    rewind(adminf);
    while(fread(&a, sizeof(a), 1, adminf) == 1) {
        if(strcmp(pass, a.pass) == 0) {
            fclose(adminf);
            char c;
            while(1) {
            system("cls");
            printf("\t\t\t\t~Admin Profile~\n");
            printf("1. Change All Classes Yearly Cost\n");
            printf("2. Print All Classes Yearly Cost\n");
            printf("3. Change Admin Password \n");
            printf("4. Change School Management Password\n");
            printf("5. Back\n\n\n");
            printf("Enter Choice : ");
            c=getch();
            if (c < '0' || c > '5') {
                    system("cls");
                    printf("\n\n\n\t\t\t\tInvalid input! Enter 1-3.\n\n\n");
                    printf("\t\t\t\t\tPress Any Key ");
                    getch();
                    continue;
                } else {
                    break;
                }
            }
            switch(c){
            case '1':
                change_cost(pass);
                break;
            case '2':
                print_all_cost(pass);
                break;
            case '3':
                change_ad_pass();
                break;
            case '4':
                change_Man_pass();
                break;
            case '5':
                transaction();
                return 0;
            default:
                break;
            }
        }
    }
}


void change_cost(char pass[100]) {
    FILE *adminf;
    char choice;
    char newAmount[20];
    int selectedClass = -1;
    adminf = fopen("adminPass.txt", "rb+");
    if (adminf == NULL) {
        printf("Error opening file\n");
        return;
    }
    while(fread(&a, sizeof(a), 1, adminf) == 1) {
        if(strcmp(pass, a.pass) == 0) {
            while(1) {
                system("cls");
                printf("\n\t\t\t\t~ CHANGE YEARLY CLASS COST ~\n\n");
                printf(" 1. Class 1  : %s\n", a.c1[0] ? a.c1 : "[Not set]");
                printf(" 2. Class 2  : %s\n", a.c2[0] ? a.c2 : "[Not set]");
                printf(" 3. Class 3  : %s\n", a.c3[0] ? a.c3 : "[Not set]");
                printf(" 4. Class 4  : %s\n", a.c4[0] ? a.c4 : "[Not set]");
                printf(" 5. Class 5  : %s\n", a.c5[0] ? a.c5 : "[Not set]");
                printf(" 6. Class 6  : %s\n", a.c6[0] ? a.c6 : "[Not set]");
                printf(" 7. Class 7  : %s\n", a.c7[0] ? a.c7 : "[Not set]");
                printf(" 8. Class 8  : %s\n", a.c8[0] ? a.c8 : "[Not set]");
                printf(" 9. Class 9  : %s\n", a.c9[0] ? a.c9 : "[Not set]");
                printf(" 0. Class 10 : %s\n\n", a.c10[0] ? a.c10 : "[Not set]");
                printf(" Press 1-9 or 0 to edit, Enter to go back\n");
                printf(" Your choice: ");
                choice = getch();
                if(choice == '\r') {
                    fclose(adminf);
                    admin_profile(pass);
                    return;
                }
                if(choice < '0' || choice > '9') {
                    printf("\n\n\tInvalid input! Please enter 0-9 or press Enter.\n");
                    printf("\tPress any key to continue...");
                    getch();
                    continue;
                }
                selectedClass = (choice == '0') ? 10 : (choice - '0');
                while(1) {
                    system("cls");
                    printf("\n\t\t\t\t~ UPDATE CLASS %d COST ~\n\n", selectedClass);
                    printf(" Current amount: %s\n\n",
                           (selectedClass == 1) ? a.c1 :
                           (selectedClass == 2) ? a.c2 :
                           (selectedClass == 3) ? a.c3 :
                           (selectedClass == 4) ? a.c4 :
                           (selectedClass == 5) ? a.c5 :
                           (selectedClass == 6) ? a.c6 :
                           (selectedClass == 7) ? a.c7 :
                           (selectedClass == 8) ? a.c8 :
                           (selectedClass == 9) ? a.c9 : a.c10);
                    printf(" Enter new amount: ");
                    fgets(newAmount, sizeof(newAmount), stdin);
                    newAmount[strcspn(newAmount, "\n")] = '\0';
                    int valid = 1;
                    for(int i = 0; newAmount[i]; i++) {
                        if(!isdigit(newAmount[i])) {
                            valid = 0;
                            break;
                        }
                    }
                    if(!valid || strlen(newAmount) == 0) {
                        printf("\n Invalid amount! Please enter numbers only.\n");
                        printf(" Press any key to try again...");
                        getch();
                        continue;
                    }
                    break;
                }
                switch(selectedClass) {
                    case 1: strcpy(a.c1, newAmount); break;
                    case 2: strcpy(a.c2, newAmount); break;
                    case 3: strcpy(a.c3, newAmount); break;
                    case 4: strcpy(a.c4, newAmount); break;
                    case 5: strcpy(a.c5, newAmount); break;
                    case 6: strcpy(a.c6, newAmount); break;
                    case 7: strcpy(a.c7, newAmount); break;
                    case 8: strcpy(a.c8, newAmount); break;
                    case 9: strcpy(a.c9, newAmount); break;
                    case 10: strcpy(a.c10, newAmount); break;
                }
                fseek(adminf, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, adminf);
                fflush(adminf);
                printf("\n Amount updated successfully!\n");
                printf(" Press any key to continue...");
                getch();
            }
        }
    }
    fclose(adminf);
}


void print_all_cost(char pass[100]){                                                                        //Print All Cost
    int count=0;
    start:
    system("cls");
    adminf = fopen("adminPass.txt", "rb");
    if (adminf == NULL) {
        printf("Error opening file\n");
        return;
    }
    rewind(adminf);
    while(fread(&a, sizeof(a), 1, adminf) == 1) {
        if(strcmp(pass, a.pass) == 0) {

            printf("\t\t\t\t~All Classes Yearly Cost~\n");

             for(int i = 1; i <= 10; i++) {
                    printf("Class %d = %s\n", i,
                          (i == 1) ? a.c1 :
                          (i == 2) ? a.c2 :
                          (i == 3) ? a.c3 :
                          (i == 4) ? a.c4 :
                          (i == 5) ? a.c5 :
                          (i == 6) ? a.c6 :
                          (i == 7) ? a.c7 :
                          (i == 8) ? a.c8 :
                          (i == 9) ? a.c9 : a.c10);
                }
        }
    }
    fclose(adminf);
    printf("\n\n\nBack (Press Enter)");
    if(count!=0){
            printf("\n\nYou Didn't Press Enter. Please Enter TO Go Back");

    }
    char a;
    a=getch();
    if(a==13){
        admin_profile(pass);
    }else{
        count=1;
        goto start;
    }
}


void change_ad_pass(){                                                                                  //Change Admin Password
    system("cls");

    char pass[60];
    char new_pass[60];
    int found = 0;
    adminf=fopen("adminPass.txt","rb+");
    if (adminf == NULL) {
        printf("Error opening file\n");
        getch();
        return;
    }
    printf("Enter Current Password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;
    rewind(adminf);
    while (fread(&a, sizeof(a), 1, adminf) == 1) {
        if (strcmp(pass, a.pass) == 0) {
            found = 1;
            printf("Enter New Password : ");
            fgets(new_pass, sizeof(new_pass), stdin);
            new_pass[strcspn(new_pass, "\n")] = 0;
            strcpy(a.pass, new_pass);
            fseek(adminf, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, adminf);
            printf("======= Password Has Been Changed =======");
            break;
        }
    }
    int count=0;
    if (found==0) {
        start:
        printf("======= Wrong Password ======= \n\n");
        printf("1. Try Again\n");
        printf("2. Back\n\n\n");
         if(count==1){
            printf("\t\t\t\tPlease Press 1 or 2");
        }
        char c;
        printf("Enter Choice : ");
        c=getch();

        if(c<'1' || c>'2'){
            count=1;
            goto start;
        }
        switch (c) {
            case '1':
                fclose(adminf);
                change_ad_pass();
                break;
            case '2':
                fclose(adminf);
                transaction();
                return 0;
            default:
                fclose(adminf);
                break;
        }
    }
    fclose(adminf);
    getch();
    transaction();
}



void change_Man_pass(){
    system("cls");

    char pass[60];
    char new_pass[60];
    int found = 0;
    adminf=fopen("adminPass.txt","rb+");
    if (adminf == NULL) {
        printf("Error opening file\n");
        getch();
        return;
    }
    printf("Enter Current Password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;
    rewind(adminf);
    while (fread(&a, sizeof(a), 1, adminf) == 1) {
        if (strcmp(pass, a.pass2) == 0) {
            found = 1;
            printf("Enter New Password : ");
            fgets(new_pass, sizeof(new_pass), stdin);
            new_pass[strcspn(new_pass, "\n")] = 0;
            strcpy(a.pass2, new_pass);
            fseek(adminf, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, adminf);
            printf("======= Password Has Been Changed =======");
            break;
        }
    }
    int count=0;
    if (found==0) {
        start:
        printf("======= Wrong Password ======= \n\n");
        printf("1. Try Again\n");
        printf("2. Back\n\n\n");
         if(count==1){
            printf("\t\t\t\tPlease Press 1 or 2");
        }
        char c;
        printf("Enter Choice : ");
        c=getch();

        if(c<'1' || c>'2'){
            count=1;
            goto start;
        }
        switch (c) {
            case '1':
                fclose(adminf);
                change_Man_pass();
                break;
            case '2':
                fclose(adminf);
                transaction();
                return 0;
            default:
                fclose(adminf);
                break;
        }
    }
    fclose(adminf);
    getch();
    transaction();

}

void pay() {                                                                                      // pay
    start:
    system("cls");
    printf("\t\t\t\t~Student Payment System~\n\n\n");

    int c, r;
    int found = 0;
    float paymentAmount;
    char receiptChoice;

    // Get class input with back option
    class_input:
    printf("\n\nEnter Class (1-10)       : ");
    c=int_input();
    if(c < 1 || c > 10) {
        printf("\nInvalid input! Please enter a number between 1-10.\n");
        printf("\nPress any key to try again...");
        printf("\nPress <0> key to return ");
        int a=getch();
        if(a=='0'){
                transaction();
                return 0;
        }
        goto class_input;

    }

    roll_input:
    printf("\n\nEnter Roll Number        : ");
    r=int_input();
    if(r<1) {
        printf("\nInvalid input! Please enter valid roll number");
        printf("\nPress any key to try again...");
        printf("\nPress <0> key to return ");
        int b=getch();
        if(b=='0'){
                transaction();
                return 0;
        }
        goto roll_input;
    }

    file = fopen("student.txt", "r+b");
    if(file == NULL) {
        printf("\n\nError opening student file!\n\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }


    while(fread(&s, sizeof(s), 1, file) == 1) {
        if(c == s.class && r == s.roll) {
            found = 1;
            long pos = ftell(file) - sizeof(s);

            payment_screen:
            system("cls");
            printf("\t\t\t\t~Payment for %s (Roll %d)~\n\n\n", s.name, s.roll);
            printf("Total Payable Amount    : %s\n", s.payble_amount);
            printf("10%% of Payable         : %s\n", s.m_Percent);
            printf("Previous Payment       : %s\n", s.payment_info);

            // Calculate remaining amount
            float total = atof(s.payble_amount);
            float paid = atof(s.payment_info);
            float remaining = total - paid;

            printf("\nRemaining Amount       : %.2f\n\n", remaining);

            if(remaining <= 0) {
                printf("\n\nNo payment due! All fees are paid.\n\n");
                printf("\t\t\t\tPress Any Key to Return");
                getch();
                fclose(file);
                return;
            }

            printf("Enter Payment Amount    : ");
            if(scanf("%f", &paymentAmount) != 1) {
                while(getchar() != '\n');
                printf("\n\nInvalid amount! Please enter numbers only.\n\n");
                printf("Press Any Key to Try Again\n\n");
                printf("<Enter>  Back");
                char c=getch();
                if(c=='\r'){
                    transaction();
                    return 0;
                }
                else{goto payment_screen;}
            }
            while(getchar() != '\n');

            if(paymentAmount <= 0) {
                printf("\n\nPayment amount must be greater than 0!\n\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                goto payment_screen;
            }

            if(paymentAmount > remaining) {
                printf("\n\nAmount exceeds remaining balance!\n");
                printf("Maximum acceptable amount: %.2f\n\n", remaining);
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                goto payment_screen;
            }

            float newPaid = paid + paymentAmount;
            char newPayment[20];
            snprintf(newPayment, sizeof(newPayment), "%.2f", newPaid);
            strcpy(s.payment_info, newPayment);

            fseek(file, pos, SEEK_SET);
            fwrite(&s, sizeof(s), 1, file);

            receipt:
            system("cls");
            printf("\t\t\t\t~Payment Successful~\n\n\n");
            printf("Student Name      : %s\n", s.name);
            printf("Roll Number       : %d\n", s.roll);
            printf("Class             : %d\n", s.class);
            printf("Amount Paid       : %.2f\n", paymentAmount);
            printf("Total Paid        : %.2f\n", newPaid);
            printf("Remaining Balance : %.2f\n\n", remaining - paymentAmount);

            printf("\n1. Print Receipt\n");
            printf("2. New Payment\n");
            printf("3. Back to Menu\n\n");
            printf("Enter Choice: ");

            receiptChoice = getch();
            printf("%c\n", receiptChoice);

            switch(receiptChoice) {
                case '1':

                    printf("\n\nReceipt printed successfully!\n");
                    printf("\t\t\t\tPress Any Key to Continue");
                    getch();
                    fclose(file);
                    return;
                case '2':
                    fclose(file);
                    goto start;
                case '3':
                    fclose(file);
                    return;
                default:
                    printf("\nInvalid choice!\n");
                    printf("\t\t\t\tPress Any Key to Continue");
                    getch();
                    goto receipt;
            }
        }
    }

    if(!found) {
        printf("\n\nStudent with Roll %d in Class %d not found!\n\n", r, c);
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");

        char opt = getch();
        printf("%c\n", opt);

        if(opt == '1') goto start;
        else if(opt == '2') { fclose(file); return; }
        else {
            printf("\nInvalid choice! Returning to menu...\n");
            getch();
            fclose(file);
            return;
        }
    }
    fclose(file);
}


//================================================================================= Notice=================================================================================


void notice_events() {
    start_menu:
    system("cls");
    printf("\t\t\t\t~Notices & Events Management~\n\n\n");

    printf("1. Add New Notice/Event\n");
    printf("2. View All Notices/Events\n");
    printf("3. Delete Notice/Event\n");
    printf("4. Back to Main Menu\n\n\n");
    printf("Enter Choice: ");

    char choice = getch();
    printf("%c\n", choice);

    switch(choice) {
        case '1':
            add_notice_event();
            break;
        case '2':
            view_notices_events();
            break;
        case '3':
            delete_notice_event();
            break;
        case '4':
            return;
        default:
            printf("\n\nInvalid choice! Please select 1-4.\n\n");
            back_option:
            printf("1. Try Again\n");
            printf("2. Back to Main Menu\n\n");
            printf("Enter Choice: ");
            char opt = getch();
            if(opt == '1') goto start_menu;
            else if(opt == '2') return;
            else {
                printf("\nInvalid choice!\n");
                goto back_option;
            }
    }
    goto start_menu;
}

void add_notice_event() {
    start:
    system("cls");
    printf("\t\t\t\t~Add New Notice/Event~\n\n\n");

    FILE *noticeFile = fopen("notices.txt", "ab");
    if(noticeFile == NULL) {
        printf("\n\nError opening notices file!\n\n");
        back_option:
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto start;
        else if(opt == '2') return;
        else {
            printf("\nInvalid choice!\n");
            goto back_option;
        }
    }

    struct NoticeEvent {
        char title[100];
        char description[500];
        char date[20];
        char type[10];
    } ne;

    memset(&ne, 0, sizeof(ne));

    type_input:
    printf("1. Notice\n");
    printf("2. Event\n\n");
    printf("Enter Type (1-2): ");
    char typeChoice = getch();
    if(typeChoice == '1') strcpy(ne.type, "NOTICE");
    else if(typeChoice == '2') strcpy(ne.type, "EVENT");
    else {
        printf("\n\nInvalid choice!\n\n");
        back_option_type:
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto type_input;
        else if(opt == '2') {
            fclose(noticeFile);
            return;
        }
        else {
            printf("\nInvalid choice!\n");
            goto back_option_type;
        }
    }
    title_input:
    printf("\nEnter Title: ");
    fgets(ne.title, sizeof(ne.title), stdin);
    ne.title[strcspn(ne.title, "\n")] = '\0';
    if(strlen(ne.title) == 0) {
        printf("\nTitle cannot be empty!\n");
        goto title_input;
    }

    date_input:
    printf("Enter Date (DD/MM/YYYY): ");
    fgets(ne.date, sizeof(ne.date), stdin);
    ne.date[strcspn(ne.date, "\n")] = '\0';
    if(strlen(ne.date) == 0) {
        printf("\nDate cannot be empty!\n");
        goto date_input;
    }

    desc_input:
    printf("Enter Description:\n");
    fgets(ne.description, sizeof(ne.description), stdin);
    ne.description[strcspn(ne.description, "\n")] = '\0';
    if(strlen(ne.description) == 0) {
        printf("\nDescription cannot be empty!\n");
        goto desc_input;
    }

    fwrite(&ne, sizeof(ne), 1, noticeFile);
    fclose(noticeFile);

    printf("\n\n%s added successfully!\n\n", ne.type);
    printf("1. Add Another\n");
    printf("2. Back to Menu\n\n");
    printf("Enter Choice: ");
    char opt = getch();
    if(opt == '1') goto start;
    else return;
}

void view_notices_events() {
    start:
    system("cls");
    printf("\t\t\t\t~All Notices & Events~\n\n\n");

    FILE *noticeFile = fopen("notices.txt", "rb");
    if(noticeFile == NULL) {
        printf("\n\nNo notices/events found!\n\n");
        back_option:
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }

    struct NoticeEvent {
        char title[100];
        char description[500];
        char date[20];
        char type[10];
    } ne;

    int count = 0;
    while(fread(&ne, sizeof(ne), 1, noticeFile) == 1) {
        printf("----------------------------------------\n");
        printf("%s [%s]\n", ne.type, ne.date);
        printf("Title: %s\n", ne.title);
        printf("Description: %s\n", ne.description);
        printf("----------------------------------------\n\n");
        count++;
    }

    if(count == 0) {
        printf("\n\nNo notices/events available!\n\n");
    }

    fclose(noticeFile);
    printf("\n1. Refresh List\n");
    printf("2. Back to Menu\n\n");
    printf("Enter Choice: ");
    char opt = getch();
    if(opt == '1') goto start;
    else return;
}

void delete_notice_event() {
    start:
    system("cls");
    printf("\t\t\t\t~Delete Notice/Event~\n\n\n");

    FILE *noticeFile = fopen("notices.txt", "rb");
    if(noticeFile == NULL) {
        printf("\n\nNo notices/events found!\n\n");
        back_option:
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }

    struct NoticeEvent {
        char title[100];
        char description[500];
        char date[20];
        char type[10];
    } ne;

    int count = 0;
    printf("List of Notices/Events:\n\n");
    while(fread(&ne, sizeof(ne), 1, noticeFile) == 1) {
        printf("%d. %s [%s] - %s\n", ++count, ne.type, ne.date, ne.title);
    }

    if(count == 0) {
        printf("\n\nNo notices/events to delete!\n\n");
        fclose(noticeFile);
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto start;
        else return;
    }

    rewind(noticeFile);

    delete_input:
    printf("\nEnter Notice/Event number to delete (1-%d)\n", count);
    printf("0. Back to Menu\n\n");
    printf("Enter Choice: ");
    int toDelete;
    if(scanf("%d", &toDelete) != 1) {
        printf("\n\nInvalid input!\n\n");
        while(getchar() != '\n');
        goto delete_input;
    }
    while(getchar() != '\n');

    if(toDelete == 0) {
        fclose(noticeFile);
        return;
    }

    if(toDelete < 1 || toDelete > count) {
        printf("\n\nInvalid selection!\n\n");
        printf("1. Try Again\n");
        printf("2. Back to Menu\n\n");
        printf("Enter Choice: ");
        char opt = getch();
        if(opt == '1') goto delete_input;
        else {
            fclose(noticeFile);
            return;
        }
    }

    FILE *tempFile = fopen("temp_notices.txt", "wb");
    if(tempFile == NULL) {
        printf("\n\nError creating temporary file!\n\n");
        fclose(noticeFile);
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    int current = 0;
    while(fread(&ne, sizeof(ne), 1, noticeFile) == 1) {
        current++;
        if(current != toDelete) {
            fwrite(&ne, sizeof(ne), 1, tempFile);
        }
    }

    fclose(noticeFile);
    fclose(tempFile);

    remove("notices.txt");
    rename("temp_notices.txt", "notices.txt");

    printf("\n\nNotice/Event deleted successfully!\n\n");
    printf("1. Delete Another\n");
    printf("2. Back to Menu\n\n");
    printf("Enter Choice: ");
    char opt = getch();
    if(opt == '1') goto start;
    else return;
}






// Global file pointers
FILE *file, *libf, *bookf, *tempf;

// ========================================================================== LIBRARY MANAGEMENT SYSTEM ===============================================================

void library() {
    start:
    system("cls");
    printf("\t\t\t\t~Library Management System~\n\n\n");
    printf("1. Add Member\n");
    printf("2. View Books\n");
    printf("3. View Members\n");
    printf("4. Add Books\n");
    printf("5. Borrow Books\n");
    printf("6. Return Books\n");
    printf("7. Back to Main Menu\n\n");

    printf("Enter your choice: ");
    char choice;
    choice = getch();
    printf("%c\n", choice);

    if(choice < '1' || choice > '7') {
        system("cls");
        printf("\n\n\n\t\t\t\tInvalid input! Please enter 1-8.\n\n\n");
        printf("\t\t\t\t\tPress Any Key ");
        getch();
        goto start;
    }

    switch(choice) {
        case '1':
            addMember();
            goto start;
        case '2':
            viewBooks();
            goto start;
        case '3':
            viewMembers();
            goto start;
        case '4':
            addBooks();
            goto start;
        case '5':
            borrowBooks();
            goto start;
        case '6':
            returnBooks();
            goto start;
        case '7':
            return;
        default:
            printf("\n\n\n\t\t\t\tWrong choice!");
            printf("\n\t\t\t\tPress Any Key");
            getch();
            goto start;
    }
}

void addMember() {
    start:
    system("cls");
    printf("\t\t\t\t~~~ Add New Member ~~~\n\n\n");

    struct student s;
    struct member m;
    int roll, class, max_id = 0, found_student = 0, is_member = 0;

    // Find maximum existing ID
    FILE *checkFile = fopen("library.txt", "rb");
    if(checkFile != NULL) {
        while(fread(&m, sizeof(m), 1, checkFile)) {
            if(m.id > max_id) max_id = m.id;
            // Check if student is already a member
            if(m.roll == roll && m.class == class) {
                is_member = 1;
            }
        }
        fclose(checkFile);
    }

    // Class input with validation
    class_input:
    printf("\nEnter Class (1-10): ");
    class=int_input();
    if(class < 1 || class > 10) {
        printf("\nInvalid class! Please enter between 1-10.\n");
        printf("\n1. Try Again\nPress Any Key to go Back Menu\nChoice: ");
        char opt = getch();
        if(opt == '1') goto class_input;
        else return ;
    }

    // Roll number input with validation
    roll_input:
    printf("\nEnter Roll Number: ");
    roll=int_input();
    if(roll<1) {
        printf("\nInvalid roll number! Numbers only.\n");
        printf("\n1. Try Again\n2. Back to Class Input\nPress Any Key To Go Back\nChoice: ");
        char opt = getch();
        if(opt == '1') goto roll_input;
        else if(opt == '2') {
            goto class_input;
        }
        else return;
    }

    // Check if student exists in student records
    FILE *studentFile = fopen("student.txt", "rb");
    if(studentFile == NULL) {
        printf("\nError opening student records!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    while(fread(&s, sizeof(s), 1, studentFile)) {
        if(s.roll == roll && s.class == class) {
            found_student = 1;
            break;
        }
    }
    fclose(studentFile);

    if(!found_student) {
        system("cls");
        printf("\nNo student found with Roll %d in Class %d!\n", roll, class);
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Check if student is already a library member
    FILE *checkMember = fopen("library.txt", "rb");
    if(checkMember != NULL) {
        while(fread(&m, sizeof(m), 1, checkMember)) {
            if(m.roll == roll && m.class == class) {
                is_member = 1;
                break;
            }
        }
        fclose(checkMember);
    }

    if(is_member) {
        printf("\nThis student is already a library member!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Add to library members
    FILE *libf = fopen("library.txt", "ab");
    if(libf == NULL) {
        printf("\nError opening library file!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }
    system("cls");
    // Initialize member data
    m.id = max_id + 1;
    m.roll = s.roll;
    strcpy(m.name, s.name);
    m.age = s.age;
    m.class = s.class;
    strcpy(m.g_num, s.g_num);

    // Initialize all book slots as empty
    m.c1 = m.c2 = m.c3 = m.c4 = m.c5 = 0;
    strcpy(m.t1, ""); strcpy(m.a1, ""); strcpy(m.d1, "");
    strcpy(m.t2, ""); strcpy(m.a2, ""); strcpy(m.d2, "");
    strcpy(m.t3, ""); strcpy(m.a3, ""); strcpy(m.d3, "");
    strcpy(m.t4, ""); strcpy(m.a4, ""); strcpy(m.d4, "");
    strcpy(m.t5, ""); strcpy(m.a5, ""); strcpy(m.d5, "");

    fwrite(&m, sizeof(m), 1, libf);
    fclose(libf);

    printf("\nMember Added Successfully!\n");
    printf("Library ID: %d\n", m.id);
    printf("Name: %s\n", m.name);
    printf("Class: %d\n", m.class);
    printf("\t\t\t\tPress Any Key to Return");
    getch();
}
void viewBooks() {
    start:
    system("cls");
    printf("\t\t\t\t~~~ Library Books ~~~\n\n\n");
    printf("%-6s%-40s%-25s%-8s\n", "Code", "Title", "Author", "Qty");
    printf("------------------------------------------------------------\n");

    struct book b;
    FILE *bookf = fopen("book.txt", "rb");
    if(bookf == NULL) {
        printf("No books found!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Display all books
    while(fread(&b, sizeof(b), 1, bookf)) {
        printf("%-6d%-40s%-25s%-8d\n", b.code, b.title, b.author, b.amount);
    }
    fclose(bookf);

    // Removal option
    printf("\n\nOptions:\n");
    printf("1. Remove a Book\n");
    printf("0. Return to Menu\n");
    printf("\nEnter your choice: ");

    char choice = getch();
    printf("%c\n", choice);

    if(choice == '0') {
        return;
    }
    else if(choice == '1') {
        remove_book:
        system("cls");
        printf("\t\t\t\t~~~ Remove Book ~~~\n\n\n");
        printf("Enter Book Code to remove (0 to cancel): ");

        int remove_code;
        if(scanf("%d", &remove_code) != 1) {
            printf("\nInvalid input! Numbers only.\n");
            while(getchar() != '\n');
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            goto remove_book;
        }
        getchar();

        if(remove_code == 0) {
            goto start;
        }

        // Check if book exists and is not borrowed
        bookf = fopen("book.txt", "rb");
        FILE *tempf = fopen("temp.txt", "wb");
        int found = 0, is_borrowed = 0;
        struct book current;
        struct member m;

        if(bookf == NULL || tempf == NULL) {
            printf("\nError opening files!\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            if(bookf) fclose(bookf);
            if(tempf) fclose(tempf);
            remove("temp.txt");
            goto start;
        }

        // First check if book is borrowed by any member
        FILE *libf = fopen("library.txt", "rb");
        if(libf != NULL) {
            while(fread(&m, sizeof(m), 1, libf)) {
                if(m.c1 == remove_code || m.c2 == remove_code ||
                   m.c3 == remove_code || m.c4 == remove_code ||
                   m.c5 == remove_code) {
                    is_borrowed = 1;
                    break;
                }
            }
            fclose(libf);
        }

        if(is_borrowed) {
            printf("\nCannot remove book - it is currently borrowed!\n");
            fclose(bookf);
            fclose(tempf);
            remove("temp.txt");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            goto start;
        }

        // Process book removal
        while(fread(&current, sizeof(current), 1, bookf)) {
            if(current.code == remove_code) {
                found = 1;
                continue; // Skip writing this book to temp file
            }
            fwrite(&current, sizeof(current), 1, tempf);
        }

        fclose(bookf);
        fclose(tempf);

        if(!found) {
            printf("\nBook with Code %d not found!\n", remove_code);
            remove("temp.txt");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            goto start;
        }

        // Replace original file with temp file
        remove("book.txt");
        rename("temp.txt", "book.txt");

        printf("\nBook with Code %d removed successfully!\n", remove_code);
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        goto start;
    }
    else {
        printf("\nInvalid choice!\n");
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        goto start;
    }
}

void viewMembers() {
    start:
    system("cls");
    printf("\t\t\t\t~~~ Library Members ~~~\n\n\n");
    printf("%-8s%-8s%-20s%-6s%-6s%-15s\n", "Lib ID", "Roll", "Name", "Age", "Class", "Contact");
    printf("------------------------------------------------------------\n");

    struct member m;
    FILE *libf = fopen("library.txt", "rb");
    if(libf == NULL) {
        printf("No members found!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Display all members
    while(fread(&m, sizeof(m), 1, libf)) {
        printf("%-8d%-8d%-20s%-6d%-6d%-15s\n",
              m.id, m.roll, m.name, m.age, m.class, m.g_num);
    }
    fclose(libf);

    // Removal option
    printf("\n\nOptions:\n");
    printf("1. Remove a Member\n");
    printf("0. Return to Menu\n");
    printf("\nEnter your choice: ");

    char choice = getch();
    printf("%c\n", choice);

    if(choice == '0') {
        return;
    }
    else if(choice == '1') {
        remove_member:
        system("cls");
        printf("\t\t\t\t~~~ Remove Member ~~~\n\n\n");
        printf("Enter Library ID to remove (0 to cancel): ");

        int remove_id=int_input();;
        if(remove_id<1) {
            printf("\nInvalid input! Numbers only.\n");
            printf("\t\t\t\tPress Any Key to go back");
            getch();
            goto start;
        }


        // Check if member exists and has no borrowed books
        libf = fopen("library.txt", "rb");
        FILE *tempf = fopen("temp.txt", "wb");
        int found = 0, has_books = 0;
        struct member current;

        if(libf == NULL || tempf == NULL) {
            printf("\nError opening files!\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            if(libf) fclose(libf);
            if(tempf) fclose(tempf);
            remove("temp.txt");
            goto start;
        }

        while(fread(&current, sizeof(current), 1, libf)) {
            if(current.id == remove_id) {
                found = 1;
                // Check if member has any books
                if(current.c1 || current.c2 || current.c3 || current.c4 || current.c5) {
                    has_books = 1;
                }
                continue; // Skip writing this member to temp file
            }
            fwrite(&current, sizeof(current), 1, tempf);
        }

        fclose(libf);
        fclose(tempf);

        if(!found) {
            printf("\nMember with ID %d not found!\n", remove_id);
            remove("temp.txt");
            printf("\t\t\t\tPress Any Key to go back");
            getch();
            goto start;
        }

        if(has_books) {
            printf("\nCannot remove member - they have borrowed books!\n");
            remove("temp.txt");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
            goto start;
        }

        // Replace original file with temp file
        remove("library.txt");
        rename("temp.txt", "library.txt");

        printf("\nMember with ID %d removed successfully!\n", remove_id);
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        goto start;
    }
    else {
        printf("\nInvalid choice!\n");
        printf("\t\t\t\tPress Any Key to Continue");
        getch();
        goto start;
    }
}
void addBooks() {
    system("cls");
    printf("\t\t\t\t~~~ Add New Books ~~~\n\n\n");

    struct book b;
    int max_code = 0;

    // Find maximum book code
    bookf = fopen("book.txt", "rb");
    if(bookf != NULL) {
        while(fread(&b, sizeof(b), 1, bookf)) {
            if(b.code > max_code) max_code = b.code;
        }
        fclose(bookf);
    }

    b.code = max_code + 1;
    printf("Auto-generated Book Code: %d\n\n", b.code);

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &b.amount);
    getchar();

    bookf = fopen("book.txt", "ab");
    if(bookf == NULL) {
        printf("\nError opening book database!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    fwrite(&b, sizeof(b), 1, bookf);
    fclose(bookf);

    printf("\nBook Added Successfully!\n");
    printf("Code: %d\nTitle: %s\n", b.code, b.title);
    printf("\t\t\t\tPress Any Key to Return");
    getch();
}



void borrowBooks() {

    int id, found_member = 0;
    struct member currentMember;
    struct book currentBook;
    time_t current_time;
    time(&current_time);

    start:
    system("cls");
    printf("\t\t\t\t~~~ Book Borrowing System ~~~\n\n\n");
    printf("Enter Library ID (0 to cancel): ");
    id=int_input();
    if(id<1) {
        printf("\nInvalid input! Numbers only.\n");
        printf("1. Try again.\nPress any key to back");
        char a=getch();
        if(a=='1'){
            goto start;
        }else{
            return;
            }
    }

    // Verify member exists
    FILE *libf = fopen("library.txt", "rb+");
    if(libf == NULL) {
        printf("\nError opening member records!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    while(fread(&currentMember, sizeof(currentMember), 1, libf)) {
        if(currentMember.id == id) {
            found_member = 1;
            break;
        }
    }

    if(!found_member) {
        printf("\nNo member found with ID %d\n", id);
        fclose(libf);
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Main borrowing interface
    while(1) {
        system("cls");
        printf("\t\t\t\t~~~ Book Borrowing (ID: %d) ~~~\n\n\n", id);

        // Display member info
        printf("Member Information:\n");
        printf("Name          : %s\n", currentMember.name);
        printf("Roll          : %d\n", currentMember.roll);
        printf("Class         : %d\n\n", currentMember.class);

        // Current books display with all 5 slots
        printf("Borrowed Books:\n");
        if(currentMember.c1 != 0) {
            printf("1. %-30s (%-20s) Due: %s\n",
                   currentMember.t1, currentMember.a1, currentMember.d1);
        } else {
            printf("1. [Empty Slot]\n");
        }
        if(currentMember.c2 != 0) {
            printf("2. %-30s (%-20s) Due: %s\n",
                   currentMember.t2, currentMember.a2, currentMember.d2);
        } else {
            printf("2. [Empty Slot]\n");
        }
        if(currentMember.c3 != 0) {
            printf("3. %-30s (%-20s) Due: %s\n",
                   currentMember.t3, currentMember.a3, currentMember.d3);
        } else {
            printf("3. [Empty Slot]\n");
        }
        if(currentMember.c4 != 0) {
            printf("4. %-30s (%-20s) Due: %s\n",
                   currentMember.t4, currentMember.a4, currentMember.d4);
        } else {
            printf("4. [Empty Slot]\n");
        }
        if(currentMember.c5 != 0) {
            printf("5. %-30s (%-20s) Due: %s\n",
                   currentMember.t5, currentMember.a5, currentMember.d5);
        } else {
            printf("5. [Empty Slot]\n");
        }

        printf("\nOptions:\n");
        printf("1. Borrow New Book\n");
        printf("0. Save and Complete\n");
        printf("9. Cancel\n\n");
        printf("Enter choice: ");

        char choice = getch();
        printf("%c\n", choice);

        if(choice == '0') {
            // Save changes and exit
            fseek(libf, -sizeof(currentMember), SEEK_CUR);
            fwrite(&currentMember, sizeof(currentMember), 1, libf);
            fclose(libf);
            printf("\nBorrowing process completed!\n");
            printf("\t\t\t\tPress Any Key to Return");
            getch();
            return;
        }
        else if(choice == '9') {
            fclose(libf);
            printf("\nBorrowing cancelled!\n");
            printf("\t\t\t\tPress Any Key to Return");
            getch();
            return;
        }
        else if(choice == '1') {
            // Check if member has available slots
            if(currentMember.c1 && currentMember.c2 && currentMember.c3 &&
               currentMember.c4 && currentMember.c5) {
                printf("\nBorrowing limit reached (5 books)!\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }

            printf("\nEnter Book Code: ");
            int code;
            if(scanf("%d", &code) != 1) {
                printf("\nInvalid book code!\n");
                while(getchar() != '\n');
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }
            getchar();

            // Check book availability
            FILE *bookf = fopen("book.txt", "rb+");
            if(bookf == NULL) {
                printf("\nError opening book database!\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }

            int found_book = 0;
            while(fread(&currentBook, sizeof(currentBook), 1, bookf)) {
                if(currentBook.code == code && currentBook.amount > 0) {
                    found_book = 1;
                    break;
                }
            }

            if(!found_book) {
                printf("\nBook unavailable!\n");
                fclose(bookf);
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }

            // Assign book to first empty slot
            char due_date[20];
            strftime(due_date, 20, "%Y-%m-%d", localtime(&(time_t){current_time + 14*24*60*60}));

            if(!currentMember.c1) {
                currentMember.c1 = currentBook.code;
                strcpy(currentMember.t1, currentBook.title);
                strcpy(currentMember.a1, currentBook.author);
                strcpy(currentMember.d1, due_date);
            }
            else if(!currentMember.c2) {
                currentMember.c2 = currentBook.code;
                strcpy(currentMember.t2, currentBook.title);
                strcpy(currentMember.a2, currentBook.author);
                strcpy(currentMember.d2, due_date);
            }
            else if(!currentMember.c3) {
                currentMember.c3 = currentBook.code;
                strcpy(currentMember.t3, currentBook.title);
                strcpy(currentMember.a3, currentBook.author);
                strcpy(currentMember.d3, due_date);
            }
            else if(!currentMember.c4) {
                currentMember.c4 = currentBook.code;
                strcpy(currentMember.t4, currentBook.title);
                strcpy(currentMember.a4, currentBook.author);
                strcpy(currentMember.d4, due_date);
            }
            else if(!currentMember.c5) {
                currentMember.c5 = currentBook.code;
                strcpy(currentMember.t5, currentBook.title);
                strcpy(currentMember.a5, currentBook.author);
                strcpy(currentMember.d5, due_date);
            }

            // Update book quantity
            currentBook.amount--;
            fseek(bookf, -sizeof(currentBook), SEEK_CUR);
            fwrite(&currentBook, sizeof(currentBook), 1, bookf);
            fclose(bookf);

            printf("\nBook '%s' borrowed successfully!\n", currentBook.title);
            printf("Due Date: %s\n", due_date);
            printf("\t\t\t\tPress Any Key to Continue");
            getch();

            // Update the display by writing changes temporarily
            fseek(libf, -sizeof(currentMember), SEEK_CUR);
            fwrite(&currentMember, sizeof(currentMember), 1, libf);
            fflush(libf);
        }
        else {
            printf("\nInvalid choice!\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
        }
    }
}

void returnBooks() {
    start:
    system("cls");
    printf("\t\t\t\t~~~ Book Return System ~~~\n\n\n");

    int id, found_member = 0;
    struct member currentMember;

    // Member ID Input
    printf("Enter Library ID (0 to cancel): ");
    id=int_input();
    if(id<1) {
        printf("\nInvalid input! Numbers only.\n");
        printf("1. Try again.\nPress any key to back");
        char a=getch();
        if(a=='1'){
            goto start;
        }else{
            return;
            }
    }
    // Verify member exists
    FILE *libf = fopen("library.txt", "rb+");
    if(libf == NULL) {
        printf("\nError opening member records!\n");
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    while(fread(&currentMember, sizeof(currentMember), 1, libf)) {
        if(currentMember.id == id) {
            found_member = 1;
            break;
        }
    }

    if(!found_member) {
        printf("\nNo member found with ID %d\n", id);
        fclose(libf);
        printf("\t\t\t\tPress Any Key to Return");
        getch();
        return;
    }

    // Main return interface
    while(1) {
        system("cls");
        printf("\t\t\t\t~~~ Book Return (ID: %d) ~~~\n\n\n", id);

        // Display member info
        printf("Member Information:\n");
        printf("Name          : %s\n", currentMember.name);
        printf("Roll          : %d\n", currentMember.roll);
        printf("Class         : %d\n\n", currentMember.class);

        // Current books display with serial numbers
        printf("Borrowed Books:\n");
        int bookCount = 0;
        int bookIndices[5] = {0}; // Tracks which slots have books (1-5)

        // Check each book slot and display if borrowed
        if(currentMember.c1 != 0) {
            printf("1. %-30s (%-20s) Due: %s\n",
                   currentMember.t1, currentMember.a1, currentMember.d1);
            bookCount++;
            bookIndices[0] = 1;
        } else {
            printf("1. [Empty Slot]\n");
        }

        if(currentMember.c2 != 0) {
            printf("2. %-30s (%-20s) Due: %s\n",
                   currentMember.t2, currentMember.a2, currentMember.d2);
            bookCount++;
            bookIndices[1] = 1;
        } else {
            printf("2. [Empty Slot]\n");
        }

        if(currentMember.c3 != 0) {
            printf("3. %-30s (%-20s) Due: %s\n",
                   currentMember.t3, currentMember.a3, currentMember.d3);
            bookCount++;
            bookIndices[2] = 1;
        } else {
            printf("3. [Empty Slot]\n");
        }

        if(currentMember.c4 != 0) {
            printf("4. %-30s (%-20s) Due: %s\n",
                   currentMember.t4, currentMember.a4, currentMember.d4);
            bookCount++;
            bookIndices[3] = 1;
        } else {
            printf("4. [Empty Slot]\n");
        }

        if(currentMember.c5 != 0) {
            printf("5. %-30s (%-20s) Due: %s\n",
                   currentMember.t5, currentMember.a5, currentMember.d5);
            bookCount++;
            bookIndices[4] = 1;
        } else {
            printf("5. [Empty Slot]\n");
        }

        if(bookCount == 0) {
            printf("\nNo books currently borrowed!\n");
            fclose(libf);
            printf("\t\t\t\tPress Any Key to Return");
            getch();
            return;
        }

        printf("\nOptions:\n");
        printf("1-5. Select Book to Return\n");
        printf("0. Save and Complete Return\n");
        printf("9. Cancel\n\n");
        printf("Enter choice: ");

        char choice = getch();
        printf("%c\n", choice);

        if(choice == '0') {
            // Save changes and exit
            fseek(libf, -sizeof(currentMember), SEEK_CUR);
            fwrite(&currentMember, sizeof(currentMember), 1, libf);
            fclose(libf);
            printf("\nReturn process completed!\n");
            printf("\t\t\t\tPress Any Key to Return");
            getch();
            return;
        }
        else if(choice == '9') {
            fclose(libf);
            printf("\nReturn cancelled!\n");
            printf("\t\t\t\tPress Any Key to Return");
            getch();
            return;
        }
        else if(choice >= '1' && choice <= '5') {
            int selectedSlot = choice - '1'; // Convert to 0-based index

            // Check if selected slot has a book
            if(!bookIndices[selectedSlot]) {
                printf("\nThis slot is already empty!\n");
                printf("\t\t\t\tPress Any Key to Continue");
                getch();
                continue;
            }

            int bookCode = 0;
            char bookTitle[100];

            // Get the selected book details
            switch(selectedSlot) {
                case 0:
                    bookCode = currentMember.c1;
                    strcpy(bookTitle, currentMember.t1);
                    currentMember.c1 = 0;
                    strcpy(currentMember.t1, "");
                    strcpy(currentMember.a1, "");
                    strcpy(currentMember.d1, "");
                    break;
                case 1:
                    bookCode = currentMember.c2;
                    strcpy(bookTitle, currentMember.t2);
                    currentMember.c2 = 0;
                    strcpy(currentMember.t2, "");
                    strcpy(currentMember.a2, "");
                    strcpy(currentMember.d2, "");
                    break;
                case 2:
                    bookCode = currentMember.c3;
                    strcpy(bookTitle, currentMember.t3);
                    currentMember.c3 = 0;
                    strcpy(currentMember.t3, "");
                    strcpy(currentMember.a3, "");
                    strcpy(currentMember.d3, "");
                    break;
                case 3:
                    bookCode = currentMember.c4;
                    strcpy(bookTitle, currentMember.t4);
                    currentMember.c4 = 0;
                    strcpy(currentMember.t4, "");
                    strcpy(currentMember.a4, "");
                    strcpy(currentMember.d4, "");
                    break;
                case 4:
                    bookCode = currentMember.c5;
                    strcpy(bookTitle, currentMember.t5);
                    currentMember.c5 = 0;
                    strcpy(currentMember.t5, "");
                    strcpy(currentMember.a5, "");
                    strcpy(currentMember.d5, "");
                    break;
            }

            // Update book quantity in book.txt
            FILE *bookf = fopen("book.txt", "rb+");
            if(bookf != NULL) {
                struct book b;
                while(fread(&b, sizeof(b), 1, bookf)) {
                    if(b.code == bookCode) {
                        b.amount++;
                        fseek(bookf, -sizeof(b), SEEK_CUR);
                        fwrite(&b, sizeof(b), 1, bookf);
                        break;
                    }
                }
                fclose(bookf);
            }

            printf("\nBook '%s' returned successfully!\n", bookTitle);
            printf("\t\t\t\tPress Any Key to Continue");
            getch();

            // Update the display by writing changes temporarily
            fseek(libf, -sizeof(currentMember), SEEK_CUR);
            fwrite(&currentMember, sizeof(currentMember), 1, libf);
            fflush(libf);
        }
        else {
            printf("\nInvalid choice!\n");
            printf("\t\t\t\tPress Any Key to Continue");
            getch();
        }
    }
}


//==================================================================== Main Function ==================================================================


int main(){

    start:
    adminf=fopen("adminPass.txt","rb");
    if(adminf==NULL){
        adminf=fopen("adminPass.txt","wb");
        fclose(adminf);
        goto start;
    }
    fseek(adminf,0,SEEK_END);
    long size=ftell(adminf);
    fclose(adminf);

     if(size==0){
        adminf=fopen("adminPass.txt","wb+");
        if (adminf == NULL) {
        printf("Error opening file.\n");
        return;
        }
        strcpy(a.pass,"Admin");
        strcpy(a.pass2,"Admin");
        strcpy(a.c1, "0");
        strcpy(a.c2, "0");
        strcpy(a.c3, "0");
        strcpy(a.c4, "0");
        strcpy(a.c5, "0");
        strcpy(a.c6, "0");
        strcpy(a.c7, "0");
        strcpy(a.c8, "0");
        strcpy(a.c9, "0");
        strcpy(a.c10, "0");
        fwrite(&a,sizeof(a),1,adminf);
        rewind(adminf);
        fclose(adminf);
    }

    char c;

    do{
        while(1){
        system("cls");
        printf("\t\t\t\t\t\t~School Management~\n\n\n");
        printf("\n\n\n\n\t\t\t\t1. Student Portal \n");
        printf("\t\t\t\t2. Teacher Management \n");
        printf("\t\t\t\t3. Admission System \n");
        printf("\t\t\t\t4. Transaction \n");
        printf("\t\t\t\t5. Notice & Events \n");
        printf("\t\t\t\t6. Library Management \n");
        printf("\t\t\t\t7. Exit \n\n\n\n");
        printf("\t\t\t\tEnter Choice :--");

            c=getch();
            if (c < '0' || c > '9') {
                system("cls");
                printf("\n\n\n\t\t\t\tInvalid input! Please enter a number.\n\n\n");
                printf("\t\t\t\t\tPress Any Key ");
                getch();
                continue;
            }else{break;}
        }
        switch(c){
        case '1':
            student_Portal();
            break;
        case '2':

            system("cls");
            adminf=fopen("adminPass.txt","rb");
            printf("\nEnter Password : ");
            char pass4[100];
            int found4=0;
            fgets(pass4, sizeof(pass4), stdin);
            pass4[strcspn(pass4, "\n")] = 0;
            while(fread(&a,sizeof(a),1,adminf)==1){
            if(strcmp(pass4, a.pass2)==0){
                found4=1;
                fclose(adminf);
                printf("\n\n\n\t\t\t\t~Log In Successful~");
                printf("\n\t\t\t\t=== Press Any Key ===");
                break;
            }
            }
            if(!found4){
                printf("\n\nWrong Password\n\n");
                printf("Press any key to go back\n");
                getch();
                break;
            }

            tm();
            break;
        case '3':

            system("cls");
            adminf=fopen("adminPass.txt","rb");
            printf("\nEnter Password : ");
            char pass1[100];
            int found1=0;
            fgets(pass1, sizeof(pass1), stdin);
            pass1[strcspn(pass1, "\n")] = 0;
            while(fread(&a,sizeof(a),1,adminf)==1){
            if(strcmp(pass1, a.pass2)==0){
                found1=1;
                fclose(adminf);
                printf("\n\n\n\t\t\t\t~Log In Successful~");
                printf("\n\t\t\t\t=== Press Any Key ===");
                break;
            }
            }
            if(!found1){
                printf("\n\nWrong Password\n\n");
                printf("Press any key to go back\n");
                getch();
                break;
            }
            admit();
            break;
        case '4':
            transaction();
            break;

        case '5':

            system("cls");
            adminf=fopen("adminPass.txt","rb");
            printf("\nEnter Password : ");
            char pass2[100];
            int found2=0;
            fgets(pass2, sizeof(pass2), stdin);
            pass2[strcspn(pass2, "\n")] = 0;
            while(fread(&a,sizeof(a),1,adminf)==1){
            if(strcmp(pass2, a.pass2)==0){
                found2=1;
                fclose(adminf);
                printf("\n\n\n\t\t\t\t~Log In Successful~");
                printf("\n\t\t\t\t=== Press Any Key ===");
                break;
            }
            }
            if(!found2){
                printf("\n\nWrong Password\n\n");
                printf("Press any key to go back\n");
                getch();
                break;
            }

            notice_events();
            break;

        case '6':

            system("cls");
            adminf=fopen("adminPass.txt","rb");
            printf("\nEnter Password : ");
            char pass3[100];
            int found3=0;
            fgets(pass3, sizeof(pass3), stdin);
            pass3[strcspn(pass3, "\n")] = 0;
            while(fread(&a,sizeof(a),1,adminf)==1){
            if(strcmp(pass3, a.pass2)==0){
                found3=1;
                fclose(adminf);
                printf("\n\n\n\t\t\t\t~Log In Successful~");
                printf("\n\t\t\t\t=== Press Any Key ===");
                break;
            }
            }
            if(!found3){
                printf("\n\nWrong Password\n\n");
                printf("Press any key to go back\n");
                getch();
                break;
            }

            library();
            break;
        default:
            system("cls");
            if(c!='7'){
            printf("\n\n\n========================Wrong choice========================\n\n\n");
            printf("========================Press Any Key========================");
            getch();
            }
        }

    }while(c!='7');

    printf("\n\n\n========================Thank For Using School management========================\n\n\n");
    printf("\n\n========================================Bye======================================");
    getch();
}
