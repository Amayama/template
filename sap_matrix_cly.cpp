#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <cassert>
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for (int i = (a); i > (b); --i)
#define memset(a,x) memset(a, x, sizeof(a))
#define ZERO(x) memset(x,0,sizeof(x))
#define pii pair<int,int>
#define ll long long
#define scan(a) scanf("%d",&a)
#define scan2(a,b) scanf("%d%d",&a,&b)
#define scan3(a,b,c) scanf("%d%d%d",&a,&b,&c)
using namespace std;
int gcd(int a, int b)
{
    return a % b == 0 ? b : gcd(b, a % b);
}
const int MAXN = 1e3 + 10;
const int INF = 0x3f3f3f3f;
int maze[MAXN][MAXN];
int gap[MAXN],dis[MAXN],pre[MAXN],cur[MAXN];
/*maze是图，gap用来常数优化，pre记录当前点的前驱，
dis记录点之间的距离，cur记录当前点的情况*/
/*节点编号从0开始*/
int sap_simple(int start,int end,int nodenum){//参数是源点、汇点、点数
    memset(cur,0);
    memset(dis,0);
    memset(gap,0);
    int u=pre[start]=start;
    int ans=0,aug=-1;
    gap[0]=nodenum;
    while(dis[start]<nodenum){
        loop:
        for(int v=cur[u];v<nodenum;v++){
            if(maze[u][v]&&dis[u]==dis[v]+1){
                if(aug==-1||aug>maze[u][v]){
                    aug=maze[u][v];
                    pre[v]=u;
                    if(v==end){
                        ans+=aug;
                        for(u=pre[v];v!=start;v=u,u=pre[v]){
                            maze[u][v]-=aug;
                            maze[u][v]+=aug;
                        }
                        aug=-1;
                    }
                }
                goto loop;
            }
            int mindis=nodenum-1;
            for(int v=0;v<nodenum;v++){
                if(maze[u][v]&&mindis>dis[v]){
                    cur[u]=v;
                    mindis=dis[v];
                }
            }
            if(--gap[dis[u]]==0)
            break;
            gap[dis[u]=mindis+1]++;
            u=pre[u];
        }
    }
    return ans;
}