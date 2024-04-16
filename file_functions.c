/* Student Management System Proto-type in C Using File Functions */
/* Compiler Used: Dev C++ (Windows) */
/* Header Files */
#include<stdio.h>
#include<stdlib.h>

/* Student Structure */
typedef struct student
{
	int roll;
	char name[100];
}student;

/* Global Variables */
FILE *fp, *ft;
char ch, *fname="students.txt"; // change name of this file according to your need. This is your db file.

/* User-defined functions */
void table_head() // to use heading for Tabular representation of data
{
	printf("\n Roll \t Name");
	printf("\n------------------------------------------------------");
}
void update_files() // to remove existing file and renaming temporary file
{
	remove(fname);
	rename("temp.txt", fname);
}
int get_roll_number() // getting next roll number for new student
{
	student s;
	s.roll = 0;
	fp = fopen(fname, "r");
	if(fp!=NULL)
		while(fread(&s, sizeof(s), 1, fp));
	fclose(fp);
	return s.roll+1;
}
void insert_student(struct student s) 
{
	fp = fopen(fname, "a");
	if(fp!=NULL) 
		fwrite(&s, sizeof(s), 1, fp);
	fclose(fp);
	printf("\n 1 student created.");
}
void show_students()
{
	student s;
	fp = fopen(fname, "r");
	if(fp==NULL) printf("\n %s not found.", fname);
	else
	{
		printf("\n Showing Students");
		table_head();
		while(fread(&s, sizeof(s), 1, fp))
		{
			printf("\n %d \t %s", s.roll, s.name);
		}
	}
	fclose(fp);
}
int search_student(int roll)
{
	student s;
	int flag=0;
	fp = fopen(fname, "r");
	if(fp==NULL) printf("\n %s not found.", fname);
	else
	{
		while(fread(&s, sizeof(s), 1, fp))
		{
			if(s.roll==roll)
			{
				flag = 1;
				break;
			}
		}
	}
	fclose(fp);
	return flag;
}
void get_student(int roll)
{
	student s;
	fp = fopen(fname, "r");
	table_head();
	while(fread(&s, sizeof(s), 1, fp))
	{
		if(s.roll==roll)
			printf("\n %d \t %s", s.roll, s.name);
	}
	fclose(fp);
}
void update_student(student t)
{
	student s;
	fp = fopen(fname,"r");
	ft = fopen("temp.txt","w");
	if(ft==NULL) printf("\n Could not create temporary file.");
	else
	{
		while(fread(&s, sizeof(s), 1, fp))
		{
			if(s.roll!=t.roll) 
				fwrite(&s, sizeof(s), 1, ft);
			else 
				fwrite(&t, sizeof(t), 1, ft);
		}
	}
	fclose(fp);
	fclose(ft);
	update_files();
	printf("\n 1 record updated.");
}
void delete_student(student t)
{
	student s;
	fp = fopen(fname,"r");
	ft = fopen("temp.txt","w");
	if(ft==NULL) printf("\n Could not create temporary file.");
	else
	{
		while(fread(&s, sizeof(s), 1, fp))
		{
			if(s.roll!=t.roll) 
				fwrite(&s, sizeof(s), 1, ft);
		}
	}
	fclose(fp);
	fclose(ft);
	update_files();
	printf("\n 1 record deleted.");
}
int main()
{
	int choice, roll;
	student s;
	while(1)
	{
		system("cls");
		printf("\n Student CRUD");
		printf("\n Menu: 1. Create Student 2. Read Students 3. Search Student 4. Update Student 5. Delete Student 0. Exit");
		printf("\n Enter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				s.roll = get_roll_number();
				printf("\n Enter name: ");
				fflush(stdin);
				gets(s.name);
				insert_student(s);
				break;	
			case 2:
				show_students();
				break;
			case 3:
				printf("\n Enter roll number to search: ");
				scanf("%d", &roll);
				if(search_student(roll)==1) get_student(roll);
				else printf("\n Student not found.");
				break;
			case 4:
				printf("\n Enter roll number to update: ");
				scanf("%d", &s.roll);
				if(search_student(s.roll)==1) 
				{	
					printf("\n Old Data: ");
					get_student(s.roll);
					printf("\n Enter new name: ");
					fflush(stdin)	;
					gets(s.name);
					update_student(s);
				}
				else printf("\n This roll number does not exist.");
				break;
			case 5:
				printf("\n Enter roll number to delete: ");
				scanf("%d", &s.roll);
				if(search_student(s.roll)==1) 
					delete_student(s);
				else printf("\n This roll number does not exist.");
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("\n Wrong choice...");
		}
		printf("\n Enter any key to continue...");
		getch();
	}
}
