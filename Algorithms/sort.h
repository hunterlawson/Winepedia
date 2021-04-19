#include <iostream>
#include <vector>
#include <string>
#include "../Data/wine.h"
#include <chrono>
using namespace std;

//3 sorting algorithms: bubble sort = O(N^2), merge sort = O(NlogN), quick sort O(NlogN)
//Compare algorithm time complexities to complete similar tasks
//Included chrono to calculate the time for each sort

//BUBBLE SORT, psuedocode cited from slides module 6
void bubbleSortPrice(vector<Wine>& vect) 
{
  for (int i = 0; i < vect.size() - 1; i++) 
  {
    int swapped = 0;
    for (int j = 0; j < vect.size() - i - 1; ++j) 
    {
      if (vect[j].getPrice() > vect[j + 1].getPrice()) 
      {
        Wine temp = vect[j];
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

void bubbleSortPoint(vector<Wine>& vect) 
{
  for (int i = 0; i < vect.size() - 1; i++) 
  {
    int swapped = 0;
    for (int j = 0; j < vect.size() - i - 1; ++j) 
    {
      if (vect[j].getPoints() > vect[j + 1].getPoints()) 
      {
        Wine temp = vect[j];
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
void mergePrice(vector<Wine>& vect, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Wine> X;
    vector<Wine> Y;

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
    if (X[i].getPrice() <= Y[j].getPrice()) 
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

void mergeSortPrice(vector<Wine>& vect, int left, int right) 
{
  if (left < right) 
  {
    // m is the point where the array is divided into two subarrays
    int mid = left + (right - left) / 2;

    mergeSortPrice(vect, left, mid);
    mergeSortPrice(vect, mid + 1, right);

    // Merge the sorted subarrays
    mergePrice(vect, left, mid, right);
  }
}

void mergePoints(vector<Wine>& vect, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Wine> X;
    vector<Wine> Y;

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
    if (X[i].getPoints() <= Y[j].getPoints()) 
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

void mergeSortPoints(vector<Wine>& vect, int left, int right) 
{
  if (left < right) 
  {
    int mid = left + (right - left) / 2;

    mergeSortPoints(vect, left, mid);
    mergeSortPoints(vect, mid + 1, right);

    // Merge the sorted subarrays
    mergePoints(vect, left, mid, right);
  }
}




//QUICK SORT, psuedocode cited from slides module 6
void swap(Wine *a, Wine *b)
{
    Wine t = *a;
    *a = *b;
    *b = t;
}

int partitionPrice(vector<Wine>& vect, int low, int high) 
{
  int pivot = vect[low].getPrice();
  int up=low, down=high;
  
  while(up<down)
  {
      for (int j = up; j < high; j++)
      {
        if(vect[up].getPrice() > pivot)
        {
            break;
        }
        up++;
      }
      for (int j = high; j > low; j--)
      {
        if(vect[down].getPrice() < pivot)
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

void quickSortPrice(vector<Wine>& vect, int low, int high) 
{
  if (low < high) 
  {
    int pivot = partitionPrice(vect, low, high);
    quickSortPrice(vect, low, pivot - 1);
    quickSortPrice(vect, pivot + 1, high);
  }
}

int partitionPoints(vector<Wine>& vect, int low, int high) 
{
  int pivot = vect[low].getPoints();
  int up=low, down=high;
  
  while(up<down)
  {
      for (int j = up; j < high; j++)
      {
        if(vect[up].getPoints() > pivot)
        {
            break;
        }
        up++;
      }
      for (int j = high; j > low; j--)
      {
        if(vect[down].getPoints() < pivot)
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

void quickSortPoints(vector<Wine>& vect, int low, int high) 
{
  if (low < high) 
  {
    int pivot = partitionPoints(vect, low, high);
    quickSortPoints(vect, low, pivot - 1);
    quickSortPoints(vect, pivot + 1, high);
  }
}