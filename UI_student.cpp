#include <conio.h>
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

Student UI_student::me = Student();

bool UI_student::run()
{
    if (!LogIn()) {
        //it should re-login
        return false;
    }
    while (1) {
        cout << endl << endl
            << "==========================================" << endl
            << "命令：" << endl
            << "1. 查看学生信息" << endl
            << "2. 修改密码" << endl
            << "3. 查看已选课程" << endl
            << "4. 选课" << endl
            << "5. 注销" << endl
            << "6. 退出系统" << endl
            << "请输入命令：" << endl;

        int temp = INT_MAX;
        while ((temp = getNumber(1,6)) == INT_MAX) {
            cout << endl;
            continue;
        }

        switch (temp) {
            case 1:
                showInfo();
                break;
            case 2:
                changePassword();
                break;
            case 3:
                showLesson();
                break;
            case 4:
                selectLesson();
                break;
            case 5: //re-login
                return false;
            case 6: //quit
                return true;
            default:
                cout << "请输入合法的数字" << endl;
        }
    }
}

bool UI_student::LogIn()
{
    int stuID = 0;
    cout << "请输入学生ID ：（按Esc退出）" << endl;
    while (1) {
        stuID = getNumber();
        if (stuID == INT_MAX) {
            return false;
        }
        if (!StudentFile::IsInFile(stuID)) {
            cout << "没有ID为" << stuID << "的学生，请确认ID ：" << endl;
            continue;
        } else {
            break;
        }
    }

    cout << "请输入密码（默认密码为ID号，按Esc取消）：" << endl;
    string correctPassword = checkPassword(stuID);
    if (correctPassword == ERROR_PASSWORD) {
        stringstream stream;
        stream << stuID;
        getline(stream, correctPassword);
    }

    while (1) {
        string password = getPassword();
        if (password == correctPassword) {
            me = Student(stuID);
            cout << endl << "=================================" << endl
                << "欢迎回来," << me.getName() << endl
                << "初次登陆请修改密码" << endl;
            return true;
        } else if (password == ERROR_PASSWORD) {
            cout << "已取消" << endl;
            return false;
        } else {
            cout << "密码或账号错误，请重新输入密码:" << endl;
        }
    }
}

void UI_student::showInfo()
{
    cout
        << "*******************" << endl
        << "* 学生信息：" << endl
        << "* 姓名：" << me.getName() << endl
        << "* 学号：" << me.getId() << endl
        << "* 性别：" << (me.getGender() == male ? "男" : "女") << endl
        << "* 年级：" << me.getGrade() << endl
        << "*******************" << endl
        << "按任意键继续" << endl;
    getch();
}

void UI_student::changePassword()
{
    cout << "请输入原密码，按Esc取消：" << endl;

    cout << "请输入密码（默认密码为ID号）：" << endl;
    string correctPassword = checkPassword(me.getId());
    if (correctPassword == ERROR_PASSWORD) {
        stringstream stream;
        stream << me.getId();
        getline(stream, correctPassword);
    }

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

    string newPassword;
    while (1) {
        cout << "请输入新密码，按Esc取消：" << endl;
        newPassword = getPassword();
        if (newPassword == ERROR_PASSWORD) {
            cout << "已取消" << endl;
            return;
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
        setNewPassword(me.getId(), newPassword);
        cout << "修改成功" << endl;
    } else {
        cout << "两次密码输入不一致，请重新操作" << endl;
    }

}

void UI_student::showLesson()
{
    cout << endl << "***************************" << endl;
    set<ID_t>lesSet = Schedule::getLessonSet(me);
    if (lesSet.empty()) {
        cout << "没有课程" << endl;
        return;
    }

    cout << "已选课程：" << endl;
    for (set<ID_t>::iterator iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
        Lesson les(*iter);
        cout << "课程名：" << les.getName() << " 课程id：" << les.getId() << endl;
    }

    UI::showLesson_Detail(lesSet);
}

typedef pair<ID_t, char[MAX_PASSWORD_LENGTH + 1]> pwdPair;

string UI_student::checkPassword(ID_t id)
{
    pwdPair temp;
    fstream file("data/password.data", fstream::in | fstream::binary);
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(pwdPair))) {
        if (temp.first == id) {
            return temp.second;
        }
    }
    return ERROR_PASSWORD;
}

void UI_student::setNewPassword(ID_t stuId, string newPassword)
{
    pwdPair temp;
    pwdPair newPair;
    newPair.first = stuId;
    strcpy(newPair.second, newPassword.c_str());

    fstream file("data/password.data", fstream::out | fstream::in | fstream::binary);
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(pwdPair))) {
        if (temp.first == stuId) {
            long offset = sizeof(pwdPair);
            file.seekg(-offset, fstream::cur);
            file.write(reinterpret_cast<char*>(&newPair), sizeof(pwdPair));
            return;
        }
    }

    file.clear();
    file.close();
    file.open("data/password.data", fstream::out | fstream::in | fstream::binary | fstream::ate);
    file.write(reinterpret_cast<char*>(&newPair), sizeof(pwdPair));
}

void UI_student::selectLesson()
{
    set<ID_t>selectionID = Administrator::getSelection(me.getId());

    cout << endl << "=====================" << endl;

    if (selectionID.empty()) {
        cout << "没有待选课程" << endl;
        return;
    } else {
        cout << "待选课程：" << endl << endl;
    }

    //显示待选项目
    for (auto iter = selectionID.begin(); iter != selectionID.end(); ++iter) {
        cout << Administrator::getSelectionName(*iter) << " " << "id:" << *iter << endl;
    }
    cout << endl;

    ID_t chooseID = INT_MAX;

    cout << "输入对应id进行选课，按Esc取消" << endl;

    cout << "请输入命令：" << endl;
    while (1) {   
        int temp = getNumber();
        if (temp == INT_MAX) {
            return;
        }

        if (find(selectionID.begin(), selectionID.end(), temp) == selectionID.end()) {
            cout << "没有id为" << temp << "的课程选择，请重新输入" << endl;
        } else {
            chooseID = temp;
            break;
        }
    }

    //显示项目中可选课程
    set<ID_t>lessonSet = Administrator::getSelectionLesson(chooseID);
    cout << endl << "可选的课程:" << endl;
    for (auto iter = lessonSet.begin(); iter != lessonSet.end(); ++iter) {
        Lesson les(*iter);
        cout << les.getName() << " "
            << "老师：" << les.getTeacherName()
            << "id：" << les.getId() << endl;
    }

    cout << endl << "输入对应课程id选择课程，（按Esc取消）" << endl;

    cout << "请输入课程id：" << endl;
    while (1) {
        int temp = getNumber();
        if (temp == INT_MAX) {
            break;
        }

        if (find(lessonSet.begin(), lessonSet.end(), temp) == lessonSet.end()) {
            cout << "没有id为" << temp << "的课程，请重新输入" << endl;
        } else {
            Administrator::sendRequest(me.getId(), temp, chooseID);
            cout
                << "================" << endl
                << "=   选课成功！ =" << endl
                << "================" << endl;
            break;
        }
    }
}
