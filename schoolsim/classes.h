/* File: classes.h */

#pragma once

#include <string>

enum Locations { out, inyard, instair, infloor, incorridor, inclass };
const std::string LocTable[] = { "Outside the School", "Yard", "Stair", "Floor", "Corridor", "Classroom" };

namespace u{
    typedef unsigned short us;
    typedef unsigned int ui;
}

struct ClassInfo{
    u::us floorNo;
    u::us classNo;
};

class Student{
    std::string name;
    struct ClassInfo ClassInfo;
    std::string location;
    public:
        Student(std::string name, struct ClassInfo ClassInfo, std::string location);
        ~Student();
        std::string getName() const { return name; }
        struct ClassInfo getClassInfo() const { return ClassInfo; }
        std::string getLocation() const { return location; }
        void setLocation(std::string newloc) { this->location = newloc; }
};

class Teacher{
    std::string name;
    struct ClassInfo ClassInfo;
    bool inClass;
    public:
        Teacher(std::string name, struct ClassInfo ClassInfo, bool inClass);
        ~Teacher();
        std::string getName() const { return name; }
        struct ClassInfo getClassInfo() const { return ClassInfo; }
        bool getLocation() const { return inClass; }
        void setLocation(bool newloc) { this->inClass = newloc; }
};

class Class{
    Teacher *teacher;
    Student **students;
    u::us ClassNo;
    u::ui StudentsCount; // zero-based
    u::ui Capacity;
    public:
        Class(const u::us ClassNo, const u::ui C_class);
        ~Class();
        bool isFull() const { return ( StudentsCount == this->Capacity-1 ); }
        void enter(Student *);
        void place(Teacher *);
        void print();
};

class Corridor{
    Student **students;
    u::ui StudentsCount; // zero-based
    u::ui Capacity;
    public:
        Corridor(const u::ui C_corr);
        ~Corridor();
        bool isFull() const { return ( StudentsCount == this->Capacity-1 ); }
        void enter(Student *);
        Student* exit();
        Student** getStudents() const { return this->students; }
        u::ui getStudentsCount() const { return StudentsCount; }
        void print();
};

class Floor{
    Corridor *corridor;
    Class *classes[6];  
    u::us FloorNo;
    u::ui Capacity;
    public:
        Floor(const u::us FloorNo, const u::ui C_class, const u::ui C_corr);
        ~Floor();
        void enter(Student *);
        void place(Teacher *);
        void placeInClass(Student *);
        Student* exit();
        void print();
        u::ui getCapacity() const { return this->Capacity; };
        bool isCorridorFull() const { return this->corridor->isFull(); }
        Student** getCorridorStudents() const { return this->corridor->getStudents(); }
        u::ui getCorridorStudentsCount() const { return corridor->getStudentsCount(); }
        bool isClassFull(u::us ClassNo) const { return this->classes[ClassNo-1]->isFull(); }
};

class Stair{
    Student **students;
    u::ui StudentsCount; // zero-based
    u::ui Capacity;
    public:
        Stair(const u::ui C_stair);
        ~Stair();
        bool isFull() const { return ( StudentsCount == this->Capacity ); }
        void enter(Student *);
        Student* exit();
        void print();
        Student** getStudents() const { return students; }
        u::ui getStudentsCount() const { return StudentsCount; }
};

class Yard{
    Student **students;
    u::ui StudentsCount; // zero-based
    u::ui Capacity;
    public:
        Yard(const u::ui C_yard);
        ~Yard();
        bool isFull() const { return ( StudentsCount == this->Capacity ); }
        bool isEmpty() const { return (StudentsCount==0); }
        void enter(Student *);
        Student* exit();
        void print();
        Student** getStudents() const { return this->students; }
        u::ui getStudentsCount() const { return StudentsCount; }
};

class School{
    Floor *floor[3];    
    Yard *yard;      
    Stair *stair;      
    public:
        School(const u::ui C_class, const u::ui C_yard, const u::ui C_stair, const u::ui C_corr);
        ~School();
        bool enter(Student *);
        void enter(Teacher *);
        bool OrganizeStudents();  
        bool floorCapacity(u::us); 
        void pushInFloor(u::us floorNo, Student *st) { floor[floorNo-1]->enter(st); }
        void print();
};