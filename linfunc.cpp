#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#include "linearAlgebra.h"

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

//For LU factorization either create LU struct or just return an array
vector<vector<vector<double> > > LU(const vector<vector<double> > &A){

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