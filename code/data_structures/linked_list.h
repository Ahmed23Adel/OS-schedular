/** @file pcb_linked_list.h
 *  @brief An initial Program contro block that is used by process generator
 *
 *  PCB uses linked list as mainly data strcuture.
 *  Why Linked list?
 *  1-the size of incoming processes is not known.
 *  2-there will be no overhead while looping over all the list
 *      a) as i will search in all of it.    
 *
 *  @author Ahmed Adel 
 *  @bug No known bugs.
 * 
 */
#ifndef pcb_linked_list_H
#define pcb_linked_list_H

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
typedef struct ll_node_
{
    process info; //Value
    struct ll_node_ *next; //Next pointer
}ll_node;
/*
*
*/
ll_node *start=NULL;

/** @brief  Display current data of linked list
 *          Mainly used in testing only .
 *  @return Void.
 */
void display()
{
    ll_node *ptr;
    if(start==NULL)
    {
        //TODO delete that line after debugging
        printf("\nList is empty:\n");
        return;
    }
    else
    {
        ptr=start;
        //TODO delete that line after debugging
        printf("\nThe List elements are:\n");
        while(ptr!=NULL)
        {
            printf("%d \n",ptr->info.identity );
            ptr=ptr->next ;
        }
    }
}

/** @brief insert new node at begining of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void insert_begin(process p)
{
    ll_node *temp;
    temp=(ll_node *)malloc(sizeof(ll_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        printf("nOut of Memory Space:n");
        return;
    }
    temp->info=p;
    temp->next =NULL;
    if(start==NULL)
    {
        // head is not intialized yer
        start=temp;
    }
    else
    {
        // set head to gived process
        temp->next=start;
        start=temp;
    }
}

/** @brief insert new node at end of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void insert_end(process p)
{
    ll_node *temp,*ptr;
    temp=(ll_node*)malloc(sizeof(ll_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        printf("nOut of Memory Space:n");
        return;
    }
    temp->info=p;
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
void delete_begin()
{
    ll_node *ptr;
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
        //TODO delete that line after debugging
        printf("nThe deleted element is :%dt",ptr->info.identity);
        free(ptr);
    }
}

/** @brief insert new node at certain position
 *  @param pos position at which you need to delete node.
 *  @return Void.
 */
void delete_pos(int pos)
{
    int i;
    ll_node *temp,*ptr;
    if(start==NULL)
    {
        //TODO delete that line after debugging
        printf("nThe List is Empty:n");
        exit(0);
    }
    else
    {
        if(pos==0)
        {
            ptr=start;
            start=start->next ;
            //TODO delete that line after debugging
            printf("\nThe deleted element is:%d \n",ptr->info.identity  );
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
            //TODO delete that line after debugging
            printf("\nThe deleted element is:%d\n",ptr->info.identity );
            free(ptr);
        }
    }
}



/** @brief delete at thbe end of linked list 
 *  @return Void.
 */
void delete_end()
{
    ll_node *temp,*ptr;
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
        //TODO delete that line after debugging
        printf("\nThe deleted element is:%d \n",ptr->info.identity);
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
        //TODO delete that line after debugging
        printf("\nThe deleted element is:%d \n",ptr->info.identity);
        free(ptr);
    }
}




#endif