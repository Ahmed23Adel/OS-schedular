#ifndef process_generator_H
#define process_generator_H

int _total_count; //Total count of processes counted from reading a file.
/** @brief ask the used for their preferred algorithm
 *
 *  @return enum of chosed algorithm.
 */
scheduling_algorithms ask_for_alg();

/** @brief clear ipc, and destroys the clock
 *
 *  @param sig_num input from catching error
 *  @return Void.
 */
void _clear_resources(int sig_num);

/** @brief managing segmentation fault
 *
 *  @param sig_num input from catching error
 *  @return Void.
 */
void _clear_resources_seg_fault(int);  //To catch segmentation faults

/** @brief forks the clock 
 *  @return Void.
 */
void _fork_clk();

/** @brief managing segmentation fault
 *          used while debugging, to stop the clk
 *  @param sig_num input from catching error
 *  @return Void.
 */
void _clear_resources_seg_fault(int);  //To catch segmentation faults

/** @brief read input file
 *          and fill pcb
 *  @return Void.
 */
void _read_input_file();
/** @brief read each row of input file
 *  
 *  @param fPointer pointer to opened file    
 *  @return Void.
 */
void _read_each_row(FILE * fPointer);

void _read_input_file();

/** @brief it just skip first line
 *          Actully it just calls _is_exist_new_line
 *          but i created it for clarity 
 *  
 *  @param fPointer pointer to opened file   
 *  @param singleLine must be provided to put values in it.
 *  @return Void.
 */
void _skip_first_line(FILE ** fPointer,char *singleLine);

#endif