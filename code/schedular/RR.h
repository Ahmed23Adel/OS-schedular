#ifndef RR_H
#define RR_H

#include "schedular_parent.h"
#include "../data_structures/circular_queue.h"

void rr_apply();


process prs_currently_running;
int quanta;
int rem_quanta;

void rr_apply();
void rr_cq_run_top();
void rr_cq_suspend_process(process *prs);
void rr_execute_process(process* prs);
void rr_cq_minus_1_sec(process *prs);

void rr_insert_prs(process prs)
{
    parent_prss_rec(prs);
    cq_enqueue(prs);
}


void init_rr(int total_prss, int quanta_)
{
    init_sch_parent(total_prss);
    quanta=quanta_;
    rr_apply();
}



void rr_apply()
{
    
    initClk();
    printf("I'm in RR at time %d \n", getClk());
    prs_currently_running=create_process(-1,-1,-1,-1);//Indication nothing started yet
    rem_quanta=quanta;
    while(true)
    {
        if(prss_completed==total_count_prss)
        {
             parent_schedular_is_done(prs_currently_running);
        }
        if(cq_is_empty() && parent_get_remaining_time(prs_currently_running)==0)
        {
            parent_prs_finished(prs_currently_running);
            prs_currently_running=create_process(-1,-1,-1,-1);
        }
        if(cq_is_empty()&& rem_quanta == -1)
        {
            rem_quanta=quanta;
        }
        if(!cq_is_empty())
        {
            if(prs_currently_running.identity ==-1)
            {
                rem_quanta=quanta;
                rr_cq_run_top();
                
            }
            else
            {
                if(rem_quanta==0)
                {
                    //fprintf(pFile, "remtime =0 \n");
                    if(parent_get_remaining_time(prs_currently_running)==0)
                    {
                        //it should finish now
                        parent_prs_finished(prs_currently_running);
                        //prs_currently_running=create_process(-1,-1,-1,-1);
                        rr_cq_run_top();
                    }
                    else
                    {
                        //fprintf(pFile, "else \n");
                        //quanta is finihsed but process still needs some time.
                        rr_cq_suspend_process(&prs_currently_running);
                        rr_cq_run_top();
                        //prs_currently_running=create_process(-1,-1,-1,-1);
                    }
                }
                else if(parent_get_remaining_time(prs_currently_running)==0)
                {
                    //prs finished before qunata finishes
                    parent_prs_finished(prs_currently_running);
                    rr_cq_run_top();
                    //prs_currently_running=create_process(-1,-1,-1,-1);
                }

            }
        }
        
        parent_sleep_1_sec();
        //fprintf(pFile, "current time : %d\n", getClk());
        //printf("current time : %d\n", getClk());
        rem_quanta=rem_quanta-1;
        //fprintf(pFile, "rem_quanta =%d \n", rem_quanta);
        rr_cq_minus_1_sec(&prs_currently_running);
    }    
}

void rr_cq_run_top()
{
   
    prs_currently_running=cq_dequeue();
    rem_quanta=quanta;
    rr_execute_process(&prs_currently_running);
   // fprintf(pFile, "run top, process %d started at time%d \n",prs_currently_running.identity, getClk() );
}

void rr_cq_suspend_process(process *prs)
{
    //fprintf(pFile, "prs %d stopped at time %d \n", prs->identity, getClk());
    parent_file_prss_stopped(*prs);
    kill(prs->prog_id, SIGSTOP);
    cq_enqueue(*prs);
}

void rr_cq_minus_1_sec(process *prs)
{
    prs->exec_time =prs->exec_time+1;
}

void rr_execute_process(process* prs)
{
    if(prs->prog_id ==-1)
    {
        printf("process %d start at time %d\n", prs->identity, getClk());
       // fprintf(pFile, "process %d start at time %d\n", prs->identity, getClk());
        parent_fork_new_prs(prs);
        prs_currently_running=*prs;
    }
    else
    {
        //forked and just needs to continue
        kill(prs->prog_id, SIGCONT); 
        prs_currently_running=*prs;
        printf("process %d resumed at time %d\n", prs->identity, getClk());
       // fprintf(pFile, "process %d resumed at time %d\n", prs->identity, getClk());
        parent_file_prss_resumed(*prs);
    }

}
#endif