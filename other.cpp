
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
函数入口：文件夹的绝对路径
const char*  dirPath

函数功能：删除该文件夹，包括其中所有的文件和文件夹

返回值：  0  删除
-1  路径不对，或其它情况，没有执行删除操作
*/
int  removeDir(const char*  dirPath)
{

    struct _finddata_t fb;   //查找相同属性文件的存储结构体  
    char  path[250];
    //long    handle; // this sentence can't work in x64
    intptr_t handle; //I change this sentence
    int  resultone;
    int   noFile;            //对系统隐藏文件的处理标记  

    noFile = 0;
    handle = 0;


    //制作路径  
    strcpy(path, dirPath);
    strcat(path, "/*");

    handle = _findfirst(path, &fb);
    //找到第一个匹配的文件  
    if (handle != 0)
    {
        //当可以继续找到匹配的文件，继续执行  
        while (0 == _findnext(handle, &fb))
        {
            //windows下，常有个系统文件，名为“..”,对它不做处理  
            noFile = strcmp(fb.name, "..");

            if (0 != noFile)
            {
                //制作完整路径  
                memset(path, 0, sizeof(path));
                strcpy(path, dirPath);
                strcat(path, "/");
                strcat(path, fb.name);
                //属性值为16，则说明是文件夹，迭代  
                if (fb.attrib == 16)
                {
                    removeDir(path);
                }
                //非文件夹的文件，直接删除。对文件属性值的情况没做详细调查，可能还有其他情况。  
                else
                {
                    remove(path);
                }
            }
        }
        //关闭文件夹，只有关闭了才能删除。找这个函数找了很久，标准c中用的是closedir  
        //经验介绍：一般产生Handle的函数执行后，都要进行关闭的动作。  
        _findclose(handle);
    }
    //移除文件夹  
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

//输入q结束
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
            cout << "请输入数字" << endl;
            continue;
        }

        if (temp < down || temp > up) {
            cout << "请输入" << down << "到" << up << "之间的整数" << endl;
            continue;
        }
        return temp;
    }
}

//输入Esc结束
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