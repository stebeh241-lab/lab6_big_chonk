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

typedef struct program_t
{
    char name[64];
    int code;
    char responsible[256];
    char email[256];
} program_t;

typedef struct student_t
{
    char personal_number[10];
    char name[256];
    gender gender;
    int age;
    char email[256];
    program_t *programp;
} student_t;

typedef struct studrecord_t
{
    student_t *population;
    size_t count;
    size_t capacity;
} studrecord_t;

typedef struct progrecord_t
{
    program_t *population;
    size_t count;
    size_t capacity;
} progrecord_t;

void print_student(student_t *stud)
{
    printf("Personal number: %s\nName: %s\nGender: %d\nAge: %d\nemail: %s\nProgram: %d\n",
           stud->personal_number, stud->name, stud->gender, stud->age, stud->email, stud->programp->code);
}

void print_student_record(studrecord_t *studrecord)
{
    for (int i = 0; i < studrecord->count; i++)
    {
        print_student(studrecord->population + 1);
    }
}

void save_student(student_t stud, studrecord_t *studrecord)
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
        studrecord->population = realloc(studrecord->population, studrecord->capacity * sizeof(student_t));
    }
    // Add student to the record.
    studrecord->population[studrecord->count + 1] = stud;
    studrecord->count++;
}

int enter_gender()
{
    while (true)
    {
        printf("Enter student gender by entering 1-3:\n 1. Male\n2. Femaile\n3. Other\n");
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

int enter_program_code(progrecord_t *progrec)
{
    while (true)
    {
        printf("Enter student program code (8 digits)\n");
        int tempcode = 0;
        scanf("%8d", &tempcode);
        for (int i = 0; i < progrec->count; i++)
        {
            if (tempcode == progrec->population[i].code)
            {
                return tempcode;
            } // Sök och kolla så att denna programkod finns
        }
        printf("No such program exists, try again.\n");
    }
}

void print_program(program_t *prog)
{
    printf("Name: %s \nCode: %d \nResponsible: %s\nemail: %s\n",
           prog->name, prog->code, prog->responsible, prog->email);
}

void print_program_name(program_t *prog)
{
}

void print_program_record(progrecord_t *progrec)
{
    for (int i = 0; i < progrec->count; i++)
    {
        printf("%d", i);
        print_program(progrec->population + i);
    }
}

student_t add_student(progrecord_t *progrec)
{
    student_t tempstud = {0};
    scanf("%10s", tempstud.personal_number);
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
    tempstud.programp = &(enter_program_code(progrec)); // FIXA DETTA POINTERCRAP VÄLJ FRÅN LISTA ISTÄLLET.
    return tempstud;
}

program_t add_program()
{
    program_t tempprog = {0};
}

void main()
{
    progrecord_t all_programs = {0};
    studrecord_t all_students = {0};
    add_program();
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
