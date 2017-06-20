#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "Administrator.h"
#include "compile_option.h"
#include "creator.h"
#include "File.h"
#include "other.h"
#include "Schedule.h"
#include "Student.h"
#include "UI.h"

using namespace std;

bool UI_administrator::run()
{
    if (!hasSetPassword()) {
        cout << "第一次进入请设置密码" << endl;
        if (!setPassword()) {
            return false;
        }
    } else {
        if (!LogIn()) {
            //re-login
            return false;
        }
    }

    while (1) {
        cout << endl
            << "=======================" << endl
            << "请输入命令：" << endl
            << "1.查看学生" << endl
            << "2.查看课程" << endl
            << "3.添加学生" << endl
            << "4.添加课程" << endl
            << "5.删除学生" << endl
            << "6.删除课程" << endl
            << "7.创建新的课程选择" << endl
            << "8.开始选课" << endl
            << "9.修改密码" << endl
            << "10.注销" << endl
            << "11.退出" << endl;

        int temp = INT_MAX;
        while ((temp = getNumber(1,11))==INT_MAX) {
            cout << endl;
            continue;
        }
        
        switch (temp) {
            case 1:
                checkStudent();
                break;
            case 2:
                checkLesson();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                addLesson();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                deleteLesson();
                break;
            case 7:
                creatNewSelection();
                break;
            case 8:
                startSelection();
                break;
            case 9: //re-login
                changePassword();
                break;
            case 10: //re-login
                return false;
            case 11: //quit
                return true;
            default:
                cout << "请输入合法的数字" << endl;
        }
    }
    return true;
}

void UI_administrator::checkStudent()
{
    while (1) {
        cout << endl
            << "=======================" << endl
            << "请输入命令：（按Esc退出）" << endl
            << "1.查看所有学生" << endl
            << "2.查看指定学号范围内的学生" << endl
            << "3.查看所有男生" << endl
            << "4.查看所有女生" << endl
            << "5.查看相同年级的学生" << endl
            << "=======================" << endl;

        int temp = getNumber();
        if (temp == INT_MAX) {
            return;
        }

        set<ID_t> stuSet;
        switch (temp) {
            case 1: {
                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    stuSet.insert((*iter).getId());
                }
                break;
            }
            case 2: {
                cout << "请输入下界：（按Esc退出）" << endl;
                int down = getNumber();
                if (down == INT_MAX) {
                    break;
                }
                cout << "请输入上界：（按Esc退出）" << endl;
                int up = getNumber();
                if (up == INT_MAX) {
                    break;
                }

                if (up < down) {
                    cout << "错误：上界小于下界" << endl;
                    break;
                }

                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getId() >= down && stu.getId() <= up) {
                        stuSet.insert(stu.getId());
                    }
                }
                break;
            }
            case 3: {
                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getGender() == male) {
                        stuSet.insert(stu.getId());
                    }
                }
                break;
            }
            case 4: {
                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getGender() == female) {
                        stuSet.insert(stu.getId());
                    }
                }
                break;
            }
            case 5: {
                cout << "请输入要查询的年级：（按Esc退出）" << endl;

                int grade = getNumber();

                if (grade == INT_MAX) {
                    return;
                }

                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getGrade() == grade) {
                        stuSet.insert(stu.getId());
                    }
                }
                break;
            }
            default:
                cout << "请输入合法的数字" << endl;
        }
        UI::showStudent(stuSet);
    }
}

void UI_administrator::checkLesson()
{
    while (1) {
        cout << endl
            << "=======================" << endl
            << "请输入命令：（按Esc结束）" << endl
            << "1.查看所有课程" << endl
            << "2.查看含有指定学生的课程" << endl
            << "3.查看指定名称的课程" << endl
            << "4.查看指定id的课程" << endl
            << "5.查看指定老师的课程" << endl
            << "=======================" << endl;

        int temp = getNumber();
        if (temp == INT_MAX) {
            return;
        }

        set<ID_t> lesSet;
        switch (temp) {
            case 1: {
                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    lesSet.insert(les.getId());
                }
                break;
            }
            case 2: {
                cout << "请输入学生id：（按Esc退出）" << endl;
                int id = getNumber();
                if (id == INT_MAX) {
                    return;
                }

                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    set<ID_t> stuSet = Schedule::getStudentSet(les);
                    if (stuSet.find(id) != stuSet.end()) {
                        lesSet.insert(les.getId());
                    }
                }
                break;
            }
            case 3: {
                cout << "请输入要查找的课程名称：" << endl;
                string key;
                getline(cin, key);

                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    if(les.getName().find(key) != string::npos) {
                        lesSet.insert(les.getId());
                    }
                }
                break;
            }
            case 4: {
                cout << "请输入要查询的id：（按Esc退出）" << endl;

                int id = getNumber();

                if (id == INT_MAX) {
                    return;
                }

                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    if (les.getId() == id) {
                        lesSet.insert(les.getId());
                    }
                }
                break;
            }
            case 5: {
                cout << "请输入要查找的老师名称：（按Esc取消）" << endl;
                string key = getString();
                if (key == ERROR_STRING) {
                    return;
                }

                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    if (les.getTeacherName().find(key) != string::npos) {
                        lesSet.insert(les.getId());
                    }
                }
                break;
            }
            default:
                cout << "请输入合法的数字" << endl;
        }

        UI::showLesson(lesSet);

        UI::showLesson_Detail(lesSet);
    }
}

void UI_administrator::addStudent()
{
    cout << "请输入学生id：（按Esc取消）" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (StudentFile::IsInFile(id)) {
        cout << "已经有id为" << id << "的学生" << endl;
        return;
    }

    cout << "请输入学生姓名" << endl;
    string name;
    getline(cin, name);
    while (name.length() <= 0 || name.length() >= STUDENT_NAME_LENGTH) {
        cout << "姓名长度过长:" << endl;
        getline(cin, name);
    }

    cout << "请输入性别，1为男，2为女：（按Esc取消）" << endl;

    Gender gender = error;
    int temp = getNumber(1, 2);

    switch (temp) {
        case 1: 
            gender = male;
            break;
        case 2:
            gender = female;
            break;
        case INT_MAX:
            return;
        default:
            break;
    }

    cout << "请输入年级：（按Esc取消）" << endl;

    int grade = getNumber(1, 4);

    Creator::creatStudent(id, name.c_str(), gender, grade);
    cout
        << "================" << endl
        << "=   创建成功！ =" << endl
        << "================" << endl;
}

void UI_administrator::addLesson()
{
    cout << "请输入要创建的课程id：（按Esc取消）" << endl;

    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (LessonFile::IsInFile(id)) {
        cout << "已经有id为" << id << "的课程" << endl;
        return;
    }

    cout << "请输入课程名称：" << endl;
    string name;
    getline(cin, name);
    while (name.length() <= 0 || name.length() >= LESSON_NAME_LENGTH) {
        cout << "名称长度过长:" << endl;
        getline(cin, name);
    }

    cout << "请输入老师姓名：" << endl;
    string teacher_name;
    getline(cin, teacher_name);
    while (teacher_name.length() <= 0 || teacher_name.length() >= TEACHER_NAME_LENGTH) {
        cout << "姓名长度过长:" << endl;
        getline(cin, teacher_name);
    }

    cout << "请输入最大课程人数：（按Esc取消）" << endl;
    int MaxStudentCount = getNumber(0, 1000);
    if (MaxStudentCount == INT_MAX) {
        return;
    }

    cout << "请输入课程介绍" << endl;
    string introduction;
    getline(cin, introduction);
    while (introduction.length() <= 0 || introduction.length() >= INTRODUCTION_LENGTH) {
        cout << "介绍长度过长:" << endl;
        getline(cin, introduction);
    }

    Creator::creatLesson(id, name.c_str(), teacher_name.c_str(), introduction.c_str(), MaxStudentCount);
    cout
        << "================" << endl
        << "=   创建成功！ =" << endl
        << "================" << endl;
}

void UI_administrator::deleteStudent()
{
    cout << "请输入要删除的学生id：（按Esc取消）" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (!StudentFile::IsInFile(id)) {
        cout
            << "===================" << endl
            << "=   没有这名学生  =" << endl
            << "===================" << endl;
        return;
    }

    Student stu(id);
    Schedule::deleteStudent(stu);
    cout
        << "================" << endl
        << "=   删除成功！ =" << endl
        << "================" << endl;
}

void UI_administrator::deleteLesson()
{
    cout << "请输入要删除的课程id：（按Esc取消）" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }

    if (!LessonFile::IsInFile(id)) {
        cout << "没有这门课程" << endl;
        return;
    }

    Lesson les(id);
    Schedule::deleteLesson(les);
    cout
        << "================" << endl
        << "=   删除成功！ =" << endl
        << "================" << endl;
}

void UI_administrator::creatNewSelection()
{
    cout << "请输入要创建的选课名称：" << endl;

    string name;
    getline(cin, name);

    set<ID_t> stuSet;
    cout << endl
        << "现在选择可选学生：" << endl;

    bool loop = true;
    while (loop) {
        cout
            << "请输入命令：（按Esc取消）" << endl
            << "1.按ID输入" << endl
            << "2.按ID输入一段学生" << endl
            << "3.插入某个年级所有学生" << endl
            << "4.插入全部学生" << endl;
        int choose = getNumber(1,4);
        if (choose == INT_MAX) {
            return;
        }
        switch (choose) {
            case 1: {
                cout << "请输入学生id:（按Esc取消）" << endl;
                int id = getNumber();
                if (id == INT_MAX) {
                    break;
                }
                while (!StudentFile::IsInFile(id)) {
                    cout << "没有这名学生，请重新输入" << endl;
                    id = getNumber();
                }
                stuSet.insert(id);
                
                loop = false;
                break;
            }
            case 2: {
                cout << "请输入下界：（按Esc退出）" << endl;
                int down = getNumber();
                if (down == INT_MAX) {
                    break;
                }
                cout << "请输入上界：（按Esc退出）" << endl;
                int up = getNumber();
                if (up == INT_MAX) {
                    break;
                }

                if (up < down) {
                    cout << "错误：上界小于下界" << endl;
                    break;
                }

                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getId() >= down && stu.getId() <= up) {
                        stuSet.insert(stu.getId());
                    }
                }
                loop = false;
                break;
            }
            case 3: {
                cout << "请输入要插入的年级：（按Esc退出）" << endl;

                int grade = getNumber();

                if (grade == INT_MAX) {
                    return;
                }

                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    if (stu.getGrade() == grade) {
                        stuSet.insert(stu.getId());
                    }
                }
                loop = false;
                break;
            }
            case 4: {
                for (auto iter = StudentFile::begin(); iter != StudentFile::end(); ++iter) {
                    Student stu = *iter;
                    stuSet.insert(stu.getId());
                }
                loop = false;
                break;
            }
            default:
                cout << "请输入正确的数字" << endl;
                break;
        }
    }
    cout
        << "================" << endl
        << "=   添加成功！ =" << endl
        << "================" << endl;

    set<ID_t>lesSet;
    cout << endl << "现在添加可选课程" << endl;
    loop = true;
    while (loop) {
        cout
            << "请输入命令：（按Esc取消）" << endl
            << "1.按ID输入" << endl
            << "2.插入全部课程" << endl;
        int choose = getNumber(1,2);
        if (choose == INT_MAX) {
            return;
        }
        switch (choose) {
            case 1: {
                cout << "请输入课程id:（按Esc取消）" << endl;
                int id = getNumber();
                while (!LessonFile::IsInFile(id)) {
                    cout << "没有这门课程，请重新输入" << endl;
                    id = getNumber();
                }
                lesSet.insert(id);
                loop = false;
                break;
            }
            case 2: {
                for (auto iter = LessonFile::begin(); iter != LessonFile::end(); ++iter) {
                    Lesson les = *iter;
                    lesSet.insert((*iter).getId());
                }
                loop = false;
                break;
            }
            default:
                cout << "请输入正确的数字" << endl;
                break;
        }
    }
    cout
        << "================" << endl
        << "=   添加成功！ =" << endl
        << "================" << endl;

    Administrator::creatSelect(name, stuSet, lesSet);
    cout
        << "====================" << endl
        << "=   创建选课成功！ =" << endl
        << "====================" << endl;
}

void UI_administrator::startSelection()
{ 
    set<ID_t> selectionSet = Administrator::getAllSelection();

    if (selectionSet.empty()) {
        cout << "没有待开始的课程，请在主菜单开设" << endl;
        return;
    } else {
        cout << "现在待开始的选课：" << endl << endl;
    }

    for (auto iter = selectionSet.begin(); iter != selectionSet.end(); ++iter) {
        cout << Administrator::getSelectionName(*iter) << " id:" << *iter << endl;
    }

    cout << endl << "输入对应选课id开始选课，按Esc结束查询" << endl;

    ID_t selectionID = INT_MAX;
    cout << "请输入命令：" << endl;
    while (1) {
        selectionID = getNumber();
        if (selectionID == INT_MAX) {
            continue;
        }

        if (find(selectionSet.begin(), selectionSet.end(), selectionID) == selectionSet.end()) {
            cout << "没有id为" << selectionID << "的选课，请重新输入" << endl;
        } else {
            cout << "确定要开始选课了吗？输入“Y”（是）或“N”（否）" << endl;

            while (1) {
                string command;
                getline(cin, command);
                if (command == "Y") {
                    break; //go to the break after
                } else if (command == "N") {
                    return; //go back to menu
                } else {
                    cout << "请输入“Y”或“N”" << endl;
                }
            }

            break; //goto statSelect()
        }
    }

    //开始选课，函数startSelect返回一个选择课程失败学生名单，这些学生将需要重新选课
    string name = Administrator::getSelectionName(selectionID);
    set<ID_t> lessonSet = Administrator::getSelectionLesson(selectionID);
    set<ID_t> failSelection = Administrator::startSelect(selectionID);
    if (!failSelection.empty()) {
        Administrator::creatSelect(name, failSelection, lessonSet);
        cout << "有" << failSelection.size() << "名学生没有排上课，他们将继续选课" << endl;
    }
    cout << "选课完成（按任意键继续）" << endl;
    getch();
}

bool UI_administrator::hasSetPassword()
{
    fstream file("data/administrator.data", fstream::in | fstream::binary);
    return file ? true : false;
}

bool UI_administrator::setPassword()
{
    string newPassword;
    cout << "请输入新密码，按Esc取消：" << endl;
    while (1) {
        newPassword = getPassword();
        if (newPassword == ERROR_PASSWORD) {
            cout << "已取消" << endl;
            return false;
        }
        if (newPassword.length() <= MIN_PASSWORD_LENGTH) {
            cout << "密码过短，请选择更长的密码" << endl;
            continue;
        }
        break;
    }

    cout << "请确认新密码，按Esc取消：" << endl;
    string repeatPassword = getPassword();

    if (newPassword == repeatPassword) {
        fstream pwd("data/administrator.data", fstream::out | fstream::binary);
        pwd << newPassword;
        cout << "修改成功" << endl;
        return true;
    } else {
        cout << "两次密码输入不一致，请重新操作" << endl;
        return false;
    }

}

void UI_administrator::changePassword()
{
    //get correct password
    string correctPassword;
    fstream pwd("data/administrator.data", fstream::in | fstream::binary);
    pwd >> correctPassword;

    cout << "请输入原密码，按Esc取消：" << endl;

    while (1) {
        string password = getPassword();
        if (password == correctPassword) {
            cout << endl << "=================================" << endl;
            break;
        } else if (password == ERROR_PASSWORD) {
            cout << "已取消" << endl;
            return;
        } else {
            cout << "密码或账号错误，请重新输入密码:" << endl;
        }
    }

    if (!setPassword()) {
        return;
    }
}

bool UI_administrator::LogIn()
{
    cout << "请输入密码（按Esc取消）：" << endl;
    string correctPassword;
    fstream pwd("data/administrator.data", fstream::in | fstream::binary);
    pwd >> correctPassword;

    while (1) {
        string password = getPassword();
        if (password == correctPassword) {
            cout << endl << "=================================" << endl
                << "欢迎回来。现在是管理员模式：" << endl;
            return true;
        } else if (password == ERROR_PASSWORD) {
            cout << "已取消" << endl;
            return false;
        } else {
            cout << "密码或账号错误，请重新输入密码:" << endl;
        }
    }
}