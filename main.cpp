#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "askisi3.cpp"

using namespace std;

void swap(Person** p1, Person** p2){ //Used to shuffle arrays
    Person* swap = *p1;
    *p1 = *p2;
    *p2 = swap;
}

int main(int argc, char* argv[]){
    int Cclass = atoi(argv[1]);
    Junior::Lj = atoi(argv[2]);
    Senior::Ls = atoi(argv[3]);
    Teacher::Lt = atoi(argv[4]);
    int N = atoi(argv[5]);
    int teachcnt = 0; //Total number of teachers
    int floorNo = 1; //Used to create teachers' and students' info properly
    int studcnt = (Cclass) * 18; //Total number of students
    int no_to_destroy = studcnt;
    int randteach = 0; //Used to enter a random teacher
    srand(time(NULL));
//////////Creation of school//////////    
    School* school = new School(Cclass);

//////////Creation of nameslist//////////
    string nameslist[600];  //I get a list of name from a .txt file
    ifstream inFile;
    inFile.open("names.txt");
    if(inFile.is_open()){
        for(int i = 0; i < 600; i++){
            getline(inFile, nameslist[i]);
            nameslist[i][nameslist[i].size()-1]=' '; //Replace last index with ' '
        }
        inFile.close();
    }
    else{
        cout << "Error opening file";
    }


//////////Creation of teachers//////////
    Teacher** teachers = new Teacher*[18];
    while(teachcnt < 18){
        for(int classNo = 1; classNo <= 6; classNo++){
            teachers[teachcnt] = new Teacher(nameslist[teachcnt], floorNo, classNo, false);
            teachcnt++;
        }
        if (teachcnt % 6 == 0){  //For every 6 teachers created, move up one floor
            floorNo++;
        }
    }
    floorNo = 1;  //Floor number again equals to 1 to properly create students as well

//////////Creation of students//////////
    Student** students; 
    students = new Student*[studcnt];
    for(int i = 0; i < studcnt; ){
        for(int classNo = 1; classNo <= 3; classNo++){ //Classes 1-3 are for juniors
            students[i] = new Junior(nameslist[i+18], floorNo, classNo, false);
            i++;
        }
        for(int classNo = 4; classNo <= 6; classNo++){ //Classes 4-6 are for seniors
            students[i] = new Senior(nameslist[i+18], floorNo, classNo, false);
            i++;
        }
        floorNo++;
        if(floorNo == 4) floorNo = 1;
    }
//////////Shuffle students//////////
    for(int k = 0; k < studcnt; k++){ //Shuffle array of students
        int i = rand() % studcnt;
        int j = rand() % studcnt;
        swap(students[i], students[j]);
    }

//////////Shuffle teachers//////////
    for(int k = 0; k < teachcnt; k++){ //Shuffle array of teachers
        int i = rand() % teachcnt;
        int j = rand() % teachcnt;
        swap(teachers[i], teachers[j]);
    }

//////////Enter students//////////
    for(int i = 0; i < studcnt; i++){
        school->enter(students[i]);
        if(i < teachcnt){
            school->place(teachers[i]);
        }
    }
//////////School operating//////////
    school->operate(N);

//////////School print//////////
    school->print();

//////////Destruction of students//////////
    for(int i = 0; i < no_to_destroy; i ++){
        delete students[i];
    }
    delete[] students;

//////////Destruction of teachers//////////
    for(int i = 0; i < 18; i ++){
        delete teachers[i];
    }
    delete[] teachers;

//////////Destruction of school//////////
    delete school;
    
    return 0;
}