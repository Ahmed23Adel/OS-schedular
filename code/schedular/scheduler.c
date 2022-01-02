#include "../headers.h"
#include "scheduler.h"
#include "../data_structures/priority_queue.h"
#include "../data_structures/circular_queue.h"
#include "../output_utils.h"
#include "HPF.h"
#include "SRTN.h"
#include  "RR.h"
#include "SJF.h"

node_priority* ready_priority_q;
process prs_to_run;
process prs_currently_running;
int quanta;
int rem_quanta;
FILE * pFile;
FILE *logFile;
int main(int argc, char * argv[])
{
    
    pFile = fopen("debugging.txt", "w");   

    initClk();
    /*+++++++++++++++++++++++++ recieving some values from process generator+++++++++++++++++++++++++++*/
    total_count_prss= atoi(argv[1]);
    alg_num = atoi(argv[2]);
    quanta= atoi(argv[3]);
    set_alg_enum(alg_num);
    logFile = fopen("schedular.log", "w");   ;
    /*++++++++++++++++++++++Intializations+++++++++++++++++*/
    prss_completed=0;
    ready_priority_q=NULL;
    /*++++++++++++++++++++++++++siganls handlers+++++++++++++++++++++++++*/
    signal(SIGUSR1, rec_handler);
    signal(SIGINT, interrupt_handler);
    /*+++++++++++++++++++++++apply specified algorith++++++++++++++++++*/
    if(chosen_alg ==HPF)
        init_hpf(total_count_prss);
        //apply_hpf();
    if(chosen_alg ==SRTN)
        init_srtn(total_count_prss);
        //apply_srtn();
    if(chosen_alg ==RR)
        init_rr(total_count_prss,quanta);
        //apply_rr();
    if(chosen_alg ==SJF)
        init_sjf(total_count_prss);

    destroyClk(true);
}
void  interrupt_handler(int signum)
{
    fclose(pFile);
    exit(EXIT_FAILURE);
}

void set_alg_enum(int alg_num)
{
    if (alg_num==0)
        chosen_alg=HPF;
    if (alg_num==1)
        chosen_alg=SRTN;
    if (alg_num==2)
        chosen_alg=RR;
    if (alg_num==3)
        chosen_alg=SJF;
}

void rec_handler(int signum)
{
    process tmp_p=rec_one_procss();
    while(tmp_p.arrival_time != -1)
    {   
        if(chosen_alg ==HPF)
            hpf_insert_prs(tmp_p);
        if(chosen_alg ==SRTN)
            srtn_insert_prs(tmp_p);
        if(chosen_alg ==RR)
            rr_insert_prs(tmp_p);
        if(chosen_alg ==SJF)
            sjf_insert_prs_to(tmp_p);

        tmp_p=rec_one_procss();
    }

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


