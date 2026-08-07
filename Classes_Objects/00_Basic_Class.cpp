#include<bits/stdc++.h>
using namespace std;

class Student{
    private:
        string name;
        int roll;
        float gpa;
        int studentID;
    public:
    
        Student(
            string name,
            int roll,
            float gpa,
            int id):
            name(name),
            roll(roll),
            gpa(gpa),
            studentID(id){}
        string getName() const{return name;}
        int getRoll() const{return roll;}
        float getGPA() const{return gpa;}
        int getStudentID() const{return studentID;}
        
        void updateGPA(float newGPA){
            if(newGPA > 0.0 && newGPA <=4.00){
                gpa = newGPA;
                cout<<"GPA Updated Successfully!\n";
            }
            else cout<<"Invalid GPA!\n";
        }
        bool isRoyalStudent(){ return gpa>3.75? true:false;}

        void printProfile(){
            cout<<"\nName: "<<name
            <<"\nRoll: "<<roll
            <<"\nGPA: "<<gpa
            <<"\nStudent ID: "<<studentID<<endl;    
        }
};

int main(){
    Student s1("Sobuj",2318013,3.80,23001313);
    Student s2("Esraf", 2318012,3.50,23001312);

    s1.printProfile();
    s2.printProfile();

    cout<<endl;
    cout<<"Gpa of "<< s1.getName() <<" : "<<s1.getGPA()<<endl;
    cout<<"Gpa of "<< s2.getName() <<" : "<<s2.getGPA()<<endl;

    s1.updateGPA(4.00);
    s2.updateGPA(4.56);

    cout<<"Gpa of "<< s1.getName() <<" : "<<s1.getGPA()<<endl;
    cout<<"Gpa of "<< s2.getName() <<" : "<<s2.getGPA()<<endl;

}