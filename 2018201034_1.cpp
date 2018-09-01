#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class BigInteger
{
  private:
    string data;
    int size;

  public:
    BigInteger(){};
    BigInteger(string input_data)
    {
        data = input_data;
        size = data.length();
    }
    string getData()
    {
        return data;
    }
    BigInteger add(BigInteger y)
    {
        int carry_val;
        int place_val;
        string ans;
        string x_data = data;
        string y_data = y.data;
        int x_len = size;
        int y_len = y.size;
        if (x_len < y_len)
        {
            while (x_len != y_len)
            {
                x_data = "0" + x_data;
                x_len++;
            }
        }
        else
        {
            while (x_len != y_len)
            {
                y_data = "0" + y_data;
                y_len++;
            }
        }
        for (int i = x_len - 1; i > 0; i--)
        {
            place_val = ((x_data[i] - '0') + (y_data[i] - '0') + carry_val) % 10;
            carry_val = ((x_data[i] - '0') + (y_data[i] - '0')) / 10;
            //cout << "p: " << place_val <<" C: " << carry_val << endl;
            ans = (char)(place_val + '0') + ans;
        }
        place_val = ((x_data[0] - '0') + (y_data[0] - '0') + carry_val);
        ans = to_string(place_val) + ans;
        //cout << x_data << endl;
        //cout << y_data << endl;
        return BigInteger(ans);
    }
    
};

int main()
{
    string x = "23865929478155176587541547874166476";
    string y = "98765432198765432198765432";
    BigInteger b1(x);
    BigInteger b2(y);
    BigInteger c;
    c = b1.add(b2);
    cout << c.getData() << endl;
    return 0;
}