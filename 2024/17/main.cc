#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

ll A{61156655}, B{}, C{};
vector<int> op{2, 4, 1, 5, 7, 5, 4, 3, 1, 6, 0, 3, 5, 5, 3, 0};
// vector<int> op{0, 3, 5, 4, 3, 0};
ll combo(int operand)
{
    if (operand == 7)
        cerr << "Wrong operand" << endl;
    else if (operand == 4)
        return A;
    else if (operand == 5)
        return B;
    else if (operand == 6)
        return C;
    return operand;
}
ostringstream program()
{
    ostringstream buffer{};
    size_t point{0};
    while (point < op.size())
    {
        int opcode = op[point];
        int operand = op[point + 1];
        // cout << "Opcode: " << opcode << endl;
        switch (opcode)
        {
        case 0:
            A /= pow(2, combo(operand));
            break;
        case 1:
            B ^= operand;
            break;
        case 2:
            B = combo(operand) % 8;
            break;
        case 3:
            if (A != 0)
            {
                point = operand;
                continue;
            }
            break;
        case 4:
            B ^= C;
            break;
        case 5:
            if (!buffer.str().empty())
            {
                buffer << ",";
            }
            buffer << combo(operand) % 8;
            break;
        case 6:
            B = A / pow(2, combo(operand));
            break;
        case 7:
            C = A / pow(2, combo(operand));
            break;
        }
        point += 2;
    }
    return buffer;
}

ll formula(ll a)
{
    ll b = a % 8;
    b ^= 5;
    ll c = a / pow(2, b);
    b ^= c;
    b ^= 6;
    a = a / pow(2, 3);
    return b % 8;
}
int main()
{
    string op_str{"2,4,1,5,7,5,4,3,1,6,0,3,5,5,3,0"};
    cout << program().str() << endl;

    A = 105734774294938;
    cout << program().str() << endl;
}
