#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
using namespace std;


int numbers[10000];//random numbers
int minimum[5];	//5 minimums
int hundmin[100];
int c=0;	//index for each second level thread that increments by 100
int x=0;	//index for hundmin array that increments by 1
int y=0;	//index for each first level thread that increments by 20
int z=0;	//index for minimum array that increments by 1

int five=0;
int twenty=0;
//helper method to find minimum of specific parts of an array
int findMin(int arr[],int start,int end){
	int output=arr[start];
	for(int i=start;i<end;i++){
		if(arr[i]<output)
			output=arr[i];
	}
	return output;
}

//method ran by second layer of 100 threads 	
void *divide2(void* args){
	//checking
	
	cout<<"Thread Level 2: "<<twenty<<endl;
	twenty++;

	int min=findMin(numbers,c,c+100);
	hundmin[x]=min;
	c=c+100;
	x++;
	return NULL;
}

//method ran by the first layer of  5 threads
void* divide(void* arg){
	//checking
	cout<<"Thread Level 1: "<<five<<endl;
	five++;

	pthread_t tids2[20];
	for(int i=0;i<sizeof(tids2)/sizeof(*tids2);i++){
		pthread_create(&tids2[i],NULL,divide2,NULL);
	}
	for(int i=0;i<sizeof(tids2)/sizeof(*tids2);i++){
		pthread_join(tids2[i],NULL);
	}
	int min=findMin(hundmin,y,y+20);
	minimum[z]=min;
	z++;
	y=y+20;
	return NULL;	
}


int main(){
	//assigning random numbers
	for(int i=0;i<sizeof(numbers)/sizeof(*numbers);i++){
		numbers[i]=rand();
	}

	//brute force finding min and max
	int max_numbers=numbers[0];
	int min_numbers=numbers[0];
	for(int i=0;i<sizeof(numbers)/sizeof(*numbers);i++){
		if(numbers[i]>max_numbers)
			max_numbers=numbers[i];
		if(numbers[i]<min_numbers)
			min_numbers=numbers[i];
	}
	
	//Threaded way to find min
	pthread_t tids[5];

	//creating threads
	for(int i=0;i<sizeof(tids)/sizeof(*tids);i++){
		pthread_create(&tids[i],NULL,divide,NULL);
	}
	//joining threads
	for(int i=0;i<sizeof(tids)/sizeof(*tids);i++){
		pthread_join(tids[i],NULL);
	}
	
	//printing first layer thread 100 minimums
	cout<<"First Layer Thread minimums:";
	for(int i=0;i<sizeof(hundmin)/sizeof(*hundmin);i++){
		if(i%20==0) cout<<endl;
		cout<<hundmin[i]<<" ,";
	}
	cout<<endl;
	cout<<"Second Layer Thread minimums:"<<endl;
	for(int i=0;i<sizeof(minimum)/sizeof(*minimum);i++){
		cout<<"minium: "<<minimum[i]<<" ,";
	}
	cout<<endl;
	//printing final minimum
	cout<<"Brute Force Max: "<<max_numbers<<endl;
	cout<<"Brute Force Min: "<<min_numbers<<endl;
	cout<<"Threaded minimum is: "<<findMin(minimum,0,sizeof(minimum)/sizeof(*minimum))<<endl;
}

		
