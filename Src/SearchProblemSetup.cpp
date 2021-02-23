#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

struct SearchTask //Used to send data chunk to thread
{
	int * Data;
	long Size;
	int SearchItem;
	long Occurrence_Count; //used to return result from thread
};

void* CreateChunk(void* searchtask_new)
{	//function to initialize the new chunk of the array
	SearchTask newtask = *((SearchTask*) searchtask_new); //convert search task pointer to search task object

	int Size = newtask.Size;
	int SearchItem = newtask.SearchItem;

	for(int i = 0; i < Size; i ++)
	{
		newtask.Data[i] = rand() % (10*SearchItem); //the modulus operand (right) is as was given in the code provided
	}

	pthread_exit(NULL);
}

SearchTask* GetRandomSearchTasks(int threads_count, long searchspace_size, int search_item)
{
	long chunk_size = searchspace_size / ((long) threads_count); //size of each subproblem except the last	

	//if searchspace_size is not a multiple of threads_count, then last thread (subproblem) must take the remaining numbers
	long last_chunk_size = (searchspace_size / ((long)threads_count)) + (searchspace_size % ((long)threads_count));

	cout <<"Search Space Size = " << searchspace_size << endl;
	cout <<"Threads Count = " << threads_count << endl;
	cout <<"Subproblem size = " << chunk_size <<endl;
	if(last_chunk_size != chunk_size)
		cout << "Last subproblem size = " << last_chunk_size << endl;

	cout <<"Number to search in data array = " << search_item << endl;

	SearchTask * tasks = new SearchTask[threads_count]; //an array of search tasks i.e chunks of data to process in threads

	pthread_t * thread_ids = new pthread_t[threads_count];

	int * statuses = new int[threads_count];

	for(int i=0;i<threads_count-1;i++)
	{
		tasks[i].Size = chunk_size;
		tasks[i].SearchItem = search_item;
		tasks[i].Data = new int[tasks[i].Size]; //create array for this chunk	

		statuses[i] = pthread_create(&thread_ids[i], NULL, CreateChunk, (void*) &tasks[i]);

		if(statuses[i] != 0)
		{
			cout <<"pthread_create failed."<< endl;
			exit(-1); //if thread creation failed, exit the process
		}
	}

	tasks[threads_count-1].Size = last_chunk_size; //last thread is created separately because it could be larger or smaller than others
	tasks[threads_count-1].SearchItem = search_item;
	tasks[threads_count-1].Data = new int[tasks[threads_count-1].Size]; //create array for this chunk	
	statuses[threads_count-1] = pthread_create(&thread_ids[threads_count-1], NULL, CreateChunk, (void*) &tasks[threads_count-1]);

	if(statuses[threads_count-1] != 0)
	{
		cout <<"pthread_create failed."<< endl;
		exit(-1); //if thread creation failed, exit the process
	}		

	for(int i=0;i<threads_count;i++)
	{
		pthread_join(thread_ids[i], NULL);
	}

	return tasks;
}
