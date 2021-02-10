# :school: School Simulation

This project is about simulating a school building.  

A school building consists of the following:  
* a schoolyard
* a staircase
* three floors  

Each of the three floors consists of:
* a corridor
* six classrooms

So, we can organize the various spaces as follows:  
```bash
School
  |__ Schoolyard
  |__ Staircase
  |__ Floor1
  |     |__ Corridor
  |     |__ Classroom1
  |     |__ Classroom2
  |     |__ Classroom3
  |     |__ Classroom4
  |     |__ Classroom5
  |     |__ Classroom6
  |__ Floor2
  |     |__ Corridor
  |     |__ Classroom1
  |     |__ Classroom2
  |     |__ Classroom3
  |     |__ Classroom4
  |     |__ Classroom5
  |     |__ Classroom6
  |__ Floor3
        |__ Corridor
        |__ Classroom1
        |__ Classroom2
        |__ Classroom3
        |__ Classroom4
        |__ Classroom5
        |__ Classroom6
  
```
Of course, every school has some students and teachers. A number of students and teachers are created randomly, for each of the school classrooms. 
The goal is to place all the students and the teachers into their classroom. Note that each space of the school building has a capacity of students that can be in it at the same time. That means, if any space is full then no more students can enter into that space. All students of each classroom have to enter their classroom before the teacher gets in, otherwise they cannot enter their classroom and hence they miss the lesson!

A student, in order to be placed in its classroom, has to go through various places as follows:
```bash 
-> Schoolyard -> Staircase -> Corridor -> Classroom
```
Instead, each teacher can be placed directly into his classroom. 
After all, each of the students are exiting the school building in reverse order they entered in it and of course the teachers can be directly be placed out of the building.

## Compile and Run instructions
Makefile it is provided. Use the Makefile for compile, run and clean. 
In terminal, do the following:
```bash
$ make
$ make run
$ make clean
```
**Note:** "make run" does the following ```$ /schoolsim 2 36 36 36```. 
If you want to enter different argument values, run the executable manually by giving in terminal the following:  
``` bash
$ ./schoolsim <C_class> <C_yard> <C_stair> <C_corr> 
```
```bash
Where,  
<C_class> : capacity of each classroom.  
<C_yard>  : capacity of the schoolyard.  
<C_stair> : capacity of the staircase.  
<C_corr>  : capacity of each of the corridors.  
```


