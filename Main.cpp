#include "SearchProblemSetup.cpp"
#include "SearchChunk.cpp"
#include <pthread.h>

void LeadSearch(SearchTask * tasks, int threads_count)
{
	pthread_t * thread_ids = new pthread_t[threads_count];

	int * statuses = new int[threads_count];

	for(int i=0;i<threads_count;i++)
	{
		statuses[i] = pthread_create(&thread_ids[i], NULL, SearchChunk, (void*) &tasks[i]);

		if(statuses[i] != 0)
		{
			cout <<"pthread_create failed."<< endl;
			exit(-1); //if thread creation failed, exit the process
		}
	}

	for(int i=0;i<threads_count;i++)
	{
		pthread_join(thread_ids[i], NULL);
	}

	int total_occurrences = 0;

	for(int i=0;i<threads_count;i++)
	{
		total_occurrences += tasks[i].Occurrence_Count;
	}

	cout << endl << "RESULTS:---> " << tasks[0].SearchItem << " occurred in the array "<< total_occurrences << " times."<< endl;

	return;
}

int main(int argc, char *argv[])
{
	cout << endl << "DESCRIPTION: This program takes the threads count and search space size parameters given on the command line. It generates a random search space, a random number to search, divides the search space into problem chunks, searches chunks via threads, and consolidates and prints the number of times the random search number occurred in the random search space."<<endl <<endl;

	//Command Line parameters
	int threads_count = 0; //number of threads to create
	int searchspace_size = 0; //size of array to search in

	if(argc>1)
		threads_count = atoi(argv[1]);
	if(argc>2)
		searchspace_size = atoi(argv[2]);

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

	SearchTask * search_tasks = GetRandomSearchTasks(threads_count, searchspace_size); //Get a random search problem in chunks
 
	LeadSearch(search_tasks, threads_count); //This will perform the search on each chunk in an individual thread and accumulate and print the result

	pthread_exit(NULL);
}
