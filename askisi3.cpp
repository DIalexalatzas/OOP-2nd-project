#include <iostream>
#include <string>
#include "askisi3.h"

using namespace std;

Person::Person(string name, int floorNo, int classNo, bool inClass)
    : name(name), floorNo(floorNo), classNo(classNo), inClass(inClass){
}

Person::~Person(){
}

string Person::get_name() const{
    return name;
}

int Person::get_floorNo() const{
    return floorNo;
}

int Person::get_classNo() const{
    return classNo;
}

bool Person::get_inClass() const{
    return inClass;
}

void Person::set_inClass(){
    inClass = true;
}

//////////////////////////////
int Teacher::Lt = 0; //Initialize to 0, valuse is given in main

Teacher::Teacher(string name, int floorNo, int classNo, bool inClass)
    : Person(name, floorNo, classNo, inClass){
        cout << "A New Teacher has been created! " << name 
            << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << endl;
}

Teacher::~Teacher(){
    cout << "A Teacher to be destroyed! " << name
        << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << " Fatigue: " << fatigue << endl;
}

void Teacher::print() const{
    cout << "The teacher is: " << name << " Fatigue: " << fatigue << "\n"<< endl;
}

void Teacher::teach(int N){
    fatigue += (Lt) * N;
}
//////////////////////////////
Student::Student(string name, int floorNo, int classNo, bool inClass)
    : Person(name, floorNo, classNo, inClass){
}

Student::~Student(){
}

void Student::print() const{
    cout << name << "Fatigue: " << fatigue << endl;
}
//////////////////////////////
int Junior::Lj = 0; //Initialize to 0, valuse is given in main

Junior::Junior(string name, int floorNo, int classNo, bool inClass)
    : Student(name, floorNo, classNo, inClass){
        cout << "A New Student has been created! " << name 
            << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << endl;
}

Junior::~Junior(){
    cout << "A Student to be destroyed! " << name 
        << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << " Fatigue: " << fatigue << endl;
}

void Junior::attend(int N){
    fatigue += (Lj) * N;
}

//////////////////////////////
int Senior::Ls = 0; //Initialize to 0, valuse is given in main

Senior::Senior(string name, int floorNo, int classNo, bool inClass)
    : Student(name, floorNo, classNo, inClass){
        cout << "A New Student has been created! " << name 
            << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << endl;
}

Senior::~Senior(){
    cout << "A Student to be destroyed! " << name 
        << "\nFloorNo: " << floorNo << " ClassNo: " << classNo << " Fatigue: " << fatigue << endl;
}

void Senior::attend(int N){
    fatigue += (Ls) * N;
}

//////////////////////////////
Space::Space(){
}

Space::~Space(){
}

//////////////////////////////
Operating::Operating(int Cclass) : Space(), Cclass(Cclass){
}

Operating::~Operating(){
}

//////////////////////////////
Non_operating::Non_operating() : Space(){
}
Non_operating::~Non_operating(){
}

void Non_operating::enter(Student* student){
    students[0] = student;
}

Student* Non_operating::exit(Student* student){
    students[0] = nullptr;
    return student;
}
//////////////////////////////
Yard::Yard() : Non_operating(){ 
    cout << "A New Yard has been created!" << endl;
}

Yard::~Yard(){
    cout << "A Yard to be destroyed!" << endl;
}

void Yard::enter(Student* student){
    Non_operating::enter(student);
    cout << student->get_name() << " enters Yard!" << endl;
}

Student* Yard::exit(Student* student){
    cout << student->get_name() << " exits Yard!" << endl;
    return Non_operating::exit(student);
}

//////////////////////////////
Stairs::Stairs() : Non_operating(){
    cout << "New Stairs have been created!" << endl;
}

Stairs::~Stairs(){
    cout << "Stairs to be destroyed!" << endl;
}

void Stairs::enter(Student* student){
    Non_operating::enter(student);
    cout << student->get_name() << " enters Stairs!" << endl;
}

Student* Stairs::exit(Student* student){
    cout << student->get_name() << " exits Stairs!" << endl;
    return Non_operating::exit(student);
}

//////////////////////////////
Corridor::Corridor() : Non_operating(){
    cout << "A New Corridor has been created!" << endl;
}

Corridor::~Corridor(){
    cout << "A Corridor to be destroyed!" << endl;
}

void Corridor::enter(Student* student){
    Non_operating::enter(student);
    cout << student->get_name() << " enters Corridor!" << endl;
}

Student* Corridor::exit(Student* student){
    cout << student->get_name() << " exits Corridor!" << endl;
    return Non_operating::exit(student);
}

//////////////////////////////
Classroom::Classroom(int Cclass, int floorNo, int classNo) : Operating(Cclass), floorNo(floorNo), classNo(classNo){
    students = new Student*[Cclass];
    teacher = nullptr;
    cout << "A New Classroom has been created!" << endl;
}

Classroom::~Classroom(){
    cout << "A Classroom to be destroyed!" << endl;
    delete[] students;
    teacher = nullptr;
    delete teacher;
}

int Classroom::get_classNo() const{
    return classNo;
}

int Classroom::get_floorNo() const{
    return floorNo;
}

void Classroom::enter(Student* student){
    students[counter] = student;
    counter++;
    student->set_inClass();
    cout << student->get_name() << " enters Classroom!" << " No: " << classNo << endl;
}

void Classroom::place(Teacher* teacher){
    cout << teacher->get_name() << " placed in Classroom!" << " No: " << classNo << endl;
    this->teacher = teacher;
    teacher->set_inClass();
}

void Classroom::operate(int N){
    teacher->teach(N);
    for(int i = 0; i < counter; i++){
        students[i]->attend(N);
    }
}

void Classroom::print() const{
    cout << "People in classroom " << classNo << " are:" << endl;
    for(int i = 0; i < counter; i++){
        students[i]->print();
    }
    cout << "\n";
    teacher->print();
}

//////////////////////////////
Floor::Floor(int Cclass, int floorNo) : Operating(Cclass), floorNo(floorNo){
    corridor = new Corridor();
    for(int i = 0; i < 6; i++){
        classes[i] = new Classroom(Cclass, floorNo, (i+1));
    }
    cout << "A New Floor has been created!" << endl;
}

Floor::~Floor(){
    cout << "A Floor to be destroyed!" << endl;
    for(int i = 0; i < 6; i++){
        delete classes[i];
    }
    delete corridor;
}

void Floor::enter(Student* student){
    cout << student->get_name() << " enters Floor!" << endl;
    corridor->enter(student);
    for(int i = 0; i < 6; i++){
        if(student->get_classNo() == (i+1)){ //classNo = [1,6] and i = [0,5]
            classes[i]->enter(corridor->exit(student));
        }
    }
}

void Floor::place(Teacher* teacher){
    cout << teacher->get_name() << " placed in Floor!" << " No: " << floorNo << endl;
    int classNo = teacher->get_classNo();
    classes[classNo-1]->place(teacher); //classes[0] has classNo = 1

}

void Floor::operate(int N){
    for(int i = 0; i < 6; i++){
        classes[i]->operate(N);
    }
}

void Floor::print() const{
    cout << "Floor number " << floorNo << " contains:\n" << endl;
    for(int i = 0; i < 6; i++){
        classes[i]->print();
    }
}

//////////////////////////////
School::School(int Cclass) : Operating(Cclass){
    yard = new Yard();
    stairs = new Stairs();
    for(int i = 0; i < 3; i++){
        floors[i] = new Floor(Cclass, (i+1)); //floors[0] has floorNo = 1
    }
    cout << "A New School has been created!" << endl;
}

School::~School(){
    cout << "A School to be destroyed!" << endl;
    for(int i = 0; i < 3; i ++){
        delete floors[i];
    }
    delete stairs;
    delete yard;
}

void School::enter(Student* student){
    cout << student->get_name() << " enters School!" << endl;
    yard->enter(student);
    stairs->enter(yard->exit(student));
    for(int i = 0; i < 3; i++){
        if(student->get_floorNo() == (i+1)){  //floors[0] has floorNo = 1
            floors[i]->enter(stairs->exit(student));
        }
    }
}

void School::place(Teacher* teacher){
    cout << teacher->get_name() << " placed in School!" << endl;
    int floorNo = teacher->get_floorNo();
    floors[floorNo-1]->place(teacher); //floors[0] has floorNo = 1

}

void School::operate(int N){
    for(int i = 0; i < 3; i++){
        floors[i]->operate(N);
    }
}

void School::print() const{
    cout << "\nSchool life consists of: " << endl;
    for(int i = 0; i < 3; i++){
        floors[i]->print();
    }
}
//////////////////////////////
