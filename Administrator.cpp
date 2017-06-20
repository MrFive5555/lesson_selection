#include <algorithm>
#include <direct.h>
#include <stdexcept>

#include "Administrator.h"
#include "compile_option.h"
#include "other.h"

using std::pair;

bool Administrator::isIdUsed[THE_MAX_SELECT] = { };

ID_t Administrator::creatSelect(string name, set<ID_t>&stuSet, set<ID_t>&lesSet)
{
    ID_t creatId = getSelectID();

    //make directory
    char fileName[50];
    sprintf(fileName, "data/select/%d", creatId);
    mkdir(fileName);

    //creat a file to record the name
    sprintf(fileName, "data/select/%d/name.data", creatId);
    fstream file_name(fileName, fstream::out);
    file_name << name;

    //creat a file to record the request
    sprintf(fileName, "data/select/%d/request.data", creatId);
    fstream file(fileName, fstream::out | fstream::binary);
    
    //record the students
    sprintf(fileName, "data/select/%d/stu.data", creatId);
    fstream stuFile(fileName, fstream::out | fstream::binary);
    for (set<ID_t>::iterator iter = stuSet.begin(); iter != stuSet.end(); ++iter) {
        ID_t temp = *iter;
        stuFile.write(reinterpret_cast<char*>(&temp), sizeof(ID_t));
    }

    //record the lesson
    sprintf(fileName, "data/select/%d/les.data", creatId);
    fstream lesFile(fileName, fstream::out | fstream::binary);
    for (set<ID_t>::iterator iter = lesSet.begin(); iter != lesSet.end(); ++iter) {
        ID_t temp = *iter;
        lesFile.write(reinterpret_cast<char*>(&temp), sizeof(ID_t));
    }

    isIdUsed[creatId] = true;
    writeIsUsed();
    return creatId;
}

bool Administrator::sendRequest(ID_t stuId, ID_t lesId, ID_t selectId)
{
    if (!StudentFile::IsInFile(stuId) || !LessonFile::IsInFile(lesId)) {
        return false;
    };

    char fileName[50];
    sprintf(fileName, "data/select/%d/request.data", selectId);
    fstream file(fileName, fstream::in | fstream::out | fstream::binary);

    pair<ID_t, ID_t> req(lesId, stuId);
    pair<ID_t, ID_t> temp = pair<ID_t, ID_t>(INT_MAX, INT_MAX);
    file.seekg(0);

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(pair<ID_t, ID_t>))) {
        if (temp.second == req.second) {
            //if the same student has send a request before
            long offset = sizeof(pair<ID_t, ID_t>);
            file.seekg(-offset, fstream::cur);
            file.write(reinterpret_cast<char*>(&req), sizeof(pair<ID_t, ID_t>));
            return true;
        }
    }
    file.clear();
    file.close();
    file.open(fileName, fstream::out | fstream::app);
    file.write(reinterpret_cast<char*>(&req), sizeof(pair<ID_t, ID_t>));

    return true;
}

set<ID_t> Administrator::getAllSelection()
{
    readIsUsed();
    set<ID_t> allSelection;
    for (int i = 0; i != THE_MAX_SELECT; ++i) {
        if (isIdUsed[i]) {
            allSelection.insert(i);
        }
    }
    return allSelection;
}

set<ID_t> Administrator::startSelect(ID_t selectId)
{
    char fileName[50];

    //get the students
    sprintf(fileName, "data/select/%d/stu.data", selectId);
    fstream stuFile(fileName, fstream::in | fstream::binary);
    vector<ID_t>stuVec;
    ID_t id;
    
    while (stuFile.read(reinterpret_cast<char*>(&id), sizeof(ID_t))) {
        stuVec.push_back(id);
    }
    stuFile.close();

    //get request
    multimap<ID_t, ID_t>requestMap;
    sprintf(fileName, "data/select/%d/request.data", selectId);
    fstream reqFile(fileName, fstream::in | fstream::binary);
    pair<ID_t, ID_t>req;

    while (reqFile.read(reinterpret_cast<char*>(&req), sizeof(pair<ID_t, ID_t>))) {
        requestMap.insert(req);
    }
    reqFile.close();

    arrangeLesson(stuVec, requestMap);

    //remove the selection file
    sprintf(fileName, "data/select/%d", selectId);
    removeDir(fileName);

    isIdUsed[selectId] = false;
    writeIsUsed();

    set<ID_t> retSet(stuVec.begin(), stuVec.end());
    return retSet;
}

set<ID_t> Administrator::getSelection(ID_t stu)
{
    readIsUsed();

    set<ID_t> selectionSet;
    //check all selection
    for (int i = 0; i != THE_MAX_SELECT; ++i) {
        if (isIdUsed[i] == false) {
            continue;
        }

        char fileName[50];
        sprintf(fileName, "data/select/%d/stu.data", i);
        fstream stuFile(fileName, fstream::in | fstream::binary);
        
        ID_t tempID = INT_MAX;
        
        while (stuFile.read(reinterpret_cast<char*>(&tempID), sizeof(ID_t))) {
            if (tempID == stu) {
                selectionSet.insert(i);
                break;
            }
        }
    }
    return selectionSet;
}

ID_t Administrator::getSelectID()
{
    for (int i = 0; i != THE_MAX_SELECT; ++i) {
        if (isIdUsed[i] == false) {
            return i;
        }
    }

    throw std::runtime_error("the macro THE_MAX_SELECT is too small");
}

string Administrator::getSelectionName(ID_t selectionID)
{
    char fileName[50];
    sprintf(fileName, "data/select/%d/name.data", selectionID);
    fstream file(fileName, fstream::in | fstream::binary);
    string ret;
    file >> ret;
    return ret;
}

set<ID_t> Administrator::getSelectionLesson(ID_t selectionID)
{
    char fileName[50];
    sprintf(fileName, "data/select/%d/les.data", selectionID);
    fstream lesFile(fileName, fstream::in | fstream::binary);
    
    ID_t temp = INT_MAX;

    set<ID_t> retSet;
    while (lesFile.read(reinterpret_cast<char*>(&temp), sizeof(ID_t))) {
        retSet.insert(temp);
    }

    return retSet;
}

void Administrator::arrangeLesson
(vector<ID_t>& stuVec, const multimap<ID_t, ID_t>& requestMap)
{
    multimap<ID_t, ID_t>::const_iterator beg = requestMap.begin();

    while (beg != requestMap.end()) {
        multimap<ID_t, ID_t>::const_iterator end = requestMap.upper_bound(beg->first);
        Lesson les(beg->first);
        vector<ID_t> allStudent; //all student choose the same lesson
        for (multimap<ID_t, ID_t>::const_iterator iter = beg; iter != end; ++iter) {
            allStudent.push_back(iter->second);
        }

        //execute the request
        while (!allStudent.empty()
            && Schedule::getTheStudentCount(les) != les.getMaxStudentNumber()) {

            vector<ID_t>::iterator pos = allStudent.begin() + rand() % allStudent.size();
            stuVec.erase(std::find(stuVec.begin(), stuVec.end(), *pos));
            Schedule::addStudentToLesson(Student(*pos), les);
            allStudent.erase(pos);
        }

        beg = end;
    }

}

void Administrator::readIsUsed()
{
    fstream file("data/select/isUsed.data", fstream::in | fstream::binary);
    for (int i = 0; i != THE_MAX_SELECT; ++i) {
        file.read(reinterpret_cast<char*>(&isIdUsed[i]), sizeof(bool));
    }
}

void Administrator::writeIsUsed()
{
    fstream file("data/select/isUsed.data", fstream::out | fstream::binary);
    for (int i = 0; i != THE_MAX_SELECT; ++i) {
        file.write(reinterpret_cast<char*>(&isIdUsed[i]), sizeof(bool));
    }
}