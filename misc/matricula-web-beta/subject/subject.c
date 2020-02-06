#include <stdio.h>
#include "subject.h"

static void extract_student_helper(bst_node* root, dlist_t * l);
static Course set_course(Student st);
static void calculate_rating(Student st, Course * cs);

void* course_constructor(void* data){
    void* ptr = (Course*)malloc(sizeof(Course));
    if(ptr == NULL){
        printf("Memory allocation error!\n");
        printf("Exiting\n");
        exit(EXIT_FAILURE);
    }
    memcpy(ptr, data, sizeof(Course));
    return ptr;
}
void course_destructor(void* data){
    free(data);
}

int subject_comparator(const void * a, const void * b){
    Subject A = *(Subject*)a;
    Subject B = *(Subject*)b;
    return strcmp(A.name, B.name);
}
void* subject_constructor(void* data){
    void* ptr = (Subject*)malloc(sizeof(Subject));
    if(ptr == NULL){
        printf("Memory allocation error!\n");
        printf("Exiting\n");
		exit(EXIT_FAILURE);
    }
    memcpy(ptr, data, sizeof(Subject));
    return ptr;
}
void subject_destructor(void* data){
    bst_delete(&(*(Subject*)data).students);
    free(data);
}
Subject set_subject(Student st){
    Subject subject;
    strcpy(subject.name, st.subject);
    return subject;
}
void register_student(void* data_sub, void* data_stu){
    bst_insert((*(Subject*)data_sub).students, data_stu);
}
void extract_student(void* data_sub, dlist_t* l){
    extract_student_helper((*(Subject*)data_sub).students->root, l);
}
static void extract_student_helper(bst_node* root, dlist_t * l){
    if(root != NULL){
        dlist_append(l, &(*(Student*)root->data));
        extract_student_helper(root->left, l);
        extract_student_helper(root->right, l);
    }
}
void process_subject(void* data){
    Subject sub = *(Subject*)data;
    printf("%-10s   %-10d\n", sub.name,(int)sub.students->size);
}
void list_subjects(bst_t * subjects){
    system("clear");
    printf("%-10s | %-10s\n","Subject", "Students");
    traverse_in_order_subject(subjects->root);
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}
void add_subject(bst_t * subjects){
    system("clear");
    Subject new_subject;
    printf("Add subject:\n");
    printf("Initials: ");
    while(scanf("%s", new_subject.name) && bst_find(subjects, &new_subject)){
       printf("This subject already exists!\n");
       printf("Initials: ");
    }
    printf("The subject will be created, but you've to register an student to persist on the dataset.\n");
    bst_initialize(&(new_subject.students), constructor_student, destructor_student, comparator_student_grade);
    bst_insert(subjects, &new_subject);
    fflush(stdin);
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}
void remove_subject(bst_t * subjects, bst_t * students_registered, dlist_t * students_not_registered){
    system("clear");
    printf("Remove subject:\n");
    printf("Enter the initials: ");
    char subject[20];
    scanf("%s", subject);
    Subject sj;
    strcpy(sj.name, subject);
    if(!bst_find(subjects, &sj)){
        printf("This subject doesn't exists!\n");
        return;
    }
    dlist_t * extracted_students;
    dlist_initialize(&extracted_students, constructor_student, destructor_student);
    bst_access_extract_subject(subjects, subjects->root, &sj, extracted_students);
    
    dlist_iterator_t it;
    for(it = extracted_students->head;it!=NULL;it = it->next){
        bst_remove(students_registered, it->data);
        Student refactor = *(Student*)it->data;
        refactor.grade = 0.0;
        strcpy(refactor.subject, "");
        refactor.miss = 0;
        strcpy(refactor.rating, "");
        dlist_append(students_not_registered, &refactor);
    }
    bst_remove(subjects, &sj);
    dlist_delete(&extracted_students);
    system("clear");

}
void include_student(bst_t* students_registered, bst_t * subjects, dlist_t * not_registered) {
    system("clear");
    printf("Include student:\n");
    int code, pos_student = 0, find_subject = 0;
    char subject[20];

    printf("Code: ");
    scanf("%d", &code);
    printf("Subject: ");
    scanf("%s", subject);
    Student student;
    Subject sj;
    strcpy(sj.name, subject);
    student.code = code;
    pos_student = dlist_find(not_registered, &student);
    find_subject = bst_find(subjects, &sj);
    if(pos_student != -1 && find_subject){
        Student st = *(Student*)dlist_access(not_registered, pos_student);

        strcpy(st.subject, subject);
        st.miss = .0;
        st.grade = .0;
        strcpy(st.rating, "SR");

        dlist_remove(not_registered, pos_student);
        bst_access_modify_subject(subjects, subjects->root, &sj, &st);
        bst_insert(students_registered, &st);
        printf("Student with code %d successfully registered on %s\n", st.code, sj.name);
    }else if(pos_student == -1){
        printf("The student is not available to include or you entered an invalid code!\n");
    }else if(!find_subject){
        printf("The subject doesn't exists!\n");
    }
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}
void remove_student_subject(char * subject_name, bst_t* students_subject, bst_t* students_registered, dlist_t* students_not_registered){
    system("clear");
    printf("Enter a student code to remove from %s: ", subject_name);
    Student st;
    scanf("%d", &st.code);
    int find_student = bst_find(students_registered, &st);
    if(!find_student){
        printf("Something went wrong (the code doesn't exists on %s subject).\n", subject_name);
    }else{
        Student extracted = *(Student*)bst_access(students_registered, students_registered->root, &st);
        bst_remove(students_registered, &st);
        bst_remove(students_subject, &extracted);
        strcpy(extracted.subject, "");
        extracted.miss = 0;
        extracted.grade = 0.0;
        strcpy(extracted.rating, "");
        dlist_append(students_not_registered, &extracted);
        printf("Student with code %d successfully removed from %s subject.\n", extracted.code, subject_name);
    }
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}

static Course set_course(Student st){
    Course cs;
    strcpy(cs.name, (st.course));
    cs.approved = 0;
    cs.repproved = 0;
    cs.ss = 0;
    cs.mm = 0;
    cs.mi = 0;
    cs.ms = 0;
    cs.ii = 0;
    cs.sr = 0;
    return cs;
}

void show_overall_dashboard(char * subject_name, bst_t* students_subject){
    system("clear");
    dlist_t * students;
    dlist_initialize(&students, constructor_student, destructor_student);
    extract_student_helper(students_subject->root, students);
    //dlist_show_elements(students);
    dlist_t * courses;
    dlist_initialize(&courses, course_constructor, course_destructor);
    dlist_iterator_t it;
    for(it = students->head;it!=NULL;it = it->next){
        Course cs = set_course(*(Student*)it->data);
        if(dlist_empty(courses)){
            calculate_rating(*(Student*)it->data, &cs);
            dlist_append(courses, &cs);
        }else{
            dlist_iterator_t finder;
            int position = -1;
            int k = 0;
            for(finder = courses->head;finder!=NULL;finder = finder->next){
                if(strcmp((*(Course*)finder->data).name, cs.name) == 0){
                    position = k;
                    break;
                }
                k++;
            }
            if(position == -1){
                calculate_rating(*(Student*)it->data, &cs);
                dlist_append(courses, &cs);
            }else{
                Course mod = *(Course*)dlist_access(courses, position);
                dlist_remove(courses, position);
                calculate_rating(*(Student*)it->data, &mod);
                dlist_append(courses, &mod);
            }
        }
    }
    printf("%s Info:\n", subject_name);
    printf("%-8s %-12s %-10s %-10s\n", "Course |", "Registered |", "Approved |", "Repproved");
    int all = 0, all_ap=0, all_rp=0;
    for(it=courses->head;it!=NULL;it=it->next){
        Course cs = *(Course*)it->data;
        int total = cs.approved+cs.repproved;
        all_ap += cs.approved;
        all_rp += cs.repproved;
        all += total;
        printf("%-8s %-12d %-10s %-10s\n", cs.name, total,
        format_string((cs.approved*100.0)/total, cs.approved), format_string((cs.repproved*100.0)/total, cs.repproved));
    }
    printf("%-8s %-12d %-10s %-10s\n", "Total", all, format_string((all_ap*100.0)/all, all_ap), format_string((all_rp*100.0)/all, all_rp));

    printf("\nRating:\n");
    printf("%-8s %-6s %-6s %-6s %-6s %-6s %-6s\n", "Course |", "SS |", "MS |", "MM |", "MI |", "II |", "SR");
    int * counter = (int*)calloc(6, sizeof(int)), i;
    for(it=courses->head;it!=NULL;it=it->next){
        Course cs = *(Course*)it->data;
        printf("%-8s %-6d %-6d %-6d %-6d %-6d %-6d\n", cs.name, cs.ss, cs.ms, cs.mm, cs.mi, cs.ii, cs.sr);
        counter[0] += cs.ss;
        counter[1] += cs.ms;
        counter[2] += cs.mm;
        counter[3] += cs.mi;
        counter[4] += cs.ii;
        counter[5] += cs.sr;
    }
    printf("%-8s ","Total");
    for(i=0;i<6;i++){
        printf("%-6d ", counter[i]);
    }
    printf("\n");
    free(counter);
    dlist_delete(&students);
    getchar();
    char c;
    printf("Press enter to go back...");
    scanf("%c", &c);
    system("clear");
}

static void calculate_rating(Student st, Course * cs){
    if(st.miss > 0.25 || st.grade == 0.0){
        cs->sr++;
        cs->repproved++;
    }else{
        if(strcmp(student_rating_calculator(st.grade), "SS") == 0){
            cs->ss++;
            cs->approved++;
        }else if(strcmp(student_rating_calculator(st.grade), "MS") == 0){
            cs->ms++;
            cs->approved++;
        }else if(strcmp(student_rating_calculator(st.grade), "MM") == 0){
            cs->mm++;
            cs->approved++;
        }else if(strcmp(student_rating_calculator(st.grade), "MI") == 0){
            cs->mi++;
            cs->repproved++;
        }else if(strcmp(student_rating_calculator(st.grade), "II") == 0){
            cs->ii++;
            cs->repproved++;
        }
    }
}

void save_modifications(bst_t* t, dlist_t* l){
    FILE * arq = fopen("output.txt", "wb");
    dlist_t * students;
    dlist_initialize(&students, constructor_student, destructor_student);
    extract_student_helper(t->root, students);
    dlist_iterator_t it;
    for(it=students->head;it!=NULL;it = it->next){
        Student st = *(Student*)it->data;
        fprintf(arq, "%s;%d;%s;%s;%.2lf;%.2lf;%s\n",
        st.name, st.code, st.course, st.subject, st.miss, st.grade, st.rating);
    }
    for(it=l->head;it!=NULL;it = it->next){
        Student st = *(Student*)it->data;
        fprintf(arq, "%s;%d;%s;;;;\n",
        st.name, st.code, st.course);
    }
    printf("All information was successfully registered on the dataset!\n");
    fclose(arq);
}