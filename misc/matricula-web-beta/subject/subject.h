#ifndef SUBJECT_H_INCLUDED
#define SUBJECT_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "../binary_search_tree/bst.h"
#include "../doubly_linked_list/dlist.h"
#include "../student/student.h"
#include "../utils/utils.h"

/*Here is the tricky part of the program. The idea is to
mantain a binary search tree of binary search trees.*/
typedef struct _subject{
    char name[20];
    bst_t * students;
}Subject;

/*
This is a structure created only to help
on the processing of a subject.
*/
typedef struct _course{
    char name[20];
    int approved;
    int repproved;
    int ss;
    int ms;
    int mm;
    int mi;
    int ii;
    int sr;
}Course;

/*
Function to allocated memory to a course structure.
*/
void* course_constructor(void* data);

/*
Function to liberate memory from a course structure.
*/
void course_destructor(void* data);

/*
Function to be used on the binary search tree. The comparator
uses the name of the subject as the key to do the comparisons.
*/
int subject_comparator(const void * a, const void * b);

/*
Function to allocate memory to a subject structure.
*/
void* subject_constructor(void* data);

/*
Function to liberate memory from a subject structure.
*/
void subject_destructor(void* data);

/*
Function to create a instance of the subject structure.
This function is used only on the beginning of the program,
because the initial information of a subject is on a student
register.
*/
Subject set_subject(Student st);

/*
This function is used after the traversal made on
the binary search tree of the subject node. It inserts
a node with the information about a student on the
bst.
*/
void register_student(void* data_sub, void* data_stu);

/*
This function is used after the traversal made on
the binary search tree of the subject node. It takes the
data of all nodes on the bst and inserts on a doubly linked
list.
*/
void extract_student(void* data_sub, dlist_t* l);

/*
Function to show the basic data of a subject. It is used
during the traversal of the binary search tree of 
subjects.
*/
void process_subject(void* data);

/*
Function to help on the processing of the subjects data.
It calls the traversal of the subject's binary search tree.
*/
void list_subjects(bst_t * subjects);

/*
Function to insert a subject on the subject's binary search tree.
*/
void add_subject(bst_t * subjects);

/*
Function to include a student without a register on subjects.
It takes a student from the doubly linked list and insert the
data with the subject information updated on the binary search tree
of the subject.
*/
void include_student(bst_t* students_registered, bst_t * subjects, dlist_t * not_registered);

/*
Function to remove a subject from the subject's binary search tree
by name.
*/
void remove_subject(bst_t * subjects, bst_t * students_registered, dlist_t * students_not_registered);

/*
Function to remove a student from a subject. It takes the student from
the binary search tree of a subject and stores the student with the
information updated (without subject) on the doubly linked list.
*/
void remove_student_subject(char * subject_name, bst_t* students_subject, bst_t* students_registered, dlist_t* students_not_registered);

/*
Function to process the information of a subject.
*/
void show_overall_dashboard(char * subject_name, bst_t* students_subject);

/*
Function to save the modifications during the execution of the program
on a .txt file.
*/
void save_modifications(bst_t* t, dlist_t* l);

#endif