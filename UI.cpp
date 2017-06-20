#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "Administrator.h"
#include "compile_option.h"
#include "File.h"
#include "other.h"
#include "Schedule.h"
#include "Student.h"
#include "UI.h"

using namespace std;

void UI::welcome()
{
    cout
        << "====================================" << endl
        << "=                                  =" << endl
        << "=           SYSU SDCS              =" << endl
        << "=       欢迎使用学生选课系统       =" << endl
        << "=                                  =" << endl
        << "=                                  =" << endl
        << "====================================" << endl
        << endl;;
}

void UI::goodBye()
{
    cout << "欢迎再次使用学生选课系统" << endl;
}

void UI::LogIn()
{
    while (1) {
    cout << endl
        << "======================================" << endl
        << "= 请选择用户类型 ：(输入数字)" << endl
        << "= 1.学生 " << endl
        << "= 2.教师 " << endl
        << "= 3.管理员" << endl
        << "======================================" << endl;

        int temp;
        while ((temp = getNumber(1,3)) == INT_MAX) {
            cout << endl;
        }
            
        switch (temp) {
            case 1:
                if (UI_student::run()) {
                    return;
                }
                break;
            case 2:
                cout << "老师端还没做~~敬请期待" << endl;
                /*
                if (UI_teacher::run()) {
                    return;
                }*/
                break;
            case 3:
                if (UI_administrator::run()) {
                    return;
                }
                break;
            default:
                cout << "请输入合法的数字" << endl;
        }
    }  
}

void UI::showLesson(set<ID_t> lesSet)
{
    if (lesSet.empty()) {
        cout << "没有满足要求的课程" << endl;
    }
    cout
        << setw(7) << "id"
        << setw(20) << "课程名称："
        << setw(14) << "老师"
        << setw(11) << "最大课容量" << endl;
    for (auto iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
        Lesson les(*iter);
        cout
            << setw(7) << les.getId()
            << setw(20) << les.getName()
            << setw(14) << les.getTeacherName()
            << setw(11) << les.getMaxStudentNumber() << endl;
    }
}

void UI::showStudent(set<ID_t> stuSet)
{
    cout << "没有满足要求的学生" << endl;
    cout
        << setw(8) << "id"
        << setw(10) << "姓名"
        << setw(6) << "性别"
        << setw(6) << "年级" << endl;
    for (auto iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
        Student stu(*iter);
        cout
            << setw(8) << stu.getId()
            << setw(10) << stu.getName()
            << setw(6) << (stu.getGender() == male ? "男" : "女")
            << setw(6) << stu.getGrade() << endl;
    }
}

void UI::showLesson_Detail(set<ID_t> lesSet)
{
    cout << endl
        << "***************************" << endl
        << "输入对应课程id查看课程信息" << endl;

    while (1) {
        cout << "请输入要查询的id：（按Esc取消）" << endl;

        int temp = getNumber();
        if (temp == INT_MAX) {
            break;
        }

        if (find(lesSet.begin(), lesSet.end(), temp) == lesSet.end()) {
            cout << "没有id为" << temp << "的课程，请重新输入" << endl;
        } else {
            Lesson les(temp);
            cout << "课程名：" << les.getName() << " 课程id：" << les.getId() << endl
                << les.getIntorduction() << endl << endl;
        }
    }
}