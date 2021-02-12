/* File: classes.h */

#pragma once

#include <string>

#define MAX_STUDENTS 1000

using namespace std;

enum Locations { out, inyard, instair, infloor, incorridor, inclass };
const string LocTable[] = { "Out of School", "Yard", "Stair", "Floor", "Corridor", "Class" };

struct ClassInfo{
    unsigned int floorNo;
    unsigned int classNo;
};

class Student{
    string name;
    struct ClassInfo ClassInfo;
    string location;
    public:
        Student(string name, struct ClassInfo ClassInfo, string location);
        ~Student();
        string getName() const { return name; }
        struct ClassInfo getClassInfo() const { return ClassInfo; }
        string getLocation() const { return location; }
        void setLocation(string newloc) { this->location = newloc; }
};

class Teacher{
    string name;
    struct ClassInfo ClassInfo;
    bool inClass;
    public:
        Teacher(string name, struct ClassInfo ClassInfo, bool inClass);
        ~Teacher();
        string getName() const { return name; }
        struct ClassInfo getClassInfo() const { return ClassInfo; }
        bool getLocation() const { return inClass; }
        void setLocation(bool newloc) { this->inClass = newloc; }
};

class Class{
    Teacher *teacher;
    Student **students;
    unsigned short int ClassNo;
    unsigned int StudentsCount; // zero-based
    unsigned int Capacity;
    public:
        Class(const unsigned short int ClassNo, const unsigned int C_class);
        ~Class();
        bool isFull() const { return ( StudentsCount == this->Capacity-1 ); }
        void enter(Student *);
        void place(Teacher *);
        void print();
};

class Corridor{
    Student **students;
    unsigned int StudentsCount; // zero-based
    unsigned int Capacity;
    public:
        Corridor(const unsigned int C_corr);
        ~Corridor();
        bool isFull() const { return ( StudentsCount == this->Capacity-1 ); }
        void enter(Student *);
        Student* exit();
        Student** getStudents() const { return this->students; }
        unsigned int getStudentsCount() const { return StudentsCount; }
        void print();
};

class Floor{
    Corridor *corridor;
    Class *classes[6];  
    unsigned short int FloorNo;
    unsigned int Capacity;
    public:
        Floor(const unsigned short int FloorNo, const unsigned int C_class, const unsigned int C_corr);
        ~Floor();
        void enter(Student *);
        void place(Teacher *);
        void placeInClass(Student *);
        Student* exit();
        void print();
        unsigned int getCapacity() const { return this->Capacity; };
        bool isCorridorFull() const { return this->corridor->isFull(); }
        Student** getCorridorStudents() const { return this->corridor->getStudents(); }
        unsigned int getCorridorStudentsCount() const { return corridor->getStudentsCount(); }
        bool isClassFull(unsigned short ClassNo) const { return this->classes[ClassNo-1]->isFull(); }
};

class Stair{
    Student **students;
    unsigned int StudentsCount; // zero-based
    unsigned int Capacity;
    public:
        Stair(const unsigned int C_stair);
        ~Stair();
        bool isFull() const { return ( StudentsCount == this->Capacity ); }
        void enter(Student *);
        Student* exit();
        void print();
        Student** getStudents() const { return students; }
        unsigned int getStudentsCount() const { return StudentsCount; }
};

class Yard{
    Student **students;
    unsigned int StudentsCount; // zero-based
    unsigned int Capacity;
    public:
        Yard(const unsigned int C_yard);
        ~Yard();
        bool isFull() const { return ( StudentsCount == this->Capacity ); }
        bool isEmpty() const { return (StudentsCount==0); }
        void enter(Student *);
        Student* exit();
        void print();
        Student** getStudents() const { return this->students; }
        unsigned int getStudentsCount() const { return StudentsCount; }
};

class School{
    Floor *floor[3];    
    Yard *yard;      
    Stair *stair;      
    public:
        School(const unsigned int C_class, const unsigned int C_yard, const unsigned int C_stair, const unsigned int C_corr);
        ~School();
        bool enter(Student *);
        void enter(Teacher *);
        bool OrganizeStudents();  
        bool floorCapacity(unsigned short); 
        void pushInFloor(unsigned short floorNo, Student *st) { floor[floorNo-1]->enter(st); }
        void print();
};