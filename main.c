#include <stdlib.h>
#include<stdio.h>

struct Node{
    int expo;
    float coeff;
    struct Node*next;
};

struct Node* create_terms(struct Node*);
struct Node*create_nodes_list(struct Node*,float, int);
void print_poly_descending_expo(struct Node*);
struct Node* add_two_polys(struct Node*,struct Node*,struct Node*);
struct Node* final_poly_simplify(struct Node*);
struct Node* mutiply_two_polys(struct Node*,struct Node*,struct Node*);

int main(){
    /*create the head pointers of the 1st,2nd,and resultant polynomials*/
    struct Node* head_poly1=NULL;
    struct Node* head_poly2=NULL;
    struct Node* head_final_poly=NULL;
    struct Node* head_final_mutiply=NULL;

    /*Enter the terms(coefficients and exponents) of two polynomials*/
    printf("__________Enter the 1st polynomial__________ \n\n");
    head_poly1=create_terms(head_poly1);
    printf("\n");
    printf("__________Enter the 2nd polynomial__________ \n\n");
    head_poly2=create_terms(head_poly2);

    /*print out two created polynomials*/
    print_poly_descending_expo(head_poly1);
    print_poly_descending_expo(head_poly2);

    printf("\n");

    /*calculate the addition of two polynomials, simplify it, and print it out*/
    head_final_poly=add_two_polys(head_poly1,head_poly2,head_final_poly);
    printf("__________The resultant polynomial(raw)after addition__________\n\n");
    print_poly_descending_expo(head_final_poly);
    printf("\n");
    printf("----------The resultant polynomial(simplied) after addition__________\n\n");
    head_final_poly=final_poly_simplify(head_final_poly);
    print_poly_descending_expo(head_final_poly);
    printf("\n");

    /*calculate the multiplication of two polynomials, simplify it, and print it out*/
    printf("----------The resultant polynomial(raw) after multiplication__________\n\n");
    head_final_mutiply=mutiply_two_polys(head_poly1,head_poly2,head_final_mutiply);
    print_poly_descending_expo(head_final_mutiply);
    printf("\n");
    printf("----------The resultant polynomial(raw) after multiplication__________\n\n");
    head_final_mutiply=final_poly_simplify(head_final_mutiply);
    print_poly_descending_expo(head_final_mutiply);



    return 0;
}

struct Node*create_terms(struct Node*head){
    float coefficient;
    int exponent;
    int num_of_terms;

    printf("How many terms does your polynomial have? ");
    scanf("%d",&num_of_terms);

    for(int i=0;i<num_of_terms;i++){
        printf("Enter the coefficient for term %d: ",i+1);
        scanf("%f",&coefficient);

        printf("Enter the exponent(no identical exponents) for term %d: ",i+1);
        scanf("%d",&exponent);

        head=create_nodes_list(head,coefficient,exponent);
    }

    return head;
}

/*create a list in descending order of the exponents of the terms*/
struct Node*create_nodes_list(struct Node*head,float coefficient, int exponent){

    struct Node*term=(struct Node*)malloc(sizeof(struct Node));
    term->coeff=coefficient;
    term->expo=exponent;
    term->next=NULL;

    int key_expo=term->expo;

    if(head==NULL||key_expo>head->expo){//empty list and insertion at the beginning(before the head node)
        term->next=head;
        head=term;
    }else{
        struct Node*ptr=head;//ptr for traversing the list
        while(ptr->next!=NULL&&(key_expo<ptr->next->expo||key_expo==ptr->next->expo)){//still traverse ptr even when exponents are identical
            ptr=ptr->next;
        }
        term->next=ptr->next;
        ptr->next=term;
    }
    return head;
}

struct Node* add_two_polys(struct Node*head_poly1,struct Node*head_poly2,struct Node* head_final_poly){
    float add_coeff=0.0;
    while(head_poly1!=NULL && head_poly2!=NULL){

        if(head_poly1->expo==head_poly2->expo){
            add_coeff=head_poly1->coeff+head_poly2->coeff;
            head_final_poly=create_nodes_list(head_final_poly,add_coeff,head_poly1->expo);
            head_poly1=head_poly1->next;
            head_poly2=head_poly2->next;

        }else if(head_poly1->expo>head_poly2->expo){

            head_final_poly=create_nodes_list(head_final_poly,head_poly1->coeff,head_poly1->expo);
            head_poly1=head_poly1->next;

        }else if(head_poly2->expo>head_poly1->expo){

            head_final_poly=create_nodes_list(head_final_poly,head_poly2->coeff,head_poly2->expo);
            head_poly2=head_poly2->next;

        }
    }

    /*finish traversing poly2. Only poly1 left*/
    while(head_poly1!=NULL){

        head_final_poly=create_nodes_list(head_final_poly,head_poly1->coeff,head_poly1->expo);
        head_poly1=head_poly1->next;

    }

    /*finish traversing poly1. Only poly2 left*/
    while(head_poly2!=NULL){

        head_final_poly=create_nodes_list(head_final_poly,head_poly2->coeff,head_poly2->expo);
        head_poly2=head_poly2->next;

    }

    return head_final_poly;
}

/*for mutiplying 2 polys*/
struct Node* mutiply_two_polys(struct Node*head_poly1,struct Node*head_poly2,struct Node* head_final_mutiply){
    struct Node*head1=head_poly1;
    struct Node*head2=head_poly2;
    float mutiply_coeff=0.0;
    int add_expo=0;
    while(head1!=NULL){
        head2=head_poly2;
        while(head2!=NULL){
            mutiply_coeff=head1->coeff*head2->coeff;
            add_expo=head1->expo+head2->expo;
            head_final_mutiply=create_nodes_list(head_final_mutiply,mutiply_coeff,add_expo);
            head2=head2->next;
        }
        head1=head1->next;
    }
    return head_final_mutiply;
}

void print_poly_descending_expo(struct Node*head) {

    struct Node *ptr = head;
    struct Node *tail = NULL;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    tail = ptr;//tail points to tail node
    ptr = head;

    printf("f(x)= ");
    while (ptr != NULL) {
        if(ptr->coeff!=0) {
            if(ptr->coeff==1) {
                if (ptr->expo == 1) {
                    printf("(x) ");//coeff=1 and exponent=1
                }else{
                    printf("(x^%d) ",ptr->expo);
                }
            }else {
                if(ptr->coeff==0){
                    printf("(%.2f) ", ptr->coeff);
                }else {
                    printf("(%.2fx^%d) ", ptr->coeff, ptr->expo);
                }
            }
            if (ptr != tail) {
                printf("+ ");
                ptr = ptr->next;
            } else {
                ptr = ptr->next;//for ptr pointing to the last node,here, ptr will equal to NULL-->exit the loop-->finished priniting out the poly
            }
        }else{
            ptr=ptr->next;
        }
    }

    printf("\n");
}

struct Node*final_poly_simplify(struct Node*head) {
    struct Node *head_final_poly_cleanup = NULL;
    struct Node *current = head;
    struct Node *ptr = head->next;
    struct Node *ptr2=ptr;//ptr2 is for deleting the node that ptr previously points to
    while (current != NULL&&ptr!=NULL) {
            while(current->expo==ptr->expo&& ptr!=NULL) {
                current->coeff = current->coeff + ptr->coeff;
                current->next=ptr->next;
                ptr = current->next;
                free(ptr2);
                ptr2=ptr;
            }
        current=ptr;
        ptr=ptr->next;
        ptr2=ptr;
    }
    return head;
}




