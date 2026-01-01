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
    program_t **population;
    size_t count;
    size_t capacity;
} progrecord_t;

const char *gender_as_text(gender gender)
{
    switch (gender)
    {
    case male:
        return "male";
    case female:
        return "female";
    case other:
        return "other";
    default:
        return "unknown";
    }
}

void print_student(student_t *stud)
{
    printf("Personal number: %s\nName: %s\nGender: %s\nAge: %d\nemail: %s\nProgram: %s\n",
           stud->personal_number, stud->name, gender_as_text(stud->gender), stud->age, stud->email, stud->programp->name);
}

void print_student_record(studrecord_t *studrecord)
{
    for (int i = 0; i < studrecord->count; i++)
    {
        print_student(&studrecord->population[i]);
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
        printf("%d. ", i);
        printf("%s\n", progrec->population[i]->name);
    }
}

void print_program_record(progrecord_t *progrec)
{
    for (int i = 0; i < progrec->count; i++)
    {
        printf("%d", i);
        print_program(progrec->population[i]);
    }
}

void save_student(student_t student, studrecord_t *studrecord)
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
    studrecord->population[studrecord->count] = student;
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
        // Reallocates the array of pointers
        progrecord->population = realloc(progrecord->population, progrecord->capacity * sizeof(program_t *));
    }
    // The new program gets a fixed place in memory that will not move
    program_t *new_program = malloc(sizeof(program_t));
    *new_program = program;
    // Add new program to the record and incrementing count
    progrecord->population[progrecord->count] = new_program;
    progrecord->count++;
}

int enter_gender()
{
    while (true)
    {
        printf("Enter student gender by entering 1-3:\n1. Male\n2. Femaile\n3. Other\n");
        int sexadded = 0;
        scanf(" %d", &sexadded);
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

int enter_program_code(progrecord_t *progrec) // denna används inte nu men kanske behöver nått liknande senare?
{
    while (true)
    {
        printf("Enter student program code (8 digits)\n");
        int tempcode = 0;
        scanf(" %8d", &tempcode);
        for (int i = 0; i < progrec->count; i++)
        {
            if (tempcode == progrec->population[i]->code)
            {
                return tempcode;
            } // Sök och kolla så att denna programkod finns
        }
        printf("No such program exists, try again.\n");
    }
}

program_t *pick_student_program(progrecord_t *progrec)
{
    while (true)
    {
        printf("Pick student program by entering number 0-%ld\n", progrec->count - 1);
        print_program_names(progrec);
        int pickedprogram = -1;
        scanf(" %d", &pickedprogram);
        if (pickedprogram >= 0 && pickedprogram < progrec->count)
        {
            return progrec->population[pickedprogram];
        }
        else
        {
            printf("Not a valid choice, try again.\n");
        }
    }
}

student_t add_student(progrecord_t *progrec)
{
    student_t tempstud = {0};
    printf("Enter student personal number (10 digits)\n");
    scanf(" %10s", tempstud.personal_number); // kan användaren skriva mer än 10 om det är %10s?
    while (getchar() != '\n')
        ;
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
    scanf(" %255s", tempstud.email);
    tempstud.programp = pick_student_program(progrec);
    return tempstud;
}

program_t add_program()
{
    program_t tempprog = {0};
    printf("Enter program name\n");
    scanf(" %63[^\n]", tempprog.name);
    printf("Name added to new program.\n");
    printf("Enter program code (8 digits, starts with year it was created, ex 2025)\n");
    scanf(" %d", &tempprog.code);
    printf("Code added to new program.\n");
    printf("Enter person responsible for program\n");
    scanf(" %255[^\n]", tempprog.responsible);
    printf("Responsible person added to new program.\n");
    printf("Enter program email\n");
    scanf(" %255[^\n]", tempprog.email);
    printf("email added to new program.\n");
    return tempprog;
}

student_t *search_student_personal_nr(char *searchstring, studrecord_t *studrec)
{
    // Loop through student record and returns pointer to student if personal number matches.
    for (int i = 0; i < studrec->count; i++)
    {
        if (strcmp(studrec->population[i].personal_number, searchstring) == 0)
        {
            return &studrec->population[i];
        }
    }
    return NULL;
}

void modify_student(student_t *student, studrecord_t *studrec, progrecord_t *progrec)
{
    printf("Enter student personal number (10 digits)\n");
    scanf(" %10s", student->personal_number); // kan användaren skriva mer än 10 om det är %10s?
    while (getchar() != '\n')
        ;
    printf("Personal number changed for student.\n");
    printf("Enter student name\n");
    scanf(" %255[^\n]", student->name);
    printf("Name changed for student.\n");
    student->gender = enter_gender();
    printf("Gender changed for student.\n");
    printf("Enter student age\n");
    scanf(" %d", &student->age);
    printf("Age changed for student.\n");
    printf("Enter student email\n");
    printf("DEBUG: Adress till email är %p\n", (void *)&student->email);
    scanf(" %255s", student->email);
    student->programp = pick_student_program(progrec);
    printf("email changed for student.\n");
    printf("Student sucessfully edited\n");
}

program_t *search_program(int searchcode, progrecord_t *progrec)
{
    for (int i = 0; i < progrec->count; i++)
    {
        if (progrec->population[i]->code == searchcode)
        {
            return progrec->population[i];
        }
    }
    return NULL;
}

void modify_program(program_t *program, progrecord_t *progrec)
{
    printf("Enter new program name\n");
    scanf(" %63[^\n]", program->name);
    printf("Name changed.\n");
    printf("Enter program code (8 digits, starts with year it was created, ex 2025)\n");
    scanf(" %d", &program->code);
    printf("Code changed.\n");
    printf("Enter person responsible for program\n");
    scanf(" %255[^\n]", program->responsible);
    printf("Responsible person changed.\n");
    printf("Enter program email\n");
    scanf(" %255[^\n]", program->email);
    printf("email changed.\n");
    printf("Program sucessfully edited\n");
}

void clean_up(progrecord_t *progrec, studrecord_t *studrec)
{
    for (size_t i = 0; i < progrec->count; i++)
    {
        free(progrec->population[i]); // Free memory from every malloc that create_program did.
    }
    free(progrec->population);
    free(studrec->population);
}

void save_to_file(char *filename, progrecord_t *progrec, studrecord_t *studrec)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file in read_file");
        return;
    }
    for (int i = 0; i < progrec->count; i++)
    {
        fprintf(fp, "program\n");
        fprintf(fp, "%s\n", progrec->population[i]->name);
        fprintf(fp, "%d\n", progrec->population[i]->code);
        fprintf(fp, "%s\n", progrec->population[i]->responsible);
        fprintf(fp, "%s\n", progrec->population[i]->email);
    }
    for (int i = 0; i > studrec->count; i++)
    {
        fprintf(fp, "student\n");
        fprintf(fp, "%s\n", studrec->population[i].personal_number);
        fprintf(fp, "%s\n", studrec->population[i].name);
        fprintf(fp, "%d\n", studrec->population[i].gender);
        fprintf(fp, "%d\n", studrec->population[i].age);
        fprintf(fp, "%s\n", studrec->population[i].email);
        fprintf(fp, "%d\n", studrec->population[i].programp->code);
    }
}

void read_from_file(char *filename, progrecord_t *progrec, studrecord_t *studrec)
{
    progrecord_t all_programs;
    studrecord_t all_students;
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file in read_file");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        buffer[strcspn(buffer, "\n")] = 0;  // Just removes the \n
        if (strcmp(buffer, "program") == 0) // Is difference between buffer and "program" 0?
        {
            program_t tmp_prog = {0};
            fgets(tmp_prog.name, 64, fp);
            tmp_prog.name[strcspn(tmp_prog.name, "\n")] = 0;
            fgets(tmp_prog.name, 64, fp);
            tmp_prog.name[strcspn(tmp_prog.name, "\n")] = 0;
            fgets(buffer, sizeof(buffer), fp);
            tmp_prog.code = atoi(buffer);
            fgets(tmp_prog.responsible, 256, fp);
            tmp_prog.responsible[strcspn(tmp_prog.responsible, "\n")] = 0;
            fgets(tmp_prog.email, 256, fp);
            tmp_prog.email[strcspn(tmp_prog.email, "\n")] = 0;
            save_program(tmp_prog, progrec);
        }
        else if (strcmp(buffer, "student") == 0)
        {
            student_t tmp_stud = {0};
            int progcode;
            fgets(tmp_stud.personal_number, 11, fp);
            tmp_stud.personal_number[strcspn(tmp_stud.personal_number, "\n")] = 0;
            fgets(tmp_stud.name, 256, fp);
            tmp_stud.name[strcspn(tmp_stud.name, "\n")] = 0;
            fgets(buffer, sizeof(buffer), fp);
            tmp_stud.gender = atoi(buffer);
            fgets(buffer, sizeof(buffer), fp);
            tmp_stud.age = atoi(buffer);
            fgets(tmp_stud.email, 256, fp);
            tmp_stud.email[strcspn(tmp_stud.email, "\n")] = 0;
            fgets(buffer, sizeof(buffer), fp);
            progcode = atoi(buffer);

            tmp_stud.programp = search_program(progcode, progrec); // looks up what program code relates to and points to is.
            save_student(tmp_stud, studrec);
        }
    }
}

void search_student_by_name(char *searchstring, studrecord_t *studrec)
{
    for (int i = 0; i < studrec->count; i++)
    {
        char *found = strstr(studrec->population[i].name, searchstring);
        if (found != 0)
        {
            printf("%s", found);
        }
    }
}

void search_student_by_program(int progcode, studrecord_t *studrec)
{
    for (int i = 0; i < studrec->count; i++)
    {
        if (studrec->population[i].programp->code == progcode)
        {
            printf("%s", studrec->population[i].name);
        }
    }
}

int main_prompt()
{
    printf("Choose action:\n");
    printf("1. Add student      (load record first if you want to add to existing record)\n");
    printf("2. Modify student   (load record first to have something to modify)\n");
    printf("3. Delete student\n");
    printf("4. Search student(s) or display statistics about current record\n");
    printf("5. Save current record to file\n");
    printf("6. Load record      (currently loaded record will be lost)\n");
    printf("7. Add program      (load record first if you want to add to existing record\n");
    printf("8. Modify program   (load record first to have something to modify\n");
    printf("9. Exit             (load record first to have something to modify\n");
    int choice = -1;
    scanf("%d", &choice);
    return choice;
}

int search_prompt()
{
    printf("Choose action:\n");
    printf("1. Search student by personal number");
    printf("2. Search student(s) by name\n");
    printf("3. Search student(s) by program\n");
    printf("4. Show statistics of current record\n");
    int choice = -1;
    scanf("%d", &choice);
    return choice;
}

void main()
{
    progrecord_t all_programs = {0};
    studrecord_t all_students = {0};
    int choice = -1;
    while (true)
    {
        choice = (main_prompt);
    }
}
// strstr
//  program_t maskintektik = {0};
//  strncpy(maskintektik.name, "Maskinteknik", sizeof(maskintektik.name) - 1);
//  program_t jobbamedata = {0};
//  save_program(maskintektik, &all_programs);
//  save_program(jobbamedata, &all_programs);
//  student_t tempstudent = (add_student(&all_programs));
//  save_student(tempstudent, &all_students);
//  printf("*****************************\nPRINTING PROGRAM RECORD\n*****************************\n");
//  print_program_record(&all_programs);
//  printf("*****************************\nPRINTING STUDENT RECORD\n*****************************\n");
//  print_student_record(&all_students);
//  clean_up(&all_programs, &all_students);
//  funk add
//   print
//   save
//   funk sök
//   sscanf personnummer
//   funk modify
//   sscanf personnummer
//   funk save
//   skapa fil och skriv till den
//   funk load database
//   confirmation on load
//   reads file to memory in form of structs
