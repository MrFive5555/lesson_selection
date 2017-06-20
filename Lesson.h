#ifndef LESSON_H_
#define LESSON_H_

#include <fstream>
#include <string>
#include <set>
#include "File.h"

#define LESSON_NAME_LENGTH 15
#define TEACHER_NAME_LENGTH 10
#define INTRODUCTION_LENGTH 200

using std::string;
using std::fstream;
using std::set;

class Lesson {
public:
    Lesson();
    Lesson(ID_t id);

    string getName() const;
    string getTeacherName() const;
    string getIntorduction() const;
    int getMaxStudentNumber() const;
    int getId() const;

private:
    ID_t id;
    char name[LESSON_NAME_LENGTH];
    char teacherName[TEACHER_NAME_LENGTH];
    char introduction[INTRODUCTION_LENGTH];
    int MaxStudentCount;

    //friend class LessonFile;
    friend class Creator;
};

#endif // !LESSON_H_

