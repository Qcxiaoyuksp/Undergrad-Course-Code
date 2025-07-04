#include<iostream>
#include<string>
#include<conio.h>
using namespace std;
struct TYPE_UFD
{
    string File_Name;
    bool Read;
    bool Write;
    bool Execute;
    int Length_File;
};
struct TYPE_MFD
{
    string User_Name;
    TYPE_UFD* Pointer;
};
struct  TYPE_AFD
{
    int File_ID;
    bool Read;
    bool Write;
    bool Execute;
    int Pointer;
};
class TYPE_FILE_SYSTEM
{
public:
    void Initial(void);
    void Start(void);
private:
    int _Number_Users;
    int _Number_Files;
    int _MaxNumber_Open_Files;
    TYPE_MFD* _MFD;
    TYPE_UFD* _UFD;
    TYPE_AFD* _AFD;
};
void TYPE_FILE_SYSTEM::Initial(void)
{
    _Number_Users = 10;
    _Number_Files = 10;
    _MaxNumber_Open_Files = 5;
    _UFD = new TYPE_UFD[_Number_Users * _Number_Files]; _MFD = new TYPE_MFD[_Number_Users];
    int i = 0;
    for (i = 0; i < _Number_Users; i++)
    {
        _MFD[i].Pointer = &(_UFD[i * _Number_Files]);
    }
    _AFD = new TYPE_AFD[_MaxNumber_Open_Files];
    _MFD[0].User_Name = "qc";
    _UFD[0].File_Name = "test1.txt";
    _UFD[0].Length_File = 10;
    _UFD[0].Read = true;
    _UFD[0].Write = false;
    _UFD[0].Execute = true;
    _UFD[1].File_Name = "test2.txt";
    _UFD[1].Length_File = 20;
    _UFD[1].Read = true;
    _UFD[1].Write = false;
    _UFD[1].Execute = false;
    for (i = 2; i < _Number_Files; i++)
    {
        _UFD[i].File_Name = "";
        _UFD[i].Length_File = -1;
        _UFD[i].Read = false;
        _UFD[i].Write = false;
        _UFD[i].Execute = false;
    }
}
void TYPE_FILE_SYSTEM::Start(void)
{
    int User_ID;
    int i, temp_int;
    string temp;
    char choice;
    int Number_Open_Files;
    string User_Name;
    string Command;
    TYPE_UFD* UFD;
    do
    {
        do
        {
            cout << "User name:";
            cin >> User_Name;
            for (User_ID = 0; User_ID < _Number_Users; User_ID++) {
                if (_MFD[User_ID].User_Name == User_Name)
                    break;
            }
            if (User_ID == _Number_Users)
                cout << "Bad user name , please try again ." << endl;
        } while (User_ID == _Number_Users);
        cout << "欢迎" << User_Name << "登录文件系统 !" << endl; UFD = _MFD[User_ID].Pointer;
        for (i = 0; i < _MaxNumber_Open_Files; i++)
        {
            _AFD[i].File_ID = -1;
        }
        Number_Open_Files = 0;
        do
        {
            cout << "C:\\" << User_Name << ">";
            cin >> Command;
            if (Command == "dir")
            {
                cout << endl;
                cout << "Files of user " << User_Name << endl;
                cout << "\t" << "State\t" << "Length\t" << "File name" << endl;
                for (i = 0; i < _Number_Files; i++) {
                    if (UFD[i].Length_File != -1) {
                        cout << "\t";
                        if (UFD[i].Read == true)
                            cout << "R";
                        else
                            cout << "-";
                        if (UFD[i].Write == true)
                            cout << "W";
                        else
                            cout << "-";
                        if (UFD[i].Execute == true)
                            cout << "E";
                        else
                            cout << "-";
                        cout << "\t";
                        cout << UFD[i].Length_File;
                        cout << "\t";
                        cout << UFD[i].File_Name << endl;
                    }
                }
                cout << endl;
            }
            else if (Command == "diropen")
            {
                cout << endl;
                cout << "Opening Files of user " << User_Name << endl; cout << "\t" << "State\t" << "Open File name" << endl; for (i = 0; i < _MaxNumber_Open_Files; i++) {
                    if (_AFD[i].File_ID != -1)
                    {
                        cout << "\t";
                        if (_AFD[i].Read == true)
                            cout << "R";
                        else
                            cout << "-";
                        if (_AFD[i].Write == true)
                            cout << "W";
                        else
                            cout << "-";
                        if (_AFD[i].Execute == true)
                            cout << "E";
                        else
                            cout << "-";
                        cout << "\t";
                        cout << UFD[_AFD[i].File_ID].File_Name << endl;
                    }
                }
                cout << endl;
            }
            else if (Command == "create") {
                for (i = 0; i < _Number_Files; i++)
                    if (UFD[i].Length_File == -1)
                        break;
                if (i == _Number_Files)
                    cout << "Error: you have already had " <<
                    _Number_Files << " files ." << endl;
                else {
                    cout << "请输入新文件信息:" << endl;
                    cout << "文件名 : ";
                    cin >> temp;
                    UFD[i].File_Name = temp;
                    cout << "Read (y/n):";
                    do
                    {
                        choice = _getch();
                    } while (choice != 'y' && choice != 'n');
                    if (choice == 'y')
                        UFD[i].Read = true;
                    else
                        UFD[i].Read = false;
                    cout << endl;
                    cout << "Write (y/n):";
                    do
                    {
                        choice = _getch();
                    } while (choice != 'y' && choice != 'n');
                    if (choice == 'y')
                        UFD[i].Write = true;
                    else
                        UFD[i].Write = false;
                    cout << endl;
                    cout << "Execute (y/n):";
                    do
                    {
                        choice = _getch();
                    } while (choice != 'y' && choice != 'n');
                    if (choice == 'y')
                        UFD[i].Execute = true;
                    else
                        UFD[i].Execute = false;
                    cout << endl;
                    cout << "Length :";
                    cin >> temp_int;
                    if (temp_int > 0)
                        UFD[i].Length_File = temp_int;
         cout << "Ok , the new file " << UFD[i].File_Name << " is created!" << endl;
                }
            }
            else if (Command == "delete")
            {
                cout << "Please enter the file name :";
                cin >> temp;
                for (i = 0; i < _Number_Files; i++)
                    if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
                        break;
                if (i == _Number_Files)
                    cout << "Bad file name , please try again ." << endl; else {
                    UFD[i].Length_File = -1;
                    cout << "Ok , the file " << UFD[i].File_Name << " is deleted ." << endl;
                }
            }
            else if (Command == "open")
            {
                if (Number_Open_Files == _MaxNumber_Open_Files)
                    cout << "Error: you have already opened " << Number_Open_Files << " files." << endl;
                else
                {
                    cout << "Please enter the file name :";
                    cin >> temp;
                    for (i = 0; i < _Number_Files; i++)
                        if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
                            break;
                    if (i == _Number_Files)
                        cout << "Bad file name , please try again ." << endl;
                    else
                    {
                        Number_Open_Files++;
                        for (temp_int = 0;
                            temp_int < _MaxNumber_Open_Files; temp_int++)
                            if (_AFD[temp_int].File_ID == -1)
                                break;
                        _AFD[temp_int].File_ID = i;
                        _AFD[temp_int].Pointer = 0;
                        cout << "Please configure the open mode :" << endl;
                        if (UFD[i].Read == true)
                        {
                            cout << "Read (y/n):";
                            do
                            {
                                choice = _getch();
                            } while (choice != 'y' && choice != 'n');
                            if (choice == 'y')
                                _AFD[temp_int].Read = true;
                            else
                                _AFD[temp_int].Read = false;
                            cout << endl;
                        }
                        else
                            _AFD[temp_int].Read = false;
                        if (UFD[i].Write == true) {
                            cout << "Write (y/n):";
                            do
                            {
                                choice = _getch();
                            } while (choice != 'y' && choice != 'n');
                            if (choice == 'y')
                                _AFD[temp_int].Write = true;
                            else
                                _AFD[temp_int].Write = false;
                            cout << endl;
                        }
                        else
                            _AFD[temp_int].Write = false;
                        if (UFD[i].Execute == true)
                        {
                            cout << "Execute (y/n):";
                            do
                            {
                                choice = _getch();
                            } while (choice != 'y' && choice != 'n');
                            if (choice == 'y')
                                _AFD[temp_int].Execute = true;
                            else
                                _AFD[temp_int].Execute = false;
                            cout << endl;
                        }
                        else
                            _AFD[temp_int].Execute;
                        cout << "Ok , the file " << temp << " is open ." << endl;
                    }
                }
            }
            else if (Command == "logout")
            {
                cout << "Ok , see you later , " << User_Name << " !" << endl;
                break;
            }
            else if (Command == "close")
            {
                cout << "Please enter the file name :";
                cin >> temp;
                for (i = 0; i < _Number_Files; i++)
                    if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
                        break;
                if (i == _Number_Files)
                    cout << "Bad file name , please try again ." << endl; else
                {
                    for (temp_int = 0; temp_int < _MaxNumber_Open_Files; temp_int++)
                        if (_AFD[temp_int].File_ID == i)
                            break;
                    if (temp_int == _MaxNumber_Open_Files)
                        cout << "The file " << temp << " isn't open ." << endl;
                    else
                    {
                        _AFD[temp_int].File_ID = -1;
                        Number_Open_Files--;
                        cout << "Ok , the file " << temp << " is closed ." << endl;
                    }
                }
            }
            else if (Command == "read")
            {
                cout << "Please enter the file name :";
                cin >> temp;
                for (i = 0; i < _Number_Files; i++)
                    if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
                        break;
                if (i == _Number_Files)
                    cout << "Bad file name , please try again ." << endl; else
                {
                    for (temp_int = 0; temp_int < _MaxNumber_Open_Files; temp_int++)
                        if (_AFD[temp_int].File_ID == i)
                            break;
                    if (temp_int == _MaxNumber_Open_Files)
                        cout << "The file " << temp << " isn't open ." << endl;
                    else
                    {
                        if (_AFD[temp_int].Read == true)
                            cout << "Ok , read the file " << temp << " successfully." << endl;
                        else
                            cout << "Error: the open mode of the file doesn't allow you to read it ." << endl;
                    }
                }
            }
            else if (Command == "write")
            {
                cout << "Please enter the file name :";
                cin >> temp;
                for (i = 0; i < _Number_Files; i++)
                    if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
                        break;
                if (i == _Number_Files)
                    cout << "Bad file name , please try again ." << endl; else
                {
                    for (temp_int = 0; temp_int < _MaxNumber_Open_Files; temp_int++)
                        if (_AFD[temp_int].File_ID == i)
                            break;
                    if (temp_int == _MaxNumber_Open_Files)
                        cout << "The file " << temp << " isn't open ." << endl;
                    else
                    {
                        if (_AFD[temp_int].Write == true)
                            cout << "Ok , write the file " << temp << " successfully." << endl;
                        else
                            cout << "Error: the open mode of the file doesn't allow you to write it ." << endl;
                    }
                }
            }
            else if (Command == "shutdown")
            {
                cout << "Loging out........" << endl;
                cout << "Ok , see you later , " << User_Name << " !" << endl;
                cout << "The power of the computer is shutting down.........." << endl;
                break;
            }
            else
            {
                cout << "Bad commands , please try again ." << endl;
            }
        } while (Command != "logout" && Command != "shutdown");
    } while (Command != "shutdown");
}
int main() {
    TYPE_FILE_SYSTEM FS;
    FS.Initial();
    FS.Start();
    return 0;
}
