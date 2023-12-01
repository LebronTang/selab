#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    string a;
    string b;
    fstream file;
    file.open("pf.txt");
   
   
   
    while (!file.eof())
    {
        file>>a;
        if(a.empty()){
            cout<<"NO data found ";
        file.close();
        }
        else{
               file.open("pf.txt",ios::app);
               cout<<"ENter a qauertion : ";
               getline(cin,a);
               cout<<a;
            }
    }
    

    
         


    return 0;
}
