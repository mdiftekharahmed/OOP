#include<bits/stdc++.h>
using namespace std;

class BaseClass{
    private:
        int private_var;
    
    protected:
        int protected_var;
    
    public:
        int public_var;

        BaseClass(int private_var, int protected_var, int public_var):private_var(private_var),
            protected_var(protected_var), public_var(public_var){}
        
        void showBaseClass(){
            cout<<"\nFrom the base class\n=====================\n"
            <<"Private: "<<private_var
            <<"\nProtected: "<<protected_var
            <<"\nPublic: "<<public_var<<endl;
        }
        void changePrivate(int val){private_var=val;cout<<"Changed Successfully!\n";}
        void changeProtected(int val){protected_var=val;cout<<"Changed Successfully!\n";}
        void changePublic(int val){public_var=val;cout<<"Changed Successfully!\n";}

};

class DerivedClass:public BaseClass{
    public:
        DerivedClass(int private_var, int protected_var, int public_var): BaseClass(
            private_var, protected_var, public_var ){}
        void showDerived(){
            cout<<"\nFrom the derived class\n====================="
            <<"\nProtected: "<<protected_var
            <<"\nPublic: "<<public_var<<endl;
        }
};

int main(){

    BaseClass obj1(1,2,3);
    obj1.showBaseClass();

    DerivedClass obj2(3,2,4);
    obj2.showDerived();

    obj2.showBaseClass();

    return 0;
}
