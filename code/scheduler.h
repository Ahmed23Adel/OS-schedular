#ifndef scheduler_H
#define scheduler
#include "headers.h"
#include "data_structures/priority_queue.h"


int total_count_prss;
int alg_num;
int prss_completed;
scheduling_algorithms chosen_alg;

/** @brief push to pcb and intialize it if null
 *          made to create priority queue easier.
 * 
 *  @param head could be null-> we will intialize it for you
 *  @param priority priority of new inserted node
 *  @return void .
 */
void push_to_pri_q(node_priority** head,process prs,int priority)
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

/** @brief signal handler for SIGUSR1
 *  @return Void.
 */
void rec_handler(int signum);

/** @brief set chosen algorthm num in enum 
 *          to better read
 *  @return Void.
 */
void set_alg_enum(int alg_num);

/** @brief apply hightest priority first
 *  @return Void.
 */
void apply_hpf();

/** @brief apply shortest remaining time next
 *  @return Void.
 */
void apply_srtn();

/** @brief apply round robin
 *  @return Void.
 */
void apply_rr();
/** @brief recieve one single process from msg queue
 *          if nothing has come it returns process with arrival time = -1
 *          as indication of error
 *  @return process .
 */
process rec_one_procss();

/** @brief insert the new coming process to appropiate data strucutre for HPF
 *  @return int .
 */
void insert_prs_to_hpf();

/** @brief insert the new coming process to appropiate data strucutre for HPF
 *  @return int .
 */
void insert_prs_to_hpf(process prs);

/** @brief insert the new coming process to appropiate data strucutre for SRTN
 *  @return int .
 */
void insert_prs_to_srtn(process prs);

/** @brief insert the new coming process to appropiate data strucutre for RR
 *  @return int .
 */
void insert_prs_to_rr(process prs);

/** @brief fires a new process 
 *  @return int .
 */
void execute_process_hpf(process prs);

#endif