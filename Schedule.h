#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <utility>
#include <map>
#include <vector>

#include "Lesson.h"
#include "Student.h"

using std::multimap;
using std::vector;

class Schedule {
public:
    static bool addStudentToLesson(Student& stu, Lesson& les);

    static bool deleteStudent(Student& stu);
    static bool deleteLesson(Lesson& les);

    static set<ID_t> getLessonSet(Student& stu);
    static set<ID_t> getStudentSet(Lesson& les);

    static size_t getTheStudentCount(Lesson& les);
};
#endif // !SCHEDULE_H_
