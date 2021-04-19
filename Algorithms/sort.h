#include <iostream>
#include <vector>
#include <string>
#include "../Data/wine.h"
#include <chrono>
#include <algorithm>
using namespace std;

//3 sorting algorithms: bubble sort = O(N^2), heap = O(NlogN), quick sort O(NlogN)
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

//Based off implementation on software testing (website)
//Also used iter_swap for vector to swap vectors
void heapifyPrice(vector<Wine>& vect, int n, int root)
{
  int largest = root;
  int l = 2*root + 1;
  int r = 2*root + 2;

  if (l < n && vect[l].getPrice() > vect[largest].getPrice())
    largest = l;

  if (r < n && vect[r].getPrice() > vect[largest].getPrice())
    largest = r;
  
  if (largest != root)
  {
    iter_swap(vect.begin() + root, vect.begin() + largest);
    heapifyPrice(vect, n, largest);
  }
}
  
void heapSortPrice(vector<Wine>& vect, int n)
{
   for (int i = n / 2 - 1; i >= 0; i--)
   heapifyPrice(vect, n, i);
  
   for (int i=n-1; i>=0; i--)
   {
      iter_swap(vect.begin(), vect.begin() + i);
      heapifyPrice(vect, i, 0);
   }
}

void heapifyPoints(vector<Wine>& vect, int n, int root)
{
  int largest = root;
  int l = 2*root + 1;
  int r = 2*root + 2;

  if (l < n && vect[l].getPoints() > vect[largest].getPoints())
    largest = l;

  if (r < n && vect[r].getPoints() > vect[largest].getPoints())
    largest = r;
  
  if (largest != root)
  {
    iter_swap(vect.begin() + root, vect.begin() + largest);
    heapifyPoints(vect, n, largest);
  }
}
  
void heapSortPoints(vector<Wine>& vect, int n)
{
   for (int i = n / 2 - 1; i >= 0; i--)
   heapifyPoints(vect, n, i);
  
   for (int i=n-1; i>=0; i--)
   {
      iter_swap(vect.begin(), vect.begin() + i);
      heapifyPoints(vect, i, 0);
   }
}



//QUICK SORT, psuedocode cited from slides module 6
void swapQ(Wine *a, Wine *b)
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
        swapQ(&vect[up], &vect[down]);
      }
  }
  swapQ(&vect[low], &vect[down]);
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
        swapQ(&vect[up], &vect[down]);
      }
  }
  swapQ(&vect[low], &vect[down]);
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