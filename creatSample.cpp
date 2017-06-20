#include <cstdlib>
#include <ctime>
#include <cstring>
#include <direct.h>
#include <iostream>
#include <io.h>

#include "compile_option.h"
#include "creator.h"
#include "Lesson.h"
#include "schedule.h"
#include "Student.h"

using namespace std;

void install() {
    mkdir("data");
    mkdir("data/StudentLesson");
    mkdir("data/Lesson_studentSet");
    mkdir("data/select");

    if (_access("data/LessonInfo.data", 0) != 0) {
        //no this file
        Lesson les;
        fstream file("data/LessonInfo.data", fstream::out);
        file.write(reinterpret_cast<char*>(&les), sizeof(Lesson));
    }
    if (_access("data/studentInfo.data", 0) != 0) {
        //no this file
        Student stu;
        fstream file("data/studentInfo.data", fstream::out);
        file.write(reinterpret_cast<char*>(&stu), sizeof(Student));
    }
    if (_access("data/password.data", 0) != 0) {
        //no this file
        Student stu;
        fstream file("data/password.data", fstream::out);
    }
    srand(static_cast<unsigned> (time(NULL)));
}

void Creator::creatStudentSample(int studentCount)
{
    srand(static_cast<unsigned> (time(NULL)));
    StudentFile file;
    for (int i = 0; i != studentCount; ++i) {
        Student stu;
        stu.id = 17340000 + i;
        string randName;
        for (int j = 0; j != 7; ++j) {
            randName.push_back('a' + rand() % 26);
        }
        strcpy(stu.name, randName.c_str());
        stu.gender = rand() % 2 == 0 ? male : female;
        stu.grade = rand() % 4 + 1;

        file.push_back(stu);
    }
}

void Creator::creatLessonSample(int lessonCount) 
{
    srand(static_cast<unsigned> (time(NULL)));
    LessonFile file;
    for (int i = 0; i != lessonCount; ++i) {
        Lesson les;
        les.id = i;
        string randName("lesson_");
        for (int j = 0; j != 5; ++j) {
            randName.push_back('a' + rand() % 26);
        }
        strcpy(les.name, randName.c_str());
        strcpy(les.introduction, "the introduction is not important");
        strcpy(les.teacherName, "Dr Tom");
        //les.MaxStudentCount = rand() % 100;
        les.MaxStudentCount = 1;

        file.push_back(les);
    }
}

Creator::STATE Creator::creatStudent
    (ID_t id, const char name[], Gender gender, int grade)
{
    if (StudentFile::IsInFile(id)) {
        return HAVE_SAME_ID;
    }
    if (strlen(name) >= STUDENT_NAME_LENGTH) {
        return TOO_LONG_LESSON_NAME;
    }
    if (grade <= 0 || grade > 4) {
        return ERROR_GRADE;
    }

    Student stu;
    stu.id = id;
    strcpy(stu.name, name);
    stu.gender = gender;
    stu.grade = grade;

    StudentFile::push_back(stu);
    return SUCCESS;
}
    
Creator::STATE Creator::creatLesson
    (ID_t id, const char name[], const char teacherName[], const char introduction[], int MaxStudentCount)
{
    if (LessonFile::IsInFile(id)) {
        return HAVE_SAME_ID;
    }
    if (strlen(name) >= LESSON_NAME_LENGTH) {
        return TOO_LONG_LESSON_NAME;
    }
    if (strlen(teacherName) >= TEACHER_NAME_LENGTH) {
        return TOO_LONG_TEACHER_NAME;
    }
    if (strlen(introduction) >= INTRODUCTION_LENGTH) {
        return TOO_LONG_INTRODUCTION;
    }
    if (MaxStudentCount <= 0) {
        return ERROR_MAX_COUNT;
    }

    Lesson les;
    les.id = id;
    strcpy(les.name, name);
    strcpy(les.teacherName, teacherName);
    strcpy(les.introduction, introduction);
    les.MaxStudentCount = MaxStudentCount;

    LessonFile::push_back(les);
    return SUCCESS;
}
