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
        << "=       ��ӭʹ��ѧ��ѡ��ϵͳ       =" << endl
        << "=                                  =" << endl
        << "=                                  =" << endl
        << "====================================" << endl
        << endl;;
}

void UI::goodBye()
{
    cout << "��ӭ�ٴ�ʹ��ѧ��ѡ��ϵͳ" << endl;
}

void UI::LogIn()
{
    while (1) {
    cout << endl
        << "======================================" << endl
        << "= ��ѡ���û����� ��(��������)" << endl
        << "= 1.ѧ�� " << endl
        << "= 2.��ʦ " << endl
        << "= 3.����Ա" << endl
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
                cout << "��ʦ�˻�û��~~�����ڴ�" << endl;
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
                cout << "������Ϸ�������" << endl;
        }
    }  
}

void UI::showLesson(set<ID_t> lesSet)
{
    if (lesSet.empty()) {
        cout << "û������Ҫ��Ŀγ�" << endl;
    }
    cout
        << setw(7) << "id"
        << setw(20) << "�γ����ƣ�"
        << setw(14) << "��ʦ"
        << setw(11) << "��������" << endl;
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
    cout << "û������Ҫ���ѧ��" << endl;
    cout
        << setw(8) << "id"
        << setw(10) << "����"
        << setw(6) << "�Ա�"
        << setw(6) << "�꼶" << endl;
    for (auto iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
        Student stu(*iter);
        cout
            << setw(8) << stu.getId()
            << setw(10) << stu.getName()
            << setw(6) << (stu.getGender() == male ? "��" : "Ů")
            << setw(6) << stu.getGrade() << endl;
    }
}

void UI::showLesson_Detail(set<ID_t> lesSet)
{
    cout << endl
        << "***************************" << endl
        << "�����Ӧ�γ�id�鿴�γ���Ϣ" << endl;

    while (1) {
        cout << "������Ҫ��ѯ��id������Escȡ����" << endl;

        int temp = getNumber();
        if (temp == INT_MAX) {
            break;
        }

        if (find(lesSet.begin(), lesSet.end(), temp) == lesSet.end()) {
            cout << "û��idΪ" << temp << "�Ŀγ̣�����������" << endl;
        } else {
            Lesson les(temp);
            cout << "�γ�����" << les.getName() << " �γ�id��" << les.getId() << endl
                << les.getIntorduction() << endl << endl;
        }
    }
}