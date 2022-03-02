#include "lab.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

Matrix Matrix::operator+(Matrix& m)
{
    if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns)
        throw Incorrect_dimensions();
    Matrix m_sum(number_of_rows, number_of_columns);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < number_of_columns; j++)
        {
            m_sum.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
    return m_sum;
}

Matrix Matrix::operator-(Matrix& m)
{
    if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns)
        throw Incorrect_dimensions();
    Matrix m_sub(number_of_rows, number_of_columns);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < number_of_columns; j++)
        {
            m_sub.mat[i][j] = mat[i][j] - m.mat[i][j];
        }
    return m_sub;
}

Matrix Matrix::operator*(Matrix& m)
{
    if (number_of_columns != m.number_of_rows)
        throw Incorrect_dimensions();
    Matrix m_mul(number_of_rows, number_of_columns);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < m.number_of_columns; j++)
            for (int k = 0; k < number_of_columns; k++)
            {
                m_mul.mat[i][j] += mat[i][k] * m.mat[k][j];
            }
    return m_mul;
}

Matrix Matrix::mul_by_a_num(float num)
{
    Matrix m_mul(number_of_rows, number_of_columns);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < number_of_columns; j++)
        {
            m_mul.mat[i][j] = mat[i][j] * num;
        }
    return m_mul;
}

Matrix Matrix::mul_of_hadamard(Matrix& m)
{
    if (number_of_rows != m.number_of_rows || number_of_columns != m.number_of_columns)
        throw Incorrect_dimensions();
    Matrix m_mul(number_of_rows, number_of_columns);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j < number_of_columns; j++)
        {
            m_mul.mat[i][j] = mat[i][j] * m.mat[i][j];
        }
    return m_mul;
}

ostream& operator<< (ostream& fo, Matrix& m)
{
    for (int i = 0; i < m.number_of_rows; i++)
    {
        for (int j = 0; j < m.number_of_columns; j++)
            fo << m.mat[i][j] << " ";
        fo << "\n";
    }
    fo << "\n";
    return fo;
}

float Matrix::trace()
{
    if (number_of_rows != number_of_columns)
        throw Incorrect_dimensions();
    float tr = 0;
    for (int i = 0; i < number_of_rows; i++)
    {
        tr += mat[i][i];
    }
    return tr;
}

float Matrix::scalar(Matrix& m)
{
    if (number_of_columns != m.number_of_rows)
        throw Incorrect_dimensions();
    float sc = 0;
    for (int i = 0; i < number_of_columns; i++)
        sc += mat[0][i] * m.mat[i][0];
    return sc;
}

float Matrix::euclidean()
{
    float euc = 0;
    for (int i = 0; i < number_of_columns; i++)
        euc += pow(mat[0][i], 2);
    euc = sqrt(euc);
    return euc;
}

float Matrix::maximum()
{
    float maxim = 0;
    for (int i = 0; i < number_of_columns; i++)
        maxim += abs(mat[0][i]);
    maxim = sqrt(maxim);
    return maxim;
}

float Matrix::frobenius()
{
    float fr = 0;
    for (int i = 0; i < number_of_rows; i++)
    {
        for (int j = 0; j < number_of_columns; j++)
        {
            fr += pow(mat[i][j], 2);
        }
    }
    fr = sqrt(fr);
    return fr;
}

float angle(Matrix& m1, Matrix& m2)
{
    Matrix m(m2.mat);
    m = m.transpose();
    if (m1.euclidean() == 0 || m.euclidean() == 0)
        return 0;

    float ang;
    ang = m1.scalar(m2) / (m1.euclidean() * m.euclidean());
    ang = acos(ang) * 180.0 / M_PI;
    return ang;
}

float Matrix::determinant()
{
    if (number_of_rows != number_of_columns)
        throw Incorrect_dimensions();

    Matrix m1(mat);
    for (int axis_1 = 0; axis_1 < number_of_rows; axis_1++)
    {
        bool flag = false;
        for (int axis_0 = axis_1; axis_0 < number_of_rows; axis_0++)
        {
            if (m1.mat[axis_0][axis_1])
            {
                if (axis_0 != axis_1)
                {
                    m1.mat[axis_0].swap(m1.mat[axis_1]);
                }
                flag = true;
                break;
            }
        }

        if (flag == false)
        {
            return 0;
        }

        for (int axis_0 = axis_1 + 1; axis_0 < number_of_rows; axis_0++)
        {
            for (; ; )
            {
                int d;
                d = m1.mat[axis_0][axis_1] / m1.mat[axis_1][axis_1];
                for (int j = axis_1; j < number_of_rows; j++)
                {
                    m1.mat[axis_0][j] -= d * m1.mat[axis_1][j];
                }
                if (m1.mat[axis_0][axis_1] == 0)
                {
                    break;
                }
                else
                {
                    m1.mat[axis_0].swap(m1.mat[axis_1]);
                }
            }
        }
    }

    float det = 1;
    for (int i = 0; i < number_of_rows; i++)
    {
        det *= m1.mat[i][i];
    }
    return abs(det);
}

Matrix Matrix::transpose()
{
    Matrix m(number_of_columns, number_of_rows);
    for (int i = 0; i < number_of_rows; i++)
    {
        for (int j = 0; j < number_of_columns; j++)
        {
            m.mat[j][i] = mat[i][j];
        }
    }
    return m;
}

int rank_mat(Matrix& m1)
{
    int rank = 0, qur = 1;

    while (qur <= min(m1.number_of_rows, m1.number_of_columns))
    {
        Matrix m2(qur, qur);
        for (int i = 0; i < (m1.number_of_rows - qur + 1); i++)
        {
            for (int j = 0; j < (m1.number_of_columns - qur + 1); j++)
            {
                for (int k = 0; k < qur; k++)
                {
                    for (int l = 0; l < qur; l++)
                    {
                        m2.mat[k][l] = m1.mat[i + k][j + l];
                    }
                }
                if (m2.determinant() != 0)
                {
                    rank = qur;
                }
            }
        }
        qur++;
    }
    return rank;
}