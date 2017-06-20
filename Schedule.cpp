#include <cstdlib>

#include "compile_option.h"
#include "schedule.h"

bool Schedule::addStudentToLesson(Student& stu, Lesson& les)
{
    if (!StudentFile::IsInFile(stu.getId()) || !LessonFile::IsInFile(les.getId())) {
        return false;
    }

    char lessonFileName[50];
    sprintf(lessonFileName, "data/StudentLesson/%d.data", stu.getId());
    fstream lessonFile(lessonFileName, fstream::out | fstream::binary | fstream::app);
    ID_t lessonId = les.getId();
    lessonFile.write(reinterpret_cast<char*>(&lessonId), sizeof(ID_t));

    char studentFileName[50];
    sprintf(studentFileName, "data/Lesson_studentSet/%d.data", les.getId());
    fstream stuFile(studentFileName, fstream::out | fstream::binary | fstream::app);
    ID_t studentId = stu.getId();
    stuFile.write(reinterpret_cast<char*>(&studentId), sizeof(ID_t));

    return true;
}

set<ID_t> Schedule::getLessonSet(Student& stu)
{
    char lessonFileName[50];
    sprintf(lessonFileName, "data/StudentLesson/%d.data", stu.getId());

    fstream lessonFile(lessonFileName, fstream::in | fstream::binary);

    set<ID_t> retSet;
    ID_t lesID;
    lessonFile.read(reinterpret_cast<char*>(&lesID), sizeof(ID_t));
    while (lessonFile) {
        retSet.insert(lesID);
        lessonFile.read(reinterpret_cast<char*>(&lesID), sizeof(ID_t));
    }

    return retSet;
}


set<ID_t> Schedule::getStudentSet(Lesson& les)
{
    char studentFileName[50];
    sprintf(studentFileName, "data/Lesson_studentSet/%d.data", les.getId());

    fstream stuFile(studentFileName, fstream::in | fstream::binary);
    stuFile.seekg(0, fstream::beg);

    set<ID_t> retSet;
    ID_t stuID;
    stuFile.read(reinterpret_cast<char*> (&stuID), sizeof(ID_t));

    while (stuFile) {
        retSet.insert(stuID);
        stuFile.read(reinterpret_cast<char*> (&stuID), sizeof(ID_t));
    }

    return retSet;
}

bool Schedule::deleteStudent(Student& stu)
{
    if (!StudentFile::IsInFile(stu.getId())) {
        return false;
    }

    //erase the record from the file
    StudentFile file;
    file.erase(stu);

    //delete all record from all of stu's lessons
    set<ID_t> lesSet = getLessonSet(stu);
    for (set<ID_t>::iterator lesIter = lesSet.begin(); lesIter != lesSet.end(); ++lesIter) {
        Lesson les(*lesIter);
        set<ID_t> studentSetOfLesson = Schedule::getStudentSet(les);

        studentSetOfLesson.erase(stu.getId());

        //get the correct name
        char studentFileName[50];
        sprintf(studentFileName, "data/Lesson_studentSet/%d.data", les.getId());

        fstream newFile(studentFileName, fstream::out | fstream::binary);

        for (set<ID_t>::iterator iter = studentSetOfLesson.begin();
            iter != studentSetOfLesson.end(); ++iter) {
            ID_t id = *iter;
            newFile.write(reinterpret_cast<char*>(&id), sizeof(ID_t));
        }
    }

    //remove the coresponding file
    char lessonOfTheStudent[50];
    sprintf(lessonOfTheStudent, "data/StudentLesson/%d.data", stu.getId());
    remove(lessonOfTheStudent);

    return true;
}

bool Schedule::deleteLesson(Lesson& les)
{
    if (!LessonFile::IsInFile(les.getId())) {
        return false;
    }

    //erase the les from the file
    LessonFile file;
    file.erase(les);

    //delete lesson's record from it's students' schedule
    set<ID_t> stuSet = getStudentSet(les);
    for (set<ID_t>::iterator stuIter = stuSet.begin(); stuIter != stuSet.end(); ++stuIter) {
        Student stu(*stuIter);
        set<ID_t> lessonSetOfStudent = Schedule::getLessonSet(stu);

        lessonSetOfStudent.erase(les.getId());

        //get the correct name
        char lessonFileName[50];
        sprintf(lessonFileName, "data/StudentLesson/%d.data", stu.getId());

        fstream newFile(lessonFileName, fstream::out | fstream::binary);

        for (set<ID_t>::iterator iter = lessonSetOfStudent.begin();
            iter != lessonSetOfStudent.end(); ++iter) {
            ID_t id = *iter;
            newFile.write(reinterpret_cast<char*>(&id), sizeof(ID_t));
        }
    }

    //remove the coresponding file
    char studentOfTheLesson[50];
    sprintf(studentOfTheLesson, "data/Lesson_studentSet/%d.data", les.getId());
    remove(studentOfTheLesson);

    return true;
}

size_t Schedule::getTheStudentCount(Lesson& les)
{
    char lessonOfTheStudent[50];
    sprintf(lessonOfTheStudent, "data/Lesson_studentSet/%d.data", les.getId());

    fstream file(lessonOfTheStudent, fstream::in | fstream::ate | fstream::binary);

    return file.tellg() / sizeof(ID_t);
}
