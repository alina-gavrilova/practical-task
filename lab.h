#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
public:
    int number_of_rows, number_of_columns;
    vector<vector<float>> mat;

    Matrix(int rows, int columns)
    {
        number_of_rows = rows;
        number_of_columns = columns;
        mat.resize(number_of_rows);
        vector<float> v(number_of_columns, 0);
        for (int i = 0; i < number_of_rows; i++)
            mat[i] = v;
    }

    Matrix(vector<vector<float>> m)
    {
        number_of_rows = size(m);
        number_of_columns = size(m[0]);
        mat.resize(number_of_rows);
        for (int i = 0; i < number_of_rows; i++)
            mat[i] = m[i];
    }

    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
    Matrix mul_by_a_num(float num);
    Matrix mul_of_hadamard(Matrix&);
    friend ostream& operator<<(ostream&, Matrix&);

    float trace();
    float determinant();
    float scalar(Matrix&);
    float euclidean();
    float maximum();
    float frobenius();

    friend float angle(Matrix&, Matrix&);
    friend int rank_mat(Matrix&);
    Matrix inverse();
    Matrix transpose();
};

class Unit : public Matrix
{
public:
    Unit(int rows, int columns) :Matrix(rows, columns)
    {
        vector<float> v(number_of_columns, 1);
        for (int i = 0; i < number_of_rows; i++)
            mat[i] = v;
    }

    Unit(vector<vector<float>> m) :Matrix(m) {}
};

class Diagonal : public Matrix
{
public:
    Diagonal(vector<float> v) :Matrix(size(v), size(v))
    {
        for (int i = 0; i < number_of_rows; i++)
            mat[i][i] = v[i];
    }

    Diagonal(vector<vector<float>> m) :Matrix(m) {}
};

class Upper_Triangular : public Matrix
{
public:
    Upper_Triangular(vector<vector<float>> m) :Matrix(m) {}
};

class Lower_Triangular : public Matrix
{
public:
    Lower_Triangular(vector<vector<float>> m) :Matrix(m) {}
};

class Symmetric : public Matrix
{
public:
    Symmetric(vector<vector<float>> m) :Matrix(m) {}
};

class Incorrect_dimensions {};