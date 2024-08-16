#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>


using namespace std;

namespace MyLib
{
    int ReadNumber(string Message)
    {
        int Number = 0;

        cout << Message;
        cin >> Number;

        return Number;
    }

    int IsPrimeNumber(int Number)
    {
        if (Number <= 1)
            return 0;

        int M = round(Number / 2);

        for (int i = 2; i <= M; i++)
        {
            if (Number % i == 0)
                return 0;
        }

        return 1;
    }

    int RandomNumber(int From, int To)
    {
        return rand() % (To - From + 1) + From;
    }

    void FillMatrixWithRandomNumbers(int Matrix[3][3], int row, int Cols)
    {

        for (short i = 0; i < row; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                Matrix[i][j] = RandomNumber(1, 100);
            }
        }
    }

    void PrintMatrix(int Matrix[3][3], int row, int column)
    {

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << setw(3) << Matrix[i][j] << "     ";
            }
            cout << "\n";
        }
    }

    int RowSum(int arr[3][3], short RowNumber, short Cols)
    {
        int Sum = 0;
        for (short j = 0; j <= Cols - 1; j++)
        {
            Sum += arr[RowNumber][j];
        }

        return Sum;
    }

    void SumMatixRowsInArry(int arr[3][3], int arrSum[3], int Rows, int Cols)
    {
        for (int i = 0; i < Rows; i++)
        {
            arrSum[i] = RowSum(arr, i, Cols);
        }
    }

    int ColSum(int arr[3][3], short Rows, short ColNumber)
    {
        int Sum = 0;
        for (short j = 0; j < Rows; j++)
        {
            Sum += arr[j][ColNumber];
        }

        return Sum;
    }

    void SumMatixColsInArry(int arr[3][3], int arrSum[3], short Rows, short Cols)
    {
        for (short i = 0; i < Cols; i++)
        {
            arrSum[i] = ColSum(arr, Rows, i);
        }
    }

    void PrintRowsSumArray(int arr[3], short Length)
    {
        cout << "\n\nThe the following are the sum of each row in the matrix:\n";

        for (short i = 0; i < Length; i++)
        {
            cout << " Row " << i + 1 << " Sum = " << arr[i] << endl;
        }
    }

    void PrintColsSumArray(int arr[3], short Length)
    {

        cout << "\n\nThe the following are the sum of each Col in the matrix:\n";

        for (int i = 0; i < Length; i++)
        {
            cout << " Col " << i + 1 << " Sum = " << arr[i] << endl;
        }
    }

    void TransposedMatrixInArray(int arr[3][3], int arrTransposed[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                arrTransposed[i][j] = arr[j][i];
            }
        }
    }

    void MultiplyMatrix(int arr1[3][3], int arr2[3][3], int arrMultiply[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                arrMultiply[i][j] = arr1[i][j] * arr2[i][j];
            }
        }
    }

    void MiddleRowOfMatrixInArray(int arr[3][3], short Rows, int arrMiddleRow[3])
    {
        short MiddleRow = Rows / 2;

        for (short i = 0; i < 3; i++)
        {
            arrMiddleRow[i] = arr[MiddleRow][i];
        }
    }

    void MiddleColOfMatrixInArray(int arr[3][3], short Cols, int arrMiddleCol[3])
    {
        short MiddleCol = Cols / 2;

        for (short i = 0; i < 3; i++)
        {
            arrMiddleCol[i] = arr[i][MiddleCol];
        }
    }

    void PrintMatrixOneDimensional(int arr[3], short limit)
    {
        for (short i = 0; i < limit; i++)
        {
            cout << setw(2);
            printf("%0*d     ", 2, arr[i]);
        }
    }

    int SumMatrix(int arr[3][3], short Rows, short Cols)
    {
        int TheSum = 0;

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                TheSum += arr[i][j];
            }
        }

        return TheSum;
    }

    bool AreEqualMatrices(int arr1[3][3], int arr2[3][3], short Rows, short Cols)
    {
        return (SumMatrix(arr1, Rows, Cols) == SumMatrix(arr2, Rows, Cols));
    }

    bool AreTypicalMatrices(int arr1[3][3], int arr2[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (arr1[i][j] != arr2[i][j])
                    return 0;
            }
        }
        return 1;
    }

    bool IsMatrixIdentity(int Matrix[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (i == j && Matrix[i][j] != 1)
                {
                    return 0;
                }
                else if (i != j && Matrix[i][j] != 0)
                {
                    return 0;
                }
            }
        }
        return 1;
    }

    bool IsScalarMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int FirstNum = Matrix[0][0];

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (i == j && Matrix[i][j] != FirstNum)
                {
                    return 0;
                }
                else if (i != j && Matrix[i][j] != 0)
                {
                    return 0;
                }
            }
        }
        return 1;
    }

    int ReadPositiveNumber(string Message = "Enter Psitive Number")
    {
        int Number = 0;

        cout << Message;
        cin >> Number;

        return Number;
    }

    int CountNumberInMatrix(short Search, int Matrix[3][3], short Rows, short Cols)
    {
        short Counter = 0;

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (Matrix[i][j] == Search)
                    Counter++;
            }
        }

        return Counter;
    }

    bool IsSparceMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        short ManyNumsInMatrix = Rows * Cols;
        short ManyZerosInMatrix = CountNumberInMatrix(0, Matrix, 3, 3);

        return (ManyNumsInMatrix / 2) <= ManyZerosInMatrix;
    }

    bool IsNumberInMatrix(int Number, int Matrix[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (Matrix[i][j] == Number)
                    return 1;
            };
        }
        return 0;
    }

    void PrintIntersectedNumbers(int Matrix1[3][3], int Matrix2[3][3], short Rows, short Cols)
    {
        int Number = 0;

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                Number = Matrix1[i][j];

                if (IsNumberInMatrix(Number, Matrix2, Rows, Cols))
                {
                    cout << setw(3) << Number << "     ";
                }
            }
        }
    }

    int MaxNumberInMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int MaxNumber = Matrix[0][0];

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (MaxNumber < Matrix[i][j])
                    MaxNumber = Matrix[i][j];
            }
        }

        return MaxNumber;
    }

    int MinNumberInMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        int MinNumber = Matrix[0][0];

        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols; j++)
            {
                if (MinNumber > Matrix[i][j])
                    MinNumber = Matrix[i][j];
            }
        }

        return MinNumber;
    }

    bool IsPalindromeMatrix(int Matrix[3][3], short Rows, short Cols)
    {
        for (short i = 0; i < Rows; i++)
        {
            for (short j = 0; j < Cols / 2; j++)
            {
                if (Matrix[i][j] != Matrix[i][(Cols - j) - 1])
                    return 0;
            }
        }

        return 1;
    }

    void PrintFibonacciUsingLoop(short Limit)
    {
        int FebNumber = 0;
        int Prev1 = 0, Prev2 = 1;
        cout << "1    ";

        for (short i = 2; i <= Limit; ++i)
        {
            FebNumber = Prev1 + Prev2;
            cout << FebNumber << "     ";
            Prev1 = Prev2;
            Prev2 = FebNumber;
        }
    }

    void FibonacciByRecursion(int Number, int Prev1, int Prev2)
    {
        int FebNumber = 0;


        if (Number > 0)
        {
            FebNumber = Prev1 + Prev2;
            cout << FebNumber << "\t";
            Prev1 = Prev2;
            Prev2 = FebNumber;
            FibonacciByRecursion(Number - 1, Prev1, Prev2);
        }
    }

    string ReadString(string Message = "")
    {
        string Tixt = "";

        cout << Message;
        // cin.ignore(numeric_limits<streamsize>::min(), '\n');
        getline(cin >> ws, Tixt);

        return Tixt;
    }

    void PrintFirstLetterOfEachWord(string S1)
    {
        bool isFirstletter = true;

        cout << "\nFirst letters of this string: \n";


        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstletter)
            {
                cout << S1[i] << endl;
            }

            isFirstletter = (S1[i] == ' ' ? true : false);
        }
    }

    string UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    string LowerFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLatter = true;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && IsFirstLatter)
            {
                S1[i] = tolower(S1[i]);
            }

            IsFirstLatter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    string AllLettersToUpper(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }

        return S1;
    }

    string AllLettersToLower(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }

        return S1;
    }

    char InvertCharacter(char Letter)
    {
        return isupper(Letter) ? tolower(Letter) : toupper(Letter);
    }

    string InvertAllLetters(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertCharacter(S1[i]);
        }
        return S1;
    }

    short CountCapitalLetter(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short CountSmallLetter(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short CountLetter(string S1, char Letter, bool MatchCase = true)
    {

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }
        }

        return Counter;
    }

    char ReadChar(string Message = "")
    {
        char CH1 = ' ';

        cout << Message;
        cin >> CH1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return CH1;
    }

    bool IsVowel(char CH1)
    {
        CH1 = tolower(CH1);

        return ((CH1 == 'a') || (CH1 == 'e') || (CH1 == 'i') || (CH1 == 'o') || (CH1 == 'u'));

        return false;
    }

    short CountVowels(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }

        return Counter;
    }

    void PrintVowlsInString(string S1)
    {
        cout << "\nVowels in string are: ";

        for (short i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                cout << S1[i] << "   ";
        }
    }

    short NumberOfWords(string S1)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] == ' ')
                Counter++;
        }

        return Counter + 1;
    }

    /*vector<string> SplitString(string S1, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord;


        while ((pos = S1.find(Delim)) != string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != "")
            {
                vString.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length());
        }

        if (S1 != "")
            vString.push_back(S1);

        return vString;
    }*/

    string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    string TrimRight(string S1)
    {
        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    string JoinString(vector<string> vString, string Delim)
    {
        string S1 = "";

        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    string JoinString(string arrString[], short Length, string Delim)
    {
        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 += arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    //string PrintReverseWordsInString(string S1)
    //{
    //    vector<string> vString;
    //    string S2 = "";

    //    vString = SplitString(S1, " ");

    //    vector<string>::iterator iter = vString.end();

    //    while (iter != vString.begin())
    //    {
    //        --iter;

    //        S2 += *iter + " ";
    //    }

    //    return S2.substr(0, S2.length() - 1);
    //}

    string ReplaceWordInString(string S1, string StringToReplace, string sReplace)
    {
        short Pos = S1.find(StringToReplace);

        while (Pos != std::string::npos)
        {
            S1 = S1.replace(Pos, StringToReplace.length(), sReplace);
            Pos = S1.find(StringToReplace);
        }

        return S1;
    }

    string FirstLetterToUpper(string Word)
    {
        Word[0] = toupper(Word[0]);

        return Word;
    }

    /*string ReplaceWordInString(string S1, string stringTOReplace, string sReplace, bool MatchCase)
    {
        vector<string> vString;

        vString = SplitString(S1, " ");

        if (MatchCase)
        {
            for (string& i : vString)
            {
                if (i == stringTOReplace)
                {
                    i = sReplace;
                }
            }
        }

        else
        {
            for (string& i : vString)
            {
                if ((FirstLetterToUpper(i)) == FirstLetterToUpper(stringTOReplace))
                {
                    i = sReplace;
                }
            }
        }

        return JoinString(vString, " ");
    }*/

    string RemovPunctuations(string S1)
    {
        string S2 = "";

        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
                S2 += S1[i];
        }

        return S2;
    }
}
