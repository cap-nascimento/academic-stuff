#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdlib.h>
#include "../doubly_linked_list/dlist.h"
#include "../binary_search_tree/bst.h"

typedef struct _student {

    int code;
    char name[60];
    char course[20];
    char subject[20];
    double miss;
    double grade;
    char rating[3];

} Student;

//function to allocate memory for a student register
void * constructor_student(void * data);
//function to liberate memory from a student register
void destructor_student(void * data);
//function to be used on the implementation of binary search tree
int comparator_student_code(const void * a, const void * b);
int comparator_student_grade(const void * a, const void * b);
//function to process (print) the required data of a student
void process_student(void * data);
//function to process (print) the data of unregistered students
void process_not_registered(void * data);
//function to show all data of a student
void show_student(Student student);
//function that separate the attributes of a student from the dataset
Student set_student(char * str_data);

//function to show data of not registered students
void list_not_registered(dlist_t* students_not_registered);
//function to add a new student into the tree
void add_student(dlist_t* students_not_registered, bst_t * students);
//function to remove a student from the tree
void remove_student(dlist_t* students_not_registered);
//function to show all students from a given subject
void list_students(char * subject_name, bst_t* students);
//function to set the grade of a student
void change_grade(char * subject_name, bst_t* students_subject, bst_t* students_registered);
//function to set the number of absenses of a student
void change_miss(char * subject_name, bst_t* students_subject, bst_t* students_registered);

#endif