#ifndef pcb_H
#define pcb_H

 /*+++++++++++++++++++++++++++++++++++++++Includes++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "headers.h"
#include "data_structures/priority_queue.h"
/** @brief push to pcb and intialize it if null
 *          made to create priority queue easier.
 * 
 *  @param head could be null-> we will intialize it for you
 *  @param priority priority of new inserted node
 *  @return void .
 */
void push_to_pcb(node_priority** head,process prs,int priority)
{
    if(*head ==NULL)
    {
        (*head) = _new_priority_node(prs,priority);
    }
    else
    {
        push(head, prs, priority);
    }
}


#endif