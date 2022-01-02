#ifndef SJF_H
#define SJF_H

#include "schedular_parent.h"
#include "../data_structures/priority_queue.h"
void sjf_apply();
void sjf_execute_process(process prs);

node_priority* ready_priority_q;

void sjf_insert_prs_to(process prs)
{
    parent_prss_rec(prs);
    parent_push_to_pri_q(&ready_priority_q, prs, prs.run_time);
}

void init_sjf(int total_prss)
{
    init_sch_parent(total_prss);
    sjf_apply();
}


void sjf_apply()
{
  while(true)
    {
        if(!is_empty(&ready_priority_q))
        {
            prs_to_run=peek(&ready_priority_q);
            sjf_execute_process(prs_to_run);
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


void sjf_execute_process(process prs)
{
    parent_fork_new_prs(&prs);
    //parent
    int status;
    fprintf(pFile, "process %d started at %d \n", prs.identity,getClk());
    if(wait(&status))
    {
        //Done
        //printf("process %d finished at %d \n", prs.identity,getClk());
        fprintf(pFile, "process %d finished at %d \n", prs.identity,getClk());

    }

}

#endif