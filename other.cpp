
#pragma warning (disable:4996)

using namespace std;

#include <conio.h>
#include <direct.h>
#include <io.h>  
#include <iostream>
#include <stdio.h>  
#include <string.h>  
#include <string>
#include <sstream>

#include "other.h"

/*
* copy from lniwn' BLOG
* link : 
* http://blog.csdn.net/blueln/article/details/8700299
*/
/*
������ڣ��ļ��еľ���·��
const char*  dirPath

�������ܣ�ɾ�����ļ��У������������е��ļ����ļ���

����ֵ��  0  ɾ��
-1  ·�����ԣ������������û��ִ��ɾ������
*/
int  removeDir(const char*  dirPath)
{

    struct _finddata_t fb;   //������ͬ�����ļ��Ĵ洢�ṹ��  
    char  path[250];
    //long    handle; // this sentence can't work in x64
    intptr_t handle; //I change this sentence
    int  resultone;
    int   noFile;            //��ϵͳ�����ļ��Ĵ�����  

    noFile = 0;
    handle = 0;


    //����·��  
    strcpy(path, dirPath);
    strcat(path, "/*");

    handle = _findfirst(path, &fb);
    //�ҵ���һ��ƥ����ļ�  
    if (handle != 0)
    {
        //�����Լ����ҵ�ƥ����ļ�������ִ��  
        while (0 == _findnext(handle, &fb))
        {
            //windows�£����и�ϵͳ�ļ�����Ϊ��..��,������������  
            noFile = strcmp(fb.name, "..");

            if (0 != noFile)
            {
                //��������·��  
                memset(path, 0, sizeof(path));
                strcpy(path, dirPath);
                strcat(path, "/");
                strcat(path, fb.name);
                //����ֵΪ16����˵�����ļ��У�����  
                if (fb.attrib == 16)
                {
                    removeDir(path);
                }
                //���ļ��е��ļ���ֱ��ɾ�������ļ�����ֵ�����û����ϸ���飬���ܻ������������  
                else
                {
                    remove(path);
                }
            }
        }
        //�ر��ļ��У�ֻ�йر��˲���ɾ����������������˺ܾã���׼c���õ���closedir  
        //������ܣ�һ�����Handle�ĺ���ִ�к󣬶�Ҫ���йرյĶ�����  
        _findclose(handle);
    }
    //�Ƴ��ļ���  
    resultone = rmdir(dirPath);
    return  resultone;
}


string getPassword()
{
    string retstr;
    char ch = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!retstr.empty()) {
                cout << "\b \b";
                retstr.erase(retstr.end() - 1);
            }
        } else if (retstr.length() >= MAX_PASSWORD_LENGTH) {
            continue;
        } else if (ch == 27) {
            return ERROR_PASSWORD;
        } else {
            cout << "*";
            retstr.push_back(ch);
        }
    }

    cout << endl;
    return retstr;
}

//����q����
int getNumber(int down, int up)
{
    while (1) {
        string choose = getString();
        if (choose == ERROR_STRING) {
            return INT_MAX;
        }
        stringstream str(choose);
        int temp = INT_MIN;
        str >> temp;
        string remain;
        str >> remain;
        if (!remain.empty()) {
            cout << "����������" << endl;
            continue;
        }

        if (temp < down || temp > up) {
            cout << "������" << down << "��" << up << "֮�������" << endl;
            continue;
        }
        return temp;
    }
}

//����Esc����
string getString()
{
    cout << "# ";
    string retstr;
    char ch = 0;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!retstr.empty()) {
                cout << "\b \b";
                retstr.erase(retstr.end() - 1);
            }
        } else if (retstr.length() >= MAX_STRING_LENGTH) {
            continue;
        } else if (ch == 27) { //Esc
            return ERROR_STRING;
        } else {
            cout << ch;
            retstr.push_back(ch);
        }
    }

    cout << endl;
    return retstr;
}