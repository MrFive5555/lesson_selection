#include <iostream>
#include <utility>

#include "Administrator.h"
#include "creator.h"
#include "File.h"
#include "Lesson.h"
#include "schedule.h"
#include "Student.h"

using std::cout;
using std::endl;
using std::pair;

//#define TEST_ERASE_STUDENT
#ifdef TEST_ERASE_STUDENT
int main()
{
    install();
    Creator::creatStudentSample(5);
    Student stu(0);
    StudentFile file;
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).getId() == INT_MAX) {
            continue;
        }
        cout << (*iter).getName() << " " << (*iter).getId()
            << " " << (*iter).getGrade() << endl;
    }

    file.erase(stu);

    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).getId() == INT_MAX) {
            continue;
        }
        cout << (*iter).getName() << " " << (*iter).getId()
            << " " << (*iter).getGrade() << endl;
    }
}

#endif

#ifdef TEST_MAIN
int main() {
    install();
    /**/
    Creator::creatStudentSample(2);
    Creator::creatLessonSample(5);


    //delete student(0)
    /*
    Student me(0);
    Schedule::deleteStudent(me);
    */


    //add student to lesson(0)
    /**/
    Schedule sch;
    Lesson lesIdOne(0);
    Lesson lesIdTwo(1);
    Student stu(1);
    for (int i = 0; i != 5; ++i) {
        sch.addStudentToLesson(stu, lesIdOne);
        sch.addStudentToLesson(stu, lesIdTwo);
    }


    //delete lesson(0)
    Lesson les_0(0);
    Schedule::deleteLesson(les_0);

    //display all student
    cout << "=============================" << endl << "list all student" << endl;
    StudentFile file;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).getId() == INT_MAX) {
            continue;
        }
        cout << (*iter).getName() << " " << (*iter).getId()
            << " " << (*iter).getGrade() << endl;
    }

    //display all lesson
    /**/
    LessonFile lesFile;
    cout << "=============================" << endl << "list all lesson" << endl;
    for (LessonFile::iterator iter = lesFile.begin(); iter != lesFile.end(); ++iter) {
        cout << (*iter).getLessonName() << " "
            << (*iter).getIntorduction() << endl;
    }


    //get student(0) lesson
    /**/
    cout << "================" << endl << "get student(0) lesson" << endl;
    Student stuId_0(0);
    LessonSet lesSet = Schedule::getLessonSet(stuId_0);
    cout << "my name is : " << stuId_0.getName() << endl;
    for (LessonSet::iterator iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
        cout << (*iter).getLessonName() << endl;
    }


    /*
    //check the student in lesson with id 0
    Lesson les(0);
    StudentSet stuSet = Schedule::getStudentSet(les);
    cout << "===================" << endl << "student set of Lesson(0) ; " << endl;
    for (StudentSet::iterator iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
    if ((*iter).getId() == INT_MAX) {
    continue;
    }
    cout << (*iter).getName() << endl;
    }
    */

    /*cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    for (int i = 0; i != 5; ++i) {
    Lesson len(i);
    StudentSet stuSet = Schedule::getStudentSet(len);
    cout << len.getLessonName() << " : ";
    for (StudentSet::iterator iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
    cout << (*iter).getId() << " " << (*iter).getName() << endl;
    }
    cout << endl << endl;
    }*/

    /*Student stu(100);
    cout << stu.getName() << " " << stu.getId() << " " << stu.getGrade();*/

}
#endif // TEST_MAIN

//#define FUNC_DELETESTUDENT
#ifdef FUNC_DELETESTUDENT
int main() {
    int const STUDENT_COUNT = 5;
    install();
    Creator::creatStudentSample(STUDENT_COUNT);
    Creator::creatLessonSample(5);

    //display all student
    StudentFile file;
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        Student stu = *iter;
        cout
            << "name: " << stu.getName() << " "
            << "id: " << stu.getId() << " "
            << "grade: " << stu.getGrade() << " "
            << "gender: " << stu.getGender() << endl;
    }

    //add student to lesson(0)
    Lesson lesIdOne(0);
    for (int i = 0; i != STUDENT_COUNT; ++i) {
        Student stu(i);
        sch.addStudentToLesson(stu, lesIdOne);
    }

    //delete student(0)
    Student me(0), me2(2);
    Schedule::deleteStudent(me);
    Schedule::deleteStudent(me2);

    cout << endl
        << "===================================" << endl
        << "delete student..." << endl
        << "===================================" << endl
        << endl;

    //display all student
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        Student stu = *iter;
        cout
            << "name: " << stu.getName() << " "
            << "id: " << stu.getId() << " "
            << "grade: " << stu.getGrade() << " "
            << "gender: " << stu.getGender() << endl;
    }

    //check the student in lesson with id 0
    Lesson les(0);
    set<ID_t> stuSet = Schedule::getStudentSet(les);
    cout << "===================" << endl << "student set of Lesson(0) ; " << endl;
    for (set<ID_t>::iterator iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
        Student stu(*iter);
        cout << stu.getName() << endl;
    }

}
#endif // !FUNC_DELETESTUDENT

//#define FUNC_DELETELESSON
#ifdef FUNC_DELETELESSON
//test function Schedule::deleteLesson(Lesson& les)
int main() {
    install();
    Creator::creatStudentSample(2);
    Creator::creatLessonSample(5);

    Lesson lesIdOne(0);
    Lesson lesIdTwo(1);
    Lesson lesIdThree(2);
    Student stu(0);
    for (int i = 0; i != 5; ++i) {
        Lesson lesWhat(i);
        Schedule::addStudentToLesson(stu, lesWhat);
        /*sch.addStudentToLesson(stu, lesIdOne);
        sch.addStudentToLesson(stu, lesIdTwo);
        sch.addStudentToLesson(stu, lesIdThree);*/
    }

    //get student(0) lesson
    cout << "================" << endl << "get student(0) lesson" << endl;
    Student stuId_00(0);
    set<ID_t> lesSet0 = Schedule::getLessonSet(stuId_00);
    cout << "my name is : " << stuId_00.getName() << endl;
    for (set<ID_t>::iterator iter = lesSet0.begin(); iter != lesSet0.end(); ++iter) {
        Lesson les(*iter);
        cout
            << les.getLessonName()
            << " id : " << les.getId()
            << " MaxStudent : " << les.getMaxStudentNumber() << endl;
    }

    //delete lesson(0)
    Lesson les_0(0);
    Schedule::deleteLesson(les_0);
    Schedule::deleteLesson(lesIdThree);

    //display all student
    StudentFile file;
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        Student stu = *iter;
        cout
            << "name: " << stu.getName() << " "
            << "id: " << stu.getId() << " "
            << "grade: " << stu.getGrade() << " "
            << "gender: " << stu.getGender() << endl;
    }

    //display all lesson
    LessonFile lesFile;
    cout << "=============================" << endl << "list all lesson" << endl;
    for (LessonFile::iterator iter = lesFile.begin(); iter != lesFile.end(); ++iter) {
        cout << (*iter).getLessonName() << " "
            << (*iter).getIntorduction() << endl;
    }

    //get student(0) lesson
    cout << "================" << endl << "get student(0) lesson" << endl;
    Student stuId(0);
    lesSet0 = Schedule::getLessonSet(stuId);
    cout << "my name is : " << stuId.getName() << endl;
    for (set<ID_t>::iterator iter = lesSet0.begin(); iter != lesSet0.end(); ++iter) {
        Lesson les(*iter);
        cout
            << les.getLessonName()
            << "id : " << les.getId()
            << "MaxStudent : " << les.getMaxStudentNumber() << endl;
    }
}

#endif // FUNC_DELETELESSON

//#define TEST_STUDENT_COUNT
#ifdef TEST_STUDENT_COUNT

int main()
{
    install();
    Creator::creatStudentSample(5);
    Creator::creatLessonSample(1);

    Lesson les(0);
    for (int i = 0; i != 5; ++i) {
        Student stu(i);
        Schedule::addStudentToLesson(stu, les);
    }

    set<ID_t> idSet = Schedule::getStudentSet(les);
    for (set<ID_t>::iterator iter = idSet.begin(); iter != idSet.end(); ++iter) {
        Student stu(*iter);
        cout << stu.getName() << endl;
    }

    cout << "the count of the les is : " << Schedule::getTheStudentCount(les) << endl;
}
#endif // TEST_STUDENT_COUNT

//#define TEST_ARRANGELESSON
#ifdef TEST_ARRANGELESSON
int main()
{
    install();
    Creator::creatStudentSample(4);
    Creator::creatLessonSample(2);

    StudentFile file;
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        if ((*iter).getId() == INT_MAX) {
            continue;
        }
        cout << (*iter).getName() << " " << (*iter).getId()
            << " " << (*iter).getGrade() << endl;
    }

    vector<ID_t> stuVec;
    for (int i = 0; i != 4; ++i) {
        stuVec.push_back(i);
    }

    multimap<ID_t, ID_t>requestMap;
    requestMap.insert(pair<ID_t,ID_t>(0, 0));
    requestMap.insert(pair<ID_t, ID_t>(0, 1));
    requestMap.insert(pair<ID_t, ID_t>(0, 2));
    requestMap.insert(pair<ID_t, ID_t>(1, 3));
    Schedule::arrangeLesson(stuVec, requestMap);

    Lesson les0(0);
    set<ID_t> stuSet0 = Schedule::getStudentSet(les0);
    cout << "===================" << endl << "student set of Lesson(0) ; " << endl;
    for (set<ID_t>::iterator iter = stuSet0.begin(); iter != stuSet0.end(); ++iter) {
        Student stu(*iter);
        cout << stu.getName() << " id : " << stu.getId() << endl;
    }

    Lesson les1(1);
    set<ID_t> stuSet1 = Schedule::getStudentSet(les1);
    cout << "===================" << endl << "student set of Lesson(1) ; " << endl;
    for (set<ID_t>::iterator iter = stuSet1.begin(); iter != stuSet1.end(); ++iter) {
        Student stu(*iter);
        cout << stu.getName() << " id : " << stu.getId() << endl;
    }

    cout << endl << endl << endl;

    for (int i = 0; i != 4; ++i) {
        //get student(0) lesson
        cout << "================" << endl << "get student(" << i << ") lesson" << endl;
        Student stuId_00(i);
        set<ID_t> lesSet0 = Schedule::getLessonSet(stuId_00);
        cout << "my name is : " << stuId_00.getName() << endl;
        for (set<ID_t>::iterator iter = lesSet0.begin(); iter != lesSet0.end(); ++iter) {
            Lesson les(*iter);
            cout
                << les.getLessonName()
                << " id : " << les.getId()
                << " MaxStudent : " << les.getMaxStudentNumber() << endl;
        }
    }
}
#endif // TEST_ARRANGELESSON

//#define TEST_ADMINISTRATOR
#ifdef TEST_ADMINISTRATOR
int main()
{
    install();
    Creator::creatStudentSample(5);
    Creator::creatLessonSample(3);

    set<ID_t> stuSet, lesSet;
    for (int i = 0; i != 5; ++i) {
        stuSet.insert(i);
    }
    for (int i = 0; i != 3; ++i) {
        lesSet.insert(i);
    }

    ID_t selID = Administrator::creatSelect("lesson", stuSet, lesSet);

    //check the lesson student 3 can choose
    set<ID_t> selection = Administrator::getSelection(3);
    for (set<ID_t>::iterator iter = selection.begin(); iter != selection.end(); ++iter) {
        set<ID_t> lessonBeSelected = Administrator::getSelectionLesson(*iter);
        cout << "==========================" << endl
            << "the lesson in id " << *iter << " selection is : " << endl;
        for (set<ID_t>::iterator it = lessonBeSelected.begin(); it != lessonBeSelected.end(); ++it) {
            Lesson les(*it);
            cout << "id : " << les.getId() << " " << les.getName() << endl;
        }
        cout << "==========================" << endl;
    }

    Administrator::sendRequest(0, 0, selID);
    Administrator::sendRequest(1, 1, selID);
    Administrator::sendRequest(2, 1, selID);
    Administrator::sendRequest(3, 1, selID);
    Administrator::sendRequest(4, 1, selID);
    Administrator::sendRequest(4, 2, selID);
    
    set<ID_t> fail = Administrator::startSelect(selID);
    cout << "the student failing to select lesson : " << endl;
    for (set<ID_t>::iterator iter = fail.begin(); iter != fail.end(); ++iter) {
        cout << *iter << endl;
    }

    //show the students' lesson
    for (int i = 0; i != 5; ++i) {
        cout << "===================================" << endl;
        Student stu(i);
        set<ID_t> lesSet = Schedule::getLessonSet(stu);
        cout << "the student " << stu.getId() << " ";
        if (lesSet.empty()) {
            cout << "fail to select lesson" << endl;
        } else {
            cout << "select : " << endl;
            for (set<ID_t>::iterator iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
                Lesson les(*iter);
                cout << "id : " << les.getId() << " " << les.getName() << endl;
            }
        }

        cout << endl;
    }
    cout << "===================================" << endl;
}
#endif // TEST_ADMINISTRATOR

//#define TEST_MAKE_SAMPLE_1
#ifdef TEST_MAKE_SAMPLE_1

int main() {
    int const STUDENT_COUNT = 500;
    install();
    Creator::creatStudentSample(STUDENT_COUNT);
    Creator::creatLessonSample(5);

    //display all student
    StudentFile file;
    cout << "=============================" << endl << "list all student" << endl;
    for (StudentFile::iterator iter = file.begin(); iter != file.end(); ++iter) {
        Student stu = *iter;
        cout
            << "name: " << stu.getName() << " "
            << "id: " << stu.getId() << " "
            << "grade: " << stu.getGrade() << " "
            << "gender: " << stu.getGender() << endl;
    }

    //add student to lesson(0)
    Lesson lesIdOne(0);
    for (int i = 0; i != STUDENT_COUNT; ++i) {
        Student stu(i);
        Schedule::addStudentToLesson(stu, lesIdOne);
    }

    //add student 0 to all lesson
    for (int i = 0; i != 5; ++i) {
        Student stu(0);
        Lesson les(i);
        Schedule::addStudentToLesson(stu, les);
    }

    //check the student in lesson with id 0
    Lesson les(0);
    set<ID_t> stuSet = Schedule::getStudentSet(les);
    cout << "===================" << endl << "student set of Lesson(0) ; " << endl;
    for (set<ID_t>::iterator iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
        Student stu(*iter);
        cout << stu.getName() << endl;
    }
}
#endif // TEST_MAKE_SAMPLE_1


//#define CREAT_SELECTION
#ifdef CREAT_SELECTION

int main()
{
    install();
    Creator::creatStudentSample(5);
    Creator::creatLessonSample(3);

    set<ID_t> stuSet, lesSet;
    for (int i = 0; i != 5; ++i) {
        stuSet.insert(i);
    }
    for (int i = 0; i != 3; ++i) {
        lesSet.insert(i);
    }

    ID_t selID = Administrator::creatSelect("¹«Ñ¡", stuSet, lesSet);
}
#endif

//#define CREAT_BIG_SAMPLE
#ifdef CREAT_BIG_SAMPLE
#define STUDENT_COUNT 100
#define LESSON_COUNT 10
int main()
{
    install();
    Creator::creatStudentSample(STUDENT_COUNT);
    Creator::creatLessonSample(LESSON_COUNT);

    set<ID_t> stuSet, lesSet;
    for (int i = 0; i != STUDENT_COUNT; ++i) {
        stuSet.insert(i);
    }
    for (int i = 0; i != LESSON_COUNT; ++i) {
        lesSet.insert(i);
    }
}
#endif