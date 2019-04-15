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
#define mem(a,x) memset(a, x, sizeof(a))
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
const int MAXM=1e6+10;
struct edge{
    int to,next,cap,flow;
}edge[MAXM];
int tol;
int head[MAXN];
void init(){
    tol=2;
    mem(head,-1);
}
/*每次建的是两条边，所以记边数从2开始记录*/
void addedge(int u,int v,int w,int rw=0){
    edge[tol].to=v;edge[tol].cap=w;edge[tol].flow=0;
    edge[tol].next=head[u];
    head[u]=tol++;
    edge[tol].to=u;edge[tol].cap=rw;edge[tol].flow=0;
    edge[tol].next=head[v];
    head[v]=tol++;
}
/*建的是双向边，第一条是主边，容量为w，
第二条是反边，容量初始为0即可*/
int Q[MAXN];//用来模拟队列
int dep[MAXN],cur[MAXN],sta[MAXN];
bool bfs(int s,int t,int n){//s->源点，t->汇点，n->点数
    int front=0,tail=0;
    //mem(dep,-1);//简单的初始化
    memset(dep,-1,sizeof(dep[0])*(n+1));//优化空间的初始化
    dep[s]=0;
    Q[tail++]=s;
    while(front<tail){
        int u=Q[front++];
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(edge[i].cap>edge[i].flow&&dep[v]==-1){
                dep[v]=dep[u]+1;
                if(v==t)
                return true;
                Q[tail++]=v;
            }
        }
    }
    return false;
}
int dinic(int s,int t,int n){
    int ans=0;
    while(bfs(s,t,n)){//可以增广的情况下
        for(int i=0;i<n;i++){
            cur[i]=head[i];
        }
        int u=s,tail=0;
        while(cur[s]!=-1){
            if(u==t){
                int tp=INF;
                for(int i=tail-1;i>=0;i--){
                    tp=min(tp,edge[sta[i]].cap-edge[sta[i]].flow);
                }
                ans+=tp;
                for(int i=tail-1;i>=0;i--){
                    edge[sta[i]].flow+=tp;
                    edge[sta[i]^1].flow-=tp;//反边减，正边加
                    if(edge[sta[i]].cap-edge[sta[i]].flow==0)
                    tail=i;
                }
                u=edge[sta[tail]^1].to;
            }
            else if(cur[u]!=-1&&edge[cur[u]].cap>edge[cur[u]].flow&&dep[u]+1==dep[edge[cur[u]].to]){
                sta[tail++]=cur[u];
                u=edge[cur[u]].to;
            }
            else{
                while(u!=s&&cur[u]==-1)
                u=edge[sta[--tail]^1].to;
                cur[u]=edge[cur[u]].next;
            }
        }
    }
    return ans;
}