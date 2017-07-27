/*
                           _________________
                      ____/:::::::::::::::::\_____
                   __/::::::::::::::::::::::::::::\___
                 _/:::::::::::::::::::::::::::::::::::\__
               _/::::::::::::::::::::::::::::::::::::::::\_
              /::::::::::::::::::::::::::::::::::::::::::::\
             |::::::::::::::::::::::::::::::::::::::::::::::\
            /::::::::::::::::::::::::::::::::::::::::::::::::\
           |:::/.:::::::;:::::::::::::::::::::::::::::::::::::|
          /:::/.:::::::/..:::::::::::::::::::::::::::::::::::::\
         |:::|.::::::;/.::::::::::::::::::::::::::::::::::::::::|
         |::/.::::::/..:::::::;;'.::::::::::::::::::::::::::::::|
         |:|.::::/./.::::::;;/..:::::::::::::::::::::::::::::::::|
         `:|.:::|.|.:::::;/..;;;;;;-'.:;;;-':::::::::::::::::::::|
          \|.:::|.|.:::;/.;;/  -..::'''...:::::::::::::::::::::::|
           \;;::|.|.::/.;/--__      |::::::::::::::::::::::::::::|
              \;;\\::/|/ =-__ --_  /::::::::::::::::::::::::::::::
                  \\/    /|  -.   |.::::::::::::::::::::::::::::::
                 _.'    /|'   /=  ||::::::::::::::::::::::::::::::
             _.-'      //'        ||::::::::::::::::::::::::::::::
            (          -          `|::::::::::::::::::::::::::::::
             \                      \:::::::::::::::::::::::::::::
              |  (c)Kolansburg      \::::::::::::::::::::::::::::
             /                      __/:::::::::::::::::::::::::::
             \                   __/::;::;;:::::::::::::::::::::::
             (`                 /;;;;/::|  \::::::::::::::::::::::
             |                 |'_,::::/ \ |::::::::::::::::::::::
            .'                _/::::::/  / /:::::::::::::::. .::::
            |                /.::;;:-'_)/_/::::::::::::::::...::::
 ----.__    |               |.::|   \___/::::::::::::::::::...::::
 :::::::`----\_____          \:::\.-'::::::::::::::::::::::...::::
 ;;;;;:::::::::::::`------     \:::::::::::::::::::::::::::...::::
      `-------:::::::\         /:::::::::::::::::::::::::::...::::
 ___.--------'::::::::\       |::::::::::::::::::::::::::::...::::
 :::::;;;:--:::::::::::|      /::::::::::::::::::::::::::::...::::
 ----'  _,-:.:::::::::::\    |.::::::::::::::::::::::::::::...::::
     __/.::::::::::::::::|   |.::::::::::::::::::::::::::::...::::
  __/.:::;;::::::::;/.:::|   |.::::::::::::::::::::::::::::. .::::
 /.::::;/ /.:::::;/ |.::::|   \_.:::::::::::::::::::::::::::::::::
 :::::/  /.:::::/  /.:::::|     \__.::::::::::::::::::::::::::::::
 ::::|  |.:::::/  /.:::::.|        \,::::::::::::::::::::::::::::
 ::::|  |.::::|   |.:::::/|       __/::::::::::::::::::::::::::::
 \.:::\  \.:::|   |.::::||| __.--::::::::::::::::::::::::::::::::
  \.:::\_ \.:::\   \.:::'/.::::::::::::::::::::::::::::::::::::::
   \.::::\ \.:::\   \.::::::::::::::::::::::::::::::::::::::::::
*/
 
#define _CRT_SECURE_NO_WARNINGS
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <stack>
#include <random>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
using namespace std;
 
#define X first 
#define Y second 
 
const long long M = 1000000007;
long long m, in, su;
vector< vector<long long> > pus;
 
vector<long long> um(vector<long long> Dp2, vector<vector<long long> > Dp)
{
    vector<long long> rezz;
    long long rez;
    for (long long i = 0; i < in; i++)
    {
        rez = 0;
        for (long long j = 0; j < in; j++)
        {
            rez += Dp2[j] * Dp[j][i];
            if (rez >= M)
                rez %= M;
        }
        rezz.push_back(rez);
    }
    return rezz;
}
 
vector<vector<long long> > um(vector<vector<long long> > Dp, vector<vector<long long> > Dp2) {
    vector<vector<long long> > anss;
    anss.resize(in);
    for (long long i = 0; i < in; i++)
    {
        anss[i].resize(in, 0);
        for (long long j = 0; j < in; j++)
        {
            for (long long z = 0; z < in; z++)
            {
                anss[i][j] += Dp[i][z] * Dp2[z][j];
                if (anss[i][j] >= M)
                    anss[i][j] %= M;
            }
        }
    }
    return anss;
}
 
vector<vector<long long> > vos(vector<vector<long long> > Dp, long long B)
{
    if (B == 0)
        return pus;
    if (B == 1)
        return Dp;
    if (B % 2 == 0)
    {
        return vos(um(Dp, Dp), B / 2);
    }
    else
    {
        return um(Dp, vos(um(Dp, Dp), B / 2));
    }
}
int main()
{
#if _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    //freopen("mpow.in", "r", stdin);
    //freopen("mpow.out", "w", stdout);
#endif
    int t;
    cin >> t;
    for (int test = 0; test < t; test++)
    {
        vector< vector<long long> > tech, tecn;
        vector<long long> nach, answer;
        cin >> m >> in;
        m--;
        in++;
        tech.resize(in);
        tecn.resize(in);
        pus.clear();
        pus.resize(in);
        nach.resize(in);
        for (long long i = 0; i < in - 1; i++)
        {
            nach[i] = 1;
        }
        nach[in - 1] = in - 1;
        for (long long i = 0; i < in; i++)
        {
            tech[i].resize(in, 0);
            tecn[i].resize(in, 0);
            pus[i].resize(in, 0);
            pus[i][i] = 1;
        }
        for (int i = 1; i < in - 2; i++)
        {
            tech[i - 1][i] = 1;
            tech[i][i] = 1;
            tech[i + 1][i] = 1;
        }
        tech[0][0] = 1;
        if (in > 2)
        {
            tech[1][0] = 1;
            tech[in - 3][in - 2] = 1;
            tech[in - 2][in - 2] = 1;
        }
        for (int i = 0; i < in - 1; i++)
        {
            for (int j = 0; j < in - 1; j++)
            {
                tech[i][in - 1] += tech[i][j];
            }
        }
        tech[in - 1][in - 1] = 1;
 
 
        for (int i = 1; i < in - 2; i++)
        {
            tecn[i - 1][i] = 1;
            tecn[i + 1][i] = 1;
        }
        if (in > 2)
        {
            tecn[1][0] = 1;
            tecn[in - 3][in - 2] = 1;
        }
        for (int i = 0; i < in - 1; i++)
        {
            for (int j = 0; j < in - 1; j++)
            {
                tecn[i][in - 1] += tecn[i][j];
            }
        }
        tech[in - 1][in - 1] = 1;
 
        answer = um(um(nach, vos(tech, m / 2)), vos(tecn, m / 2 + m % 2));
        cout << answer[in - 1] << endl;
    }
    return 0;
}
