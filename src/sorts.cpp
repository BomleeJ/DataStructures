#include "sorts.h"
#include <algorithm>


bool comp(ItemHandle& lhs, ItemHandle& rhs, bool ascending)
{
    return (ascending) ? lhs < rhs : rhs < lhs;
}
// TODO: Implement stable insertion sort on vector<ItemHandle>
void insertionSortItems(std::vector<ItemHandle>& a, bool ascending) {
    if (a.size() <= 1) { return; }

    size_t bor = 1;

    for(; bor < a.size(); bor++)
    {
        ItemHandle key = a[bor];
        size_t i = bor;
        while ((i > 0) && comp(key, a[i - 1], ascending))
        {
            a[i] = a[i - 1];
            i--;
        }
        a[i] = key;
    }
}

void merge(std::vector<ItemHandle>& left, std::vector<ItemHandle>& right, std::vector<ItemHandle>& mid, bool ascending)
{
    size_t lptr = 0;
    size_t rptr = 0;

    while (lptr < left.size() && rptr < right.size())
    {
        if (comp(left[lptr], right[rptr], ascending))
        {
            mid[lptr + rptr] = left[lptr];
            lptr++;
        }
        else
        {
            mid[lptr + rptr] = right[rptr];
            rptr++;
        }
    }

    size_t mptr = lptr + rptr;


    while (lptr < left.size())
    {
        mid[mptr++] = left[lptr++];
    }

    while (rptr < right.size())
    {
        mid[mptr++] = right[rptr++];
    }


}

/* [7,3,9,12,74,16]*/
/* [7,3,9] [12,74,16] */
/* [7] [3, 9]*/
void mergeSort(std::vector<ItemHandle>& a, bool ascending)
{
    if (a.size() <= 1) { return; }
    
    size_t MID = a.size() / 2;

    std::vector<ItemHandle> lhs(a.begin(), a.begin() + MID);
    std::vector<ItemHandle> rhs(a.begin() + MID, a.end());
    mergeSort(lhs, ascending);
    mergeSort(rhs, ascending);
    merge(lhs, rhs, a, ascending);
}


// TODO: Implement stable merge sort on vector<ItemHandle>
void mergeSortItems(std::vector<ItemHandle>& a, bool ascending) {
    (void)a; (void)ascending; // STUB: no-op
    mergeSort(a, ascending);
}

void sortItems(std::vector<ItemHandle>& a, SortAlgo algo, bool ascending) {
    switch (algo) {
        case SortAlgo::Insertion: insertionSortItems(a, ascending); break;
        case SortAlgo::Merge:     mergeSortItems(a,     ascending); break;
    }
}

