#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include <sstream>

using namespace std;

int solver(const string raw){// return with solving input sudoku in raw in output seed_matrix.
  int i,j,k;
  int A[9][9];
  int countNO=0;
  ifstream file1;
  /*clauses for input by users*/
  file1.open(raw.c_str());//used to make seed
  for(i=0;i<9;i++){//to count the number of clauses
    for(j=0;j<9;j++){
      file1 >> A[i][j];
      if(A[i][j] != 0){
        countNO++;//countNO is the number of +ve number or say non zero numbers which already present in the input array.
      }
    }
  }
  file1.close();
  ofstream file;
  file.open("encode2.txt");
  ifstream readEncode;
  readEncode.open("encode3.txt");
  file << "p cnf 999 " << countNO + 3241 << endl;

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

  for(i=1;i<99;i++){
    file << -i << " 0 \n";
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


  for(i=0;i<9;i++){//inserting in  clauses if non zero entry inside sudoku.
    for(j=0;j<9;j++){
      if(A[i][j] != 0){
        file << 100*(i+1) + 10*(j+1) + A[i][j] << " 0 \n";
      }
    }
  }

  ifstream seed_neg;
  seed_neg.open("seed_neg.txt");
  int h;
  while(seed_neg >> h){
    if(h < 0){
      file << h << " ";
    }
  }
  file << " 0";
  file.close();
  system("minisat encode2.txt decode.txt");

  ifstream myfile;
  myfile.open("decode.txt");
  int x;
  i=0,j=0;
  string str;
  myfile >> str;
  if(str == "UNSAT"){//unique
    return 1;
  }
  if(str == "SAT"){//non-unique
    return 0;
  }
}

void solver2(const string raw,string seed_matrix){
  int i,j,k;
  int A[9][9];
  int count=0;
  ifstream file1;
  /*clauses for input by users*/
  file1.open(raw.c_str());//used to make seed
  for(i=0;i<9;i++){//to count the number of clauses
    for(j=0;j<9;j++){
      file1 >> A[i][j];
      if(A[i][j] != 0){
        count++;
      }
    }
  }
  file1.close();
  ofstream file;
  ofstream file_to_be_used;
  file_to_be_used.open("encode3.txt");
  file.open("encode.txt");
  file << "p cnf 999 " << count + 3241 << " \n";
  for(i=0;i<9;i++){//inserting in  clauses if non zero entry inside sudoku.
    for(j=0;j<9;j++){
      if(A[i][j] != 0){
        file_to_be_used << 100*(i+1) + 10*(j+1) + A[i][j] << " 0 \n";
        file << 100*(i+1) + 10*(j+1) + A[i][j] << " 0 \n";
      }
    }
  }

  /*individual cell clauses*/
  for(i=1;i<=9;i++){//clauses for showing every cell have atleast one of values from 1-9
    for(j=1;j<=9;j++){
      for(k=1;k<=9;k++){
        file_to_be_used << 100*i + 10*j + k << " ";
        file << 100*i + 10*j + k << " ";
      }
      file_to_be_used << "0 \n";
      file << "0 \n";
    }
  }
  for(i=1;i<=9;i++){//no cell can has two values
    for(j=1;j<=9;j++){
      for(k=1;k<=9;k++){
        for(int x=k+1;x<=9;x++){
          file_to_be_used << -(100*i + 10*j + k) << " " << -(100*i + 10*j + x) << " 0 \n";
          file << -(100*i + 10*j + k) << " " << -(100*i + 10*j + x) << " 0 \n";
        }
      }
    }
  }

  /*row clauses*/
  for(i=1;i<=9;i++){//clauses for showing all rows contain all value form 1-9
    for(k=1;k<=9;k++){
      for(j=1;j<=9;j++){
        file_to_be_used << 100*i + 10*j + k << " " ;
        file << 100*i + 10*j + k << " " ;
      }
      file_to_be_used << "0 \n";
      file << "0 \n";
    }
  }

  /*column clauses*/
  for(j=1;j<=9;j++){//clauses for showing all column contain all value form 1-9
    for(k=1;k<=9;k++){
      for(i=1;i<=9;i++){
        file_to_be_used << 100*i + 10*j + k << " " ;
        file << 100*i + 10*j + k << " " ;
      }
      file_to_be_used << "0 \n";
      file << "0 \n";
    }
  }
  /*block clauses*/
  for(k=1;k<=9;k++){
    for(i=1;i<=9;i=i+3){
      for(j=1;j<=9;j=j+3){
        for(int x=i;x<i+3;x++){
          for(int y=j;y<j+3;y++){
            file_to_be_used << 100*x + 10*y + k << " ";
            file << 100*x + 10*y + k << " ";
          }
        }
        file_to_be_used << "0 \n";
        file << "0 \n";
      }
    }
  }
  file_to_be_used.close();
  file.close();
  srand(time(NULL));
  stringstream ss;
  ss << rand();
  string random = ss.str();
  string cmd = "minisat -rnd-seed=";
  cmd += random;
  cmd += " -rnd-freq=1 encode.txt decode.txt";//encode.txt contains block,row,col and negation of seed_matrix.//////////////////////////////////
  system(cmd.c_str());

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
  ofstream ffile;
  ffile.open(seed_matrix.c_str());
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      ffile << A[i][j] << " ";
    }
     ffile << endl;
  }
  ffile.close();
  //add negation to encoded file.
  ofstream fileEM;
  ofstream fileEM2;
  ifstream myfile2;
  myfile2.open("decode.txt");
  fileEM.open("encode.txt",ios::app);
  fileEM2.open("encode3.txt",ios::app);
  ofstream file_seed_neg;
  file_seed_neg.open("seed_neg.txt");
  string isSAT;
  myfile2 >> isSAT;
  while(myfile2 >> x){
    fileEM2 << -x << " ";
    fileEM << -x << " ";
    file_seed_neg << -x << " ";
  }
  file_seed_neg.close();
  fileEM2.close();
  fileEM.close();
  myfile2.close();
}


int main(){
  int bug=0;
  solver2("raw.txt","seed_matrix.txt");
  //set seed as initial-matrix.
 int makeArray[9][9];
  ifstream fileX;
  fileX.open("seed_matrix.txt");
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      fileX >> makeArray[i][j];
    }
  }
  fileX.close();
  ofstream fileY;
  fileY.open("initial-matrix.txt");
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      fileY << makeArray[i][j] << " ";
    }
  }
  fileY.close();
//till now fileY i.e. initial-matrix.txt contains the seeded matrix.and encode.txt have been updated.
  int count = 0;
  srand(time(NULL));
  //while loop starts here
  while(true){
    int remove_row_idx = rand()%9;
    int remove_col_idx = rand()%9;
    cout << remove_row_idx << " , " << remove_col_idx << endl;
    int temp[9][9];
    ifstream fileA;
    fileA.open("initial-matrix.txt");
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        fileA >> temp[i][j];
      }
    }
    fileA.close();
     //temp contain the initial form of matrix in the while loop.
    ofstream fileB;
    fileB.open("final-matrix.txt");
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        if((i==remove_row_idx) && (j==remove_col_idx)){
          fileB << "0" << " ";
        }else{
          fileB << temp[i][j] << " ";
        }
      }
      fileB << endl;
    }
    fileB.close();
    //final-matrix is the matrix which is being feeded to minisat for checking if it is satisfiable or not
    int breaker = solver("final-matrix.txt");
    if(breaker == 0){
     break;
    }
    ofstream file_paste;
    file_paste.open("initial-matrix.txt");
    ifstream file_copy;
    file_copy.open("final-matrix.txt");
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        int x;
        file_copy >> x;
        file_paste << x << " ";
      }
    }
    file_copy.close();
    file_paste.close();
    count++;
//while loop ends here
}
  int left = 81 - count;
  int M[9][9];
  ifstream finFile;
  finFile.open("initial-matrix.txt");
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      finFile >> M[i][j];
    }
  }
  finFile.close();//as initial-matrix or M[][] contains the matrix which came out of loop and removing any one random no would give non unique solution.
  int outflag = 0;
    outflag=1;
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        if(M[i][j]!=0){
          ofstream test;
          test.open("test.txt");
          for(int k=0;k<9;k++){
            for(int l=0;l<9;l++){
              if(k==i &&l==j){
                test << 0 << " ";
              }else{
                test << M[k][l] << " ";
              }
            }
          }//test.txt contain a particularly removed element from M[][]
          test.close();
          int counter;
          counter = solver("test.txt");//return 1 if unique and 0 if not unique on removing M[i][j]
          if(counter == 1){
            M[i][j] = 0;
            outflag =0;
          }
        }
      }
    }
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        if(M[i][j] == 0){
          cout << ".";
        }else{
          cout << M[i][j];
        }
      }
      cout <<endl;
    }

  return 0;
}
