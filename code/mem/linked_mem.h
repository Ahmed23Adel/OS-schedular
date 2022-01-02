#ifndef linked_mem_H
#define linked_mem_H

/*-- Includes --*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

/* for all gloobal shard variables intialized there */
#include "../headers.h"

/* For NULL definition*/
#include <stddef.h>


/**
*   represent node in linked list containg value of current process and pointer for next element.
**/
typedef struct mem_node
{
    int start;
    int end;
    struct mem_node *next; //Next pointer
}mem_node;
/*
*
*/
mem_node *p_start=NULL;
mem_node *h_start=NULL;




void mem_display(mem_node **start)
{
    mem_node *ptr;
    if(*start==NULL)
    {
        //TODO delete that line after debugging
        printf("\nList is empty:\n");
        return;
    }
    else
    {
        ptr=*start;
        //TODO delete that line after debugging
        printf("\nThe List elements are:\n");
        printf("###############\n");
        while(ptr!=NULL)
        {
            printf("%d, %d \n",ptr->start,ptr->end );
            ptr=ptr->next ;
        }
        printf("###############\n");
    }
}

/** @brief insert new node at begining of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void mem_insert_begin(mem_node **start,int start_, int end_)
{
    mem_node *temp;
    temp=(mem_node *)malloc(sizeof(mem_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        printf("nOut of Memory Space:n");
        return;
    }
    temp->start=start_;
    temp->end=end_;
    temp->next =NULL;
    if(*start==NULL)
    {
        // head is not intialized yer
        *start=temp;
    }
    else
    {
        // set head to gived process
        temp->next=*start;
        *start=temp;
    }
}

/** @brief insert new node at end of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void mem_insert_end(mem_node *start,int start_, int end_)
{
    mem_node *temp,*ptr;
    temp=(mem_node*)malloc(sizeof(mem_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        printf("nOut of Memory Space:n");
        return;
    }
    temp->start=start_;
    temp->end=end_;
    temp->next =NULL;
    if(start==NULL)
    {
        //head is not intialized yet
        start=temp;
    }
    else
    {
        ptr=start;
        while(ptr->next !=NULL) // find last element
        {
            ptr=ptr->next ;
        }
        ptr->next =temp;
    }
}

/*
*       delete the first element of linked list
*/
/** @brief delete the first element of linked list
 *  @return Void.
 */
void mem_delete_begin(mem_node *start)
{
    mem_node *ptr;
    if(ptr==NULL)
    {
        //TODO delete that line after debugging
        printf("nList is Empty:n");
        return;
    }
    else
    {
        ptr=start;
        start=start->next ;
        free(ptr);
    }
}

/** @brief insert new node at certain position
 *  @param pos position at which you need to delete node.
 *  @return Void.
 */
void mem_delete_pos(mem_node *start,int pos)
{
    int i;
    mem_node *temp,*ptr;
    if(start==NULL)
    {
        exit(0);
    }
    else
    {
        if(pos==0)
        {
            ptr=start;
            start=start->next ;
            free(ptr);
        }
        else
        {
            ptr=start;
            for(i=0; i<pos; i++)
            {
                temp=ptr;
                ptr=ptr->next ;
                if(ptr==NULL)
                {
                    printf("\nPosition not Found:\n");
                    return;
                }
            }
            temp->next =ptr->next ;
            free(ptr);
        }
    }
}



/** @brief delete at thbe end of linked list 
 *  @return Void.
 */
void mem_delete_end(mem_node *start)
{
    mem_node *temp,*ptr;
    if(start==NULL)
    {
        //TODO delete that line after debugging
        printf("\nList is Empty:");
        exit(0);
    }
    else if(start->next ==NULL)
    {
        ptr=start;
        start=NULL;
        free(ptr);
    }
    else
    {
        ptr=start;
        while(ptr->next!=NULL)
        {
            temp=ptr;
            ptr=ptr->next;
        }
        temp->next=NULL;
        free(ptr);
    }
}

void mem_insert_hole(int x, int y)
{
    //remove from p
    mem_node* tmp=p_start;
    mem_node* tmp_before=NULL;
    while(tmp != NULL)
    {

        if(tmp->start==x && tmp->end==y)
        {
            printf("IIIII should transfer now0 \n");
            if(tmp_before==NULL)
            {
                printf("IIIII should transfer now1 \n");
                p_start =tmp->next;
                break;
            }
            tmp_before->next=tmp->next;
            break;

        }
        tmp_before=tmp;
        tmp=tmp->next;
    }

    //insert into h
    if(x==0 && (y+1)==h_start->start)
    {
        printf("insert hole0\n");
        h_start->start=x;
        return;

    }
    if(y==((int)MAX_SIZE))
    {
        mem_node* tmp=h_start;
        while(tmp->next != NULL)
        {
            
            tmp=tmp->next;
        }
        tmp->end=y;
        printf("insert hole1\n");
        return;
    }
    else
    {
        mem_node* tmp=h_start;
        while(tmp->next != NULL)
        {
            if(tmp->end==x)
            {
                tmp->end=y;
                printf("insert hole2\n");
                return;
            }
            else if(y == tmp->start)
            {
                tmp->start=x;
                return;
            }
            tmp=tmp->next;
        }
        //not even found
        mem_node* tmp2=h_start->next;
        mem_node* tmp_before2=h_start;
        while(tmp2->next != NULL)
        {
            if(tmp_before2->end<x && tmp2->start>x)
            {
                mem_node *n;
                n=(mem_node*)malloc(sizeof(n));
                tmp_before2->next=n;
                n->next=tmp2;
            }
            tmp2=tmp2->next;
        }
    }
}

int get_size_of_node(mem_node node)
{
    return node.end-node.start+1;
}
bool is_node_fit(mem_node* start, int size)
{
   if(get_size_of_node(*start) == size)
            return true; 
}


bool is_any_node_fit(mem_node* start, int size)
{
    mem_node* tmp=start;
    while(tmp != NULL)
    {
        if(get_size_of_node(*tmp) == size)
            return true;
        tmp=tmp->next;
    }
    return false;
}

void divide_till_size(mem_node **start,int size)
{
    if(is_any_node_fit(*start, size))
    {
        return;
    }
        

    //find first place that is larger than desired size
    mem_node *tmp=*start;
    mem_node *tmp_before=NULL;;
    while(tmp!= NULL)
    {
        
        if(get_size_of_node(*tmp) > size)
            break;
        tmp_before=tmp;
        tmp=tmp->next;
    }
    //now i either have a node that its size is larger than size or equal to size
    //i i couldn't find a place?
    if(tmp==NULL)
    {
        printf("No memory found\n");
        return;
    }
    else
    {
       mem_node *n1,*n2;
       n1=(mem_node*)malloc(sizeof(n1));
       n2=(mem_node*)malloc(sizeof(n2));
       n1->start=tmp->start;
       n1->end=((int)floor((tmp->end-tmp->start)/2));

       n2->start=n1->end+1;
       n2->end=tmp->end;

       if(tmp_before==NULL)
       {
           *start=n1;
           (*start)->next=n2;
           n2->next=tmp->next;
           divide_till_size(start,size);
           return;
       }
       n1->next=n2;
       n2->next=tmp->next;
       tmp_before->next=n1;
       

    }

}

void get_exact_limits(mem_node **start,int size,int **x, int **y)
{
    mem_node* tmp=*start;
    printf("in exact \n");
    while(tmp != NULL)
    {
        printf("current size is %d \n",get_size_of_node(*tmp));
        if(get_size_of_node(*tmp) == size)
        {
            printf("current size is heey %d \n",get_size_of_node(*tmp));
            *x=&(tmp->start);
            *y=&(tmp->end);
            return;
        }
            
        tmp=tmp->next;
    }

}

void transfer_node(mem_node **from, mem_node **to, int x, int y)
{
    mem_node* tmp=*from;
    mem_node* tmp_before=NULL;
    while(tmp != NULL)
    {

        if(tmp->start==x && tmp->end==y)
        {
             printf("I should transfer now0 \n");
            if(tmp_before==NULL)
            {
                printf("I should transfer now1 \n");
                *from =tmp->next;
                mem_insert_begin(to, x,y);
                return;
            }
            tmp_before->next=tmp->next;
            mem_insert_begin(to, x,y);

        }
        tmp_before=tmp;
        tmp=tmp->next;
    }
}

#endif