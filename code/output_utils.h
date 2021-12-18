#ifndef output_utils_H
#define output_utils_H

#include "data_structures/linked_list.h"
#include <math.h>
#include <stdio.h>

/** @brief add new process to finished process 
 *  @param p process to calculate waiting time
 *  @return void
 * 
 */
void add_new_finished_pros(process prs)
{
    insert_begin(prs);
} 
/** @brief calculate  turn around to certain process
 *  @param p process to calculate waiting time
 *  @return  turn around
 * 
 */
double out_get_trn_arnd_time(process p)
{
    return p.finish_time-p.arrival_time;
}
/** @brief calculate weighted turn around to certain process
 *  @param p process to calculate waiting time
 *  @return weighted turn around
 * 
 */
double out_get_weighted_turn_around(process p)
{

    return out_get_trn_arnd_time(p)/p.run_time;
}
/** @brief calculate waiting time to certain process
 *  @param p process to calculate waiting time
 *  @return waiting time.
 * 
 */
double out_get_waiting_time(process p)
{
    return (p.finish_time - p.arrival_time)-p.run_time;
}
/** @brief calculate average weighted turn around time
 *  @return average weighted turn around time.
 * 
 */
double get_avg_weighted_turn_around()
{
     ll_node *ptr;
        if(start==NULL)
        {
                return 0;
        }
        else
        {
                ptr=start;
                double sum_wgt_trn_arnd=0;
                double counter=0;
                while(ptr!=NULL)
                {
                    counter= counter +1;
                    sum_wgt_trn_arnd=sum_wgt_trn_arnd+out_get_weighted_turn_around(ptr->info);
                    ptr=ptr->next ;
                }
                double avg_wgt_trn_arnd=(1/counter)*sum_wgt_trn_arnd;
                return avg_wgt_trn_arnd;
        }
    
}
/** @brief calculate average waiting time
 *  @return average waiting time.
 * 
 */
double get_avg_waiting_time()
{
     ll_node *ptr;
        if(start==NULL)
        {
                return 0;
        }
        else
        {
                ptr=start;
                double sum_wtng_time=0;
                double counter=0;
                while(ptr!=NULL)
                {
                    counter= counter +1;
                    sum_wtng_time=sum_wtng_time+out_get_waiting_time(ptr->info);
                    ptr=ptr->next ;
                }
                double avg_wtng_time=(1/counter)*sum_wtng_time;
                return avg_wtng_time;
        }
}
/** @brief calculate standard deviation of weighted turn around time
 *  @param avg_weigted_trn_arnd mean vallue fo weighted turn around times
 *  @return std.
 * 
 */
double get_std_WTA(double avg_weigted_trn_arnd)
{
     ll_node *ptr;
        if(start==NULL)
        {
                return 0;
        }
        else
        {
                ptr=start;
                double sum_subtractions=0;
                double counter=0;
                while(ptr!=NULL)
                {
                    counter= counter +1;
                    sum_subtractions=sum_subtractions+(out_get_weighted_turn_around(ptr->info)-avg_weigted_trn_arnd)*(out_get_weighted_turn_around(ptr->info)-avg_weigted_trn_arnd);
                    ptr=ptr->next ;
                }
                double std=sqrt((1/counter)*sum_subtractions);
                return std;
        }
}

double calc_cpu_util()
{
     ll_node *ptr;
        if(start==NULL)
        {
                return 0;
        }
        else
        {
                ptr=start;
                double sum_running_times=0;
                double counter;
                double finish=0;
                double start_of_first_prs=0;
                while(ptr!=NULL)
                {
                    if(ptr->info.identity ==1)
                        start_of_first_prs=ptr->info.arrival_time;
                    counter= counter +1;
                    if(ptr->info.finish_time > finish)
                        finish=ptr->info.finish_time;
                    sum_running_times=sum_running_times+ptr->info.run_time;
                    ptr=ptr->next ;
                }
                finish=finish-start_of_first_prs;
                double cpu_util=(sum_running_times)/(finish);
                return cpu_util;
        }
}
/** @brief create output file in perf format\
 *  @param util cpu utilizatiokn
 *  @param avg_wgt_trn_arnd avg value of waiting time
 *  @param avg_weigted_trn_arnd mean vallue fo weighted turn around times
 *  @param std_wta standard deviation of weighted turn around time.
 *  @return void.
 * 
 */
void create_perf(double util, double avg_wgt_trn_arnd,
                    double avg_waiting_time,
                    double std_wta)
{
    FILE * pFile;
    pFile = fopen("scheduler.perf", "w");   
    fprintf(pFile, "CPU utilization = %.2f  \naverage weighted turn around time = %.2f \naverage waiting time = %.2f \nstandard deviation of weighted turn around time = %.2f  \n", util,avg_wgt_trn_arnd,avg_waiting_time,std_wta);
    fclose(pFile);
}

/** @brief calculate 
 *          1- average weighted turn around time
 *          2-average waiting time
 *          3-standard deviation of weighted turn around time
 *  @return process.
 * 
 */
void do_calculations()
{
    //CPU utilization
    //Avg Weighted turnaround time
        //turn around time = finish time - arrivarl time
        //weighted turn around time= (turn around time)/ runtime
    //Average waiting time
        //waiting time = (finish time- arrival time)-runtime
        // avg = (1/count)*SUM(wating times)
    //std Weighted turn around time
            //sqrt(sum(x-m)/N)
            //1- get mean weighted turnaroud time --> from second '
            //2- sum subtractions
            //divide by count
    double cpu_utilization=calc_cpu_util();
    double avg_wgt_trn_arnd=get_avg_weighted_turn_around();
    double avg_waiting_time=get_avg_waiting_time();
    double std_wta=get_std_WTA(avg_wgt_trn_arnd);
    printf("CPU utilization: %f\n", cpu_utilization*100);
    printf("average weighted turn around time %.2f \n", avg_wgt_trn_arnd);
    printf("average waiting time %.2f \n", avg_waiting_time);
    printf("standard deviation of weighted turn around time %.2f \n", std_wta);

    create_perf(cpu_utilization*100, avg_wgt_trn_arnd, avg_waiting_time, std_wta);
}



#endif
