/*******************************************************************************
* 
* FILENAME : tests.c
*
* DESCRIPTION : Source file containing test functions
*
* AUTHOR : filipang 
* 
* START DATE :		13/12/2021
*
*******************************************************************************/

int testCreateFullEntityList()
{
	printf("Creating as many entities as possible...\n");
	int i = 0;
	while(creatureCreate() != -1)
	{
		i++;
	}
	printf("Stopped at %d creatures because we ran out of memory. \n", i);
	return i;
}

int testCreateFullMapList()
{
	printf("Creating as many maps as possible...\n");
	int i = 0;
	while(mapCreate() != -1)
	{
		i++;
	}
	printf("Stopped at %d maps because we ran out of memory. \n", i);
	return i;
}

void testDeleteCreatureList(int n)
{
	printf("Deleting %d creatures...\n", n);
	for(int i = 0; i < n; i++)
	{
		creatureDelete(i);
	}
	printf("Success!\n");
}

void testDeleteMapList(int n)
{
	printf("Deleting %d maps...\n", n);
	for(int i = 0; i < n; i++)
	{
		mapDelete(i);
	}
	printf("Success!\n");
}

void testBatch1()
{
	testDeleteCreatureList(testCreateFullCreatureList());
	testDeleteItemList(testCreateFullItemList());
	testDeleteActiveList(testCreateFullActiveList());
	testDeleteMapList(testCreateFullMapList());
}
