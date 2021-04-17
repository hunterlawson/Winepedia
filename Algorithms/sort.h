#include <iostream>
#include <vector>
#include <string>
using namespace std;

//3 sorting algorithms: bubble sort = O(N^2), merge sort = O(NlogN), quick sort O(NlogN)
//Compare algorithm time complexities to compare different tasks

//BUBBLE SORT, psuedocode cited from slides module 6
void bubbleSort(vector<int>& vect) 
{
  for (int i = 0; i < vect.size() - 1; i++) 
  {
    int swapped = 0;
    for (int j = 0; j < vect.size() - i - 1; ++j) 
    {
      if (vect[j] > vect[j + 1]) 
      {
        int temp = vect[j];
        vect[j] = vect[j + 1];
        vect[j + 1] = temp;
        swapped = 1;
      }
    }
    if (swapped == 0)
    {
        break;
    }
  }
}

//MERGE SORT, psuedocode cited from slides module 6
void merge(vector<int>& vect, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> X;
    vector<int> Y;

    for (int i = 0; i < n1; i++)
    {
        X[i] = vect[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        Y[j] = vect[mid + 1 + j];
    }

  // Merge the arrays X and Y into vector
  int i, j, k;
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) 
  {
    if (X[i] <= Y[j]) 
    {
      vect[k] = X[i];
      i++;
    } 
    else 
    {
      vect[k] = Y[j];
      j++;
    }
    k++;
  }
 
  while (i < n1) 
  {
    vect[k] = X[i];
    i++;
    k++;
  }

  while (j < n2) 
  {
    vect[k] = Y[j];
    j++;
    k++;
  }
}


void mergeSort(vector<int>& vect, int left, int right) 
{
  if (left < right) 
  {
    // m is the point where the array is divided into two subarrays
    int mid = left + (right - left) / 2;

    mergeSort(vect, left, mid);
    mergeSort(vect, mid + 1, right);

    // Merge the sorted subarrays
    merge(vect, left, mid, right);
  }
}

//QUICK SORT, psuedocode cited from slides module 6
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<int>& vect, int low, int high) 
{
  int pivot = vect[low];
  int up=low, down=high;
  
  while(up<down)
  {
      for (int j = up; j < high; j++)
      {
        if(vect[up] > pivot)
        {
            break;
        }
        up++;
      }
      for (int j = high; j > low; j--)
      {
        if(vect[down] < pivot)
        {
            break;
        }
        down--;
      }
      if(up<down)
      {
        swap(&vect[up], &vect[down]);
      }
  }
  swap(&vect[low], &vect[down]);
  return down;
}

void quickSort(vector<int>& vect, int low, int high) 
{
  if (low < high) 
  {
    int pivot = partition(vect, low, high);
    quickSort(vect, low, pivot - 1);
    quickSort(vect, pivot + 1, high);
  }
}

//NEED TO WRITE SORT FUNCTION BASED OFF STRINGS
//i.e. country, name, etc.