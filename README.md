# :school: School Simulation

This project is about simulating a school building.  

A school building consists of the following:  
* a schoolyard
* a stair
* three floors  

Each of the three floors consists of:
* a corridor
* six classrooms

So, we can organize the various spaces as follows:  
```bash
School
  |__ Schoolyard
  |__ Stair
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
The goal is to place all the students and the teachers into their classroom. Note that, a student cannot enter his classroom if the teacher is already in! Also, note that if any space is full then no more students can enter into that space.
A student, in order to be placed in its classroom, has to go through various places as follows:
```bash 
-> Schoolyard -> Stair -> the Corridor of the Floor where his Classroom is -> Classroom
```
Instead, each teacher can be placed directly into his classroom. 
After all, each of the students are exiting the school building in reverse order they entered in it and of course the teachers can be directly be placed out of the building.
