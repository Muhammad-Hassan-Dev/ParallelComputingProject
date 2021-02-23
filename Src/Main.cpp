#include "SearchExecution.cpp"

int main(int argc, char *argv[])
{
	cout << endl << "DESCRIPTION: This program takes the threads count, search space size, and search item parameters given on the command line. It generates a random array of given size, divides the array into chunks (one for each thread), searches chunks through given number of threads for the given search item, and consolidates and prints the number of times the given search number occurs in the random array."<<endl <<endl;

	//Command Line parameters
	int threads_count = 0; //number of threads to create
	long searchspace_size = 0; //size of array to search in
	int search_item = 0; //the item to search for in the array

	if(argc>1)
		threads_count = atoi(argv[1]);
	if(argc>2)
		searchspace_size = atol(argv[2]);
	if(argc>3)
		search_item = atoi(argv[3]);

	if(threads_count <= 0)
	{
		threads_count = 1; //default threads count is 1
		cout <<"Invalid value for threads count. Initializing to default 1."<<endl;
	}

	if(searchspace_size <= 0)
	{
		searchspace_size = 1000000;	//default search space size is 1 million
		cout <<"Invalid value for search space size. Initializing to default 1 million."<<endl;
	}

	if(searchspace_size < threads_count) //Must be not more than one thread for each element in array
	{
		cout <<"Threads Count must be lesser than or same as Search Space size. Setting Threads Count = Search Space size."<<endl;
		threads_count = searchspace_size;
	}

	if(search_item == 0)
	{
		cout << "Search Item cannot be zero, since it is used in modulus operation to initialize search array. Randomizing search item to fall between 1 to 10."<<endl;
		srand(time(NULL));
		search_item = rand() % 10 + 1;
	}

	SearchTask * search_tasks = GetRandomSearchTasks(threads_count, searchspace_size, search_item); //Get a random search problem in chunks
 
	cout << "Successfully initialized search array."<<endl;

	LeadSearch(search_tasks, threads_count); //This will perform the search on each chunk in an individual thread and accumulate and print the result

	cout << "Search Complete. Exitting program."<<endl;

	pthread_exit(NULL);
}
