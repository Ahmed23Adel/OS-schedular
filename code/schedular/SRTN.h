#ifndef SRTN_H
#define SRTN_H

#include "schedular_parent.h"
#include "../data_structures/priority_queue.h"
/** @brief insert the new coming process to appropiate data strucutre for SRTN
 *  @return int .
 */
void srtn_insert_prs(process prs);

/** @brief just peek but redifined it for calrity
 *  @return process .
 */
process srtn_get_shortest_in_rem_time(node_priority* head);

/** @brief executre process, but should be used only by srtn algorithm
 *          as it does extra work for SRTN algorith
 *  @return void .
 */
void srtn_execute_process(process* prs);

/** @brief it adds one second to exec time to 
 *          currenly running process, update its priority
 *  @return void .
 */
void srtn_minus_1_sec(process *prs);

/** @brief apply shortest remaining time next
 *  @return Void.
 */
void srtn_apply();


process prs_currently_running;



void srtn_insert_prs(process prs)
{
    parent_prss_rec(prs);
    parent_push_to_pri_q(&ready_priority_q, prs,parent_get_remaining_time(prs));
}

void init_srtn(int total_prss)
{
    init_sch_parent(total_prss);
    srtn_apply();
}

void srtn_apply()
{
    prs_currently_running=create_process(-1,-1,-1,-1,-1);//Indication nothing started yet
    while(true)
    {
        if(prss_completed==total_count_prss)
        {
            parent_schedular_is_done(prs_currently_running);

        }
        if(!is_empty(&ready_priority_q))
        {
            if(prs_currently_running.identity ==-1)
            {
                process prs=srtn_get_shortest_in_rem_time(ready_priority_q);
                srtn_execute_process(&prs);
                //continue;
            }
            else
            {
                
                srtn_minus_1_sec(&prs_currently_running); 

                process prs=srtn_get_shortest_in_rem_time(ready_priority_q);
                if(parent_get_remaining_time(prs_currently_running)==0)  
                {
                    //printf("process %d finished at time %d \n", prs_currently_running.identity, getClk());
                    fprintf(pFile, "process %d finished at time %d \n", prs_currently_running.identity, getClk());

                    parent_prs_finished(prs_currently_running);
                    pop_at_id(&ready_priority_q, prs_currently_running.identity);
                    prs_currently_running=create_process(-1,-1,-1,-1,-1);//Indication nothing is running now yet
                    
                    continue;
                }
                if(prs.identity ==prs_currently_running.identity)
                {
                    //pass
                }
                
                else
                {
                    kill(prs_currently_running.prog_id, SIGSTOP);
                    parent_file_prss_stopped(prs_currently_running);
                    //printf("process %d will paused now at time %d\n", prs_currently_running.identity, getClk());
                    fprintf(pFile, "process %d will paused now at time %d\n", prs_currently_running.identity, getClk());
                    prs_currently_running=prs;
                    srtn_execute_process(&prs);

                }
                
            }
        }

        parent_sleep_1_sec();
        fprintf(pFile, "current time : %d\n", getClk());
        //printf("current time : %d\n", getClk());
    }
}


process srtn_get_shortest_in_rem_time(node_priority* head)
{

    return peek(&ready_priority_q);
    
}


void srtn_execute_process(process* prs)
{
    if(prs->prog_id ==-1)
    {
        //printf("process %d start at time %d\n", prs->identity, getClk());
        fprintf(pFile, "process %d start at time %d\n", prs->identity, getClk());
        parent_fork_new_prs(prs);
        prs_currently_running=*prs;
    }
    else
    {
        //forked and just needs to continue
        kill(prs->prog_id, SIGCONT); 
        prs_currently_running=*prs;
        //printf("process %d resumed at time %d\n", prs->identity, getClk());
        fprintf(pFile, "process %d resumed at time %d\n", prs->identity, getClk());
        parent_file_prss_resumed(*prs);
    }

}

void srtn_minus_1_sec(process *prs)
{
    prs->exec_time=prs->exec_time+1;
    pop_at_id(&ready_priority_q, prs->identity);
    parent_push_to_pri_q(&ready_priority_q, *prs, parent_get_remaining_time(*prs));
}



#endif