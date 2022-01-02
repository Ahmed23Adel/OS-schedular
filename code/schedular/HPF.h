#ifndef HPF_H
#define HPF_H

#include "schedular_parent.h"
#include "../data_structures/priority_queue.h"



/** @brief insert the new coming process to appropiate data strucutre for HPF
 *  @return int .
 */
void insert_prs_to_hpf(process prs);

/** @brief You should call thie function to run hpf
 *  @return void .
 */
void init_hpf(int total_prss);

/** @brief fires a new process 
 *  @return int .
 */
void hpf_execute_process(process prs);

/** @brief apply hightest priority first
 *  @return Void.
 */
void hpf_apply();

node_priority* ready_priority_q;

void hpf_insert_prs(process prs)
{
    parent_prss_rec(prs);
    parent_push_to_pri_q(&ready_priority_q, prs, prs.priority);
}


void init_hpf(int total_prss)
{
    init_sch_parent(total_prss);
    hpf_apply();
}


void hpf_apply()
{
    while(true)
    {
        if(!is_empty(&ready_priority_q))
        {
            prs_to_run=peek(&ready_priority_q);
            hpf_execute_process(prs_to_run);
            parent_prs_finished(prs_to_run);
            pop_at_id(&ready_priority_q, prs_to_run.identity);
        }
        if(prss_completed==total_count_prss)
        {

            parent_schedular_is_done(prs_to_run);
        }
        //sleep(1);
       
    }
}


void hpf_execute_process(process prs)
{
    parent_fork_new_prs(&prs);
    //parent
    int status;
    fprintf(pFile, "process %d started at %d \n", prs.identity,getClk());
    if(wait(&status))
    {
        //Done
        fprintf(pFile, "process %d finished at %d \n", prs.identity,getClk());

    }

}

#endif