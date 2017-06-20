#ifndef CREATSAMPLE_H_
#define CREATSAMPLE_H_

#include "File.h"

void install();

class Creator {
public:
    typedef enum {
        SUCCESS,
        HAVE_SAME_ID,
        TOO_LONG_LESSON_NAME,
        TOO_LONG_TEACHER_NAME,
        TOO_LONG_INTRODUCTION,
        ERROR_MAX_COUNT,
        ERROR_GRADE
    } STATE;
    static void creatStudentSample(int studentCount);
    static void creatLessonSample(int lessonCount);

    static STATE creatStudent(ID_t id, const char name[], Gender gender, int grade);
    static STATE creatLesson(ID_t id, const char name[], const char teacherName[], const char introduction[], int MaxStudentCount);
};
#endif // !CREATSAMPLE_H_

