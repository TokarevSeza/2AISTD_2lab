#include <iostream>
#include "Huffman.h"
using namespace std;

int main()
{
    int sizeInStr = 500;
    char* str = new char[sizeInStr];
    int size;
    size = 0;
    char c;
    do
    {
        cin >> noskipws >> c;
        str[size] = c;
        size++;
    } while ((c != '.') && ((size + 1) < sizeInStr));
    str[size] = '\n';
    double coeff = 1.0 * sizeof(char) * size * 8;
    Huffman ForCode(str);
    int sizeC;
    bool* code = ForCode.Code(size);
    char* decode = ForCode.Decode(sizeC);
    for (size_t i = 0; i < size; i++)
    {
        cout << code[i];
    }
    cout << endl;
    coeff = coeff / (1 * size);
    cout << "Coefficient : " << coeff << endl;
    for (size_t i = 0; i < sizeC; i++)
    {
        cout << decode[i];
    }
}

