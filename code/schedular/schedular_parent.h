#ifndef schedular_parent_H
#define schedular_parent_H

#include "../headers.h"
#include "../data_structures/priority_queue.h"
#include "../output_utils.h"
#include "../plots/queue_ll_plots.h"
#include "../mem/linked_mem.h"

FILE * pFile;
FILE *logFile;
process prs_to_run;
int prss_completed;
int total_count_prss;

/** @brief to start the schedlar, made to define some important variables
 * 
 *  @param total_prss total number of incoming processes, it's used by algorithsm; to check if they are done.
 *  @return void .
 */
void init_sch_parent(int total_prss);

/** @brief it push a process of certain priority to priority queue, it jues does some check to check if priotiry queue
 *          is empty and hence it need to intialize the head or just append to the end of it.
 * 
 *  @param head could be null-> we will intialize it for you
 *  @param priority priority of new inserted node
 *  @return void .
 */
void parent_push_to_pri_q(node_priority** head,process prs,int priority);

/** @brief it just forks new process 
 *  @return void .
 */
void parent_fork_new_prs(process* prs);

/** @brief used in debuggin file, it just print some some info, when process is recieved
 * 
 *  @param prs process recievd
 *  @return void .
 */
void parent_prss_rec(process prs);

/** @brief calculte the waiting time for process it took,
 *  @param prs process to calculate waiting time for.
 *  @return void .
 */
int parent_get_waiting_time(process prs);


/** @brief calculte the turn aroutn time  time for process it took,
 *  @param prs process to calculate turn aroutn time  time for.
 *  @return void .
 */
int parent_get_turn_around_time(process prs);


/** @brief calculte the turn weighted aroutn time  time for process it took,
 *  @param prs process to calculate weighted turn aroutn time  time for.
 *  @return void .
 */
float parent_get_weighted_trn_arnd(process prs);

/** @brief write to the .log file tha process has started
 *  @param prs process 
 *  @return void .
 */
void parent_file_prss_started(process prs);

/** @brief write to the .log file that process has finished
 *  @param prs process 
 *  @return void .
 */

void parent_file_prss_finished(process prs);

/** @brief write to the .log file that process has stopped
 *  @param prs process 
 *  @return void .
 */
void parent_file_prss_stopped(process prs);

/** @brief write to the .log file that process has resumed
 *  @param prs process 
 *  @return void .
 */
void parent_file_prss_resumed(process prs);

/** @brief when algorithms is done, it should call that function to close all files.
 *  @return void .
 */
void parent_schedular_is_done(process final_prs);

/** @brief it lets the schedular sleep for one second, but as not to wake up,
 *      i disable some possible intrrupts.
 *  @return void .
 */
void parent_sleep_1_sec();

void init_mem();
void allocate_mem(process *prs);

void init_sch_parent(int total_prss)
{

    pFile = fopen("debugging.txt", "w");   
    logFile = fopen("schedular.log", "w");   
    prss_completed=0;
    total_count_prss=total_prss;
    init_plots();
    init_mem();

}


void parent_push_to_pri_q(node_priority** head,process prs,int priority)
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

void parent_prss_rec(process prs)
{

    printf("Process %d received at time: %d \n", prs.identity, getClk());
    fprintf(pFile, "Process %d received at time: %d \n", prs.identity, getClk());
}


int parent_get_waiting_time(process prs)
{
    return getClk()-prs.arrival_time- prs.exec_time;
}

int parent_get_turn_around_time(process prs)
{
   return prs.finish_time-prs.arrival_time;
}

float parent_get_weighted_trn_arnd(process prs)
{
       return ((float)parent_get_turn_around_time(prs))/((float)prs.run_time);
}

int parent_get_remaining_time(process prs)
{
    return prs.run_time-prs.exec_time;
}

void parent_fork_new_prs(process* prs)
{
    allocate_mem(prs);

    int pid;
    pid=fork();
    if(pid==0)
    {
        //Child
        char buffer[15]; 
        sprintf(buffer, "%d", prs_to_run.run_time);
        char *argv[] = {"process.out", buffer, NULL};
        fprintf(pFile, "process %d started at %d \n", prs->identity,getClk());
        execv("process.out", argv);
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(pFile, "program id is updated to %d\n", pid);
        prs->prog_id=pid;
    }
    parent_file_prss_started(*prs);
}

void parent_file_prss_started(process prs)
{
    //TODO make sure if i need to change arrival time, as some processes come to schedular little later
    fprintf(logFile,"At time %d process %d started arr %d total %d remain %d wait %d from %d to %d \n" ,
                getClk(),prs.identity,prs.arrival_time, prs.run_time, prs.run_time, parent_get_waiting_time(prs), prs.memsize_start, prs.memsize_end);
    plots_insert_end(getClk(), prs.identity);
}

void parent_file_prss_stopped(process prs)
{
    fprintf(logFile,"At time %d process %d stopped arr %d total %d remain %d wait %d from %d to %d \n" ,
                getClk(),prs.identity,prs.arrival_time, prs.run_time, parent_get_remaining_time(prs),  parent_get_waiting_time(prs),prs.memsize_start, prs.memsize_end);
}


void parent_file_prss_resumed(process prs)
{
    fprintf(logFile,"At time %d process %d resumed arr %d total %d remain %d wait %d from %d to %d\n" ,
                getClk(),prs.identity,prs.arrival_time, prs.run_time, parent_get_remaining_time(prs),  parent_get_waiting_time(prs),prs.memsize_start, prs.memsize_end);
    plots_insert_end(getClk(), prs.identity);
}

void parent_file_prss_finished(process prs)
{
    fprintf(logFile,"At time %d process %d finished arr %d total %d remain %d wait %d TA %d WTA %.2f from %d to %d\n" ,
                getClk(),prs.identity,prs.arrival_time, prs.run_time, 0,  parent_get_waiting_time(prs), parent_get_turn_around_time(prs),parent_get_weighted_trn_arnd(prs) ,prs.memsize_start, prs.memsize_end);

    
}

void parent_prs_finished(process prs)
{
    prs.finish_time=getClk();
    prs.exec_time=prs.run_time;
    prs.curr_state=FINISHED;
    prss_completed ++;
    printf("process %d finished at time %d\n", prs.identity, getClk());
    fprintf(pFile, "process %d finished at time %d\n", prs.identity, getClk());
    printf("%d completed\n", prss_completed);
    fprintf(pFile, "%d completed\n", prss_completed);
    parent_file_prss_finished(prs);
    add_new_finished_pros(prs);
    
    //mem
    printf("%d %d \n",prs.memsize_start,prs.memsize_end);
    //transfer_node(&p_start, &h_start, prs.memsize_start,prs.memsize_end);
    mem_display(&h_start);
    mem_insert_hole(prs.memsize_start,prs.memsize_end);

    mem_display(&h_start);
    mem_display(&p_start);
    printf("prs  finished \n");
}



void parent_schedular_is_done(process final_prs)
{
    plots_insert_end(getClk(), final_prs.identity);
    get_img();

    fclose(logFile);
    do_calculations();
    killpg(getpgrp(), SIGINT);
}


void parent_sleep_1_sec()
{

    signal(SIGUSR1, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    sleep(1);

    signal(SIGUSR1, SIG_DFL);
    signal(SIGINT, SIG_DFL);

    signal(SIGUSR1, rec_handler);
    signal(SIGINT, interrupt_handler);
    rec_handler(-1);
    //printf("completed: %d\n" ,prss_completed);
}

void init_mem()
{
    printf("max size is %d \n", ((int)MAX_SIZE) -1);
    mem_insert_begin(&h_start, 0,((int)MAX_SIZE) -1);
    if(h_start==NULL)
        printf("HSTART IS NULL \n");
    else
        printf("HSTART IS NOT NOT NOT NOT NULL \n");
}

void allocate_mem(process *prs)
{
    
    mem_display(&h_start);
    printf("prs %d wanted memory of %d \n",prs->identity,prs->memsize);
    divide_till_size(&h_start, prs->memsize);
    mem_display(&h_start);
    //get limits and put it into prs
    int *x,*y;
    printf("HOla!!\n");
    printf("%d, %d \n", h_start->start,h_start->end);
    get_exact_limits(&h_start, prs->memsize,&x,&y);
    printf("ooooh \n");
    //printf("prs %d has start %d and end %d \n", prs.identity,*x, *y);
    prs->memsize_start=*x;
    prs->memsize_end=*y;
    printf("prs %d has start %d and end %d\n", prs->identity, prs->memsize_start, prs->memsize_end);
    transfer_node(&h_start,&p_start,  *x,*y);

    mem_display(&h_start);
    mem_display(&p_start);
}
#endif