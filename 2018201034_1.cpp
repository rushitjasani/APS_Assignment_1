/*
 * BIGINT LIBRARY by Rushit M Jasani : 2018201034
 */

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define ll long long
/*
 * Biginteger class.
 */
class BigInteger
{
  private:
    string data;    //stores each digit in string.
    int size;       //size of string.
    int sign;       //stores sign of number

  public:
    /*
     * Empty constructor.
     */
    BigInteger(){};
    /*
     * Takes string in argument, if sign is there then remove signs
     * and set sign bit accordingly. then remove leading 
     * zeros from number and then finds size of string 
     * and store in size.
     */
    BigInteger(string input_data)
    {
        if (input_data[0] == '-')
        {
            sign = 1;
            size = input_data.length() - 1;
            data = input_data.substr(1, size);
            data.erase(0, min(data.find_first_not_of('0'), data.size() - 1));
            if (data.length() == 0)
                data += "0";
            size = data.length();
        }
        else
        {
            input_data.erase(0, min(input_data.find_first_not_of('0'), input_data.size() - 1));
            if (input_data.length() == 0)
                input_data += "0";
            sign = 0;
            size = input_data.length();
            data = input_data;
        }
    }
    /*
     * returns data by concatenation of sign.
     */
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
    /*
     * method to add two BigInteger.
     */
    BigInteger add(BigInteger y)
    {
        return add(*this, y);
    }
    /*
     * overloaded add method.
     */
    BigInteger add(BigInteger x, BigInteger y)
    {
        if (x.sign == y.sign)
        {   
            //if sign is same then add data and handle sign at end.
            //copy data in two temp variables called x_data and y_data.
            int carry_val = 0;
            int place_val;
            string ans;
            string x_data = x.data;
            string y_data = y.data;
            int x_len = x.size;
            int y_len = y.size;
            int t_len;
            //pad zeroes in shorter string.
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
            //Basic Addition operation.
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
            // if sign is diff then do subtraction of both numbers.
            y.sign = 0;
            BigInteger ans = subtract(x, y);
            y.sign = 1;
            return ans;
        }
        else
        {
            // if sign is diff then do subtraction of both numbers.
            x.sign = 0;
            BigInteger ans = subtract(y, x);
            x.sign = 1;
            return ans;
        }
    }
    /*
     * find 10s complement by finding 9s complement and adding 1 to data.
     */
    string tenscomp(string s)
    {
        if (s.length() == 1 && s[0] == '0')
            return s;
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
    /*
     * method to subtract two numbers.
     */
    BigInteger subtract(BigInteger y)
    {
        return subtract(*this, y);
    }
    /*
     * overloaded method to subtract two numbers.
     */
    BigInteger subtract(BigInteger x, BigInteger y)
    {   
        if (y.size == 1 && y.data[0] == '0')
            return x;
        if (x.sign == 0 && y.sign == 0)
        {
            // if both has same sign then we have to subtract one from other.
            int carry_val = 0;
            int place_val;
            string ans = "";
            string x_data = x.data;
            string y_data = y.data;
            int x_len = x.size;
            int y_len = y.size;
            int t_len;
            //making length equal by padding zeros to shorter string
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
            /*
             * addition of both num :: 
             * num1 - num2 = num1 + tenscomp(num2);
             */ 
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
        {   //if sign are diff then we can add two numbers.
            y.sign = 1 - y.sign;
            BigInteger ans = add(x, y);
            y.sign = 1 - y.sign;
            return ans;
        }
        else
        {   
            // if both num are -ve then change sign of both and then subtract.
            x.sign = 0;
            y.sign = 0;
            BigInteger ans = subtract(y, x);
            x.sign = 1;
            y.sign = 1;
            return ans;
        }
    }
    /*
     * multiplication of two numbers by classical method of multiplication.
     */
    BigInteger multiply(BigInteger x)
    {
        BigInteger *mult;
        string x_data;
        string y_data;
        int x_len;
        int y_len;
        //storing bigger number in x_data and smaller in y_data.
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
        //standard multiplication method.
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
                BigInteger part_sum = mult->add(addition_helper);
                *mult = part_sum;
            }
        }
        if (this->sign != x.sign)
        {
            mult->sign = 1;
        }
        return (*mult);
    }
    /*
     * division algo implemented as repeated subtraction.
     */
    BigInteger divide(BigInteger x)
    {
        BigInteger one("1");
        BigInteger ans("0");
        int sign;
        if (this->data[0] == 0 && x.data[0] == 0)
        {
            return BigInteger("0");
        }
        else
        {
            if (this->sign != x.sign)
            {
                sign = 1;
            }
            x.sign = 0;
            this->sign = 0;
            while (1)
            {
                BigInteger tmp = subtract(*this, x);
                this->data = tmp.data;
                this->sign = tmp.sign;
                this->size = tmp.size;
                if (tmp.sign == 1)
                    break;
                tmp = add(ans, one);
                ans.data = tmp.data;
                ans.sign = tmp.sign;
                ans.size = tmp.size;
            }
            if (sign == -1)
            {
                ans.sign = sign;
            }
            return ans;
        }
    }
    /*
     * returns true if two BigInt is totally same.
     */
    bool isEqual(BigInteger x, BigInteger y)
    {
        if (x.data == y.data && x.sign == y.sign && x.size == y.size)
            return true;
        return false;
    }
    /*
     * GCD of two numbers by Euclids algo.
     */
    BigInteger my_gcd(BigInteger x)
    {
        BigInteger zero("0");
        if (isEqual(*this, zero))
            return x;
        else
        {
            BigInteger divisoin, mult, sub, res, a, b;
            a = *this;
            b = x;
            divisoin = b.divide(a);
            mult = divisoin.multiply(a);
            b = x;
            sub = b.subtract(mult);
            return sub.my_gcd(a);
        }
    }
};

int main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        string x, y;
        int m;
        cin >> x >> y >> m;
        BigInteger b1(x);
        BigInteger b2(y);
        BigInteger ans;
        switch (m)
        {
        case 1:
            ans = b1.add(b2);
            ;
            break;
        case 2:
            ans = b1.subtract(b2);
            break;
        case 3:
            ans = b1.multiply(b2);
            break;
        case 4:
            ans = b1.divide(b2);
            break;
        case 5:
            ans = b1.my_gcd(b2);
            break;
        }
        cout << ans.getData() << endl;
    }
    return 0;
}