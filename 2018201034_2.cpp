#include <bits/stdc++.h>
using namespace std;
#define ll long long

typedef struct AVLnode
{
    ll data;
    AVLnode *left;
    AVLnode *right;
    ll height;
    ll total_node;
} node;

node *root = NULL;

node *create_node(ll data)
{
    node *n = (node *)malloc(sizeof(node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    n->total_node = 1;
    return n;
}

ll getHeight(node *n)
{
    if (n == NULL)
        return 0;
    else
        return n->height;
}
ll computeTotalHeight(node *n)
{
    return max(getHeight(n->left), getHeight(n->right)) + 1;
}
ll getTotalnode(node *n)
{
    if (n == NULL)
        return 0;
    else
        return n->total_node;
}
ll computeTotalNode(node *n)
{
    return getTotalnode(n->left) + getTotalnode(n->right) + 1;
}
ll computeBalFact(node *n)
{
    ll l_h = getHeight(n->left);
    ll r_h = getHeight(n->right);
    return (l_h - r_h);
}

node *Lrotate(node *n)
{
    node *store_rc = n->right;
    node *store_lcor = store_rc->left;
    store_rc->left = n;
    n->right = store_lcor;
    n->height = computeTotalHeight(n);
    n->total_node = computeTotalNode(n);
    store_rc->height = computeTotalHeight(store_rc);
    store_rc->total_node = computeTotalNode(store_rc);
    return store_rc;
}

node *Rrotate(node *n)
{
    node *store_lc = n->left;
    node *store_rcol = store_lc->right;
    store_lc->right = n;
    n->left = store_rcol;
    n->height = computeTotalHeight(n);
    n->total_node = computeTotalNode(n);
    store_lc->height = computeTotalHeight(store_lc);
    store_lc->total_node = computeTotalNode(store_lc);
    return store_lc;
}

node *do_balancing(node *n, ll balanceFact)
{
    if (balanceFact == -2)
    {
        ll balanceFactc = computeBalFact(n->right);
        if (balanceFactc == -1)
            return Lrotate(n); //LL
        else if (balanceFactc == 1)
        { //RL
            n->right = Rrotate(n->right);
            return Lrotate(n);
        }
    }
    else if (balanceFact == 2)
    {
        ll balanceFactc = computeBalFact(n->left);
        if (balanceFactc == -1)
        { //LR
            n->left = Lrotate(n->left);
            return Rrotate(n);
        }
        else if (balanceFactc == 1)
            return Rrotate(n); //RR
    }
    return n;
}

node *insert(node *r, ll d)
{
    node *newroot = NULL;
    if (r == NULL)
        return create_node(d);
    if (d == r->data)
        return r;
    if (d > r->data)
        r->right = insert(r->right, d);
    else
        r->left = insert(r->left, d);

    r->height = computeTotalHeight(r);
    r->total_node = computeTotalNode(r);

    ll balanceFact = computeBalFact(r);

    if (balanceFact > 1 || balanceFact < -1)
    {
        newroot = do_balancing(r, balanceFact);
        r = newroot;
    }
    return r;
}

node *deleteNode(node *r, ll d)
{
    node *newroot;
    if (r == NULL)
        return r;
    if (d > r->data)
        r->right = deleteNode(r->right, d);
    else if (d < r->data)
        r->left = deleteNode(r->left, d);
    else if (d == r->data)
    {
        if (r->left == NULL && r->right == NULL)
        {
            node *tmp = r;
            r = NULL;
            free(tmp);
        }
        else if (r->left == NULL || r->right == NULL)
        {
            node *child;
            if (r->left != NULL)
                child = r->left;
            else
                child = r->right;

            r->data = child->data;
            r->left = child->left;
            r->right = child->right;
            r->height = child->height;
            r->total_node = child->total_node;

            free(child);
        }
        else
        {
            node *ino_suc = r->right;
            while (ino_suc->left != NULL)
                ino_suc = ino_suc->left;
            r->data = ino_suc->data;
            r->right = deleteNode(r->right, ino_suc->data);
        }
    }
    if (r == NULL)
        return r;
    r->height = computeTotalHeight(r);
    r->total_node = computeTotalNode(r);
    ll balanceFact = computeBalFact(r);
    if (balanceFact > 1 || balanceFact < -1)
    {
        newroot = do_balancing(r, balanceFact);
        r = newroot;
    }
    return r;
}

bool search_node(node *root, ll d)
{
    if (root == NULL)
        return false;
    else if (root->data == d)
        return true;
    else if (root->data < d)
        return search_node(root->right, d);
    else
        return search_node(root->left, d);
    return false;
}

ll inOrder_2(node *r, ll y)
{
    int r_pos = r->total_node - getTotalnode(r->right);
    if (y == r_pos)
        return r->data;
    else if (y < r_pos)
        return inOrder_2(r->left, y);
    else
        return inOrder_2(r->right, y - r_pos);
}

void print_kth_min(node *r, ll y)
{
    ll kth_elem = inOrder_2(r, y);
    cout << kth_elem << endl;
    r = deleteNode(r, kth_elem);
}

int main()
{
    ios_base::sync_with_stdio(false);
    ll n, m;
    cin >> n >> m;
    vector<ll> d(n);
    ll tmp_data;
    for (ll i = 0; i < n; i++)
    {
        cin >> tmp_data;
        root = insert(root, tmp_data);
    }
    while (m--)
    {
        ll x, y;
        cin >> x >> y;
        switch (x)
        {
        case 1:
            root = insert(root, y);
            break;
        case 2:
            search_node(root, y) ? cout << "1" << endl : cout << "0" << endl;
            break;
        case 3:
            print_kth_min(root, y);
            break;
        }
    }
    return 1;
}