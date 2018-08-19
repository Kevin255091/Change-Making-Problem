#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    getline(cin, line);
    vector<int> values;
    stringstream ss(line);
    for(string s; ss >> s; )
    {
        values.push_back(stoi(s));
    }

    int target_value = values.back();
    values.pop_back();

    vector<int> & coin_value = values;
    coin_value.insert(coin_value.begin(), 0);
    //coin_value[1] should be 1
    //the values in coin_value vector should be in ascending order

    int coin_type_num = coin_value.size()-1;

    int **coins = new int * [coin_type_num+1];
    bool **coin_choice = new bool * [coin_type_num+1];
    int *coin_usage = new int [coin_type_num+1];
    for(int i = 0; i <= coin_type_num; i++)
    {
        coins[i] = new int[target_value + 1];
        coin_choice[i] = new bool[target_value + 1];
        coin_usage[i] = 0;
    }

    //To get the value v, coins[n][v] stores the fewest coins consisting of coin type 1 to n,
    //coin_choice[n][v] stands for whether coin type n is choosed, and
    //coin_usage[n] stores the number of coins of type n being used to achieve the fewest coins.

    int impossible_coins = target_value + 1;
    for(int i = 0; i <= target_value; i++)
    {
        coins[0][i] = impossible_coins;
    }

    for(int i = 1; i <= coin_type_num; i++)
    {
        coins[i][0] = 0;
        for(int j = 1; j <= target_value; j++)
        {
            if ( j - coin_value[i] < 0 )
            {
                coins[i][j] = coins[i-1][j];
                coin_choice[i][j] = false;
            }
            else
            {
                int x = coins[i-1][j];
                int y = coins[i][j - coin_value[i]] + 1;
                if(x < y)
                {
                    coins[i][j] = x;
                    coin_choice[i][j] = false;
                }
                else
                {
                    coins[i][j] = y;
                    coin_choice[i][j] = true;
                }
            }
        }
    }

    int v = target_value;
    int n = coin_type_num;
    while(v > 0)
    {
        if(coin_choice[n][v] == true)
        {
            coin_usage[n] ++;
            v -= coin_value[n];
        }
        else
        {
            n--;
        }
    }

    cout << "The fewest coins : " << coins[coin_type_num][target_value] << endl;
    for(int i = coin_type_num; i > 0; i--)
    {
        cout << "coin with value " << coin_value[i] << " : " << coin_usage[i] << endl;
    }

    for(int i = 0; i <= coin_type_num; i++)
    {
        delete [] coins[i];
        delete [] coin_choice[i];
    }
    delete [] coins;
    delete [] coin_choice;
    delete [] coin_usage;

    return 0;
}
