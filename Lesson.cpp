#include "Lesson.h"
#include "Student.h"
#include "compile_option.h"

Lesson::Lesson() : id(INT_MAX), MaxStudentCount(INT_MAX)
{
    strcpy(name, "error");
    strcpy(introduction, "error");
    strcpy(teacherName, "error");
}

Lesson::Lesson(ID_t id) : id(INT_MAX), MaxStudentCount(INT_MAX)
{
    LessonFile file;
    for (LessonFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).id == id) {
            (*this) = *iter;
            break;
        }
    }
}

string Lesson::getName() const
{
    return name;
}

string Lesson::getTeacherName() const
{
    return teacherName;
}

string Lesson::getIntorduction() const
{
    return introduction;
}

int Lesson::getMaxStudentNumber() const
{
    return MaxStudentCount;
}

int Lesson::getId() const
{
    return id;
}

//======================================================================================

LessonFile::iterator& LessonFile::iterator::operator ++()
{
    ptr += sizeof(Lesson);
    return *this;
}

LessonFile::iterator LessonFile::iterator::operator ++(int)
{
    LessonFile::iterator ret(ptr);
    ptr += sizeof(Student);
    return ret;
}

Lesson LessonFile::iterator::operator*() const
{
    Lesson les;
    LessonFile file;
    LessonFile::lessonFile.seekg(ptr);
    LessonFile::lessonFile.read(reinterpret_cast<char*>(&les), sizeof(Lesson));
    return les;
}

//======================================================================================
fstream LessonFile::lessonFile("data/LessonInfo.data",
    fstream::in | fstream::out | fstream::binary);

LessonFile::LessonFile()
{
    fresh();
}

bool LessonFile::IsInFile(int id) {
    for (LessonFile::iterator iter = begin(); iter != end(); ++iter) {
        if ((*iter).getId() == id) {
            return true;
        }
    }
    return false;
}

void LessonFile::push_back(Lesson& newLes)
{
    if (!IsInFile(newLes.getId())) {
        //there is no same student
        lessonFile.seekp(0, fstream::end);
        lessonFile.write(reinterpret_cast<char*>(&newLes), sizeof(Lesson));
    }
}

void LessonFile::erase(Lesson& les)
{
    if (!IsInFile(les.getId())) {
        //there is no same student
        return;
    }

    lessonFile.clear();
    lessonFile.close();
    rename("data/LessonInfo.data", "data/temp");

    lessonFile.open("data/LessonInfo.data", fstream::out | fstream::binary);
    fstream temp("data/temp", fstream::in | fstream::binary);

    Lesson getLes;
    temp.read(reinterpret_cast<char*>(&getLes), sizeof(Lesson));
    while (getLes.getId() != les.getId()) {
        lessonFile.write(reinterpret_cast<char*>(&getLes), sizeof(Lesson));
        temp.read(reinterpret_cast<char*>(&getLes), sizeof(Lesson));
    }

    temp.read(reinterpret_cast<char*>(&getLes), sizeof(Lesson));

    while (temp) {
        lessonFile.write(reinterpret_cast<char*>(&getLes), sizeof(Lesson));
        temp.read(reinterpret_cast<char*>(&getLes), sizeof(Lesson));
    }

    Lesson tempLesson = *(begin());
    //I don't know why this sentence is neccessary, but without it an unknown bug occur

    temp.close();
    remove("data/temp");
    fresh();
}

//void startLesson(LessonPtr lesPtr);
//void stopLesson(LessonPtr lesPtr);

LessonFile::iterator LessonFile::begin()
{
    fresh();
    lessonFile.seekg(0, fstream::beg);
    return iterator
    (lessonFile.tellg() + static_cast<fstream::pos_type>(sizeof(Lesson)));
}

LessonFile::iterator LessonFile::end()
{
    fresh();
    lessonFile.seekg(0, fstream::end);
    return iterator(lessonFile.tellg());
}

void LessonFile::fresh()
{
    if (!lessonFile) {
        lessonFile.clear();
        lessonFile.close();
        lessonFile.open("data/LessonInfo.data",
            fstream::in | fstream::out | fstream::binary);
    }
}