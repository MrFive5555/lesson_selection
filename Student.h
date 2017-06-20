#ifndef STUDENT_H_
#define STUDENT_H_

#include "File.h"

#define STUDENT_NAME_LENGTH 10

class StudentFile;

class Student {
public:
    Student();
    explicit Student(ID_t id);

    int getId() const;
    string getName() const;
    Gender getGender() const;
    int getGrade() const;

private:
    ID_t id;
    char name[STUDENT_NAME_LENGTH];
    Gender gender;
    int grade;

    friend class Creator;
};

#endif // !STUDENT_H