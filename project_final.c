#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

typedef struct
{
  char name[20];
  char mail[30];
  long int mobile;
} PROFESSOR;

typedef struct
{
  char name[20];
  char address[50];
  char schoolstat[10];
  int scholarship;
  char abroad[10];
  long int phone;
  int age;
  int ID;
  float cgpa;
} STUDENT;

typedef struct
{
  char type;
  union
  {
    PROFESSOR prof;
    STUDENT stu;
  } u;
} PERSON;

int main()
{
  int MAX_NUMBER_OF_STUDENTS = 6;

  FILE *infile, *ofp;
  PERSON data[MAX_NUMBER_OF_STUDENTS];

  // Read Files
  infile = fopen("inputfile.txt", "r");
  if (infile == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit(1);
  }
  ofp = fopen("outputfile.txt", "w");
  if (ofp == NULL)
  {
    printf("\nOutput file open error!\n");
    return 1;
  }


  data[0] = (PERSON){
      .type = 'p',
      .u.prof.name = "Sam",
      .u.prof.mail = "ssss@mail.com",
	  .u.prof.mobile = 88003334545};


  for (int i = 1; i < MAX_NUMBER_OF_STUDENTS; i++)
  {
    data[i] = (PERSON){.type = 'n', .u.stu = (STUDENT){0}, .u.prof = (PROFESSOR){0}};
  }

  int i = 1; 
  int total = 0;
  int total_age = 0;


  while (fscanf(
			 infile,
             "%s %d %d %d %s %s %15[^\n] %ld %f\n",
             data[i].u.stu.name,
             &data[i].u.stu.ID,
             &data[i].u.stu.age,
             &data[i].u.stu.scholarship,
             data[i].u.stu.schoolstat,
             data[i].u.stu.abroad,
             data[i].u.stu.address,
             &data[i].u.stu.phone,
             &data[i].u.stu.cgpa) != EOF &&
         i != MAX_NUMBER_OF_STUDENTS)
  {
    
    data[i].type = 's';

    // printf("\n[DEBUG] name = %s", data[i].u.stu.name);
    total += data[i].u.stu.cgpa;
    total_age += data[i].u.stu.age;
    // printf("\n[DEBUG] total = %d", total);
    // printf("\n[DEBUG] total age = %d\n", total_age);

    // save
    fprintf(ofp, "%d %s %d %d %s %s %s %ld %f\n",
            data[i].u.stu.ID,
            data[i].u.stu.name,
            data[i].u.stu.age,
            data[i].u.stu.scholarship,
            data[i].u.stu.schoolstat,
            data[i].u.stu.abroad,
            data[i].u.stu.address,
            data[i].u.stu.phone,
            data[i].u.stu.cgpa);

    i++;
  }

	printf("Student: \tName\tAge\tID\t Scholarship InSchool Abroad Address\t\tPhone\tCGPA");
  for (int i = 0; i < MAX_NUMBER_OF_STUDENTS; i++)
  {
	if (data[i].type == 'p')
    {
      printf("\n\nProfessor: %s,\n%s, %ld\n\n",
             data[i].u.prof.name,
             data[i].u.prof.mail,
             data[i].u.prof.mobile);
    }
    else if (data[i].type == 's')
    {
	  printf("Student: \t%s \t%d \t%d \t%d \t%s \t%s \t%s \t%ld \t%f\n\n",
             data[i].u.stu.name,
             data[i].u.stu.age,
             data[i].u.stu.ID,
             data[i].u.stu.scholarship,
             data[i].u.stu.schoolstat,
             data[i].u.stu.abroad,
             data[i].u.stu.address,
             data[i].u.stu.phone,
             data[i].u.stu.cgpa);
    }
    else
    {
      // do nothing
    }
  }

	int menu;
	printf("menu:\n1. Count the lines.\n2. Total cgpa\n3. Average age\n4.Find a phone number by name from the list\n5. Exit\n");
	printf("enter the menu number: ");
	scanf("%d", &menu);
	if(menu==1){
		printf("\nNumber of lines: %d\n", i);
		fprintf(ofp, "\nNumber of lines: %d\n", i);
	}
	else if(menu==2){
		printf("Total value of cgpa: %d", total);
		fprintf(ofp, "Total value of cgpa: %d", total);
	}
	else if(menu==3){
		printf("Average age: %.2f", (float)total_age/(i-1));
		fprintf(ofp, "Average age: %.2f", (float)total_age/(i-1));
	}
	else if(menu==4){
		//int numStudents=MAX_NUMBER_OF_STUDENTS;
    	//STUDENT* students = malloc(numStudents * sizeof *students);
    	//for (int i= 0; i < numStudents; i++)
   		// {
        //	students[i].age=(char*)malloc(sizeof(char*));
    	//}
    	char name[6];
    	printf("name? ");
    	scanf("%s", &name);
    	int index=-1;
    	for(i=0;i<6;i++){
    		if(strcmp(data[i].u.stu.name, name)==0){
    			index=i;
    			break;
			}
		
		}
		if(index>=0){
			printf("%s's phone number: %d", data[index].u.stu.name, data[index].u.stu.phone);
			fprintf(ofp, "%s's phone number: %d", data[index].u.stu.name, data[index].u.stu.phone);
		}
		else{
			printf("did not find.\n");
		}
	}
	else if(menu==5){
		exit(1);
	}
  // Close Files
  fclose(infile);
  fclose(ofp);

  return 0;
}


