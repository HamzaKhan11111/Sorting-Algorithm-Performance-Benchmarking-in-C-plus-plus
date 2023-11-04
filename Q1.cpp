#include<iostream>
#include<fstream>
#include <time.h>
#include <sys/time.h>
#include <cmath>
#include <string>
using std::ofstream;
using namespace std;
ofstream out;
ofstream t;
ofstream initial;
int operation_count=0;

void merge(int arr[],int left,int mid,int right)
{
	int n1=mid-left+1;
	int n2=right-mid;
	
	int l[n1];
	int r[n2];
	
	for(int i=0;i<n1;i++)
	{
		l[i]=arr[left+i];
		operation_count++;
	}
	for(int j=0;j<n2;j++)
	{
		r[j]=arr[mid+1+j];
		operation_count++;
	}
		
	int i=0;
	int j=0;
	int k=left;
	
	while(i<n1 && j<n2)
	{
		if(l[i]<=r[j])
		{
			arr[k]=l[i];
			operation_count++;
			i++;
		}
		else
		{
			arr[k]=r[j];
			operation_count++;
			j++;
		}
		k++;
	}
	
	while(i<n1)
	{
		arr[k]=l[i];
		operation_count++;
		i++;
		k++;
	}
	while(j<n2)
	{
		arr[k]=r[j];
		operation_count++;
		j++;
		k++;
	}
}

void mergeSort(int arr[],int l,int r)
{
	if(l<r)
	{
		int mid=l+(r-l)/2;
		mergeSort(arr,l,mid);
		mergeSort(arr,mid+1,r);
		merge(arr,l,mid,r);
	}
}

int partition(int arr[], int low, int high) 
{
	int pivot=arr[high];
	int i=low-1;
	for (int j=low;j<=high-1;j++) 
	{
		if (arr[j]<pivot) 
		{
			operation_count++;
			i++;
			int temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
		operation_count++;
	}
	int temp = arr[i+1];
	arr[i+1] = arr[high];
	arr[high] = temp;
	return i+1;
}

void quickSort(int arr[],int low,int high)
{
	if (low<high) 
	{
		int pivot = partition(arr,low,high);
		quickSort(arr,low, pivot-1);
		quickSort(arr,pivot+1,high);
	}
}

int main(int argc,char** argv)
{
	string quick="quick";
	string merge="merge";;
	int input=0;
	int size=0;

    	out.open("output.txt");
    	t.open("time.txt");
    	initial.open("inital.txt");
    	int s[4]={11,13,15,17};
    	for(int k=0;k<4;k++)
    	{
    		size=pow(2,s[k]);
    		
    		int *arr=new int[size];
    		int *arr1=new int[size];
		for(int i=0;i<size;i++)
		{
			arr[i]=(rand()%1000);
		}
		
		if(s[k]==atoi(argv[2]) && merge==argv[1])
	    	{
		    	initial<<"Merge Sort size 2^"<<s[k]<<":"<<endl;
			for(int i=0;i<size;i++)
			{
				initial<<arr[i]<<" ";
			}
			initial<<endl;
		}
		
		for(int i=0;i<size;i++)
		{
			arr1[i]=arr[i];
		}
		
		if(s[k]==atoi(argv[2]) && quick==argv[1])
	    	{
		    	initial<<"Quick Sort size 2^"<<s[k]<<":"<<endl;
			for(int i=0;i<size;i++)
			{
				initial<<arr[i]<<" ";
			}
			initial<<endl;
		}
		
		struct timeval start, end;
		operation_count=0;
		
		gettimeofday( &start, NULL );
		mergeSort(arr,0,size-1);
		gettimeofday( &end, NULL );
		
		double seconds = (end.tv_sec - start.tv_sec) +1.0e-6 * (end.tv_usec - start.tv_usec);
	    	double Gflops = 2e-9*operation_count/seconds;
	    	t<<"Merge Sort size 2^"<<s[k]<<"\t"<<Gflops<<endl<<endl;
	    	
	    	if(s[k]==atoi(argv[2]) && merge==argv[1])
	    	{
		    	out<<"Merge Sort size 2^"<<s[k]<<":"<<endl;
			for(int i=0;i<size;i++)
			{
				out<<arr[i]<<" ";
			}
			out<<endl;
		}
		
		
		operation_count=0;
		
		gettimeofday( &start, NULL );
		quickSort(arr1,0,size-1);
		gettimeofday( &end, NULL );
		
		seconds = (end.tv_sec - start.tv_sec) +1.0e-6 * (end.tv_usec - start.tv_usec);
	    	Gflops = 2e-9*operation_count/seconds;
	    	t<<"Quick Sort size 2^"<<s[k]<<"\t"<<Gflops<<endl<<endl;
	    	if(s[k]==atoi(argv[2]) && quick==argv[1])
	    	{
		    	out<<"Quick Sort size 2^"<<s[k]<<":"<<endl;
			for(int i=0;i<size;i++)
			{
				out<<arr[i]<<" ";
			}
			out<<endl;
		}
    	}
    	
	
	cout<<"Initial unsorted array is stored in inital.txt. Sorted Array is stored in output.txt"<<endl;
	cout<<"This program also ran for all 4 sizes and GFlops of them are stored in time.txt"<<endl;
	out.close();
	t.close(); 
	initial.close();
	return 0;
}
