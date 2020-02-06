/******** Matricula Web Beta ********************
 * by:                                          *
 *  Anderson Vieira do Nascimento - 19/0102322  *
 *  Felipe da Graça Costa         - 17/0141667  *
 ************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils.h"
#include "ui/user_interface.h"
#include "binary_search_tree/bst.h"
#include "doubly_linked_list/dlist.h"
#include "student/student.h"
#include "subject/subject.h"

int main(int argc, char * argv[]){

    //show greetings and check the input file
    greetings();
    if(!verify_file(argc, argv)){
        exit(EXIT_FAILURE);
    }
    
    //Read File
    FILE * arq = get_file(strcat(argv[1], ".txt"));
    char * content = read_file(arq);

    printf("OK!\n");

    //Create and initialize data structures
    bst_t * students_registered;
    dlist_t* students_not_registered;
    bst_t * subjects;
    bst_initialize(&students_registered, constructor_student, destructor_student, comparator_student_code);
    dlist_initialize(&students_not_registered, constructor_student, destructor_student);
    bst_initialize(&subjects, subject_constructor, subject_destructor, subject_comparator);

    //Fill the data structures
    char * ptr = strtok(content, "\n");
    while(ptr != NULL){
        Student st = set_student(ptr);
        //Set SR rating case the number of absenses is more than 25 percent
        if(st.miss > 0.25) {
            strcpy(st.rating, "SR");
        }
        //if the subject have a grade, add in bst students_registered
        if(strcmp(st.rating, "") != 0){ 
            bst_insert(students_registered, &st);
            Subject sj = set_subject(st);
            //add students in subject tree
            if(bst_find(subjects, &sj)){
                bst_access_modify_subject(subjects, subjects->root, &sj, &st);
            }else{
                bst_initialize(&(sj.students), constructor_student, destructor_student, comparator_student_grade);
                bst_insert(sj.students, &st);
                bst_insert(subjects, &sj);
            }
        }
        else{
            //Add not registered students in a list
            dlist_append(students_not_registered, &st);
        }
        ptr = strtok(NULL, "\n");
    }

    //show the menus and wait a user entry
    menu_general(students_not_registered->size);
    int option;
    Subject sj;
    while(scanf("%d", &option) && option != 10){
        switch(option){
            case 1:
                list_subjects(subjects);
                break;
            case 2:
                getchar();
                add_subject(subjects);
                break;
            case 3:
                getchar();
                remove_subject(subjects, students_registered, students_not_registered);
                break;
            case 4:
                list_not_registered(students_not_registered);
                break;
            case 5:
                getchar();
                add_student(students_not_registered, students_registered);
                break;
            case 6:
                remove_student(students_not_registered);
                break;
            case 7:
                include_student(students_registered, subjects, students_not_registered);
                break;
            case 8:
                system("clear");
                getchar();
                printf("Manage subject: ");
                while(scanf("%s", sj.name) && !bst_find(subjects, &sj.name)){
                    printf("Invalid subject name!\nManage subject: ");
                }
                system("clear");
                menu_subject(sj.name, bst_access(subjects, subjects->root, &sj));
                while(scanf("%d", &option) && option!=6){
                    switch(option){
                        case 1:
                            list_students(sj.name, (*(Subject*)bst_access(subjects, subjects->root, &sj)).students);
                            break;
                        case 2:
                            remove_student_subject(sj.name, (*(Subject*)bst_access(subjects, subjects->root, &sj)).students, students_registered, students_not_registered);
                            break;
                        case 3:
                            change_grade(sj.name, (*(Subject*)bst_access(subjects, subjects->root, &sj)).students, students_registered);
                            break;
                        case 4:
                            change_miss(sj.name, (*(Subject*)bst_access(subjects, subjects->root, &sj)).students, students_registered);
                            break;
                        case 5:
                            show_overall_dashboard(sj.name, (*(Subject*)bst_access(subjects, subjects->root, &sj)).students);
                            break;
                        default:
                            printf("Invalid option!\n");
                            break;
                    }
                    menu_subject(sj.name, bst_access(subjects, subjects->root, &sj));
                }
                system("clear");
                break;
            case 9:
                save_modifications(students_registered, students_not_registered);
                system("clear");
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
        menu_general(students_not_registered->size);
    }

    //Free the data structures
    free(content);
    bst_delete(&subjects);
    bst_delete(&students_registered);
    dlist_delete(&students_not_registered);

    return 0;
}