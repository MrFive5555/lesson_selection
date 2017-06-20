#ifndef UI_H_
#define UI_H_

class UI {
public:
    static void welcome();
    static void LogIn();
    static void goodBye();

    static void showLesson(set<ID_t> lesSet);
    static void showStudent(set<ID_t> stuSet);
    static void showLesson_Detail(set<ID_t> lesSet);
};

/* 
* if it should re-login the function run() and LogIn() return false
* else return true if the program will exit
*/

class UI_student {
public:
    static bool run();
private:
    static bool LogIn();
    static void showInfo();
    static void changePassword();
    static void showLesson();
    static void selectLesson();

    static string checkPassword(ID_t id);
    static void setNewPassword(ID_t stuId, string newPassword);
    static Student me;
};

class UI_teacher {
public:
    static bool run();
};

/*
* if it should re-login the function run() and LogIn() return false
* else return true if the program will exit
*/
class UI_administrator {
public:
    static bool run();
private:
    static void checkStudent();
    static void checkLesson();
    static void addStudent();
    static void addLesson();
    static void deleteStudent();
    static void deleteLesson();
    static void creatNewSelection();
    static void startSelection();

    static bool hasSetPassword();
    static bool setPassword();
    static void changePassword();

    static bool LogIn();
};


#endif // !UI_H_
