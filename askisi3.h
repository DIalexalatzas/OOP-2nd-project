#include <iostream>
#include <string>

using namespace std;

class Person{
    protected:
        string name;
        int floorNo;
        int classNo;
        bool inClass;
        int fatigue = 0;
    public:
        Person(string name, int floorNo, int classNo, bool inClass);
        virtual ~Person();
        virtual string get_name() const;
        virtual int get_floorNo() const;
        virtual int get_classNo() const;
        virtual bool get_inClass() const;
        virtual void set_inClass();
        virtual void print() const = 0;
};

class Teacher:public Person{
    public:
        static int Lt;
        Teacher(string name, int floorNo, int classNo, bool inClass);
        ~Teacher();
        void print() const;
        void teach(int N);
};

class Student:public Person{
    public:
        Student(string name, int floorNo, int classNo, bool inClass);
        virtual ~Student();
        virtual void print() const;
        virtual void attend(int N) = 0;
};

class Junior:public Student{
    public:
        static int Lj;
        Junior(string name, int floorNo, int classNo, bool inClass);
        ~Junior();
        void attend(int N);
};

class Senior:public Student{
    public:
        static int Ls;
        Senior(string name, int floorNo, int classNo, bool inClass);
        ~Senior();
        void attend(int N);
};
////////////////////////////////////////////////////////////////////////////////////


class Space{
    public:
        Space();
        virtual ~Space();
        virtual void enter(Student* s) = 0;
};

class Operating:public Space{
    protected:
        int Cclass;
    public:
        Operating(int Cclass);
        virtual ~Operating();
        virtual void enter(Student* student) = 0;
        virtual void place(Teacher* teacher) = 0;
        virtual void operate(int N) = 0;
        virtual void print() const = 0;
};

class Non_operating:public Space{
    protected:
        Student* students[1]; //Array of size 1
    public:
        Non_operating();
        virtual ~Non_operating() = 0;
        virtual void enter(Student* student);
        virtual Student* exit(Student* student);
};

class Yard:public Non_operating{ 
    public:
        Yard();
        ~Yard();
        void enter(Student* student);
        Student* exit(Student* student);
};

class Stairs:public Non_operating{
    public:
        Stairs();
        ~Stairs();
        void enter(Student* student);
        Student* exit(Student* student);
};

class Corridor:public Non_operating{
    public:
        Corridor();
        ~Corridor();
        void enter(Student* student);
        Student* exit(Student* student);
};

class Classroom:public Operating{
    private:
        int floorNo;
        int classNo;
        int counter = 0; //Students counter
        Teacher* teacher;
        Student** students;
    public:
        Classroom(int Cclass, int floorNo, int classNo);
        ~Classroom();
        int get_floorNo() const;
        int get_classNo() const;
        void enter(Student* student);
        void place(Teacher* teacher);
        void operate(int N);
        void print() const;
};

class Floor:public Operating{
    private:
        int floorNo;
        Corridor* corridor;
        Classroom* classes[6];
    public:
        Floor(int Cclass, int floorNo);
        ~Floor();
        void enter(Student* student);
        void place(Teacher* teacher);
        void operate(int N);
        void print() const;
};

class School:public Operating{
    private:
        Yard* yard;
        Stairs* stairs;
        Floor* floors[3];
    public:
        School(int Cclass);
        ~School();
        void enter(Student* student);
        void place(Teacher* teacher);
        void operate(int N);
        void print() const;
};