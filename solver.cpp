#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

int main(){
  int i,j,k;
  int A[9][9];
  int count=0;
  ofstream file;
  /*clauses for input by users*/
  file.open("encode.txt");
              for(i=0;i<9;i++){//to count the number of clauses
                for(j=0;j<9;j++){
                  cin >> A[i][j];
                  if(A[i][j] != 0){
                    count++;
                  }
                }
              }
              file << "p cnf 999 " << count + 3240 << " \n";
              for(i=0;i<9;i++){//inserting in  clauses if non zero entry inside sudoku.
                for(j=0;j<9;j++){
                  if(A[i][j] != 0){
                    file << 100*(i+1) + 10*(j+1) + A[i][j] << " 0 \n";
                  }
                }
              }

  /*individual cell clauses*/
  for(i=1;i<=9;i++){//clauses for showing every cell have atleast one of values from 1-9
    for(j=1;j<=9;j++){
      for(k=1;k<=9;k++){
        file << 100*i + 10*j + k << " ";
      }
      file << "0 \n";
    }
  }
  for(i=1;i<=9;i++){//no cell can has two values
    for(j=1;j<=9;j++){
      for(k=1;k<=9;k++){
        for(int x=k+1;x<=9;x++){
          file << -(100*i + 10*j + k) << " " << -(100*i + 10*j + x) << " 0 \n";
        }
      }
    }
  }

  /*row clauses*/
  for(i=1;i<=9;i++){//clauses for showing all rows contain all value form 1-9
    for(k=1;k<=9;k++){
      for(j=1;j<=9;j++){
        file << 100*i + 10*j + k << " " ;
      }
      file << "0 \n";
    }
  }

  /*column clauses*/
  for(j=1;j<=9;j++){//clauses for showing all column contain all value form 1-9
    for(k=1;k<=9;k++){
      for(i=1;i<=9;i++){
        file << 100*i + 10*j + k << " " ;
      }
      file << "0 \n";
    }
  }
  /*block clauses*/
  for(k=1;k<=9;k++){
    for(i=1;i<=9;i=i+3){
      for(j=1;j<=9;j=j+3){
        for(int x=i;x<i+3;x++){
          for(int y=j;y<j+3;y++){
            file << 100*x + 10*y + k << " ";
          }
        }
        file << "0 \n";
      }
    }
  }
  file.close();

  system("minisat encode.txt decode.txt");

  ifstream myfile;
  myfile.open("decode.txt");
  int x;
  i=0,j=0;
  string str;
  myfile >> str;
  while (myfile >> x){
    if(x>0){
      A[i][j]= x%10;
      if(i==8){
        i++;
        j=0;
      }else{
        j++;
      }
    }
  }
  myfile.close();
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
