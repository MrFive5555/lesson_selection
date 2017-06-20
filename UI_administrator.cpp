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
        cout << "��һ�ν�������������" << endl;
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
            << "���������" << endl
            << "1.�鿴ѧ��" << endl
            << "2.�鿴�γ�" << endl
            << "3.���ѧ��" << endl
            << "4.��ӿγ�" << endl
            << "5.ɾ��ѧ��" << endl
            << "6.ɾ���γ�" << endl
            << "7.�����µĿγ�ѡ��" << endl
            << "8.��ʼѡ��" << endl
            << "9.�޸�����" << endl
            << "10.ע��" << endl
            << "11.�˳�" << endl;

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
                cout << "������Ϸ�������" << endl;
        }
    }
    return true;
}

void UI_administrator::checkStudent()
{
    while (1) {
        cout << endl
            << "=======================" << endl
            << "�������������Esc�˳���" << endl
            << "1.�鿴����ѧ��" << endl
            << "2.�鿴ָ��ѧ�ŷ�Χ�ڵ�ѧ��" << endl
            << "3.�鿴��������" << endl
            << "4.�鿴����Ů��" << endl
            << "5.�鿴��ͬ�꼶��ѧ��" << endl
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
                cout << "�������½磺����Esc�˳���" << endl;
                int down = getNumber();
                if (down == INT_MAX) {
                    break;
                }
                cout << "�������Ͻ磺����Esc�˳���" << endl;
                int up = getNumber();
                if (up == INT_MAX) {
                    break;
                }

                if (up < down) {
                    cout << "�����Ͻ�С���½�" << endl;
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
                cout << "������Ҫ��ѯ���꼶������Esc�˳���" << endl;

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
                cout << "������Ϸ�������" << endl;
        }
        UI::showStudent(stuSet);
    }
}

void UI_administrator::checkLesson()
{
    while (1) {
        cout << endl
            << "=======================" << endl
            << "�������������Esc������" << endl
            << "1.�鿴���пγ�" << endl
            << "2.�鿴����ָ��ѧ���Ŀγ�" << endl
            << "3.�鿴ָ�����ƵĿγ�" << endl
            << "4.�鿴ָ��id�Ŀγ�" << endl
            << "5.�鿴ָ����ʦ�Ŀγ�" << endl
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
                cout << "������ѧ��id������Esc�˳���" << endl;
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
                cout << "������Ҫ���ҵĿγ����ƣ�" << endl;
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
                cout << "������Ҫ��ѯ��id������Esc�˳���" << endl;

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
                cout << "������Ҫ���ҵ���ʦ���ƣ�����Escȡ����" << endl;
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
                cout << "������Ϸ�������" << endl;
        }

        UI::showLesson(lesSet);

        UI::showLesson_Detail(lesSet);
    }
}

void UI_administrator::addStudent()
{
    cout << "������ѧ��id������Escȡ����" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (StudentFile::IsInFile(id)) {
        cout << "�Ѿ���idΪ" << id << "��ѧ��" << endl;
        return;
    }

    cout << "������ѧ������" << endl;
    string name;
    getline(cin, name);
    while (name.length() <= 0 || name.length() >= STUDENT_NAME_LENGTH) {
        cout << "�������ȹ���:" << endl;
        getline(cin, name);
    }

    cout << "�������Ա�1Ϊ�У�2ΪŮ������Escȡ����" << endl;

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

    cout << "�������꼶������Escȡ����" << endl;

    int grade = getNumber(1, 4);

    Creator::creatStudent(id, name.c_str(), gender, grade);
    cout
        << "================" << endl
        << "=   �����ɹ��� =" << endl
        << "================" << endl;
}

void UI_administrator::addLesson()
{
    cout << "������Ҫ�����Ŀγ�id������Escȡ����" << endl;

    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (LessonFile::IsInFile(id)) {
        cout << "�Ѿ���idΪ" << id << "�Ŀγ�" << endl;
        return;
    }

    cout << "������γ����ƣ�" << endl;
    string name;
    getline(cin, name);
    while (name.length() <= 0 || name.length() >= LESSON_NAME_LENGTH) {
        cout << "���Ƴ��ȹ���:" << endl;
        getline(cin, name);
    }

    cout << "��������ʦ������" << endl;
    string teacher_name;
    getline(cin, teacher_name);
    while (teacher_name.length() <= 0 || teacher_name.length() >= TEACHER_NAME_LENGTH) {
        cout << "�������ȹ���:" << endl;
        getline(cin, teacher_name);
    }

    cout << "���������γ�����������Escȡ����" << endl;
    int MaxStudentCount = getNumber(0, 1000);
    if (MaxStudentCount == INT_MAX) {
        return;
    }

    cout << "������γ̽���" << endl;
    string introduction;
    getline(cin, introduction);
    while (introduction.length() <= 0 || introduction.length() >= INTRODUCTION_LENGTH) {
        cout << "���ܳ��ȹ���:" << endl;
        getline(cin, introduction);
    }

    Creator::creatLesson(id, name.c_str(), teacher_name.c_str(), introduction.c_str(), MaxStudentCount);
    cout
        << "================" << endl
        << "=   �����ɹ��� =" << endl
        << "================" << endl;
}

void UI_administrator::deleteStudent()
{
    cout << "������Ҫɾ����ѧ��id������Escȡ����" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }
    if (!StudentFile::IsInFile(id)) {
        cout
            << "===================" << endl
            << "=   û������ѧ��  =" << endl
            << "===================" << endl;
        return;
    }

    Student stu(id);
    Schedule::deleteStudent(stu);
    cout
        << "================" << endl
        << "=   ɾ���ɹ��� =" << endl
        << "================" << endl;
}

void UI_administrator::deleteLesson()
{
    cout << "������Ҫɾ���Ŀγ�id������Escȡ����" << endl;
    int id = getNumber();
    if (id == INT_MAX) {
        return;
    }

    if (!LessonFile::IsInFile(id)) {
        cout << "û�����ſγ�" << endl;
        return;
    }

    Lesson les(id);
    Schedule::deleteLesson(les);
    cout
        << "================" << endl
        << "=   ɾ���ɹ��� =" << endl
        << "================" << endl;
}

void UI_administrator::creatNewSelection()
{
    cout << "������Ҫ������ѡ�����ƣ�" << endl;

    string name;
    getline(cin, name);

    set<ID_t> stuSet;
    cout << endl
        << "����ѡ���ѡѧ����" << endl;

    bool loop = true;
    while (loop) {
        cout
            << "�������������Escȡ����" << endl
            << "1.��ID����" << endl
            << "2.��ID����һ��ѧ��" << endl
            << "3.����ĳ���꼶����ѧ��" << endl
            << "4.����ȫ��ѧ��" << endl;
        int choose = getNumber(1,4);
        if (choose == INT_MAX) {
            return;
        }
        switch (choose) {
            case 1: {
                cout << "������ѧ��id:����Escȡ����" << endl;
                int id = getNumber();
                if (id == INT_MAX) {
                    break;
                }
                while (!StudentFile::IsInFile(id)) {
                    cout << "û������ѧ��������������" << endl;
                    id = getNumber();
                }
                stuSet.insert(id);
                
                loop = false;
                break;
            }
            case 2: {
                cout << "�������½磺����Esc�˳���" << endl;
                int down = getNumber();
                if (down == INT_MAX) {
                    break;
                }
                cout << "�������Ͻ磺����Esc�˳���" << endl;
                int up = getNumber();
                if (up == INT_MAX) {
                    break;
                }

                if (up < down) {
                    cout << "�����Ͻ�С���½�" << endl;
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
                cout << "������Ҫ������꼶������Esc�˳���" << endl;

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
                cout << "��������ȷ������" << endl;
                break;
        }
    }
    cout
        << "================" << endl
        << "=   ��ӳɹ��� =" << endl
        << "================" << endl;

    set<ID_t>lesSet;
    cout << endl << "������ӿ�ѡ�γ�" << endl;
    loop = true;
    while (loop) {
        cout
            << "�������������Escȡ����" << endl
            << "1.��ID����" << endl
            << "2.����ȫ���γ�" << endl;
        int choose = getNumber(1,2);
        if (choose == INT_MAX) {
            return;
        }
        switch (choose) {
            case 1: {
                cout << "������γ�id:����Escȡ����" << endl;
                int id = getNumber();
                while (!LessonFile::IsInFile(id)) {
                    cout << "û�����ſγ̣�����������" << endl;
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
                cout << "��������ȷ������" << endl;
                break;
        }
    }
    cout
        << "================" << endl
        << "=   ��ӳɹ��� =" << endl
        << "================" << endl;

    Administrator::creatSelect(name, stuSet, lesSet);
    cout
        << "====================" << endl
        << "=   ����ѡ�γɹ��� =" << endl
        << "====================" << endl;
}

void UI_administrator::startSelection()
{ 
    set<ID_t> selectionSet = Administrator::getAllSelection();

    if (selectionSet.empty()) {
        cout << "û�д���ʼ�Ŀγ̣��������˵�����" << endl;
        return;
    } else {
        cout << "���ڴ���ʼ��ѡ�Σ�" << endl << endl;
    }

    for (auto iter = selectionSet.begin(); iter != selectionSet.end(); ++iter) {
        cout << Administrator::getSelectionName(*iter) << " id:" << *iter << endl;
    }

    cout << endl << "�����Ӧѡ��id��ʼѡ�Σ���Esc������ѯ" << endl;

    ID_t selectionID = INT_MAX;
    cout << "���������" << endl;
    while (1) {
        selectionID = getNumber();
        if (selectionID == INT_MAX) {
            continue;
        }

        if (find(selectionSet.begin(), selectionSet.end(), selectionID) == selectionSet.end()) {
            cout << "û��idΪ" << selectionID << "��ѡ�Σ�����������" << endl;
        } else {
            cout << "ȷ��Ҫ��ʼѡ���������롰Y�����ǣ���N������" << endl;

            while (1) {
                string command;
                getline(cin, command);
                if (command == "Y") {
                    break; //go to the break after
                } else if (command == "N") {
                    return; //go back to menu
                } else {
                    cout << "�����롰Y����N��" << endl;
                }
            }

            break; //goto statSelect()
        }
    }

    //��ʼѡ�Σ�����startSelect����һ��ѡ��γ�ʧ��ѧ����������Щѧ������Ҫ����ѡ��
    string name = Administrator::getSelectionName(selectionID);
    set<ID_t> lessonSet = Administrator::getSelectionLesson(selectionID);
    set<ID_t> failSelection = Administrator::startSelect(selectionID);
    if (!failSelection.empty()) {
        Administrator::creatSelect(name, failSelection, lessonSet);
        cout << "��" << failSelection.size() << "��ѧ��û�����ϿΣ����ǽ�����ѡ��" << endl;
    }
    cout << "ѡ����ɣ��������������" << endl;
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
    cout << "�����������룬��Escȡ����" << endl;
    while (1) {
        newPassword = getPassword();
        if (newPassword == ERROR_PASSWORD) {
            cout << "��ȡ��" << endl;
            return false;
        }
        if (newPassword.length() <= MIN_PASSWORD_LENGTH) {
            cout << "������̣���ѡ�����������" << endl;
            continue;
        }
        break;
    }

    cout << "��ȷ�������룬��Escȡ����" << endl;
    string repeatPassword = getPassword();

    if (newPassword == repeatPassword) {
        fstream pwd("data/administrator.data", fstream::out | fstream::binary);
        pwd << newPassword;
        cout << "�޸ĳɹ�" << endl;
        return true;
    } else {
        cout << "�����������벻һ�£������²���" << endl;
        return false;
    }

}

void UI_administrator::changePassword()
{
    //get correct password
    string correctPassword;
    fstream pwd("data/administrator.data", fstream::in | fstream::binary);
    pwd >> correctPassword;

    cout << "������ԭ���룬��Escȡ����" << endl;

    while (1) {
        string password = getPassword();
        if (password == correctPassword) {
            cout << endl << "=================================" << endl;
            break;
        } else if (password == ERROR_PASSWORD) {
            cout << "��ȡ��" << endl;
            return;
        } else {
            cout << "������˺Ŵ�����������������:" << endl;
        }
    }

    if (!setPassword()) {
        return;
    }
}

bool UI_administrator::LogIn()
{
    cout << "���������루��Escȡ������" << endl;
    string correctPassword;
    fstream pwd("data/administrator.data", fstream::in | fstream::binary);
    pwd >> correctPassword;

    while (1) {
        string password = getPassword();
        if (password == correctPassword) {
            cout << endl << "=================================" << endl
                << "��ӭ�����������ǹ���Աģʽ��" << endl;
            return true;
        } else if (password == ERROR_PASSWORD) {
            cout << "��ȡ��" << endl;
            return false;
        } else {
            cout << "������˺Ŵ�����������������:" << endl;
        }
    }
}