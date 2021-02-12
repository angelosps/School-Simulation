/* File: main.c */

#include <iostream>
#include <string>
#include <fstream>  
#include <ctime>    
#include <cstdlib> 
#include <vector>
#include <random>

#include "classes.h"

using namespace std;

int main(int argc, char *argv[]){

    if (argc != 5) {  /* Error check */
        cerr << "\nUsage:\t" << argv[0] 
        << " <C_class> <C_yard> <C_stair> <C_corr>\n" << endl;
        exit(EXIT_FAILURE); 
    }

    unsigned int C_class = atoi(argv[1]);
    unsigned int C_yard = atoi(argv[2]);
    unsigned int C_stair = atoi(argv[3]);
    unsigned int C_corr = atoi(argv[4]);

    School *di = new School(C_class, C_yard, C_stair, C_corr);
    
    ifstream fin; fin.open("names.txt");
    string namesList[5000];   
    unsigned int namesListSize = 0;

    while (fin) {
        string tmp;
        fin >> tmp; 
        namesList[++namesListSize] = tmp;
    }
    fin.close();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned> rndC(C_class/2, C_class), rndN(0,namesListSize), rnd2(0,1);

    int studentsCounter=0;
    Student *enterStudents[18*C_class+1];

    for(int i=1; i<=3; i++){
        for(int j=1; j<=6; j++){
            for(int k=1; k<=rndC(gen); k++){ 
                unsigned int n = rndN(gen);
                Locations loc = out;
                Student *st = new Student(namesList[n], (struct ClassInfo) {i,j}, LocTable[out]);
                enterStudents[studentsCounter++] = st;
            }
        }
    }    

    cout << "\n\nTotal students entered school: " << studentsCounter << endl;
    bool allStudentsIn; unsigned int StudentsLeft = studentsCounter, tries = 5;

    for(;;){
        allStudentsIn = true;
        for (int i=0; i<studentsCounter; i++) {
            if (enterStudents[i] == NULL) continue;
            if (di->enter(enterStudents[i])) enterStudents[i] = NULL, StudentsLeft--;
            else allStudentsIn = false;
        }
        cout << endl << StudentsLeft << " students are currently outside of School! \n\n";
        bool organized = di->OrganizeStudents();
        if (StudentsLeft == 0 && organized) {
            cout << "All students are in their classroom!\n";
            break;
        }
        if (tries-- == 0) {     // set a max number of tries in order to avoid big or infinite loops
            cout << "\nWARNING! Maximum tries to place the students into calssrooms reached! \n";
            cout << "Maybe too much students and small capacities entered.\n";
            cout << "No more students to be placed into their classrooms.\n\n";
            break;
        }
    } 

    bool choice = rnd2(gen);     // random choice if teachers will be placed in classrooms
    if (choice) {
        cout << "Teachers to be placed in classrooms!\n";
        for(unsigned int i=1; i<=3; i++){
            for(unsigned int j=1; j<=6; j++){
                unsigned int n = rndN(gen);
                Teacher *t = new Teacher(namesList[n], (struct ClassInfo) {i,j}, false);
                di->enter(t);   // place the teacher into the school and right after in his classroom
            }
        }    
    } else {
        cout << "Teachers won't be placed in classrooms!\n";
    }
    
    di->print();  
    
    delete di;

    return 0;
}