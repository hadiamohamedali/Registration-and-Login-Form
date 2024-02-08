#include <iostream>
#include "sqlite3.h"
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string.h>
using namespace std;
//Operations Related With Database
void connection(); //Connect With Database...
void insertR();   //Add Information to Database...
void retrieve(); //Read Information From Database...
void deleteQ(); //Delete From Database...
void update(); //Update Information in Database...
sqlite3 *db;
sqlite3_stmt *stmt;
int result , age;
string query , name , email;
class Login{
private:
    string LoginID , Password;
public:
    Login():LoginID("") , Password(""){}

    void setID(string id)
    {
        LoginID = id;
    }
    void setPW(string pw)
    {
        Password = pw;
    }
    string getID()
    {
        return LoginID;
    }
    string getPW()
    {
        return Password;
    }
};
registration(Login log)
{
    system("cls");
    string idd , pw;
    cout<<"\tEnter Login ID: ";
    cin>>idd;
    log.setID(idd);

    start:
    cout <<"\tEnter Login Strong Password: ";
    cin >> pw;
    if(pw.length() >= 8)
    {
        log.setPW(pw);
    }
    else
    {
        cout << "\tEnter Minimum 8 Characters...!" << endl;
        goto start;
    }
    ofstream outfile("Login.txt" , ios :: app);
    if(!outfile)
    {
        cout << "\tError: File Can Not Open...!" << endl;
    }
    else
    {
        outfile << "\t" << log.getID() << " : " << log.getPW() << endl << endl;
        cout << "\tUser Registered Successfully...!" << endl;
    }
    outfile.close();
    Sleep(3000);
}
login()
{
    system("cls");
    string id , pw;
    cout << "\tEnter Login ID: ";
    cin >> id;

    cout << "\t Enter Password: ";
    cin >>pw;

    ifstream infile("Login.txt");
    if(!infile)
    {
        cout << "\tError: File Can Not Open...!"<< endl;
    }
    else
    {
        string line;
        bool found = false;
        while(getline(infile , line))
        {
            stringstream ss;
            ss<<line;
            string userID , userPW;
            char delimiter;
            ss>>userID>>delimiter>>userPW;

            if(id == userID && pw == userPW)
            {
                found = true;
                cout << "\tPlease Wait....";
                for(int i = 0; i < 3; i++)
                {
                    cout << ".";
                    Sleep(800);
                }
                system("cls");
                cout << "\tWelcome To This Page..!" << endl;
            }
        }
        if(!found)
        {
            cout << "\tError: Incorrect Login ID Or Password...!" << endl;
        }
    }
    infile.close();
    Sleep(5000);
}
class visitor
{
public:
    char Name[100];
    int Age , ID;
};
//Operations Related With File Handling
//Add Information of Visitor in File...
void AddVisitor()
{
    fstream outfile1;
    outfile1.open("Visitor.txt" , ios::out | ios::app);
    visitor v; char x;
    do
    {
      cout << "Enter The Visitor'S Name: ";
      cin >> v.Name;
      cout << "Enter The Visitor'S Age: ";
      cin >> v.Age;
      cout << "Enter The Visitor'S ID: ";
      cin >> v.ID;
      //File Writing
      outfile1.write((char*)&v , sizeof(v));
      cout << "Enter Any Record Again (Y / N) : ";
      cin >> x; cout << endl;
    }while(x == 'Y');

    outfile1.close();
}
//Read Information of Visitor From File...
void ReadVisitor()
{
    ifstream in1; visitor v;
    in1.open("Visitor.txt", ios::in);
    if(in1.is_open())
    {
        cout << "Name\tAge\tID" << endl;
        in1.read((char*)&v , sizeof(v));
        while(!in1.eof())
        {
            cout << v.Name << "\t" << v.Age << "\t" << v.ID<< endl;
            in1.read((char*)&v , sizeof(v));
        }
        in1.close();

    }
    else
    {
        cout << "----This File Not Found----" << endl;
    }
}
//Search to Find Any Visitor...
void SearchVisitor()
{
    char str[100];
    cout << "Enter The Name Search For : ";
    cin >> str; cout << endl;
    bool found = false;
    ifstream in1; visitor v;
    in1.open("Visitor.txt", ios::in);
    if(in1.is_open())
    {
        in1.read((char*)&v , sizeof(v));
        while(!in1.eof())
        {
            if(strcmp(str , v.Name) == 0)
            {
              cout << "Name\tAge\tID" << endl;
              cout << v.Name<<"\t"<<v.Age<<"\t"<<v.ID<<endl;
              found = true;
            }
            in1.read((char*)&v , sizeof(v));
        }
        if(!found)
        {
            cout << "----Name Not Found----" << endl;
        }
        in1.close();
    }
    else
    {
        cout << "----File Not Found----" << endl;
    }
}
//If you insert information and you want to Edit Anything...
void UpdateVisitor()
{
    char str[100];
    cout << "Enter The Name Update For : ";
    cin >> str; cout << endl;
    bool found = false;
    fstream in1; visitor v;
    in1.open("Visitor.txt", ios::in | ios::out);
    if(in1.is_open())
    {
        in1.read((char*)&v , sizeof(v));
        while(!in1.eof())
        {
            if(strcmp(str , v.Name) == 0)
            {
               cout << "Enter The New ID For : " << str << endl;
               cin >> v.ID;
               int CurPos = in1.tellg();
               int VisSize = sizeof(v);
               in1.seekp(CurPos - VisSize , ios::beg);
               in1.write((char*) &v , sizeof(v));
               in1.seekg(CurPos - VisSize , ios::beg);
               in1.read((char*) &v , sizeof(v));
               cout << "Name\tAge\tID" << endl;
               cout << v.Name <<"\t"<<v.Age<<"\t"<<v.ID<<endl;
               found = true;
               break;
            }
            in1.read((char*)&v , sizeof(v));
        }
        if(!found)
        {
            cout << "----Name Not Found----" << endl;
        }
        in1.close();
    }
    else
    {
        cout << "----File Not Found----" << endl;
    }
}
//If Visitor Exits From Form , Delete Information of Visitor...
void DeleteVisitor()
{
     char str[100];
     cout << "Enter The Name Delete For : ";
     cin >> str; cout << endl;
     bool found = false;
     visitor v;
     ifstream in1("Visitor.txt", ios::in);
     ofstream out1("NewVisitor.txt" , ios::out | ios::app);
    if(in1.is_open())
    {
        in1.read((char*)&v , sizeof(v));
        while(!in1.eof())
        {
            if(strcmp(str , v.Name) != 0)
            {
              out1.write((char*)&v , sizeof(v));
              found = true;
            }
            in1.read((char*)&v , sizeof(v));
        }
        if(!found)
        {
            cout << "----Name Not Found----" << endl;
        }
        in1.close();
        out1.close();
        remove("Visitor.txt");
        rename("NewVisitor.txt" , "Visitor.txt");
    }
    else
    {
        cout << "----File Not Found----" << endl;
    }
  cout << "This Visitor Exits From The Form....." << endl;
}
int main()
{
    connection();
    Login log;
    bool exit = false;
    cout << "If you Want To Join US Please, Enter Yes And Enter No If You Do Not Want..." << endl;
    string x;
    cout << "Enter Your Choice: ";
    cin >> x;
    if(x == "Yes")
{
      cout << "Please, Complete Our Application..." << endl;
      insertR();
      cout << "Confirm  Registration..." << endl;
      AddVisitor();
      cout << "Application Completed..." << endl;
      cout << "If You Want To Edit AnyThing in Application...\n Click 1 To Edit\n Click 2 Delete All Information\n Press 3 To Continue..." << endl;
      int xx; cin >> xx;
      switch(xx)
      {
       case 1:
           update();
           main();
           cout << "...Confirm Updating..." << endl;
           UpdateVisitor();
           break;
       case 2:
           deleteQ();
           main();
           cout << "...Confirm Deleting..." << endl;
           DeleteVisitor();
           break;
       case 3:
           while(!exit)
           {
               system("cls");
               int val;
               cout << "\tWelcome To Registration & Login Form" << endl;
               cout << "\t************************************" <<endl;
               cout << "\t1.Register." << endl;
               cout << "\t2.Login." << endl;
               cout <<"\t3.Exit." << endl;
               cout << "\tEnter Choice: "; cin >> val;

               if(val == 1)
               {
                   registration(log);
               }
               else if(val == 2)
               {
                   Login();
               }
               else if(val == 3)
               {
                   system("cls");
                   exit = true;
                   cout << "\tGood Luck..!" << endl;
                   Sleep(3000);
               }
               Sleep(3000);
           }

          }



    }
    else
    {
      system("cls");
      exit = true;
      cout << "\tGood Luck!" << endl;
    }

    return 0;
}
//Functions Related With Database...
void connection()
{
    if(sqlite3_open("demo.db" , &db) == SQLITE_OK)
    {
        result = sqlite3_prepare_v2(db , "CREATE TABLE IF NOT EXISTS user(name VARCHAR(50) , age INT , email VARCHAR(80));" , -1 , &stmt , NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK)
        {
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
        }
    }
}

void insertR()
{
    cout << "Enter Your Name: \n";
    cin >> name;


    cout << "Enter Your Age: \n";
    cin >> age;

    cout << "Enter Your Email: \n";
    cin >> email;




    query = "INSERT INTO user(name , age , email) VALUES(? , ? , ?);";

    result = sqlite3_prepare_v2(db , query.c_str() , -1 , &stmt , NULL);

    sqlite3_bind_text(stmt, 1, name.c_str(), name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_text(stmt, 3,email.c_str(), email.length() , SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result != SQLITE_OK)
    {
        cout << "ERROR: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cout << "Data Inserted Successfully \n";
    }
}

void retrieve()
{
    query = "SELECT rowid, *FROM user";
    result = sqlite3_prepare_v2(db, query.c_str() , -1 , &stmt , NULL);

    if(result != SQLITE_OK)
    {
        cout << "ERROR: "<< sqlite3_errmsg(db) << "\n";
    }
    else
    {

       cout <<"\n---------------------------------------------------------------------------------------\n";
       cout << left << "\t" << setw(15) << "ID "
          << setw(25) << "Name "
          << setw(25) << "Age"
          << setw(25) << "Email ";
        cout <<"\n---------------------------------------------------------------------------------------\n";
        while((result = sqlite3_step(stmt) == SQLITE_ROW))
        {
            cout <<  left << "\t" << setw(15) << sqlite3_column_text(stmt , 0)
                 <<  setw(25)<< sqlite3_column_text(stmt , 1)
                 <<  setw(25) << sqlite3_column_text(stmt , 2)
                 <<  setw(25) << sqlite3_column_text(stmt , 3) << endl;
        }
        cout <<"\n---------------------------------------------------------------------------------------\n";
    }
}

void deleteQ()
{
    int id; char confirm;
    cout << "Which Record You Want to delete ? Enter [id] number: "; cin >> id;
    getchar();

    cout << "Are you Sure? Enter [y] for Yes , [n] For No: \n";
    cin >> confirm;
    if(confirm == 'y')
    {
           query = "DELETE FROM user WHERE rowid = ?";
    result = sqlite3_prepare_v2(db , query.c_str() , -1 , &stmt , NULL);
    sqlite3_bind_int(stmt , 1 , id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result == SQLITE_OK)
    {
        cout << "Data Deleted Successfully...!" << endl;
    }
    else
    {
        cout << "Failed: " << sqlite3_errmsg(db) << endl;
    }

   }
   else
   {
      cout << "...Delete Operation Failed..." << endl;
   }
}
void update()
{
    int id;
    cout << "Which Record you want to Update? Enter [id] number: \n";
    cin >> id;
    getchar();

    cout << "Enter New Name: ";
    getline(cin , name);

    cout << "Enter New Age: ";
    cin >> age;
    getchar();

    query ="UPDATE user SET name = ?, pass = ?, email = ? WHERE rowid = ?;";
    result = sqlite3_prepare_v2(db , query.c_str() , - 1 , &stmt , NULL);
    sqlite3_bind_text(stmt , 1 , name.c_str() , name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt , 2 , age);
    sqlite3_bind_text(stmt , 3 , email.c_str() , name.length() , SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt , 4 , id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(result != SQLITE_OK)
    {
        cout << "Failed : " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        cout << "...Data Updated Successfully..." << endl;
    }
}
