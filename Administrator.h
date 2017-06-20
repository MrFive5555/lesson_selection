#ifndef ADMINISTRATOR_H_
#define ADMINISTRATOR_H_

#include "Schedule.h"

#define THE_MAX_SELECT 100

class Administrator {
public:
    /*
    * @para stuSet is a set of id of the students who should select lesson
    * @para lesSet is a set of lesson which can be selected
    * return the select id
    */
    static ID_t creatSelect(string name, set<ID_t>&stuSet, set<ID_t>&lesSet);
    static bool sendRequest(ID_t stuId, ID_t lesId, ID_t selectId);

    static set<ID_t> getAllSelection();

    /*
    * when all student have selected their lesson, the administrator can 
    * start to arrange the lesson
    * return the student set, they fail to select lesson
    */
    static set<ID_t> startSelect(ID_t selectId);

    /* return the set of stu should perform
    */
    static set<ID_t> getSelection(ID_t stu);

    static string getSelectionName(ID_t selectionID);

    /* return the lesson can be selected in the selection
    */
    static set<ID_t> getSelectionLesson(ID_t selectionID);
private:
    /*
    * @para stuVec : the vector of all student should choose a lesson
    * @para requestMap : it's a map from a lesson id to some student ids,
    * these students have request for take the lesson with id
    * very element of the returned vector is a pair. The first is the Student
    * and the second is the lesson.
    */
    static void arrangeLesson(vector<ID_t>& stuVec, const multimap<ID_t, ID_t>& requestMap);

    /*
    * return the id the new selection can use
    */
    static ID_t getSelectID();

    static void readIsUsed();

    static void writeIsUsed();

    static bool isIdUsed[THE_MAX_SELECT];
};
#endif // !ADMINISTRATOR_H_