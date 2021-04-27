#include <cmath>
#include <string>
#include <iostream>
#include <map>

#define mem(a,b) memset(a,b,sizeof a)
#define ssclr(ss) ss.clear(), ss.str("")
#define INF 0x3f3f3f3f
#define MOD 1000000007

using namespace std;

typedef long long ll;

struct node
{
    int d;
    node* left, * right;
};

//Val to Depth
map<int, int> lvl;
//Val to Node*
map<int, node*> fu;

node* insertBST(node* rt, int d, int l, node* fa)
{
    if (rt == NULL)
    {
        rt = new node;
        rt->left = rt->right = NULL;
        rt->d = d;
        lvl[d] = l;
        if (fa == NULL) fa = rt;
        fu[d] = fa;
        return rt;
    }

    if (rt->d > d) rt->left = insertBST(rt->left, d, l + 1, rt);
    else if (rt->d < d) rt->right = insertBST(rt->right, d, l + 1, rt);
}

int main()
{
    int n, a, q, b;
    string ts;
    cin>>n;
    node* tree = NULL;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        tree = insertBST(tree, a, 1, tree);
    }
    cin>>q;
    while (q--)
    {
        int f = 0, flag = 0;
        cin >> a >> ts;
        if (lvl[a] == 0) flag = 1;
        if (ts[0] == 'i')
        {
            cin >> ts >> ts;
            if (ts[1] == 'o')
            {
                if (!flag && fu[a]->d == a) f = 1;
            }
            else if (ts[0] == 'p')
            {
                cin >> ts >> b;
                if (lvl[b] == 0) flag = 1;
                if (!flag && fu[b]->d == a && a != b) f = 1;
            }
            else if (ts[0] == 'l')
            {
                cin >> ts >> ts >> b;
                if (lvl[b] == 0) flag = 1;
                if (!flag && fu[a]->d != a)
                {
                    node* l = fu[a]->left;
                    if (!flag && l != NULL && l->d == a && fu[a]->d == b) f = 1;
                }
            }
            else if (ts[1] == 'i')
            {
                cin >> ts >> ts >> b;
                if (lvl[b] == 0) flag = 1;
                if (!flag && fu[a]->d != a)
                {
                    node* r = fu[a]->right;
                    if (!flag && r != NULL && r->d == a && fu[a]->d == b) f = 1;
                }
            }
        }
        else
        {
            cin >> b;
            getline(cin, ts);
            if (lvl[b] == 0) flag = 1;
            if (ts[ts.length() - 1] == 's')
            {
                if (!flag && fu[a] == fu[b]) f = 1;
            }
            else
            {
                if (!flag && lvl[a] == lvl[b]) f = 1;
            }
        }

        if (flag == 1) f = 0;
        cout<<(f ? "Yes\n" : "No\n");
    }
    return 0;
}