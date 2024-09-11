#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace ::std;

// the following table was provided by ChatGPT (OpenAI)

const int sBox[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

// the following table was provided by ChatGPT (OpenAI)
const int invSBox[16][16] = {
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}};

const int mixCol[4][4] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}};

const int invMixCol[4][4] = {
    {14, 11, 13, 9},
    {9, 14, 11, 13},
    {13, 9, 14, 11},
    {11, 13, 9, 14}};

class AES
{
private:
    // const int numRounds = 10;
    bool isEnc = false;

    string input = "";

    int keyArray[11][4][4] = {0}, DecKeyArray[11][4][4] = {0};
    int addRounds[11][4][4] = {0}; // for all the add rounds outputs to be stored
    int inpArray[4][4] = {0};
    int outArray[4][4] = {0};
    int sBoxArray[11][4][4] = {0};
    int shiftArray[11][4][4] = {0};
    int mixColArray[11][4][4] = {0};

    // Pre-derived keys for AES Encryption
    vector<string> roundKeys{
        /*Round  0*/ "000102030405060708090a0b0c0d0e0f",
        /*Round  1*/ "d6aa74fdd2af72fadaa678f1d6ab76fe",
        /*Round  2*/ "b692cf0b643dbdf1be9bc5006830b3fe",
        /*Round  3*/ "b6ff744ed2c2c9bf6c590cbf0469bf41",
        /*Round  4*/ "47f7f7bc95353e03f96c32bcfd058dfd",
        /*Round  5*/ "3caaa3e8a99f9deb50f3af57adf622aa",
        /*Round  6*/ "5e390f7df7a69296a7553dc10aa31f6b",
        /*Round  7*/ "14f9701ae35fe28c440adf4d4ea9c026",
        /*Round  8*/ "47438735a41c65b9e016baf4aebf7ad2",
        /*Round  9*/ "549932d1f08557681093ed9cbe2c974e",
        /*Round 10*/ "13111d7fe3944a17f307a78b4d2b30c5"};

    void init()
    {
        // Converting keys to matrix format
        for (int k = 0; k < 11; k++)
        {
            for (int i = 0; i < 16; i++)
            {
                keyArray[k][i % 4][i / 4] = stoi(roundKeys[k].substr(2 * i, 2), nullptr, 16);
            }
        }

        for (int k = 0; k < 11; k++)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    DecKeyArray[10 - k][i][j] = keyArray[k][i][j];
                }
            }
        }

        inpToMatrix(input);
        initArray();
    }

    void inpToMatrix(string input)
    {
        for (int i = 0; i < 16; i++)
        {
            inpArray[i % 4][i / 4] = stoi(input.substr(2 * i, 2), nullptr, 16);
        }
    }

    void initArray()
    {
        for (int k = 0; k < 11; k++)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    shiftArray[k][i][j] = 0;
                    mixColArray[k][i][j] = 0;
                    addRounds[k][i][j] = 0;
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    // supporting functions
    void sBoxSubstitution(int roundNo, int inputArr[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            if (isEnc)
            {
                for (int j = 0; j < 4; j++)
                {
                    int temp = inputArr[i][j];
                    sBoxArray[roundNo][i][j] = sBox[((temp >> 4) & 0x0F)][(temp & 0x0F)];
                }
            }
            else
            {
                for (int j = 0; j < 4; j++)
                {
                    int temp = inputArr[i][j];
                    sBoxArray[roundNo][i][j] = invSBox[((temp >> 4) & 0x0F)][(temp & 0x0F)];
                }
            }
        }
    }

    string toHex(int array[4][4])
    {
        stringstream hexStream;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                hexStream << hex << setw(2) << setfill('0') << (array[j][i] & 0xFF);
            }
        }

        return hexStream.str();
    }

    void shiftRows(int roundNo, int array[4][4])
    {
        int temp[4];
        // Row i, shift by i
        if (isEnc)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    temp[j] = array[i][(j + i) % 4];
                }

                for (int j = 0; j < 4; j++)
                {
                    shiftArray[roundNo][i][j] = temp[j];
                }
            }
        }
        else
        {
            // Dec ShiftRows Logic
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    // Chat gpt helped me clarify this logic
                    temp[j] = array[i][(j - i + 4) % 4];
                }

                for (int j = 0; j < 4; j++)
                {
                    shiftArray[roundNo][i][j] = temp[j];
                }
            }
        }
    }

    void mixColumns(int roundNo, int array[4][4])
    {
        int temp[4];
        if (isEnc)
        {
            for (int col = 0; col < 4; col++)
            {
                for (int i = 0; i < 4; i++)
                {
                    temp[i] = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        temp[i] ^= multiply(array[j][col], mixCol[i][j]);
                    }
                }

                for (int i = 0; i < 4; i++)
                {
                    mixColArray[roundNo][i][col] = temp[i];
                }
            }
        }
        else
        {
            for (int col = 0; col < 4; col++)
            {
                for (int i = 0; i < 4; i++)
                {
                    temp[i] = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        temp[i] ^= multiply(array[j][col], invMixCol[i][j]);
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    mixColArray[roundNo][i][col] = temp[i];
                }
            }
        }
    }

    int multiply(int a, int b)
    {
        int temp = 0;
        for (int i = 0; i < 8; i++)
        {
            if (b & 1)
                temp ^= a;
            bool highBit = (a & 0x80);
            a <<= 1;
            if (highBit)
                a ^= 0x1b;
            b >>= 1;
        }
        return temp;
    }

    void addRoundKey(int roundNo, int array[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (isEnc)
                {
                    addRounds[roundNo][i][j] = keyArray[roundNo][i][j] ^ array[i][j];
                }
                else
                {
                    addRounds[roundNo][i][j] = DecKeyArray[roundNo][i][j] ^ array[i][j];
                }
            }
        }
    };

    // Encryption and Decryption modules
    void encryption()
    {
        isEnc = true;
        // Initial AddRoundKey function
        addRoundKey(0, inpArray);

        for (int i = 1; i < 11; i++)
        {

            sBoxSubstitution(i, addRounds[i - 1]);
            shiftRows(i, sBoxArray[i]);
            if (i < 10)
            {
                mixColumns(i, shiftArray[i]);
            }
            if (i < 10)
            {
                addRoundKey(i, mixColArray[i]);
            }
            else
            {
                addRoundKey(i, shiftArray[i]);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                outArray[i][j] = addRounds[10][i][j];
            }
        }
    }

    void decryption()
    {
        isEnc = false;
        initArray();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                inpArray[i][j] = outArray[i][j];
                outArray[i][j] = 0;
            }
        }

        // dec logic
        addRoundKey(0, inpArray);
        shiftRows(0, addRounds[0]);
        sBoxSubstitution(0, shiftArray[0]);

        for (int i = 1; i < 10; i++)
        {
            addRoundKey(i, sBoxArray[i - 1]);
            mixColumns(i, addRounds[i]);
            shiftRows(i, mixColArray[i]);
            sBoxSubstitution(i, shiftArray[i]);
        }
        addRoundKey(10, sBoxArray[9]);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                outArray[i][j] = addRounds[10][i][j];
            }
        }
    }

public:
    AES(string input)
    { // Defaults to encryption
        isEnc = true;
        this->input = input;
        init();
    }

    AES(string input, bool isEnc)
    { // Defaults to encryption
        this->isEnc = isEnc;
        this->input = input;
        init();
    }

    void run()
    {
        if (isEnc)
        {
            encryption();
        }
        else
        {
            decryption();
        }
    }

    void run(bool isEnc)
    {
        this->isEnc = isEnc;

        if (isEnc)
        {
            encryption();
        }
        else
        {
            decryption();
        }
    }

    // Print Statements to help with debugging and traces
    void showKeys()
    {
        for (int k = 0; k < 11; k++)
        {
            cout << "Key [" << k << "]:    " << toHex(keyArray[k]) << endl;
        }
    }

    void showInput()
    {
        cout << "Input:    " << toHex(inpArray) << endl;
    }

    void printArray(string text, int array[4][4])
    {
        cout << text << toHex(array) << endl;
    }

    void printMatrix(string text, int array[4][4])
    {
        cout << text;
        for (int i = 0; i < 4; i++)
        {
            cout << endl
                 << "       ";
            for (int j = 0; j < 4; j++)
            {
                cout << hex << setw(2) << setfill('0') << array[i][j] << "  ";
            }
        }
    }

    void showInitialTransformation()
    {
        cout << "Initial Transformation:    " << toHex(addRounds[0]) << endl;
    }

    void printAns()
    {
        cout << "\nQuestion 1:   What is the value you obtain? This is the value (round[ 1].start) you start your first round of AES. \n Ans.  ";
        printArray("", addRounds[0]);

        cout << "\nQuestion 2:   What is the value (round[1].s_box) you obtain?  \n Ans.  ";
        printArray("", sBoxArray[1]);

        cout << "\nQuestion 3:  What is the matrix you obtain?  \n Ans.  ";
        printMatrix("", sBoxArray[1]);

        cout << "\nQuestion 4:  What is the value (round[ 1].s row) you obtain?  \n Ans.  ";
        printArray("", shiftArray[1]);

        cout << "\nQuestion 5:  What is the value (round[ 1].m_col) you obtain?  \n Ans.  ";
        printArray("", mixColArray[1]);

        cout << "\nQuestion 6:  What is the value  (round[ 2].start) you obtain?  \n Ans.  ";
        printArray("", addRounds[1]);

        cout << "\nQuestion 7:  What is the value (round[10].start) you obtain?  \n Ans.  ";
        printArray("", addRounds[9]);

        cout << "\nQuestion 8:  What is the output ciphertext you obtain?  \n Ans.  ";
        // printArray("", addRounds[10]);
        printArray("", outArray);

        cout << "\nQuestion 9: Report how much time you spent on this assignment in hours.  \n Ans.  About 6-7 Hours";
    }

    void printTrace()
    {
        cout << ((isEnc) ? "\n\nEncryption Trace" : "\n\nDecryption Trace") << endl;
        printArray("\n\nInput:", inpArray);
        for (int i = 0; i < 11; i++)
        {
            cout << "\nRound " << dec << i << "\n====================================================== " << endl;
            printArray("subBytes:       ", sBoxArray[i]);
            printArray("Shift Rows:     ", shiftArray[i]);
            if (i < 10)
                printArray("Mix Columns:    ", mixColArray[i]);
            printArray("Add Round:      ", addRounds[i]);
        }

        printArray("\n\nOuput:", outArray);
    }

    void printOutput()
    {
        cout << "Output:        " << toHex(outArray) << endl;
    }
};

int main()
{
    string input = "00112233445566778899aabbccddeeff";

    AES test = AES(input, true);
    test.run();
    // test.printOutput();
    // test.printAns();
    test.printTrace();
    // For Decryption - with the saved output, taken as input
    test.run(false);
    // test.printOutput();
    test.printTrace();

    return 0;
}
