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
            << "���" << endl
            << "1. �鿴ѧ����Ϣ" << endl
            << "2. �޸�����" << endl
            << "3. �鿴��ѡ�γ�" << endl
            << "4. ѡ��" << endl
            << "5. ע��" << endl
            << "6. �˳�ϵͳ" << endl
            << "���������" << endl;

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
                cout << "������Ϸ�������" << endl;
        }
    }
}

bool UI_student::LogIn()
{
    int stuID = 0;
    cout << "������ѧ��ID ������Esc�˳���" << endl;
    while (1) {
        stuID = getNumber();
        if (stuID == INT_MAX) {
            return false;
        }
        if (!StudentFile::IsInFile(stuID)) {
            cout << "û��IDΪ" << stuID << "��ѧ������ȷ��ID ��" << endl;
            continue;
        } else {
            break;
        }
    }

    cout << "���������루Ĭ������ΪID�ţ���Escȡ������" << endl;
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
                << "��ӭ����," << me.getName() << endl
                << "���ε�½���޸�����" << endl;
            return true;
        } else if (password == ERROR_PASSWORD) {
            cout << "��ȡ��" << endl;
            return false;
        } else {
            cout << "������˺Ŵ�����������������:" << endl;
        }
    }
}

void UI_student::showInfo()
{
    cout
        << "*******************" << endl
        << "* ѧ����Ϣ��" << endl
        << "* ������" << me.getName() << endl
        << "* ѧ�ţ�" << me.getId() << endl
        << "* �Ա�" << (me.getGender() == male ? "��" : "Ů") << endl
        << "* �꼶��" << me.getGrade() << endl
        << "*******************" << endl
        << "�����������" << endl;
    getch();
}

void UI_student::changePassword()
{
    cout << "������ԭ���룬��Escȡ����" << endl;

    cout << "���������루Ĭ������ΪID�ţ���" << endl;
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
            cout << "��ȡ��" << endl;
            return;
        } else {
            cout << "������˺Ŵ�����������������:" << endl;
        }
    }

    string newPassword;
    while (1) {
        cout << "�����������룬��Escȡ����" << endl;
        newPassword = getPassword();
        if (newPassword == ERROR_PASSWORD) {
            cout << "��ȡ��" << endl;
            return;
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
        setNewPassword(me.getId(), newPassword);
        cout << "�޸ĳɹ�" << endl;
    } else {
        cout << "�����������벻һ�£������²���" << endl;
    }

}

void UI_student::showLesson()
{
    cout << endl << "***************************" << endl;
    set<ID_t>lesSet = Schedule::getLessonSet(me);
    if (lesSet.empty()) {
        cout << "û�пγ�" << endl;
        return;
    }

    cout << "��ѡ�γ̣�" << endl;
    for (set<ID_t>::iterator iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
        Lesson les(*iter);
        cout << "�γ�����" << les.getName() << " �γ�id��" << les.getId() << endl;
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
        cout << "û�д�ѡ�γ�" << endl;
        return;
    } else {
        cout << "��ѡ�γ̣�" << endl << endl;
    }

    //��ʾ��ѡ��Ŀ
    for (auto iter = selectionID.begin(); iter != selectionID.end(); ++iter) {
        cout << Administrator::getSelectionName(*iter) << " " << "id:" << *iter << endl;
    }
    cout << endl;

    ID_t chooseID = INT_MAX;

    cout << "�����Ӧid����ѡ�Σ���Escȡ��" << endl;

    cout << "���������" << endl;
    while (1) {   
        int temp = getNumber();
        if (temp == INT_MAX) {
            return;
        }

        if (find(selectionID.begin(), selectionID.end(), temp) == selectionID.end()) {
            cout << "û��idΪ" << temp << "�Ŀγ�ѡ������������" << endl;
        } else {
            chooseID = temp;
            break;
        }
    }

    //��ʾ��Ŀ�п�ѡ�γ�
    set<ID_t>lessonSet = Administrator::getSelectionLesson(chooseID);
    cout << endl << "��ѡ�Ŀγ�:" << endl;
    for (auto iter = lessonSet.begin(); iter != lessonSet.end(); ++iter) {
        Lesson les(*iter);
        cout << les.getName() << " "
            << "��ʦ��" << les.getTeacherName()
            << "id��" << les.getId() << endl;
    }

    cout << endl << "�����Ӧ�γ�idѡ��γ̣�����Escȡ����" << endl;

    cout << "������γ�id��" << endl;
    while (1) {
        int temp = getNumber();
        if (temp == INT_MAX) {
            break;
        }

        if (find(lessonSet.begin(), lessonSet.end(), temp) == lessonSet.end()) {
            cout << "û��idΪ" << temp << "�Ŀγ̣�����������" << endl;
        } else {
            Administrator::sendRequest(me.getId(), temp, chooseID);
            cout
                << "================" << endl
                << "=   ѡ�γɹ��� =" << endl
                << "================" << endl;
            break;
        }
    }
}
