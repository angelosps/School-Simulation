/* File: school.cpp */

#include <iostream>
#include <string>

#include "classes.h"

using namespace std;

/* ===================================||  S T U D E N T  F U N C T I O N S  ||===================================== */

Student::Student(string name, struct ClassInfo ClassInfo, string location) {
    this->name = name; 
    this->ClassInfo = ClassInfo;
    this->location = location;
    cout << "\nA New Student has been created!\n";
    cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo <<
    " Location: " << getLocation() << endl;
}

Student::~Student(){
    cout << "\nA Student to be destroyed!\n";
    cout << getName() << ", Class " << getClassInfo().classNo << " / Floor " << 
    getClassInfo().floorNo << ", Location: " << getLocation() << endl << endl;
}

/* ===================================||  T E A C H E R  F U N C T I O N S  ||===================================== */

Teacher::Teacher(string name, struct ClassInfo ClassInfo, bool inClass) {
    this->name = name;
    this->ClassInfo = ClassInfo;
    this->inClass = inClass;
    cout << "\nA New Teacher has been created!\n";
    cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo << " Location: ";
    getLocation() ? cout << "In Class\n" : cout << "Not in Class\n";
}

Teacher::~Teacher(){
    cout << "\nA Teacher to be destroyed!\n";
    cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo << " Location: ";
    getLocation() ? cout << "In Class\n" : cout << "Not in Class\n";
    /* No need for memory operations. That's STL job and magic! */
}

/* =====================================||  C L A S S  F U N C T I O N S  ||======================================== */

Class::Class(const unsigned short int ClassNo, const unsigned int C_class){
    cout << "A New Class has been created!\n\n";
    this->ClassNo = ClassNo;
    this->StudentsCount = 0;
    this->students = new Student*[C_class];
}

Class::~Class(){
    cout << "A Class to be destroyed!\n\n";
    delete this->teacher;
    for(int i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Class::enter(Student *s){
    this->students[StudentsCount++] = s;
    cout << s->getName() << " enters classroom!\n";
    Locations tmp = inclass;
    s->setLocation(LocTable[tmp]);
}

void Class::place(Teacher *t) { 
    if (this->teacher!=NULL) {
        cerr << "This class has teacher!\n";
        return;
    }
    this->teacher = t;     
    t->setLocation(true); 
    cout << "Teacher " << this->teacher->getName() << " enters classroom!\n";
}

void Class::print(){
    cout << "People in class " << this->ClassNo << " are: \n";
    cout<< this->StudentsCount <<endl;
    
    for (int i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        cout << students[i]->getName() << " ";
    }
    if (this->teacher != NULL) cout << "\nThe teacher is: " << this->teacher->getName() << endl << endl;
    else cout << "\nNo teacher in this classroom!\n";
    cout << endl;
}

/* =====================================||  F L O O R  F U N C T I O N S  ||======================================== */

Floor::Floor(const unsigned short int FloorNo, const unsigned int C_class, const unsigned int C_corr){
    this->FloorNo = FloorNo;
    this->Capacity = C_class*6; // there are six classes in each floor
    corridor = new Corridor(C_corr);
    for (int i = 0 ; i < 6; i++){
        classes[i] = new Class(i+1, C_class);
    }
    cout << "A New Floor has been created!\n\n";
}

Floor::~Floor(){
    cout << "A Floor to be destroyed!\n\n";
    delete corridor;
    for (int i = 0 ; i < 6; i++){
        delete classes[i];
    }
}

void Floor::enter(Student *s){
    if (corridor->isFull()){
        cerr << "Can't enter Floor. Corridor is full!\n";
        return;
    }
    cout << s->getName() << " enters floor " << this->FloorNo << "!\n";
    Locations tmp = infloor;
    s->setLocation(LocTable[tmp]);
    corridor->enter(s);
}

void Floor::placeInClass(Student *s){
    unsigned short int ClassNo;
    ClassNo = s->getClassInfo().classNo;
    if (classes[ClassNo-1]->isFull()) {
        cerr << "Can't enter. Class is full!\n";
        return;
    }
    classes[ClassNo-1]->enter(s);
}

Student* Floor::exit(){
    if (corridor->getStudentsCount() <= 0) {
        cerr << "Floor is empty!\n";
        return NULL;
    }
    Student *temp; temp = corridor->exit();
    return temp;
}

void Floor::place(Teacher *t){
    unsigned short ClassNo = t->getClassInfo().classNo;
    classes[ClassNo-1]->place(t);
}

void Floor::print(){
    cout << "\nFloor number " << this->FloorNo << " contains:\n\n";
    this->corridor->print();
    
    for(int i=1; i<=6; i++)
        classes[i-1]->print();
}

/* ===================================||  C O R R I D O R  F U N C T I O N S  ||====================================== */

Corridor::Corridor(const unsigned int C_corr){
    cout << "A New Corridor has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_corr;
    this->students = new Student*[C_corr];
}

Corridor::~Corridor(){
    cout << "A Corridor to be destroyed!\n\n";
    for(int i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Corridor::enter(Student *s){
    this->students[StudentsCount++] = s;
    cout << s->getName() << " enters corridor!\n";
    Locations tmp = incorridor;
    s->setLocation(LocTable[tmp]);
}

Student* Corridor::exit(){
    if (StudentsCount <= 0) {
        cerr << "Corridor is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    cout << temp->getName() << " exits corridor!\n";
    return temp;
}

void Corridor::print(){
    cout << "People in corridor are: \n";
    cout << StudentsCount << endl;
    for (int i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        cout << students[i]->getName() << " ";
    }
    cout << endl;
}

/* ======================================||  S T A I R  F U N C T I O N S  ||======================================== */

Stair::Stair(const unsigned int C_stair){
    cout << "A New Stair has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_stair;
    this->students = new Student*[C_stair];
}

Stair::~Stair(){
    cout << "A Stair to be destroyed!\n\n";
    for(int i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Stair::enter(Student *s){
    this->students[StudentsCount++] = s;
    cout << s->getName() << " enters stairs!\n";
    Locations tmp = instair;
    s->setLocation(LocTable[tmp]);
}

Student* Stair::exit(){
    if (StudentsCount <= 0) {
        cerr << "Stair is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    cout << temp->getName() << " exits stairs!\n";
    return temp;
}

void Stair::print(){
    cout << "People in stairs are:\n";
    cout << this->StudentsCount <<endl;

    for (int i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        cout << students[i]->getName() << " ";
    }
    cout << endl;
}

/* ========================================||  Y A R D  F U N C T I O N S  ||======================================== */

Yard::Yard(const unsigned int C_yard){
    cout << "A New Yard has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_yard;
    this->students = new Student*[C_yard];
}

Yard::~Yard(){
    cout << "A Yard to be destroyed!\n\n";
    for(int i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Yard::enter(Student *s){
    this->students[StudentsCount++] = s;
    cout << s->getName() << " enters schoolyard!\n";
    Locations tmp = inyard;
    s->setLocation(LocTable[tmp]);
}

Student* Yard::exit(){
    if (StudentsCount <= 0) {
        cerr << "Schoolyard is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    cout << temp->getName() << " exits schoolyard!\n";
    return temp;
}

void Yard::print(){
    cout << "People in schoolyard are:\n";
    cout << StudentsCount << endl;
    for (int i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        cout << students[i]->getName() << " ";
    }
    cout << endl << endl;
}

/* ====================================||  S C H O O L  F U N C T I O N S  ||======================================== */

School::School(const unsigned int C_class, const unsigned int C_yard, const unsigned int C_stair, const unsigned int C_corr){
    this->yard = new Yard(C_yard);
    this->stair = new Stair(C_stair);
    for (short i = 1; i <= 3; i++){
        this->floor[i-1] = new Floor(i, C_class, C_corr);
    }
    cout << "A New School has been created!\n\n";
}

School::~School(){
    cout << "\nA School to be destroyed!\n\n";
    delete yard;
    delete stair;
    for (short i = 0; i < 3; i++){
        delete floor[i];
    }
}

bool School::enter(Student *s){
    if (yard->isFull()) {
        cerr << "Can't enter School. Yard is full!\n";
        return false;
    }
    cout << s->getName() << " enters school!\n";
    yard->enter(s);
    return true;
}

void School::enter(Teacher *t){
    cout << "Teacher " << t->getName() << " enters school!\n";
    unsigned short floorNo = t->getClassInfo().floorNo;
    floor[floorNo-1]->place(t);
}

bool School::OrganizeStudents(){

    /* MOVE STUDENTS FROM YARD TO STAIR */
    Student **yardStudents;
    yardStudents = yard->getStudents();

    for (int i=yard->getStudentsCount()-1; i>=0; i--){
        if (yardStudents[i] == NULL) continue;
        if (!stair->isFull()) {
            stair->enter(yard->exit()); 
            yardStudents[i] = NULL;     
        }
    }

    /* STAIR TO FLOOR (CORRIDOR) */
    Student **stairStudents;
    stairStudents = stair->getStudents();

    for (int i=stair->getStudentsCount()-1; i>=0; i--){
        if (stairStudents[i] == NULL) continue;
        unsigned short int floorNo;
        floorNo = stairStudents[i]->getClassInfo().floorNo;
        if (!floor[floorNo-1]->isCorridorFull()) {
            Student *tmp = stair->exit();
            floor[floorNo-1]->enter(tmp);   
            stairStudents[i] = NULL;        
        }
    }

    /* CORRIDOR TO CLASS */
    for (int i=0; i<3; i++) {

        Student **corridorStudents;
        corridorStudents = floor[i]->getCorridorStudents();

        for (int j=floor[i]->getCorridorStudentsCount()-1; j>=0; j--){
            if (corridorStudents[j] == NULL) continue;
            unsigned short ClassNo = corridorStudents[j]->getClassInfo().classNo;
            if (!floor[i]->isClassFull(ClassNo)) {
                Student *tmp = floor[i]->exit();
                floor[i]->placeInClass(tmp);    
                corridorStudents[j] = NULL;     
            }
        }
    }

    /* Checking if there are students that are in the School building but not in their classroom */
    cout << "\n%%% In schoolyard " << yard->getStudentsCount() << endl;
    cout << "%%% In stair " <<stair->getStudentsCount() << endl;
    unsigned int totalCorrStudentsLeft;
    totalCorrStudentsLeft = floor[0]->getCorridorStudentsCount() + floor[1]->getCorridorStudentsCount() > 0 + floor[2]->getCorridorStudentsCount();
    cout << "%%% In corridors " <<totalCorrStudentsLeft << endl << endl;

    if (!yard->isEmpty() || stair->getStudentsCount() > 0 || floor[0]->getCorridorStudentsCount() > 0
    || floor[1]->getCorridorStudentsCount() > 0 || floor[2]->getCorridorStudentsCount() > 0) {
        cout << "\nSome students are still out of their classrooms!\n";
        return false;
    } 
    return true;
}
        
void School::print(){
    cout << "\n====================================================\n";
    cout << "\n\nSchool life consists of:\n\n";
    this->yard->print();
    this->stair->print();
    for (int i=0; i<3; i++)
        this->floor[i]->print();
}
