#include "headers.h"
#include "scheduler.h"
#include "data_structures/priority_queue.h"


node_priority* ready_priority_q;
process prs_to_run;
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

}

void insert_prs_to_rr(process prs)
{

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

void apply_hpf()
{
    while(true)
    {
        printf("total_count_prss %d \n",total_count_prss);
        if(!is_empty(&ready_priority_q))
        {
            prs_to_run=peek(&ready_priority_q);
            execute_process_hpf(prs_to_run);
            prss_completed++;
            pop_at_id(&ready_priority_q, prs_to_run.identity);
            printf("%d completed \n", prss_completed);
        }
        if(prss_completed==total_count_prss)
        {
            killpg(getpgrp(), SIGINT);
        }
        sleep(1);
       
    }
}

void apply_srtn()
{
    while(true)
    {
        
    }
}

void apply_rr()
{
    while(true)
    {
        
    }
}

void execute_process_hpf(process prs)
{
    int pid;
    pid=fork();
    if(pid==0)
    {
        //Child
        char buffer[15]; // Runtime int-->string
        sprintf(buffer, "%d", prs_to_run.run_time);
        char *argv[] = {"process.out", buffer, NULL};
        printf("process %d started at %d \n", prs.identity,getClk());
        execv("process.out", argv);
        exit(EXIT_SUCCESS);
    }
    else
    {
        //parent
        int status;
        if(wait(&status))
        {
            //Done
            printf("process %d finished at %d \n", prs.identity,getClk());
        }

    }


}

