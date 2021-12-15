#include "headers.h"
#include "scheduler.h"
#include "data_structures/priority_queue.h"


node_priority* ready_priority_q;
process prs_to_run;
process prs_currently_running;
int main(int argc, char * argv[])
{
    initClk();
    /*+++++++++++++++++++++++++ recieving some values from process generator+++++++++++++++++++++++++++*/
    total_count_prss= atoi(argv[1]);
    alg_num = atoi(argv[2]);
    set_alg_enum(alg_num);
    /*++++++++++++++++++++++Intializations+++++++++++++++++*/
    prss_completed=0;
    ready_priority_q=NULL;
    /*++++++++++++++++++++++++++siganls handlers+++++++++++++++++++++++++*/
    signal(SIGUSR1, rec_handler);
    /*+++++++++++++++++++++++apply specified algorith++++++++++++++++++*/
    if(chosen_alg ==HPF)
        apply_hpf();
    if(chosen_alg ==SRTN)
        apply_srtn();
    if(chosen_alg ==RR)
        apply_rr();

    destroyClk(true);
}

void set_alg_enum(int alg_num)
{
    if (alg_num==0)
        chosen_alg=HPF;
    if (alg_num==1)
        chosen_alg=SRTN;
    if (alg_num==2)
        chosen_alg=RR;
}

void rec_handler(int signum)
{
    process tmp_p=rec_one_procss();
    while(tmp_p.arrival_time != -1)
    {   
        if(chosen_alg ==HPF)
            insert_prs_to_hpf(tmp_p);
        if(chosen_alg ==SRTN)
            insert_prs_to_srtn(tmp_p);
        if(chosen_alg ==RR)
            insert_prs_to_rr(tmp_p);

        tmp_p=rec_one_procss();
    }

}
void insert_prs_to_hpf(process prs)
{
    printf("Process %d received at time: %d \n", prs.identity, getClk());
    push_to_pri_q(&ready_priority_q, prs, prs.priority);
}

void insert_prs_to_srtn(process prs)
{
    printf("Process %d received at time: %d , rem time is %d\n", prs.identity, getClk(), get_remaining_time(prs));
    push_to_pri_q(&ready_priority_q, prs, get_remaining_time(prs));

}

void insert_prs_to_rr(process prs)
{

}
int get_remaining_time(process prs)
{
    return prs.run_time-prs.exec_time;
}
process rec_one_procss()
{
    msg_buff message; // create a message
    int rec_val; 
    rec_val = msgrcv(get_msg_q_id(), &message, sizeof(message.prs), 0, IPC_NOWAIT); // receive a message No waiting if a message is not found
    if (rec_val == -1)                                                            // if no process is received
    {
        process s={.arrival_time=-1}; //Indication that it's an error
        return s;
    }
    else
    {
        process *ptbp = (process *)malloc(sizeof(process)); 
        *ptbp = message.prs; 
        ptbp->curr_state = WAITING;
        return *ptbp;
    }

}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++HPF++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void apply_hpf()
{
    while(true)
    {
        if(!is_empty(&ready_priority_q))
        {
            prs_to_run=peek(&ready_priority_q);
            execute_process_hpf(prs_to_run);
            prs_finished(prs_to_run);
            pop_at_id(&ready_priority_q, prs_to_run.identity);
        }
        if(prss_completed==total_count_prss)
        {
            killpg(getpgrp(), SIGINT);
        }
        sleep(1);
       
    }
}

void execute_process_hpf(process prs)
{
    fork_new_prs(&prs);
    //parent
    int status;
    if(wait(&status))
    {
        //Done
        printf("process %d finished at %d \n", prs.identity,getClk());
    }

}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++SRTN++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void apply_srtn()
{
    prs_currently_running=create_process(-1,-1,-1,-1);//Indication nothing started yet
    while(true)
    {
        if(prss_completed==total_count_prss)
        {
            killpg(getpgrp(), SIGINT);

        }
        if(!is_empty(&ready_priority_q))
        {
            if(prs_currently_running.identity ==-1)
            {
                process prs=get_shortest_in_rem_time(ready_priority_q);
                execute_process_srtn(&prs);
                //continue;
            }
            else
            {
                
                minus_1_sec(&prs_currently_running); 

                process prs=get_shortest_in_rem_time(ready_priority_q);
                if(get_remaining_time(prs_currently_running)==0)  
                {
                    printf("process %d finished at time %d \n", prs_currently_running.identity, getClk());
                    prs_finished(prs_currently_running);
                    pop_at_id(&ready_priority_q, prs_currently_running.identity);
                    prs_currently_running=create_process(-1,-1,-1,-1);//Indication nothing is running now yet
                    
                    continue;
                }
                if(prs.identity ==prs_currently_running.identity)
                {
                    //pass
                }
                
                else
                {
                    kill(prs_currently_running.prog_id, SIGSTOP);
                    printf("process %d will paused now at time %d\n", prs_currently_running.identity, getClk());
                    prs_currently_running=prs;
                    execute_process_srtn(&prs);

                }
                
            }
        }
        sleep(1);
    }
}
process get_shortest_in_rem_time(node_priority* head)
{

    return peek(&ready_priority_q);
    
}
void execute_process_srtn(process* prs)
{
    if(prs->prog_id ==-1)
    {
        fork_new_prs(prs);
        prs_currently_running=*prs;
    }
    else
    {
        //forked and just needs to continue
        kill(prs->prog_id, SIGCONT); 
        prs_currently_running=*prs;
        printf("process %d resumed at time %d\n", prs->identity, getClk());

    }

}

void minus_1_sec(process *prs)
{
    prs->exec_time=prs->exec_time+1;
    pop_at_id(&ready_priority_q, prs->identity);
    push_to_pri_q(&ready_priority_q, *prs, get_remaining_time(*prs));
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++RR++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void prs_finished(process prs)
{
    prs.finish_time=getClk();
    prs.exec_time=prs.run_time;
    prs.curr_state=FINISHED;
    prss_completed ++;
    printf("%d completed\n", prss_completed);
}
void apply_rr()
{
    while(true)
    {
        
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Common++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void fork_new_prs(process* prs)
{
    int pid;
    pid=fork();
    if(pid==0)
    {
        //Child
        char buffer[15]; // Runtime int-->string
        sprintf(buffer, "%d", prs_to_run.run_time);
        char *argv[] = {"process.out", buffer, NULL};
        printf("process %d started at %d \n", prs->identity,getClk());
        execv("process.out", argv);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("program id is updated to %d\n", pid);
        prs->prog_id=pid;
    }
}



