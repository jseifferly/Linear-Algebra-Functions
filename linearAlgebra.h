#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

std::vector<std::vector<double> > matrixMult(const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &B);
std::vector<std::vector<double> > forwardSub(const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &b);
void printMatrix(const std::vector<std::vector<double> > &X, std::ostream &out);
std::vector<std::vector<double> > backwardSub(const std::vector<std::vector<double> > &A, const std::vector<std::vector<double> > &b);
std::vector<std::vector<double> > identity(int size);
std::vector<std::vector<double> > transpose(const std::vector<std::vector<double> > &A);
//Add LU factorization, inverse matrix, and det