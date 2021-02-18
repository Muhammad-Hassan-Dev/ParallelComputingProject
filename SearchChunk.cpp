void* SearchChunk(void* searchtask)
{	
	SearchTask task = *((SearchTask*) searchtask); //convert search task pointer to search task object

	int * Data = task.Data;
	int Size = task.Size;
	int SearchItem = task.SearchItem;

	int count = 0; //how many times search item occurs in the data chunk

	for(int i = 0; i < Size; i ++)
	{
		if(Data[i] == SearchItem)
			count ++;
	}

	((SearchTask*) searchtask)->Occurrence_Count = count; //set the result of this chunk before exiting thread

	pthread_exit(NULL);
}
