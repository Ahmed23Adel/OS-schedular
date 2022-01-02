#ifndef scheduler_H
#define scheduler
#include "../headers.h"
#include "../data_structures/priority_queue.h"

int total_count_prss;
int alg_num;
int prss_completed;
scheduling_algorithms chosen_alg;


/** @brief for Debugging, i print output to output.txt. might be removed when i'm done debuggint
 *          it just closes the file opened to write output in it.
 *  @return void .
 */
void  interrupt_handler(int signum);

/** @brief set chosen algorthm num in enum 
 *          to better read
 *  @return Void.
 */
void set_alg_enum(int alg_num);

/** @brief signal handler for SIGUSR1
 *  @return Void.
 */
void rec_handler(int signum);


/** @brief recieve one single process from msg queue
 *          if nothing has come it returns process with arrival time = -1
 *          as indication of error
 *  @return process .
 */

process rec_one_procss();

#endif