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
	numberOfCustomers = customerNumber;
	numberOfResources = resourcesNumber;

	for (int i = 0; i < resourcesNumber; i++) {
		available[i] = resources[i];
	}
}


void showState() {
    int i, j;
	printf("\nCurrent state:\n\n");

	printf("Available:\n");
	for (i = 0; i < numberOfResources; i++) {
		printf("  %c: %d\n", i+65, available[i]);
	}
	printf("\n");

	printf("\nMaximum:\n\t");
    for (i = 0; i < numberOfResources; i++) printf("%c ", i+65);
    printf("\n");
	for (i = 0; i < numberOfCustomers; i++) {
        printf("%d\t", i);
		for (j = 0; j < numberOfResources; j++) printf("%d ", maximum[i][j]);
		printf("\n");		
	}

	printf("\nAllocation:\n\t");
    for (i = 0; i < numberOfResources; i++) printf("%c ", i+65);
    printf("\n");
	for (i = 0; i < numberOfCustomers; i++) {
        printf("%d\t", i);
		for (j = 0; j < numberOfResources; j++) printf("%d ", allocation[i][j]);
		printf("\n");		
	}
	
	printf("\nNeed:\n\t");
    for (i = 0; i < numberOfResources; i++) printf("%c ", i+65);
    printf("\n");
	for (i = 0; i < numberOfCustomers; i++) {
        printf("%d\t", i);
		for (j = 0; j < numberOfResources; j++) printf("%d ", need[i][j]);
		printf("\n");		
	}
	printf("\n");
}


int addCustomer(int customerId, int maximumDemand[]) {
	if(customerId >= numberOfCustomers || customerId < 0) return 1;

	for (int i = 0; i < numberOfResources; i++) {
		maximum[customerId][i] = maximumDemand[i];
		need[customerId][i] = maximumDemand[i];
	}
	return 0;
}


int checkSafe(int customerId, int request[]) {
	int temp_need[10][10], temp_alloc[10][10];
	int i, j, work[10];
	bool finish[10];
	bool done = false;
    bool feasible = true;

	for (j = 0; j < numberOfResources; j++) {
		work[j] = available[j] - request[j];
		for (i = 0; i < numberOfCustomers; i++) {
            temp_need[i][j] = need[i][j];
            temp_alloc[i][j] = allocation[i][j];
		}
        temp_need[customerId][j] -= request[j];
        temp_alloc[customerId][j] += request[j];
	}

	for (i = 0; i < numberOfCustomers; i++) finish[i] = false;

	while (!done) {
		done = true;
		for (i = 0; i < numberOfCustomers; i++) {
			feasible = true;
			for (j = 0; j < numberOfResources; j++) {
				if (temp_need[i][j] > work[j]) feasible = false;
			}
			if (!finish[i] && feasible) {
                done = false;
				finish[i] = true;
				for (j = 0; j < numberOfResources; j++) work[j] += temp_alloc[i][j];
			}
		}
	}

	for (i = 0; i < numberOfCustomers; i++){
		if (!finish[i]) return -1;
	}
	return 0;
}

int requestResources(int customerId, int request[]) {
    int i;

	printf("\nRequest from customerId %d\n", customerId);
	for (i = 0; i < numberOfResources; i++) {
		printf("  %c: %d\n", i+65, request[i]);
		if (request[i] > need[customerId][i] || request[i] > available[i]) {
			printf("  -- Request for resource is too much!\n");
			return -1;
        }
    }

	if (checkSafe(customerId, request) != 0) {
		printf("Request is unsafe. Rejected.\n");
		return -1;
    }

	printf("Request granted.\n");

	for (i = 0; i < numberOfResources; i++){
		available[i] -= request[i];
		allocation[customerId][i] += request[i];
		need[customerId][i] -= request[i];
	}
	return 0;
}


int releaseResources(int customerId, int release[]) {
	printf("\nRelease resources for customerId %d\n", customerId);
	for (int i = 0; i < numberOfResources; i++) {
		printf("  %c: %d\n", i+65, release[i]);
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