/* File: main.c */

#include <iostream>
#include <string>
#include <fstream>  
#include <cstdlib> 
#include <vector>
#include <random>

#include "classes.h"

int main(int argc, char *argv[]){

    if (argc != 5) {  /* Error check */
        std::cerr << "\nUsage:\t" << argv[0] 
        << " <C_class> <C_yard> <C_stair> <C_corr>\n\n";
        exit(EXIT_FAILURE); 
    }

    ui C_class = atoi(argv[1]);
    ui C_yard = atoi(argv[2]);
    ui C_stair = atoi(argv[3]);
    ui C_corr = atoi(argv[4]);

    School *di = new School(C_class, C_yard, C_stair, C_corr);
    
    std::ifstream fin; fin.open("names.txt");
    std::string namesList[5000];   
    ui namesListSize = 0;

    while (fin) {
        std::string tmp;
        fin >> tmp; 
        namesList[++namesListSize] = tmp;
    }
    fin.close();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ui> rndC(C_class/2, C_class), rndN(0,namesListSize), rnd2(0,1);

    ui studentsCounter=0;
    Student *enterStudents[18*C_class+1];

    for(us i=1; i<=3; i++){
        for(us j=1; j<=6; j++){
            for(ui k=1; k<=rndC(gen); k++){ 
                ui n = rndN(gen);
                Locations loc = out;
                Student *st = new Student(namesList[n], (struct ClassInfo) {i,j}, LocTable[out]);
                enterStudents[studentsCounter++] = st;
            }
        }
    }    

    std::cout << "\n\nTotal students entered school: " << studentsCounter << std::endl;
    bool allStudentsIn; ui StudentsLeft = studentsCounter, tries = 5;

    for(;;){
        allStudentsIn = true;
        for (ui i=0; i<studentsCounter; i++) {
            if (enterStudents[i] == NULL) continue;
            if (di->enter(enterStudents[i])) enterStudents[i] = NULL, StudentsLeft--;
            else allStudentsIn = false;
        }
        std::cout << std::endl << StudentsLeft << " students are currently outside of School! \n\n";
        bool organized = di->OrganizeStudents();
        if (StudentsLeft == 0 && organized) {
            std::cout << "All students are in their classroom!\n";
            break;
        }
        if (tries-- == 0) {     // set a max number of tries in order to avoid big or infinite loops
            std::cout << "\nWARNING! Maximum tries to place the students into calssrooms reached! \n";
            std::cout << "Maybe too much students and small capacities entered.\n";
            std::cout << "No more students to be placed into their classrooms.\n\n";
            break;
        }
    } 

    bool choice = rnd2(gen);     // random choice if teachers will be placed in classrooms
    if (choice) {
        std::cout << "Teachers to be placed in classrooms!\n";
        for(ui i=1; i<=3; i++){
            for(ui j=1; j<=6; j++){
                ui n = rndN(gen);
                Teacher *t = new Teacher(namesList[n], (struct ClassInfo) {i,j}, false);
                di->enter(t);   // place the teacher into the school and right after in his classroom
            }
        }    
    } else {
        std::cout << "Teachers won't be placed in classrooms!\n";
    }
    
    di->print();  
    
    delete di;

    return 0;
}