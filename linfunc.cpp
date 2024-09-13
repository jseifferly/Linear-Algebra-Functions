#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#include "linearAlgebra.h"

vector<vector<double> > scale(const vector<vector<double> > &A, double num, char op){
    vector<double> col (A[0].size(),0);
    vector<vector<double> > answer(A.size(), col);
    
    if(op == '+'){
        for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = A[i][j] + num;
        }
     }
     return answer;
    }else if(op == '-'){
        for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = num - A[i][j];
        }
     }
     return answer;
    }else if(op == '*'){
        for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = A[i][j] * num;
        }
     }
     return answer;
    }else if(op == '/'){
        for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = A[i][j] / num;
        }
     }
     return answer;
    }else{
        cout << "Error: no valid operator given" <<endl;
        return {};
    }
}

vector<vector<double> > matrixAdd(const vector<vector<double> > &A, const vector<vector<double> > &B){
    vector<double> col (B[0].size(),0);
    vector<vector<double> > answer(A.size(), col);
    if(A.size() != B.size() || A[0].size() != B[0].size()){
        std::cout << "Matrices cannot compute (size error)" <<std::endl;
        return {};
    }
     for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = A[i][j] + B[i][j];
        }
     }
    return answer;
}

vector<vector<double> > matrixSub(const vector<vector<double> > &A, const vector<vector<double> > &B){
    vector<double> col (B[0].size(),0);
    vector<vector<double> > answer(A.size(), col);
    if(A.size() != B.size() || A[0].size() != B[0].size()){
        std::cout << "Matrices cannot compute (size error)" <<std::endl;
        return {};
    }
     for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
            answer[i][j] = A[i][j] - B[i][j];
        }
     }
    return answer;
}

vector<vector<double> > matrixMult(const vector<vector<double> > &A, const vector<vector<double> > &B){
    vector<double> col (B[0].size(),0);
    vector<vector<double> > answer(A.size(), col);
    if(A.size() != B[0].size()){
        std::cout << "Matrices cannot compute (size error)" <<std::endl;
        return {};
    }
    for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < A[0].size(); ++j){
           for(int k = 0; k < B.size(); ++k) {
                answer[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return answer;
}

vector<vector<double> > forwardSub(const vector<vector<double> > &A, const vector<vector<double> > &b){   
    int N = b[0].size();
    vector<double> xc (N,0);      
    vector<vector<double> > x (1,xc);
    for(int i = 0; i < N; ++i){
        double s = 0.0;
        for(int j = 0; j < i; ++j){
            s += A[i][j] * x[0][j];
        }
        x[0][i] = (b[0][i]- (s)) / A[i][i];
    }
    return x;
}

vector<vector<double> > backwardSub(const vector<vector<double> > &A, const vector<vector<double> > &b){   
    int N = b[0].size();
    vector<double> xc (N,0);      
    vector<vector<double> > x (1,xc); 
    for(int i = N-1; i >= 0; --i){
        double s = 0.0;
        for(int j = N-1; j > i; --j){
            s += A[i][j] * x[0][j];
        }
        x[0][i] = (b[0][i] - (s)) / A[i][i];
    }
    return x;
}

void printMatrix(const vector<vector<double> > &X, ostream &out){
    for(int i = 0; i < X.size(); ++i){
        out << "[ ";
        for(int j = 0; j < X[0].size(); ++j){
            out << X[i][j] << " ";
        }
        out << "]" << endl;
    }
}

vector<vector<double> > identity(int size){
    vector<double> row (size,0);
    vector<vector<double> > I;
    for(int i = 0; i < size; ++i){
        I.push_back(row);
        for(int j = i; j <= i; ++j){
            I[i][j] = 1.0;
        }
    }
    return I;
}

vector<vector<double> > transpose(const vector<vector<double> > &A){
    vector<double> col (A.size(),0); 
    vector<vector<double> > a (A[0].size(), col);
    
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < a[0].size(); ++j){
            a[i][j] = A[j][i];
        }
    }
    return a;
}

//still buggy, piovt error doesnt seem to work, but outputing 1s on diag so thats good!
vector<vector<double> > LU(const vector<vector<double> > &A, char key){
  
    // Creating varible matrices
    vector<double> n (A.size(),0);
    vector<vector<double> > temp = A;
    vector<vector<double> > L (n.size(),n);
    vector<vector<double> > U (n.size(), n);
    vector<vector<double> > C (A.size(),vector<double>(1, 0));
    vector<vector<double> > R (1, vector<double>(A[0].size(), 0));
    vector<vector<double> > p;
    int pivot = 0;

    //Define pivot and error check
    for(int i = 0; i < temp.size(); ++i){
        pivot = temp[i][i];
        if(pivot == 0){
            cout << "Error 0 on pivot" << endl;
            break;
        }
        //Create Column and row vecotrs
        for(int j = 0; j < C.size(); ++j){
            C[j][0] = temp[j][i];
        }
        C = scale(C,pivot,'/');
        for(int j = 0; j < A[0].size(); ++j){
            R[0][j] = temp[i][j];
        }

        p = matrixMult(C,R);

        //Subtract from temp
        temp = matrixSub(temp,p);
        
        //Add C and R vectors to L and U matricies
        for(int j = 0; j < C.size(); ++j){
            L[j][i] = L[j][i] + C[j][0];
        }

        for(int j = 0; j < R[0].size(); ++j){
            U[i][j] = U[i][j] + R[0][j];
        }
    }

    //Return L and U

    if(key == 'L'){
        return L;
    }else if(key == 'U'){
        return U;
    }else{
        cout<< "Error: Proper key not entered"<<endl;
    }
}


//LU factorizations first to make this easy
double det(const vector<vector<double> > &A){
    //det(A) = det(L) * det(U)
    //det(A) = det(U)
    //det(U) = sum(diag)
}










////Do det first to make this easy
//vector<vector<double> > inverse(vector<vector<double> > A){
//
//}
