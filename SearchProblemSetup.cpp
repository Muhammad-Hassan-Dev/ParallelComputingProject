#include <iostream>
#include <stdlib.h>

using namespace std;

struct SearchTask //Used to send data chunk to thread
{
	int * Data;
	int Size;
	int SearchItem;
	int Occurrence_Count; //used to return result from thread
};

SearchTask* GetRandomSearchTasks(int threads_count, int searchspace_size)
{
	int chunk_size = searchspace_size / threads_count; //size of each subproblem except the last	

	//if searchspace_size is not a multiple of threads_count, then last thread (subproblem) must take the remaining numbers
	int last_chunk_size = (searchspace_size / threads_count) + (searchspace_size % threads_count);

	SearchTask * tasks = new SearchTask[threads_count]; //an array of search tasks i.e chunks of data to process in threads

	cout <<"Search Space Size = " << searchspace_size << endl;
	cout <<"Threads Count = " << threads_count << endl;
	cout <<"Subproblem size = " << chunk_size <<endl;
	if(last_chunk_size != chunk_size)
		cout << "Last subproblem size = " << last_chunk_size << endl;

	srand (time(NULL));
	int search_item = rand() % 10 + 1; //random search item

	cout <<"Random number to search in data array = " << search_item << endl;

	for(int i=0;i<threads_count-1;i++)
	{
		tasks[i].Data = new int[chunk_size];
		tasks[i].Size = chunk_size;
		tasks[i].SearchItem = search_item;

		srand (time(NULL));

		for(int j=0;j<chunk_size;j++)
			tasks[i].Data[j] = rand() % 10 + 1;		
	}

	tasks[threads_count-1].Data = new int[last_chunk_size];
	tasks[threads_count-1].Size = last_chunk_size;
	tasks[threads_count-1].SearchItem = search_item;

	srand (time(NULL));

	for(int j=0;j<last_chunk_size;j++)
		tasks[threads_count-1].Data[j] = rand() % 10 + 1;

	return tasks;
}
