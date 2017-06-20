#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <set>
#include <string>

using std::fstream;
using std::string;
using std::set;

typedef enum { male = 0, female, error } Gender;
typedef int ID_t; //id type

class Student;
class Lesson;

class StudentFile {
public:
    StudentFile();

    class iterator {
    private:
        size_t ptr;
    public:
        iterator() : ptr(NULL) {}
        iterator(const fstream::pos_type stuPtr)
            : ptr(static_cast<size_t>(stuPtr)) {}
        operator size_t() { return ptr; }
        iterator& operator ++();
        iterator operator ++(int);
        iterator& operator --();
        Student operator*() const;
        bool operator == (const iterator other) const { return this->ptr == other.ptr; }
        bool operator < (const iterator & other) const { return this->ptr < other.ptr; }
    };
    static iterator begin();
    static iterator end();

    static bool IsInFile(int id);
    static void push_back(Student& newStu);
    static void erase(Student& Stu);
private:

    static void fresh();
    static fstream stuFile; //Singleton Pattern
};


class LessonFile {
public:
    LessonFile();

    class iterator {
    private:
        size_t ptr;
    public:
        iterator() {};
        iterator(size_t lesPtr) : ptr(lesPtr) {};
        iterator(fstream::pos_type lesPtr) : ptr(static_cast<size_t>(lesPtr)) {};
        operator size_t() { return ptr; };
        iterator& operator ++();
        iterator operator ++(int);
        Lesson operator*() const;
        bool operator < (const iterator& otherIter) const
        {
            return this->ptr < otherIter.ptr;
        }
    };
    static iterator begin();
    static iterator end();

    static bool IsInFile(int id);
    static void push_back(Lesson& newLes);
    static void erase(Lesson& Les);
private:

    static void fresh();
    static fstream lessonFile; //Singleton Pattern
};

#endif // !FILE_H_