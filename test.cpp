  //**************************将输入的单词逆序输出*************************//
 #include <iostream>
  #include<stack>
  #include <stdio.h>
  #include<stdlib.h>
  using namespace std;
   
  int main(){
      string temp;
     stack<char> s;//
     int time;
   cin >> time;
  
     for(int i = 0; i < time ; i++){
  
         if(cin >> temp ){   //把输入赋值
             for(int j = 0; j < temp.length(); j++){
                 s.push(temp[j]);
             }
 
             while(!s.empty()){
                cout << s.top() ;
                 s.pop();
             }

             cout << " ";
       }        cout << endl;
     }
     return 0 ;
}
