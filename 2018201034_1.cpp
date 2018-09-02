#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

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
            data.erase(0, min(data.find_first_not_of('0'), data.size()-1));
            size = data.length();
        }
        else if (input_data[0] == '-')
        {
            sign = 1;
            size = input_data.length() - 1;
            data = input_data.substr(1, size);
            data.erase(0, min(data.find_first_not_of('0'), data.size()-1));
            size = data.length();
        }
        else
        {
            input_data.erase(0, min(input_data.find_first_not_of('0'), input_data.size()-1));
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
            int carry_val=0;
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
                t_len  = x_len;
                while (x_len != y_len)
                {
                    y_data = "0" + y_data;
                    y_len++;
                }
            }
            //cout << x_data << " # " << y_data << endl ;
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
    string tenscomp(string s){
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
        if (x.sign == 0 && y.sign == 0)
        {
            int carry_val=0;
            int place_val;
            string ans="";
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
            // cout <<"After length same : " <<x_data << " # " << y_data << endl;
            // finding 10's complement.
            y_data = tenscomp(y_data);
            // cout <<"After 10s complement : " <<x_data << " # " << y_data << endl;
            //addition of both num.
            for (int i = t_len-1; i >= 0; i--)
            {   

                place_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) % 10;
                carry_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) / 10;
                ans = (char)(place_val + '0') + ans;
            }
            // cout << "After Addition : " << x_data << " ### " << y_data << " ### " << ans <<  " ## " << carry_val << endl;
            if (carry_val == 0)
            {
                ans = tenscomp(ans);
                ans = "-" + ans;
            }
            // cout << "Final ans : " << ans << endl;
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
    BigInteger multiply(BigInteger x){
        
    }
};

int main()
{
    while(1){
    string x,y;
    cin >> x >> y;
    BigInteger b1(x);
    BigInteger b2(y);
    BigInteger c,d;
    c = b1.add(b2);
    d = b1.subtract(b2);
    cout << c.getData() << " " << d.getData() << endl;
    }
    return 0;
}