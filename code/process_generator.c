#include "headers.h"
#include "process_generator.h"
#include "pcb.h"



node_priority* head;
int main(int argc, char * argv[])
{
    /*++++++++++++++++++++DECLarations++++++++++++++++++++*/
    head=NULL;
    /*++++++++++++++++++++Signal handlers+++++++++++++++++*/
    signal(SIGINT, _clear_resources);
    signal(SIGSEGV, _clear_resources_seg_fault);
    /*++++++++++++++++++++Chosen algorithm +++++++++++++++*/
    scheduling_algorithms chosen_alg =ask_for_alg();
    /*+++++++++++++++++++Read input files++++++++++++++++*/
    _read_input_file();
    /*++++++++++++++++++++Forking clock++++++++++++++++++*/
    _fork_clk();
    initClk();
    

    /*++++++++++++++++++++Sending process to schedular ++++++++++++++++++++*/
    while(true)
    {
        printf("Current clock: %d in seconds\n",getClk());
        sleep(1);
    }

    destroyClk(true);
}


scheduling_algorithms ask_for_alg()
{

    int answer;
    scheduling_algorithms chosed_alg;

    while(!(answer ==1 || answer ==2 | answer ==3))
    {
        printf("Please specifiy an algorithm for sceduling. \n 1: HPF \n 2: SRTN\n 3: RR \n");
        scanf("%i", &answer);

        switch (answer)
        {
        case 1:
            printf("Working with HPF, highest priority first \n ");
            return HPF;
            break;

         case 2:
            printf("Working with SRTN, Shortest remaing time next \n");
            return SRTN;
            break;
        case 3:
            printf("Working with RR, Round robin \n");
            return RR;
            break;
        
        default:
            break;
        }
       
    }


}

void _read_input_file()
{
    static const char filename[] = "processes.txt";
    FILE * fPointer;
    fPointer = fopen(filename, "r");
    _read_each_row(fPointer);
    fclose(fPointer);

}

void _read_each_row(FILE * fPointer)
{
    char singleLine[BUFSIZ];
    int ID, arrival, runtime, priority;
    _skip_first_line(&fPointer,singleLine);//To skip first line

    while (fgets(singleLine, sizeof singleLine, fPointer) != NULL)
    {
        if ( sscanf(singleLine, "%d", &ID) == 1 
            && sscanf(singleLine, "%*d\t%d", &arrival) == 1 
            && sscanf(singleLine, "%*d\t%*d\t%d", &runtime) == 1 
            && sscanf(singleLine, "%*d\t%*d\t%*d\t%d", &priority) == 1
            )
        {
            push_to_pcb(&head,create_process(ID,arrival,runtime,priority), priority);
            _total_count++;

        }
    }
}

void _skip_first_line(FILE **fPointer,char *singleLine)
{
    fgets(singleLine, sizeof singleLine, *fPointer) != NULL;
} 





void _clear_resources(int signum)
{
    destroyClk(true);
    //msgctl(set_msg_q_id(), IPC_RMID, NULL);
    exit(EXIT_SUCCESS);
}

void _clear_resources_seg_fault(int signum)
{
    printf("SegFault \n");
    _clear_resources(signum);
}

void _fork_clk()
{
    int pid;
    pid= fork();
    if (pid ==0)
    {
        //Child
        char *args[]= {"./clk.out",NULL};
        execvp(args[0],args);

    }
}


