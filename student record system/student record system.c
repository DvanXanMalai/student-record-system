#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{
    char ID[15];
    char name[20];
    char add[20];
    char parname[20];
    int Class;
    long unsigned int phone_no;
};
struct student stu;

void print_heading(const char st[]){
    printf("SRS : %s",st);
}



void add_student(){
    printf("\n");
    print_heading("\t\t--Add Record--\n");
    int print = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");

    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        printf("ID: ");gets(stu.ID);
        //here you can confirms the ID
        printf("Name: ");gets(stu.name);
        printf("Address: ");gets(stu.add);
        printf("Parent's name: ");gets(stu.parname);
        printf("Class: ");scanf("%d",&stu.Class);
        printf("Phone Number: ");scanf("%ld",&stu.phone_no);
        fwrite(&stu, sizeof(stu), 1, fp);
        printf("The record is sucessfully added");
    }
    fclose(fp);
    return;
}

void search_student(){
    printf("\n");
    print_heading("\t\t--Search Record--\n");
    char s_id[15];
    int isFound = 0;
    printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(s_id,stu.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        printf("\n");
        printf("The record is Found\n");
        printf("ID: %s\n",stu.ID);
        printf("Name: %s\n",stu.name);
        printf("Address: %s\n",stu.add);
        printf("Parent's Name: %s\n",stu.parname);
        printf("Class: %d\n",stu.Class);
        printf("Phone No: %ld\n",stu.phone_no);
    }else{
        printf("\n");
        printf("Sory, No record found in the database");
    }
    fclose(fp);
    return;
}

void mod_student(){
    printf("\n");
    print_heading("\t\t--Modify Record--\n");
    char s_id[15];
    int isFound = 0, print = 37;
    printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){
            fflush(stdin);
            printf("ID: ");gets(stu.ID);
            printf("Name: ");gets(stu.name);
            printf("Address: ");gets(stu.add);
            printf("Parent's name: ");gets(stu.parname);
            printf("Class: ");scanf("%d",&stu.Class);
            printf("Phone Number: ");scanf("%ld",&stu.phone_no);
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        printf("\n");
        printf("No Record Found");
    }
    fclose(fp);
    return;
}

void gen_marksheet(){
    //left for further enhancement
}

void delete_student(){
    printf("\n");
    print_heading("\t\t--Delete Record--");
    char s_id[15];
    int isFound = 0, print = 37;
    printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){
            fwrite(&stu,sizeof(stu),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    printf("The record is sucessfully deleted");
    return;
}

void main_console(){
    char username[50],password[50],user[]="admin", pass[]="password";
    int choice;
    printf("Enter Username:");
    scanf("%s",&username);
    printf("\nEnter Password:");
    scanf("%s",&password);
    int x = 2;
    char tempPass[40];
if(strcmp(username,user)==0 && strcmp(password,pass)==0){
    while(1){
        printf("\t\t\t\t---STUDENT RECORD SYSTEM---\n");
        printf("\t1. Add Student\n");
        printf("\t2. Search Student\n");
        printf("\t3. Modify Student Record\n");
        printf("\t4. Delete Student Record\n");
        printf("\t5. Exit\n");
        printf("\tEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                mod_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                    exit(0);
            break;
            default:
                break;
        }

    }

}
}

int main(){
    
    //use_pass_field();
    main_console();
    return 0;
}