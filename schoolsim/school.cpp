#include <iostream>
#include <string>

#include "classes.h"

/* ===================================||  S T U D E N T  F U N C T I O N S  ||===================================== */

Student::Student(std::string name, struct ClassInfo ClassInfo, std::string location) {
    this->name = name; 
    this->ClassInfo = ClassInfo;
    this->location = location;
    std::cout << "\nA New Student has been created!\n";
    std::cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo <<
    " Location: " << getLocation() << std::endl;
}

Student::~Student(){
    std::cout << "\nA Student to be destroyed!\n";
    std::cout << getName() << ", Class " << getClassInfo().classNo << " / Floor " << 
    getClassInfo().floorNo << ", Location: " << getLocation() << "\n\n";
}

/* ===================================||  T E A C H E R  F U N C T I O N S  ||===================================== */

Teacher::Teacher(std::string name, struct ClassInfo ClassInfo, bool inClass) {
    this->name = name;
    this->ClassInfo = ClassInfo;
    this->inClass = inClass;
    std::cout << "\nA New Teacher has been created!\n";
    std::cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo << " Location: ";
    getLocation() ? std::cout << "In Class\n" : std::cout << "Not in Class\n";
}

Teacher::~Teacher(){
    std::cout << "\nA Teacher to be destroyed!\n";
    std::cout << getName() << " Class " << getClassInfo().classNo << " / Floor " << getClassInfo().floorNo << " Location: ";
    getLocation() ? std::cout << "In Class\n" : std::cout << "Not in Class\n";
    /* No need for memory operations. That's STL job and magic! */
}

/* =====================================||  C L A S S  F U N C T I O N S  ||======================================== */

Class::Class(const us ClassNo, const ui C_class){
    std::cout << "A New Class has been created!\n\n";
    this->ClassNo = ClassNo;
    this->StudentsCount = 0;
    this->students = new Student*[C_class];
}

Class::~Class(){
    std::cout << "A Class to be destroyed!\n\n";
    delete this->teacher;
    for(ui i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Class::enter(Student *s){
    this->students[StudentsCount++] = s;
    std::cout << s->getName() << " enters classroom!\n";
    Locations tmp = inclass;
    s->setLocation(LocTable[tmp]);
}

void Class::place(Teacher *t) { 
    if (this->teacher!=NULL) {
        std::cerr << "This class has teacher!\n";
        return;
    }
    this->teacher = t;     
    t->setLocation(true); 
    std::cout << "Teacher " << this->teacher->getName() << " enters classroom!\n";
}

void Class::print(){
    std::cout << "People in class " << this->ClassNo << " are: \n";
    std::cout<< this->StudentsCount << std::endl;
    
    for (ui i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        std::cout << students[i]->getName() << " ";
    }
    if (this->teacher != NULL) std::cout << "\nThe teacher is: " << this->teacher->getName() << "\n\n";
    else std::cout << "\nNo teacher in this classroom!\n";
    std::cout << std::endl;
}

/* =====================================||  F L O O R  F U N C T I O N S  ||======================================== */

Floor::Floor(const us FloorNo, const ui C_class, const ui C_corr){
    this->FloorNo = FloorNo;
    this->Capacity = C_class*6; // there are six classes in each floor
    corridor = new Corridor(C_corr);
    for (us i = 0 ; i < 6; i++){
        classes[i] = new Class(i+1, C_class);
    }
    std::cout << "A New Floor has been created!\n\n";
}

Floor::~Floor(){
    std::cout << "A Floor to be destroyed!\n\n";
    delete corridor;
    for (us i = 0 ; i < 6; i++){
        delete classes[i];
    }
}

void Floor::enter(Student *s){
    if (corridor->isFull()){
        std::cerr << "Can't enter Floor. Corridor is full!\n";
        return;
    }
    std::cout << s->getName() << " enters floor " << this->FloorNo << "!\n";
    Locations tmp = infloor;
    s->setLocation(LocTable[tmp]);
    corridor->enter(s);
}

void Floor::placeInClass(Student *s){
    us ClassNo;
    ClassNo = s->getClassInfo().classNo;
    if (classes[ClassNo-1]->isFull()) {
        std::cerr << "Can't enter. Class is full!\n";
        return;
    }
    classes[ClassNo-1]->enter(s);
}

Student* Floor::exit(){
    if (corridor->getStudentsCount() <= 0) {
        std::cerr << "Floor is empty!\n";
        return NULL;
    }
    Student *temp; temp = corridor->exit();
    return temp;
}

void Floor::place(Teacher *t){
    us ClassNo = t->getClassInfo().classNo;
    classes[ClassNo-1]->place(t);
}

void Floor::print(){
    std::cout << "\nFloor number " << this->FloorNo << " contains:\n\n";
    this->corridor->print();
    
    for(us i=1; i<=6; i++)
        classes[i-1]->print();
}

/* ===================================||  C O R R I D O R  F U N C T I O N S  ||====================================== */

Corridor::Corridor(const ui C_corr){
    std::cout << "A New Corridor has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_corr;
    this->students = new Student*[C_corr];
}

Corridor::~Corridor(){
    std::cout << "A Corridor to be destroyed!\n\n";
    for(ui i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Corridor::enter(Student *s){
    this->students[StudentsCount++] = s;
    std::cout << s->getName() << " enters corridor!\n";
    Locations tmp = incorridor;
    s->setLocation(LocTable[tmp]);
}

Student* Corridor::exit(){
    if (StudentsCount <= 0) {
        std::cerr << "Corridor is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    std::cout << temp->getName() << " exits corridor!\n";
    return temp;
}

void Corridor::print(){
    std::cout << "People in corridor are: \n";
    std::cout << StudentsCount << std::endl;
    for (ui i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        std::cout << students[i]->getName() << " ";
    }
    std::cout << std::endl;
}

/* ======================================||  S T A I R  F U N C T I O N S  ||======================================== */

Stair::Stair(const ui C_stair){
    std::cout << "A New Stair has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_stair;
    this->students = new Student*[C_stair];
}

Stair::~Stair(){
    std::cout << "A Stair to be destroyed!\n\n";
    for(ui i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Stair::enter(Student *s){
    this->students[StudentsCount++] = s;
    std::cout << s->getName() << " enters stairs!\n";
    Locations tmp = instair;
    s->setLocation(LocTable[tmp]);
}

Student* Stair::exit(){
    if (StudentsCount <= 0) {
        std::cerr << "Stair is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    std::cout << temp->getName() << " exits stairs!\n";
    return temp;
}

void Stair::print(){
    std::cout << "People in stairs are:\n";
    std::cout << this->StudentsCount << std::endl;

    for (ui i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        std::cout << students[i]->getName() << " ";
    }
    std::cout << std::endl;
}

/* ========================================||  Y A R D  F U N C T I O N S  ||======================================== */

Yard::Yard(const ui C_yard){
    std::cout << "A New Yard has been created!\n\n";
    this->StudentsCount = 0;
    this->Capacity = C_yard;
    this->students = new Student*[C_yard];
}

Yard::~Yard(){
    std::cout << "A Yard to be destroyed!\n\n";
    for(ui i=0; i<StudentsCount; i++)
        delete students[i];
    delete students;
}

void Yard::enter(Student *s){
    this->students[StudentsCount++] = s;
    std::cout << s->getName() << " enters schoolyard!\n";
    Locations tmp = inyard;
    s->setLocation(LocTable[tmp]);
}

Student* Yard::exit(){
    if (StudentsCount <= 0) {
        std::cerr << "Schoolyard is empty!\n";
        return NULL;
    }
    Student *temp = this->students[--StudentsCount];
    this->students[StudentsCount] = NULL;
    std::cout << temp->getName() << " exits schoolyard!\n";
    return temp;
}

void Yard::print(){
    std::cout << "People in schoolyard are:\n";
    std::cout << StudentsCount << std::endl;
    for (ui i=0; i<StudentsCount; i++){
        if (this->students[i] == NULL) continue;
        std::cout << students[i]->getName() << " ";
    }
    std::cout << "\n\n";
}

/* ====================================||  S C H O O L  F U N C T I O N S  ||======================================== */

School::School(const ui C_class, const ui C_yard, const ui C_stair, const ui C_corr){
    this->yard = new Yard(C_yard);
    this->stair = new Stair(C_stair);
    for (us i = 1; i <= 3; i++){
        this->floor[i-1] = new Floor(i, C_class, C_corr);
    }
    std::cout << "A New School has been created!\n\n";
}

School::~School(){
    std::cout << "\nA School to be destroyed!\n\n";
    delete yard;
    delete stair;
    for (us i = 0; i < 3; i++){
        delete floor[i];
    }
}

bool School::enter(Student *s){
    if (yard->isFull()) {
        std::cerr << "Can't enter School. Yard is full!\n";
        return false;
    }
    std::cout << s->getName() << " enters school!\n";
    yard->enter(s);
    return true;
}

void School::enter(Teacher *t){
    std::cout << "Teacher " << t->getName() << " enters school!\n";
    us floorNo = t->getClassInfo().floorNo;
    floor[floorNo-1]->place(t);
}

bool School::OrganizeStudents(){

    /* MOVE STUDENTS FROM YARD TO STAIR */
    Student **yardStudents;
    yardStudents = yard->getStudents();

    for (ui i=yard->getStudentsCount(); i>0; i--){
        if (yardStudents[i-1] == NULL) continue;
        if (!stair->isFull()) {
            stair->enter(yard->exit()); 
            yardStudents[i-1] = NULL;     
        }
    }

    /* STAIR TO FLOOR (CORRIDOR) */
    Student **stairStudents;
    stairStudents = stair->getStudents();

    for (ui i=stair->getStudentsCount(); i>0; i--){
        if (stairStudents[i-1] == NULL) continue;
        us floorNo = stairStudents[i-1]->getClassInfo().floorNo;
        if (!floor[floorNo-1]->isCorridorFull()) {
            Student *tmp = stair->exit();
            floor[floorNo-1]->enter(tmp);   
            stairStudents[i-1] = NULL;        
        }
    }

    /* CORRIDOR TO CLASS */
    for (us i=0; i<3; i++) {

        Student **corridorStudents;
        corridorStudents = floor[i]->getCorridorStudents();

        for (ui j=floor[i]->getCorridorStudentsCount(); j>0; j--){
            if (corridorStudents[j-1] == NULL) continue;
            us ClassNo = corridorStudents[j-1]->getClassInfo().classNo;
            if (!floor[i]->isClassFull(ClassNo)) {
                Student *tmp = floor[i]->exit();
                floor[i]->placeInClass(tmp);    
                corridorStudents[j-1] = NULL;     
            }
        }
    }

    /* Checking if there are students that are in the School building but not in their classroom */
    std::cout << "\n%%% In schoolyard " << yard->getStudentsCount() << std::endl;
    std::cout << "%%% In stair " <<stair->getStudentsCount() << std::endl;
    ui totalCorrStudentsLeft;
    totalCorrStudentsLeft = floor[0]->getCorridorStudentsCount() + floor[1]->getCorridorStudentsCount() > 0 + floor[2]->getCorridorStudentsCount();
    std::cout << "%%% In corridors " <<totalCorrStudentsLeft << "\n\n";

    if (!yard->isEmpty() || stair->getStudentsCount() > 0 || floor[0]->getCorridorStudentsCount() > 0
    || floor[1]->getCorridorStudentsCount() > 0 || floor[2]->getCorridorStudentsCount() > 0) {
        std::cout << "\nSome students are still out of their classrooms!\n";
        return false;
    } 
    return true;
}
        
void School::print(){
    std::cout << "\n====================================================\n";
    std::cout << "\n\nSchool life consists of:\n\n";
    this->yard->print();
    this->stair->print();
    for (us i=0; i<3; i++)
        this->floor[i]->print();
}