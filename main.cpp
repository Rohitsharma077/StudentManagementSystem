#include <iostream>
#include <mysql.h>

using namespace std;

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "tarun_rahul"

MYSQL *conn;

void connectDB(){
    conn = mysql_init(NULL);


    if(!mysql_real_connect(conn,"127.0.0.1",USER,PASS,DB,3306,NULL,0)){
        cout << "Connection Failed" << mysql_error(conn) << endl;
    }
    else{
            cout <<"Connected Successfully\n";
    }
}

void addStudent(){
    cout <<"Add student\n";
    string name , course;
    int age;
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter Age: ";
    cin>>age;
    cout<<"Enter Course Name: ";
    cin>>course;
    char query[400];
    sprintf(query,"INSERT INTO students(name , age , course) VALUES('%s',' %d ','%s')",name.c_str(),age , course.c_str());
    if(mysql_query(conn,query)){
        cout<<"Insert Failed: "<<mysql_error(conn)<<endl;
    }else{
        cout<<"Student Added Successfully "<<endl;
    }
}
void viewStudent(){
    if(mysql_query(conn, "SELECT * FROM students")){
        cout<<"Query Failed!"<<endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout<<"\nid\tName\tAge\tCourse\n";
    cout<<"------------------------------------------\n";
    while((row = mysql_fetch_row(res))){
        cout<<row[0]<<"\t"
            <<row[1]<<"\t"
            <<row[2]<<"\t"
            <<row[3]<<endl;
    }
    mysql_free_result(res);
}
void deleteStudent(){
    int ID;
    cout << "Enter Your ID: ";
    cin>>ID;

    char query[200];
    sprintf(query," DELETE FROM students WHERE ID = %d ", ID);

    if(mysql_query(conn, query)){
        cout<<"Deletion Failed"<<mysql_error(conn)<<endl;
    }
}
int main()
{
     connectDB();
    int choice;

    while(true){
        cout<<"===============================================\n";
        cout << "--- Student Management System ---\n";
        cout <<"==============================================\n";
        cout <<" \n";
        cout <<"----------------------------------------------\n";
        cout <<"1. Add Student\n";
        cout <<"2. View Student\n";
        cout <<"3. Delete Student\n";
        cout <<"4. Exit\n";
        cout <<"----------------------------------------------\n";
        cout <<"----------------------------------------------\n";
        cout<<"Enter a Number :- ";
        cin >> choice;
        cout <<"----------------------------------------------\n";
        cout <<"----------------------------------------------\n";
        cout<<"\nYour choice is : "<<choice <<endl;
        switch (choice){
        case 1:
            addStudent();
            break;
        case 2:
            viewStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            cout<<"Thank You for visiting !\n";
            return 0;
        default:
            cout<<"Invaild Choice\n";

        }

    }
}
