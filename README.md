# OS-schedular

Here we present parts of operating systems cores, CPU scheduling, and memory management.

in the CPU scheduler part, we implemented the following 

1-  HPF (Nonperemtive highest priority first)

2- SRTN (shortest remaining time next)

3- RR (Round-robin)

4-SJF (Shortest job first)

you can use process_generator to create files containing data for processes to be executed like data for running time, priority,...etc.

![image](https://user-images.githubusercontent.com/69484554/154485476-0dd65fbe-8e3f-4130-a158-1cbd69117ac4.png)


and then you can simply call make run to run the program and it will ask for the specified algorithm, and hence you can choose one and will the rest of work for you.

it will output like that, detailed report the processes and memory details in schedular.log, and in the scheduler. perf it will print overall performace

![unnamed](https://user-images.githubusercontent.com/69484554/154486099-c96f2f5e-fa25-46cf-8a47-6b174a2cc457.png)


![image](https://user-images.githubusercontent.com/69484554/154485785-93c40557-cc7f-49b5-9937-b4407dce9da9.png)


and also we provided mem.log that is generated to specify the details of memory management.


![unnamed (1)](https://user-images.githubusercontent.com/69484554/154486355-088c0e60-3953-4e60-9735-d7691c502a3f.png)


and we provided at the end of terminal points to be plotted by any software so that you can plot the processes execution like the following



![example1](https://user-images.githubusercontent.com/69484554/154486536-996c60c9-f094-442a-a828-2b2932eb16ed.png)


