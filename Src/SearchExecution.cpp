#include "SearchProblemSetup.cpp"

void* SearchChunk(void* searchtask)
{
	SearchTask task = *((SearchTask*) searchtask); //convert search task pointer to search task object

	int * Data = task.Data;
	long Size = task.Size;
	int SearchItem = task.SearchItem;

	long count = 0; //how many times search item occurs in the data chunk

	for(int i = 0; i < Size; i ++)
	{
		if(Data[i] == SearchItem)
			count ++;
	}

	((SearchTask*) searchtask)->Occurrence_Count = count; //set the result of this chunk before exiting thread

	pthread_exit(NULL);
}

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

	long total_occurrences = 0;

	for(int i=0;i<threads_count;i++)
	{
		total_occurrences += tasks[i].Occurrence_Count;
	}

	cout << endl << "RESULTS:---> " << tasks[0].SearchItem << " occurred in the array "<< total_occurrences << " times."<< endl;

	return;
}

