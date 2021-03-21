#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include <algorithm>
using namespace std;

int str2int(string& input_string)  // from  string to int
{
    int result = 0;
    int ten_dd = 1;
    int sign_flag = 1;
    int end_flag = -1;
    int length = input_string.size();
    if (input_string[0] == '-')
    {
        sign_flag = -1;
        end_flag = 0;
    }
    if (input_string[0] == '+')
    {
        sign_flag =1;
        end_flag = 0;
    }
    for (int search_flag =length- 1; search_flag !=end_flag; search_flag--)
    {
        result = result + ten_dd * (input_string[search_flag] - 48);
        ten_dd *= 10;
    }
    return result * sign_flag;
}
vector<string> split_string(string& input_string) //split the string to easy to calculate
{
    vector<string> splited_string;
    int length = input_string.size();
    int last_flag = 0;
    for (int i = 0; i != length; i++)
    {
        if((input_string[i]<'0')||(input_string[i]>'9'))
        {
                if(i-last_flag)
                    splited_string.push_back(input_string.substr(last_flag, i - last_flag));
                if (input_string[i] == '*' || input_string[i] == '/')
                {
                    string s(1, input_string[i]);
                    splited_string.push_back(s);
                    last_flag = i + 1;
                }
                else
                {
                    last_flag = i;
                }
        }
    }
    splited_string.push_back(input_string.substr(last_flag, length - last_flag));
    return splited_string;
}
int calculator_junior(vector<string>input_string_vector)  //do the simple calculation without brackets
{
    stack<int> result_stack;
    int length = input_string_vector.size();
    int temp_result;
    for (int i = 0; i != length;)
    {
        switch (input_string_vector[i][0])
        {
            case '*':
            {
                temp_result = result_stack.top()*str2int(input_string_vector[++i]);
                i++;
                result_stack.pop();
                result_stack.push(temp_result);
                break;
            }
            case '/':
            {
                temp_result = result_stack.top() / str2int(input_string_vector[++i]);
                i++;
                result_stack.pop();
                result_stack.push(temp_result);
                break;
            }
            default:
            {
                result_stack.push(str2int(input_string_vector[i]));
                i++;
            }
            
        }
        
    }
    temp_result = 0;
    while (!result_stack.empty())
    {
        temp_result += result_stack.top();
        result_stack.pop();
    }
    return temp_result;

    
}
string int2str(int input_int)   //from int to string
{
    string result_string;
    int sign_flag = 1;
    if (input_int < 0)
    {
        input_int = -input_int;
        sign_flag = -1;
    }
    while (input_int)
    {
        result_string.push_back(char(48 + input_int % 10));
        input_int = input_int / 10;

    }
    if (sign_flag < 0)
        result_string.push_back('-');
    reverse(result_string.begin(), result_string.end());
    return result_string;
}
int calculator_senior(string input_string,int start,int end) //do calculation with brackets
{
    int temp_start, temp_end;
    string result_string;
    int i = start;
    int k;
    int last_find = start;
    for (; i != end; i++)
    {
        
        if (input_string[i] == '(')
        {
            if(last_find!=i)
                result_string += input_string.substr(last_find, i - last_find);
            k = 0;
            temp_start = ++i;
            while ((input_string[i] != ')') ||(k))
            {
                if (input_string[i] == '(')
                    k++;
                if (input_string[i] == ')')
                    k--;
                i++;
            }
            result_string += int2str(calculator_senior(input_string,temp_start,i));
            last_find = i + 1;
        }

    }
    if (last_find!= end)
        result_string += input_string.substr(last_find,end-last_find);
    return  calculator_junior(split_string(result_string));
}
int main()
{
    string input_string = "(3*(4+5)+9*9+(3-4)*256+2)/2-188"; //legal input math string 
   // cout << calculator_junior(split_string(input_string));
  cout<<calculator_senior(input_string,0,input_string.size());
    return 0;
}
