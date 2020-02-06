#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"
#include "student.h"

// static void find_and_modify_grade(bst_t * t, bst_node * root, Student st);

void * constructor_student(void * data) {
    void* ptr = (Student*)malloc(sizeof(Student));
    if(ptr == NULL) {
        printf("Memory allocation error!\n");
        printf("Exiting\n");
		exit(EXIT_FAILURE);
    }
    memcpy(ptr, data, sizeof(Student));
    return ptr;
}

void destructor_student(void* data) {
    free(data);
}

int comparator_student_grade(const void* a, const void *b) {
    Student A = *(Student*)a;
    Student B = *(Student*)b;
    if(A.grade < B.grade){
        return 1;
    }else if(A.grade > B.grade){
        return -1;
    }else{
        if(A.code > B.code){
            return 1;
        }else if(A.code < B.code){
            return -1;
        }
        return 0;
    }
    return 0;
}

int comparator_student_code(const void* a, const void* b){
    return (*(Student*)a).code - (*(Student*)b).code;
}

void process_not_registered(void * data) {
    Student student = *(Student*)data;
    printf("%-50s   %-10d   %-10s\n", 
        student.name, student.code,  student.course
    );
}

void show_student(Student student){
    printf("%9d   %s  %.2lf  %s  %s  %.2lf  %s\n", 
        student.code, student.name, student.miss,
        student.course, student.subject,
        student.grade, student.rating
    );
}

Student set_student(char * str_data){
    Student new_student;
    int not_registered = 0;
    int index = 0, i=0, k=0;
    for(i=0;str_data[i]!='\0' && !not_registered;i++){
        if(str_data[i] == ';' && str_data[i+1] == ';')
            not_registered = 1;
    }
    char curr_string[100];
    if(!not_registered){
        for(i=0;str_data[i] != '\0'; i++){
            if(str_data[i] == ';' || str_data[i+1] == '\0'){
                if(str_data[i+1] == '\0')
                    curr_string[k++] = str_data[i];
                curr_string[k] = '\0';
                k = 0;
                switch (index)
                {
                    case 0: strcpy(new_student.name, curr_string); break;
                    case 1: new_student.code = strtoint(curr_string); break;
                    case 2: strcpy(new_student.course, curr_string); break;
                    case 3: strcpy(new_student.subject, curr_string); break;
                    case 4: new_student.miss = strtodouble(curr_string); break;
                    case 5: new_student.grade = strtodouble(curr_string); break;
                    case 6: strcpy(new_student.rating, curr_string); break;
                    default: break;
                }
                index++;
            }else{
                curr_string[k++] = str_data[i];
            }
            
        }
    }else{
        strcpy(new_student.subject, "");
        new_student.miss = 0;
        new_student.grade = 0.0;
        strcpy(new_student.rating, "");
        for(i=0;str_data[i] != '\0';i++){
            if(str_data[i] == ';'){
                curr_string[k] = '\0';
                k=0;
                switch (index)
                {
                    case 0: strcpy(new_student.name, curr_string); break;
                    case 1: new_student.code = strtoint(curr_string); break;
                    case 2: strcpy(new_student.course, curr_string); break;
                    default: break;
                }
                if(str_data[i+1] == ';'){
                    break;
                }
                index++;
            }else{
                curr_string[k++] = str_data[i];
            }
        }
    }
    return new_student;
}

void list_not_registered(dlist_t* students_not_registered){
    system("clear");
    printf("%-50s | %-10s | %-5s\n", "Name", "Code", "Course");
    dlist_show_elements(students_not_registered);
    getchar();
    char c;
    printf("Press enter to go back. ");
    scanf("%c", &c);
    system("clear");
}
void add_student(dlist_t* students_not_registered, bst_t* students){
    system("clear");
    Student new_student;

    new_student.grade = .0;
    new_student.miss = .0;
    strcpy(new_student.rating, "");
    strcpy(new_student.subject, "");

    printf("Add student:\n");
    printf("Name: ");
    scanf("%s", new_student.name);
    printf("Code: ");
    scanf("%d", &new_student.code);
    printf("Course: ");
    scanf("%s", new_student.course);

    if(dlist_find(students_not_registered, &new_student) == -1 &&
        !bst_find(students, &new_student)){
        dlist_append(students_not_registered, &new_student);
        printf("New student on the blocks!\n");
    }else{
        printf("Something went wrong (code already exists).\n");
    }
    getchar();
    char c;
    printf("Press enter to go back. ");
    scanf("%c", &c);
    system("clear");
}
void remove_student(dlist_t* students_not_registered){
    system("clear");
    Student tmp;
    printf("Remove students:\n");
    printf("Code: ");
    scanf("%d", &tmp.code);
    int student_position = dlist_find(students_not_registered, &tmp);
    if(student_position != -1){
        dlist_remove(students_not_registered, student_position);
        printf("Successfully removed student with code %d\n", tmp.code);
    }else{
        printf("Something went wrong (This student doesn't exists on the list).\n");
    }
    getchar();
    char c;
    printf("Press enter to go back. ");
    scanf("%c", &c);
    system("clear");
}

void list_students(char * subject_name, bst_t * students) {
    system("clear");
    printf("%s Students\n", subject_name);
    printf("%-6s %-50s %-12s %-7s %-6s\n", "Code", "| Name", "| Absentions", "| Grade", "| Rating ");
    traverse_in_order_student(students->root);
    getchar();
    char c;
    printf("Press enter to go back. ");
    scanf("%c", &c);
    system("clear");
}

void process_student(void * data){
    Student student = *(Student*)data;
    printf("%-6d   %-50s %-12.2lf %-7.2lf %-6s\n", student.code, student.name, student.miss,student.grade, student.rating
    );
}

void change_grade(char * subject_name, bst_t* students_subject, bst_t* students_registered) {
    system("clear");
    printf("Change grade of a student from %s subject\n", subject_name);
    Student st;
    printf("Code: ");
    scanf("%d", &st.code);
    printf("Grade: ");
    scanf("%lf", &st.grade);
    if(bst_find(students_registered, &st)){
        Student extracted = *(Student*)bst_access(students_registered, students_registered->root, &st);
        if(strcmp(extracted.subject, subject_name) == 0){
            bst_remove(students_registered, &extracted);
            bst_remove(students_subject, &extracted);
            extracted.grade = st.grade;
            strcpy(extracted.rating, student_rating_calculator(st.grade));
            bst_insert(students_registered, &extracted);
            bst_insert(students_subject, &extracted);
            printf("Grade successfully changed! New rating of student with code %d: %s\n", extracted.code, extracted.rating);
        }else{
            printf("Something went wrong (this student doesn't exists on %s subject).\n", subject_name);
        }
    }else{
        printf("Something went wrong (tree of registered students error).\n");
    }
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}

// static void find_and_modify_grade(bst_t * t, bst_node * root, Student st){
//     if(root != NULL){
//         if(st.code == (*(Student*)root->data).code){
//             (*(Student*)root->data).grade = st.grade;
//             strcpy((*(Student*)root->data).rating, st.rating);
//             return;
//         }
//         find_and_modify_grade(t, root->left, st);
//         find_and_modify_grade(t, root->right, st);
//     }
// }

void change_miss(char * subject_name, bst_t* students_subject, bst_t* students_registered) {
    system("clear");
    printf("Change absentions of a student from %s subject\n", subject_name);
    Student st;
    printf("Code: ");
    scanf("%d", &st.code);
    printf("Absentions: ");
    scanf("%lf", &st.miss);
    if(bst_find(students_registered, &st)){
        Student extracted = *(Student*)bst_access(students_registered, students_registered->root, &st);
        if(strcmp(extracted.subject, subject_name) == 0){
            bst_remove(students_registered, &extracted);
            bst_remove(students_subject, &extracted);
            extracted.miss = st.miss;
            if(extracted.miss > 0.25) {
                strcpy(extracted.rating, "SR");
            }else{
                strcpy(extracted.rating,student_rating_calculator(extracted.grade));
            }
            bst_insert(students_registered, &extracted);
            bst_insert(students_subject, &extracted);
            printf("Absentions of student with code %d successfully changed!\n", extracted.code);
        }else{
            printf("Something went wrong (this student doesn't exists on %s subject).\n", subject_name);
        }
    }else{
        printf("Something went wrong (tree of registered students error).\n");
    }
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}