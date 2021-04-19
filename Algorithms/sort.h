#include <iostream>
#include <vector>
#include <string>
#include "../Data/wine.h"
#include <chrono>
using namespace std;

//3 sorting algorithms: bubble sort = O(N^2), selection = O(N^2), quick sort O(NlogN)
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

void shellSortPrice(vector<Wine>& vect)
{
  for(int i = vect.size(); i > 0; i /= 2)
  {
    for(int k = i; k < vect.size(); k += 1)
    {
      Wine temp = vect[k];

      int j;
      for(int j = k; j >= i && vect[j - i].getPrice() > temp.getPrice(); j -= k)
      {
        vect[j] = vect[j - i];
      }
      vect[j] = temp;
    }
  }
}

void shellSortPoints(vector<Wine>& vect)
{
  for(int i = vect.size(); i > 0; i /= 2)
  {
    for(int k = i; k < vect.size(); k += 1)
    {
      Wine temp = vect[k];

      int j;
      for(int j = k; j >= i && vect[j - i].getPoints() > temp.getPoints(); j -= k)
      {
        vect[j] = vect[j - i];
      }
      vect[j] = temp;
    }
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