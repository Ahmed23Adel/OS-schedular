#ifndef queue_ll_plots_H
#define queue_ll_plots_H

/*-- Includes --*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "pbPlots.h"
#include "supportLib.h"

/* for all gloobal shard variables intialized there */
#include "../headers.h"

/* For NULL definition*/
#include <stddef.h>


/**
*   represent node in linked list containg value of current process and pointer for next element.
**/
typedef struct plots_ll_node_
{
    int x; //Value
    int y;
    struct plots_ll_node_ *next; //Next pointer
}plots_ll_node;
/*
*
*/
plots_ll_node *plots_start=NULL;
int count;

void init_plots()
{
    count=0;
}

/** @brief insert new node at begining of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void plots_insert_begin(int x, int y)
{
    count= count+1;
    plots_ll_node *temp;
    temp=(plots_ll_node *)malloc(sizeof(plots_ll_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        return;
    }
    temp->x=x;
    temp->y=y;
    temp->next =NULL;
    if(plots_start==NULL)
    {
        // head is not intialized yer
        plots_start=temp;
    }
    else
    {
        // set head to gived process
        temp->next=plots_start;
        plots_start=temp;
    }
}

/** @brief insert new node at end of linked list
 *  @param p process to be inserted at end of linked list.
 *  @return Void.
 */
void plots_insert_end(int x, int y)
{
     count= count+1;
    plots_ll_node *temp,*ptr;
    temp=(plots_ll_node*)malloc(sizeof(plots_ll_node));
    if(temp==NULL)
    {
        //TODO delete that line after debugging
        return;
    }
    temp->x=x;
    temp->y=y;
    temp->next =NULL;
    if(plots_start==NULL)
    {
        //head is not intialized yet
        plots_start=temp;
    }
    else
    {
        ptr=plots_start;
        while(ptr->next !=NULL) // find last element
        {
            ptr=ptr->next ;
        }
        ptr->next =temp;
    }
}


void get_img()
{

    int *xs;
    int *ys;
    xs=(int *)malloc((2*count)*sizeof *xs);
    ys=(int *)malloc((2*count)*sizeof *ys);
    plots_ll_node *tmp_ptr=plots_start;
    int counter=0;

    while(tmp_ptr != NULL)
    {
        if(counter!=0)
        {


            xs[counter]=tmp_ptr->x;
            ys[counter]=ys[counter-1];
            counter =counter +1;
            
        }

        xs[counter]=tmp_ptr->x;
        ys[counter]=tmp_ptr->y;
        
        counter =counter +1;
        tmp_ptr=tmp_ptr->next;

    }

    printf("{");
    printf("0, %d,",xs[0]);
    for(int i =0; i<counter;i++)
    {
        printf("%d,",((int) xs[i]));
    }
    printf("}\n");

    printf("{");
    printf("0, %d,",0);
    for(int i =0; i<counter;i++)
    {
        printf("%d,",((int) ys[i]));
    }
    printf("}\n");

	

}


#endif