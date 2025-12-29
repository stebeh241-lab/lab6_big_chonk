#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum gender
{
    male,
    female,
    other
} gender;

typedef struct program
{
    char name[64];
    int code;
    char responsible[256];
    char email[256];
} program;

typedef struct student
{
    char personal_number[10];
    char name[256];
    gender gender;
    int age;
    char email[256];
    program *programp;
} student;

typedef struct studrecord
{
    student *population;
    size_t count;
    size_t capacity;
} studrecord;

typedef struct progrecord
{
    program *population;
    size_t count;
    size_t capacity;
} progrecord;

void save_student(student stud, studrecord *studrecord)
{
    //  Do we have enough capacity, if not we extend it and reallocate.
    if (studrecord->count >= studrecord->capacity)
    {
        if (studrecord->capacity == 0)
        {
            studrecord->capacity = 32;
        }
        else
        {
            studrecord->capacity *= 2;
        }
        studrecord->population = realloc(studrecord->population, studrecord->capacity * sizeof(student));
    }
    // Add person to the array.
    studrecord->population[studrecord->count + 1] = stud;
    studrecord->count++;
}

int enter_gender()
{
    while (true)
    {
        printf("Enter student gender by entering 1-3:\n 1. Male\n2. Femaile\n3. Other");
        int sexadded = 0;
        scanf("%d", &sexadded);
        if (sexadded == 1)
        {
            return male;
        }
        else if (sexadded == 2)
        {
            return female;
        }
        else if (sexadded == 3)
        {
            return other;
        }
        else
        {
            printf("incorrect choice, try again.\n");
        }
    }
}

int enter_program_code(progrecord progrec)
{
    while (true)
    {
        printf("Enter student program code (8 digits)\n");
        int tempcode = 0;
        scanf("%8d", &tempcode);
        for (int i = 0; i < progrec.count; i++)
        {
            if (tempcode == progrec.population[i].code)
            {
                return tempcode;
            } // Sök och kolla så att denna programkod finns
        }
        else
        {
            prinf("No such program exists, try again.")
        }
    }
}

student add_student()
{
    student tempstud = {0};
    char number[11];
    scanf("%10s", number);
    printf("Personal number added to new student.\n");
    printf("Enter student name\n");
    scanf(" %255[^\n]", tempstud.name);
    printf("Name added to new student.\n");
    tempstud.gender = enter_gender();
    printf("Gender added to new student.\n");
    printf("Enter student age\n");
    scanf("%3d", &tempstud.age);
    printf("Enter student email\n");
    scanf("%255s", tempstud.email);
    tempstud.programp->code = enter_program_code();
}

void main()
{
    add_student();
}
// funk add
//  print
//  save
//  funk sök
//  sscanf personnummer
//  funk modify
//  sscanf personnummer
//  funk save
//  skapa fil och skriv till den
//  funk load database
//  confirmation on load
//  reads file to memory in form of structs
