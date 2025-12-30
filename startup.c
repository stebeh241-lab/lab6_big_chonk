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
    char personal_number[11];
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

void save_program(program_t program, progrecord_t *progrecord)
{
    //  Do we have enough capacity, if not we extend it and reallocate.
    if (progrecord->count >= progrecord->capacity)
    {
        if (progrecord->capacity == 0)
        {
            progrecord->capacity = 32;
        }
        else
        {
            progrecord->capacity *= 2;
        }
        progrecord->population = realloc(progrecord->population, progrecord->capacity * sizeof(program_t));
    }
    // Add student to the record.
    progrecord->population[progrecord->count + 1] = program;
    progrecord->count++;
}

int enter_gender()
{
    while (true)
    {
        printf("Enter student gender by entering 1-3:\n1. Male\n2. Femaile\n3. Other\n");
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

void print_program_names(progrecord_t *progrec)
{
    for (int i = 0; i < progrec->count; i++)
    {
        printf("%d", i);
        printf("%s\n", progrec->population[i].name);
    }
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
    printf("Enter student personal number (10 digits)\n");
    scanf("%10s", tempstud.personal_number);
    printf("Personal number added to new student.\n");
    printf("Enter student name\n");
    scanf(" %255[^\n]", tempstud.name);
    printf("Name added to new student.\n");
    tempstud.gender = enter_gender();
    printf("Gender added to new student.\n");
    printf("Enter student age\n");
    scanf(" %d", &tempstud.age);
    printf("Enter student email\n");
    printf("DEBUG: Adress till email är %p\n", (void *)tempstud.email);
    scanf("%255s", tempstud.email);
    printf("Pick student program by entering number 1-%ld\n", progrec->count);
    print_program_names(progrec);
    int pickedprogram = 0;
    scanf("%d", &pickedprogram);
    tempstud.programp = &progrec->population[pickedprogram];
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
    program_t maskintektik = {0};
    program_t jobbamedata = {0};
    save_program(maskintektik, &all_programs);
    save_program(jobbamedata, &all_programs);
    student_t tempstudent = (add_student(&all_programs));
    save_student(tempstudent, &all_students);
    print_program_record(&all_programs);
    print_student_record(&all_students);
    // program_t maskinteknik;
    // strncpy(maskinteknik.name, "Maskinteknik", sizeof(maskinteknik.name) - 1);
    // maskinteknik.code = 20230001;
    // strncpy(maskinteknik.responsible, "Jens Oakenshield", sizeof(maskinteknik.responsible) - 1);
    // strncpy(maskinteknik.email, "jensa@oru.se", sizeof(maskinteknik.email - 1));
    // save_program(maskinteknik, all_programs);
    // student_t student_1;
    // strncpy(student_1.personal_number, "8704166654", sizeof(student_1.personal_number -1));
    // strncpy(student_1.name, "Stefan Bergman", sizeof();
    // student_1.gender = male;
    // student_1.age = 38;
    // student_1.email = "superkingen@kingmail.com";
    // student_1.programp = &maskinteknik;
    // save_student(student_1, all_students);
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
