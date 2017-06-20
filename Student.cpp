#include "Student.h"
#include "Lesson.h"
#include "compile_option.h"

#include <cstdio>
#include <fstream>
#include <string>

using std::string;

//======================================================================================
Student::Student() : id(INT_MAX), gender(error), grade(INT_MAX)
{
    strcpy(name, "error");
}

Student::Student(ID_t id) : id(INT_MAX), gender(error), grade(INT_MAX)
{
    StudentFile file;
    strcpy(name, "error");
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).id == id) {
            (*this) = *iter;
            break;
        }
    }
}

int Student::getId() const
{
    return id;
}

string Student::getName() const
{
    return name;
}

Gender Student::getGender() const
{
    return gender;
}

int Student::getGrade() const
{
    return grade;
}

//======================================================================================
StudentFile::iterator& StudentFile::iterator::operator ++() {
    ptr += sizeof(Student);
    return *this;
}

StudentFile::iterator StudentFile::iterator::operator ++(int) {
    StudentFile::iterator ret(ptr);
    ptr += sizeof(Student);
    return ret;
}

StudentFile::iterator& StudentFile::iterator::operator --() {
    ptr -= sizeof(Student);
    return *this;
}

Student StudentFile::iterator::operator*() const {
    Student stu;
    fresh();
    stuFile.seekg(ptr);
    stuFile.read(reinterpret_cast<char*>(&stu), sizeof(Student));
    return stu;
}

//======================================================================================
fstream StudentFile::stuFile("data/studentInfo.data",
    fstream::in | fstream::out | fstream::binary);

StudentFile::StudentFile()
{
    fresh();
}

bool StudentFile::IsInFile(int id)
{
    for (StudentFile::iterator iter = begin(); iter != end(); ++iter) {
        if ((*iter).getId() == id) {
            return true;
        }
    }
    return false;
}

void StudentFile::push_back(Student& newStu)
{
    if (!IsInFile(newStu.getId())) {
        //there is no same student
        stuFile.seekp(0, fstream::end);
        stuFile.write(reinterpret_cast<char*>(&newStu), sizeof(Student));
    }
}

void StudentFile::erase(Student& Stu)
{
    if (!IsInFile(Stu.getId())) {
        //there is no same student
        return;
    }

    stuFile.clear();
    stuFile.close();
    rename("data/studentInfo.data", "data/temp");

    stuFile.open("data/studentInfo.data", fstream::out | fstream::binary);
    fstream temp("data/temp", fstream::in | fstream::binary);

    Student getStu;
    temp.read(reinterpret_cast<char*>(&getStu), sizeof(Student));
    while (getStu.getId() != Stu.getId()) {
        stuFile.write(reinterpret_cast<char*>(&getStu), sizeof(Student));
        temp.read(reinterpret_cast<char*>(&getStu), sizeof(Student));
    }

    temp.read(reinterpret_cast<char*>(&getStu), sizeof(Student));

    while (temp) {
        stuFile.write(reinterpret_cast<char*>(&getStu), sizeof(Student));
        temp.read(reinterpret_cast<char*>(&getStu), sizeof(Student));
    }

    Student tempStudent = *(begin()); 
    //I don't know why this sentence is neccessary, but without it an unknown bug occur

    temp.close();
    remove("data/temp");
    fresh();
}

StudentFile::iterator StudentFile::begin()
{
    fresh();
    stuFile.seekg(0, fstream::beg);
    return StudentFile::iterator
    (stuFile.tellg() + static_cast<fstream::pos_type>(sizeof(Student)));
}

StudentFile::iterator StudentFile::end()
{
    fresh();
    stuFile.seekg(0, fstream::end);
    return StudentFile::iterator(stuFile.tellg());
}

void StudentFile::fresh()
{
    if (!stuFile) {
        stuFile.clear();
        stuFile.close();
        stuFile.open("data/studentInfo.data",
            fstream::in | fstream::out | fstream::binary);
    }
}