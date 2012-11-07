#include "MockCache.h"

#define OOOClass MockCache

typedef struct _Entry Entry;
struct _Entry
{
	char * szName;
	unsigned char * pData;
	size_t uSize;
	Entry * pNext;
};

OOOPrivateData
	Entry * pEntries;
OOOPrivateDataEnd

OOODestructor
{
	Entry * pEntry = OOOF(pEntries);
	Entry * pLast = NULL;
	while (pEntry)
	{
		pLast = pEntry;
		pEntry = pEntry->pNext;
		O_free(pLast->szName);
		O_free(pLast->pData);
		O_free(pLast);
	}
}
OOODestructorEnd

OOOMethod(void, set, char * szName, unsigned char * pData, size_t uSize)
{
	Entry * pEntry = OOOF(pEntries);

	if (pData == NULL)
	{
		/* Delete */
		Entry * pLast = NULL;
		while (pEntry)
		{
			if (O_strcmp(pEntry->szName, szName) == 0)
			{
				if (pLast)
				{
					pLast->pNext = pEntry->pNext;
				}
				else
				{
					OOOF(pEntries) = pEntry->pNext;
				}
				O_free(pEntry->szName);
				O_free(pEntry->pData);
				O_free(pEntry);
				break;
			}
			pLast = pEntry;
			pEntry = pEntry->pNext;
		}
	}
	else
	{
		/* Set */
		while (pEntry)
		{
			if (O_strcmp(pEntry->szName, szName) == 0)
			{
				break;
			}
			pEntry = pEntry->pNext;
		}

		if (!pEntry)
		{
			/* Add */
			pEntry = O_malloc(sizeof(Entry));
			pEntry->pNext = OOOF(pEntries);
			OOOF(pEntries) = pEntry;
			pEntry->szName = O_strdup(szName);
			pEntry->pData = NULL;
			pEntry->uSize = 0;
		}

		if (pEntry->pData)
		{
			O_free(pEntry->pData);
		}

		pEntry->pData = O_calloc(uSize, sizeof(unsigned char));
		O_memcpy(pEntry->pData, pData, uSize);
		pEntry->uSize = uSize;
	}
}
OOOMethodEnd

OOOMethod(void, get, char * szName, unsigned char ** ppData, size_t * pSize)
{
	Entry * pEntry = OOOF(pEntries);
	*ppData = NULL;
	*pSize = 0;
	while (pEntry)
	{
		if (O_strcmp(pEntry->szName, szName) == 0)
		{
			*pSize = pEntry->uSize;
			*ppData = O_calloc(pEntry->uSize, sizeof(unsigned char));
			O_memcpy(*ppData, pEntry->pData, pEntry->uSize);
			break;
		}
		pEntry = pEntry->pNext;
	}
}
OOOMethodEnd

OOOConstructor()
{
#define OOOInterface OOOICache
	OOOMapVirtuals
		OOOMapVirtual(set)
		OOOMapVirtual(get)
	OOOMapVirtualsEnd
#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
