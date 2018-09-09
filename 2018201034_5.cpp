/*
 * RUNNING MEDIAN by Rushit M Jasani : 2018201034
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll min_heap[100005];
ll max_heap[100005];

/*
 * Heapify for MaxHeap
 */
void Max_Heapify(ll index, ll size)
{
    ll left_child = (2 * index) + 1;
    ll right_child = (2 * index) + 2;
    ll max_pos;
    if (left_child <= size - 1 && max_heap[left_child] > max_heap[index])
        max_pos = left_child;
    else
        max_pos = index;

    if (right_child <= size - 1 && max_heap[right_child] > max_heap[max_pos])
        max_pos = right_child;
    if (max_pos != index)
    {
        ll temp = max_heap[index];
        max_heap[index] = max_heap[max_pos];
        max_heap[max_pos] = temp;
        Max_Heapify(max_pos, size);
    }
    return;
}
/*
 * Heapify in MinHeap
 */
void Min_Heapify(ll index, ll size)
{
    ll left_child = (2 * index) + 1;
    ll right_child = (2 * index) + 2;
    ll min_pos;
    if (left_child <= size - 1 && min_heap[left_child] < min_heap[index])
        min_pos = left_child;
    else
        min_pos = index;

    if (right_child <= size - 1 && min_heap[right_child] < min_heap[min_pos])
        min_pos = right_child;

    if (min_pos != index)
    {
        ll temp = min_heap[index];
        min_heap[index] = min_heap[min_pos];
        min_heap[min_pos] = temp;
        Min_Heapify(min_pos, size);
    }
    return;
}
/**
 * Insert element in MaxHeap
 */ 
void max_insert(ll a, ll size)
{
    max_heap[size - 1] = a;
    for (ll i = ceil(size - 1 / 2.0) - 1; i >= 0;)
    {
        Max_Heapify(i, size);
        i = ceil(i / 2.0) - 1;                          //parent node
    }
}
/**
 * Insert element in MinHeap
 */ 
void min_insert(ll a, ll size)
{
    min_heap[size - 1] = a;
    for (ll i = ceil(size - 1 / 2.0) - 1; i >= 0;)
    {
        Min_Heapify(i, size);
        i = ceil(i / 2.0) - 1;                           //parent node
    }
}
/*
 * Deletes Maximum Element from Maxheap
 */ 
void delete_max(ll size)
{
    max_heap[0] = max_heap[size - 1];
    size--;
    Max_Heapify(0, size);
}
/*
 * Deletes Minimum Element from Minheap
 */ 
void delete_min(ll size)
{
    min_heap[0] = min_heap[size - 1];
    size--;
    Min_Heapify(0, size);
}

void runningMedian(ll a[], ll size)
{
    ll max_heap_size = 0;
    ll min_heap_size = 0;
    double ans[size] = {0};
    max_insert(a[0], ++max_heap_size);
    ans[0] = a[0];

    for (ll i = 1; i < size; i++)
    {
        ll el = a[i];
        if (max_heap_size == min_heap_size)
        {
            if (ans[i - 1] > el)
            {
                max_insert(el, ++max_heap_size);
                ans[i] = max_heap[0] * 1.0;
            }
            else
            {
                min_insert(el, ++min_heap_size);
                ans[i] = min_heap[0] * 1.0;
            }
        }
        else if (max_heap_size > min_heap_size)
        {
            if (el < ans[i - 1])
            {
                min_insert(max_heap[0], ++min_heap_size);
                delete_max(max_heap_size);
                max_heap_size--;
                max_insert(el, ++max_heap_size);
            }
            else
            {
                min_insert(el, ++min_heap_size);
            }
            ans[i] = (min_heap[0] + max_heap[0]) / 2.0;
        }
        else
        {
            if (el > ans[i - 1])
            {
                max_insert(min_heap[0], ++max_heap_size);
                delete_min(min_heap_size);
                min_heap_size--;
                min_insert(el, ++min_heap_size);
            }
            else
            {
                max_insert(el, ++max_heap_size);
            }
            ans[i] = (min_heap[0] + max_heap[0]) / 2.0;
        }
    }
    for (ll i = 0; i < size; i++)
        cout << fixed << setprecision(1) << ans[i] << endl;
    return;
}

int main()
{
    ll n = 0;
    cin >> n;
    ll a[100005];
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    runningMedian(a, n);
    return 0;
}
