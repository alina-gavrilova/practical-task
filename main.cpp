#include "lab.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    try
    {
        vector < vector <float> > ivector = { {1, 4, 7}, {2, 2, 7}, {2, 4, 3} };
        vector < vector <float> > ivector_1 = { {1, 4, 7}, {2, 2, 7} };
        vector < vector <float> > ivector_3 = { {1, 4, 7} };
        vector < vector <float> > ivector_4 = { {2}, {4}, {11} };
        vector < vector <float> > ivector_5 = { {2, 4, 11} };
        Matrix m1(ivector);
        Diagonal m2({ 4, 1, 3 });
        Matrix m3(ivector_1);
        Matrix m4(3, 3);

        /*
        cout << "m1:" << "\n" << m1;
        cout << "m2:" << "\n" << m2;
        cout << "m3:" << "\n" << m3;
        m4 = m1 + m2;
        cout << "m1 + m2:" << "\n" << m4;
        //m4 = m1 + m3;
        m4 = m1 - m2;
        cout << "m1 - m2:" << "\n" << m4;
        m4 = m1 * m2;
        cout << "m1 * m2:" << "\n" << m4;
        m4 = m3.mul_by_a_num(2);
        cout << "2 * m3:" << "\n" << m4;
        m4 = m1.mul_of_hadamard(m2);
        cout << "mul_of_hadamard m1 and m2:" << "\n" << m4;
        */

        vector < vector <float> > ivector_2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        Matrix m5(ivector_2);
        Matrix m6(ivector_3);
        Matrix m7(ivector_4);

        /*
        cout << "m5:" << "\n" << m5;
        cout << "trace m5: " << m5.trace() << "\n";
        cout << "det m1: " << m1.determinant() << "\n";
        cout << "det m5: " << m5.determinant() << "\n\n";
        cout << "m6:" << "\n" << m6;
        cout << "m7:" << "\n" << m7;
        cout << "scalar m6 and m7: " << m6.scalar(m7) << "\n";
        cout << "euclidean m6: " << m6.euclidean() << "\n";
        cout << "maximum m6: " << m6.maximum() << "\n";
        cout << "frobenius m5: " << m5.frobenius() << "\n";
        */

        Matrix m8(ivector_5);
        cout << "m6:" << "\n" << m6;
        cout << "m7:" << "\n" << m7;
        cout << "angle between m6 and m7: " << angle(m6, m7) << "\n\n";
        cout << "m5:" << "\n" << m5;
        m4 = m5.transpose();
        cout << "transposed m5:" << "\n" << m4;
        cout << "rank m5: " << rank_mat(m5);
    }
    catch (Incorrect_dimensions)
    {
        cout << "Error! Check the dimensions of the matrices, please." << endl;
    }
    catch (...)
    {
        cout << "Some other error." << endl;
    }
}