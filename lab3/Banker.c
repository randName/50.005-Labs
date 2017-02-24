#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int numberOfCustomers;
int numberOfResources;

int available[10];
int maximum[10][10];
int allocation[10][10];
int need[10][10];


void initBank(int resources[], int resourcesNumber, int customerNumber) {
	// set numberOfCustomers and numberOfResources
	numberOfCustomers = customerNumber;
	numberOfResources = resourcesNumber;

	// init available/maximum/allocation/need
	for(int i = 0; i < resourcesNumber; i++){
		available[i] = resources[i];
	}
}


void showState() {
	// print the current state with a tidy format
	printf("\nCurrent state: \n");
	printf("Available: \n");
	for (int i = 0; i < numberOfResources; i++) {
		printf("%d ", available[i]);
	}
	printf("\n");
	printf("\nmaximum: \n");
	for (int i = 0; i < numberOfCustomers; i++) {
		for(int j = 0; j < numberOfResources; j++) {
			printf("%d ", maximum[i][j]);
		}
		printf("\n");		
	}
	printf("\nAllocation: \n");
	for (int i = 0; i < numberOfCustomers; i++) {
		for(int j = 0; j < numberOfResources; j++) {
			printf("%d ", allocation[i][j]);
		}
		printf("\n");		
	}
	
	printf("\nNeed: \n");
	for (int i = 0; i < numberOfCustomers; i++) {
		for(int j = 0; j < numberOfResources; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");		
	}	
	printf("\n");
}


int addCustomer(int customerId, int maximumDemand[]) {
	// add customer, update maximum and need
	if(customerId >= numberOfCustomers || customerId < 0){
		return -1;
	}

	for (int i = 0; i < numberOfResources; i++){
		maximum[customerId][i] = maximumDemand[i];
		need[customerId][i] = maximumDemand[i];
	}
	return 0;
}


int checkSafe(int customerId, int request[]) {
	// check if the new state is safe
	int temp_avail[10];
	int temp_need[10][10];
	int temp_allocation[10][10];
	int work[10];
	bool finish[10];
	bool possible = true;

	for(int j = 0; j < numberOfResources; j++){
		temp_avail[j] = available[j] - request[j];
		work[j] = temp_avail[j];
		for(int i = 0; i < numberOfCustomers; i++){
			if (i == customerId){
				temp_need[customerId][j] = need[customerId][j] - request[j];
				temp_allocation[customerId][j] = allocation[customerId][j] + request[j];
			}
			else{
				temp_need[i][j] = need[i][j];
				temp_allocation[i][j] = allocation[i][j];
			}
		}
	}

	for (int i = 0; i < numberOfCustomers; i++){
		finish[i] = false;
	}

	while(possible){
		possible = false;
		for (int i = 0; i < numberOfCustomers; i++){
			bool feasible = true;
			for(int j = 0; j < numberOfResources; j++){
				if(temp_need[i][j] > work[j]){
					feasible = false;
				}
			}
			if(finish[i] == 0 && feasible){
				possible = true;
				for(int j = 0; j < numberOfResources; j++){
					work[j] += temp_allocation[i][j];
				}
				finish[i] = true;
			}
		}
	}
	int safe = 0;
	for (int i = 0; i < numberOfCustomers; i++){
		if(!finish[i]){
			safe = -1;
		}
	}
	return safe;
}

int requestResources(int customerId, int request[]) {

	// deal with new request resources
	printf("\nRequest resource, customerId %d: [", customerId);
	for(int i = 0; i < numberOfResources-1; i++) {
		printf("%d, ", request[i]);
	}
	printf("%d]\n",request[numberOfResources-1]);

	// judge if request larger than need
	for(int i = 0; i < numberOfResources; i++){
		if(request[i] > need[customerId][i]){
			printf("Request from customer %d exceeds the need for resource %d!\n", customerId, i);
			return -1;
		}
	}

	// judge if request larger than avaliable
	for(int i = 0; i < numberOfResources; i++){
		if(request[i] > available[i]){
			printf("Request from customer %d is more than avaliable for resource %d!\n", customerId, i);
			return -1;
		}
	}

	// judge if the new state is safe if grants this request (for question 2)
	if (checkSafe(customerId, request) == -1){
		printf("Request may cause the system unsafe. Rejected.\n");
		return -1;
	}

	// request is granted, update state
	printf("Request granted.\n");
	for(int i = 0; i < numberOfResources; i++){
		available[i] -= request[i];
		allocation[customerId][i] += request[i];
		need[customerId][i] -= request[i];
	}
	return 0;
}


int releaseResources(int customerId, int release[]) {
	// deal with release (:For simplicity, we do not judge the release request, just update directly)
	printf("\nRelease resource, customerId %d: [", customerId);
	for(int i = 0; i < numberOfResources-1; i++) {
		printf("%d, ", release[i]);
	}
	printf("%d]\n",release[numberOfResources-1]);

	for (int i = 0; i < numberOfResources; i++){
		available[i] += release[i];
		allocation[customerId][i] -= release[i];
		need[customerId][i] += release[i];
	}
	return 0;
}


int main (int argc, const char * argv[]) 
{	// Test code for Question 1
	numberOfCustomers = 5;
	numberOfResources = 3;
	int resource[3] = {10, 5, 7};
	initBank(resource, sizeof(resource)/sizeof(int),numberOfCustomers);
	int maximumDemand[5][3] = {
		{7, 5, 3}, 
		{3, 2, 2}, 
		{9, 0, 2},
		{2, 2, 2},
		{4, 3, 3}
		};
	for(int i = 0; i < numberOfCustomers; i++) {
		addCustomer(i,maximumDemand[i]);
	}
	
	int request[5][3] = {
		{0, 1, 0},
		{2, 0, 0},
		{3, 0, 2},
		{2, 1, 1},
		{0, 0, 2}
	};
   requestResources(0,request[0]);
   requestResources(1,request[1]);
   requestResources(2,request[2]);
   requestResources(3,request[3]);
   requestResources(4,request[4]);
   showState();

   // Test code for Question 2, please comment out the following part when test Question 1
   int newRequest1[3] = {1, 0, 2};
   requestResources(1, newRequest1);
   showState();
   int newRequest2[3] = {0, 2, 0};
   requestResources(0, newRequest2);
   showState();
   // End of test code for Question 2
   return 0;
}