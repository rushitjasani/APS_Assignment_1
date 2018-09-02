#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define ll long long;

class BigInteger
{
  private:
    string data;
    int size;
    int sign;

  public:
    BigInteger(){};
    BigInteger(string input_data)
    {
        if (input_data[0] == '+')
        {
            sign = 0;
            size = input_data.length() - 1;
            data = input_data.substr(1, size);
            data.erase(0, min(data.find_first_not_of('0'), data.size() - 1));
            if(data.length() == 0) data += "0";
            size = data.length();
        }
        else if (input_data[0] == '-')
        {
            sign = 1;
            size = input_data.length() - 1;
            data = input_data.substr(1, size);
            data.erase(0, min(data.find_first_not_of('0'), data.size() - 1));
            if(data.length() == 0) data += "0";
            size = data.length();
        }
        else
        {
            input_data.erase(0, min(input_data.find_first_not_of('0'), input_data.size() - 1));
            if(input_data.length() == 0) input_data += "0";
            sign = 0;
            size = input_data.length();
            data = input_data;
        }
    }
    string getData()
    {
        if (this->sign == 0)
        {
            return this->data;
        }
        else
        {
            return '-' + this->data;
        }
    }
    BigInteger add(BigInteger y)
    {
        return add(*this, y);
    }
    BigInteger add(BigInteger x, BigInteger y)
    {
        if (x.sign == y.sign)
        {
            int carry_val = 0;
            int place_val;
            string ans;
            string x_data = x.data;
            string y_data = y.data;
            int x_len = x.size;
            int y_len = y.size;
            int t_len;
            if (x_len < y_len)
            {
                t_len = y_len;
                while (x_len != y_len)
                {
                    x_data = "0" + x_data;
                    x_len++;
                }
            }
            else
            {
                t_len = x_len;
                while (x_len != y_len)
                {
                    y_data = "0" + y_data;
                    y_len++;
                }
            }
            for (int i = t_len - 1; i > 0; i--)
            {
                place_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) % 10;
                carry_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) / 10;
                ans = (char)(place_val + '0') + ans;
            }
            place_val = ((x_data[0] - '0') + (y_data[0] - '0') + carry_val);
            ans = to_string(place_val) + ans;
            if (x.sign == 1)
                ans = "-" + ans;
            return BigInteger(ans);
        }
        else if (x.sign == 0 && y.sign == 1)
        {
            y.sign = 0;
            BigInteger ans = subtract(x, y);
            y.sign = 1;
            return ans;
        }
        else
        {
            x.sign = 0;
            BigInteger ans = subtract(y, x);
            x.sign = 1;
            return ans;
        }
    }
    string tenscomp(string s)
    {
        if(s.length() == 1 && s[0] == '0') return s;
        for (unsigned int i = 0; i < s.length(); i++)
        {
            s[i] = '9' - s[i] + '0';
        }
        int carry = 1;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            char c = s[i];
            s[i] = (((c - '0') + carry) % 10) + '0';
            carry = ((c - '0') + carry) / 10;
            if (carry == 0)
                break;
        }
        if (carry != 0)
            s = (char)(carry + '0') + s;
        return s;
    }
    BigInteger subtract(BigInteger y)
    {
        return subtract(*this, y);
    }
    BigInteger subtract(BigInteger x, BigInteger y)
    {
        if(y.size == 1 && y.data[0] == '0') return x;
        if (x.sign == 0 && y.sign == 0)
        {
            int carry_val = 0;
            int place_val;
            string ans = "";
            string x_data = x.data;
            string y_data = y.data;
            int x_len = x.size;
            int y_len = y.size;
            int t_len;
            //making length equal
            if (x_len < y_len)
            {
                t_len = y_len;
                while (x_len != y_len)
                {
                    x_data = "0" + x_data;
                    x_len++;
                }
            }
            else
            {
                t_len = x_len;
                while (x_len != y_len)
                {
                    y_data = "0" + y_data;
                    y_len++;
                }
            }
            // finding 10's complement.
            y_data = tenscomp(y_data);
            //addition of both num.
            for (int i = t_len - 1; i >= 0; i--)
            {

                place_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) % 10;
                carry_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) / 10;
                ans = (char)(place_val + '0') + ans;
            }
            if (carry_val == 0)
            {
                ans = tenscomp(ans);
                ans = "-" + ans;
            }
            return BigInteger(ans);
        }
        else if (x.sign != y.sign)
        {
            y.sign = 1 - y.sign;
            BigInteger ans = add(x, y);
            y.sign = 1 - y.sign;
            return ans;
        }
        else
        {
            x.sign = 0;
            y.sign = 0;
            BigInteger ans = subtract(y, x);
            x.sign = 1;
            y.sign = 1;
            return ans;
        }
    }
    BigInteger multiply(BigInteger x)
    {
        BigInteger *mult;
        string x_data;
        string y_data;
        int x_len;
        int y_len;
        if (this->size > x.size)
        {
            x_data = this->data;
            y_data = x.data;
            x_len = this->size;
            y_len = x.size;
        }
        else
        {
            y_data = this->data;
            x_data = x.data;
            y_len = this->size;
            x_len = x.size;
        }
        string ans = "";
        int append_zero = y_len - 1;
        for (int i = 0; i < y_len; i++)
        {
            int two = y_data[i] - '0';
            string one_digit_mul = "";
            int iter = append_zero;
            while (iter--)
                one_digit_mul += '0';
            append_zero--;
            int carry = 0;
            int sum = 0;
            for (int j = x_len - 1; j >= 0; j--)
            {
                int one = x_data[j] - '0';
                sum = ((one * two) + carry) % 10;
                carry = ((one * two) + carry) / 10;
                one_digit_mul = (char)(sum + '0') + one_digit_mul;
            }
            if (carry)
                one_digit_mul = (char)(carry + '0') + one_digit_mul;
            if (i == 0)
            {
                mult = new BigInteger(one_digit_mul);
            }
            else
            {
                BigInteger addition_helper(one_digit_mul);
                cout << "old_val:: " << mult->data << "oneline : " << one_digit_mul << endl;
                BigInteger part_sum = mult->add(addition_helper);
                cout << "part_sum :: " << part_sum.data << endl;
                *mult = part_sum;
            }
        }
        if (this->sign != x.sign)
        {
            mult->sign = 1;
        }
        return (*mult);
    }
};

int main()
{
    while (1)
    {
        string x, y;
        cin >> x >> y;
        BigInteger b1(x);
        BigInteger b2(y);
        BigInteger c, d, e;
        e = b1.multiply(b2);
        c = b1.add(b2);
        d = b1.subtract(b2);
        cout << c.getData() << endl;
        cout << d.getData() << endl;
        cout << e.getData() << endl;
    }
    return 0;
}