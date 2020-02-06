#include <stdio.h>
#include <stdlib.h>
#include "../subject/subject.h"

void menu_general(size_t not_registered){
    printf("Hello Professor,\n");
    printf("%d students haven't registered yet.\n", (int)not_registered);
    printf("What you want to do:\n");
    printf("1. List subjects;\n");
    printf("2. Add subject;\n");
    printf("3. Remove subject;\n");
    printf("4. List students without register;\n");
    printf("5. Add student;\n");
    printf("6. Remove student;\n");
    printf("7. Register a student in subject;\n");
    printf("8. Manage subject;\n");
    printf("9. Save modifications;\n");
    printf("10. Exit;\n");
    printf("Type an option: ");
}
void menu_subject(char * subject_name, void* data){
    printf("Managing %s\n", subject_name);
    printf("Student count: %d\n", (int)(*(Subject*)data).students->size);
    printf("Options:\n");
    printf("1. List students;\n");
    printf("2. Remove student from subject;\n");
    printf("3. Set grade;\n");
    printf("4. Set missed classes;\n");
    printf("5. Overall dashboard;\n");
    printf("6. Back;\n");
    printf("Type an option: ");
}