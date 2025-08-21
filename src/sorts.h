#pragma once
#include "item.h"
#include <vector>

enum class SortAlgo { Insertion, Merge };

bool comp(ItemHandle& lhs, ItemHandle& rhs, bool ascending);
void insertionSortItems(std::vector<ItemHandle>& a, bool ascending);
void merge(std::vector<ItemHandle>& a, std::vector<ItemHandle>& lhs, std::vector<ItemHandle>& rhs, bool ascending);
void mergeSort(std::vector<ItemHandle>& a, bool ascending);
void mergeSortItems(std::vector<ItemHandle>& a, bool ascending);
void sortItems(std::vector<ItemHandle>& a, SortAlgo algo, bool ascending);
