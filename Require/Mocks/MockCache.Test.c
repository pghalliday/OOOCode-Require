#include "OOOUnitTestDefines.h"
#include "MockCache.h"

static char * szHelloWorld = "Hello, world!";
static char * szGoodbyeWorld = "Goodbye, world!";
static char * szApple = "Apple";
static char * szBanana = "Banana";
static char * szPear = "Pear";

OOOTest(MockCache)
{
	char * szBuffer;
	size_t uSize;
	MockCache * pMockCache = OOOConstruct(MockCache);
	OOOICache * iCache = OOOCast(OOOICache, pMockCache);

	/* Should be able to set and get cached data by name */
	OOOICall(iCache, set, "HelloWorld", (unsigned char *) szHelloWorld, O_strlen(szHelloWorld) + 1);
	OOOICall(iCache, set, "GoodbyeWorld", (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);
	OOOICall(iCache, set, "Apple", (unsigned char *) szApple, O_strlen(szApple) + 1);
	OOOICall(iCache, set, "Banana", (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	OOOICall(iCache, set, "Pear", (unsigned char *) szPear, O_strlen(szPear) + 1);

	OOOICall(iCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szHelloWorld) == 0);
	OOOCheck(uSize == O_strlen(szHelloWorld) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szGoodbyeWorld) == 0);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szApple) == 0);
	OOOCheck(uSize == O_strlen(szApple) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szBanana) == 0);
	OOOCheck(uSize == O_strlen(szBanana) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szPear) == 0);
	OOOCheck(uSize == O_strlen(szPear) + 1);
	O_free(szBuffer);

	/* Should be able to overwrite entries in the cache */
	OOOICall(iCache, set, "Apple", (unsigned char *) szBanana, O_strlen(szBanana) + 1);
	OOOICall(iCache, set, "Pear", (unsigned char *) szGoodbyeWorld, O_strlen(szGoodbyeWorld) + 1);

	OOOICall(iCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szHelloWorld) == 0);
	OOOCheck(uSize == O_strlen(szHelloWorld) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szGoodbyeWorld) == 0);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szBanana) == 0);
	OOOCheck(uSize == O_strlen(szBanana) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szBanana) == 0);
	OOOCheck(uSize == O_strlen(szBanana) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szGoodbyeWorld) == 0);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);
	O_free(szBuffer);

	/* Should return NULL when entry is not in the cache */
	OOOICall(iCache, get, "Nothing", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	/* Should be possible to delete an entry from the cache by passing in NULL */
	OOOICall(iCache, set, "HelloWorld", NULL, 0);
	OOOICall(iCache, set, "Banana", NULL, 0);

	OOOICall(iCache, get, "HelloWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	OOOICall(iCache, get, "GoodbyeWorld", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szGoodbyeWorld) == 0);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Apple", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szBanana) == 0);
	OOOCheck(uSize == O_strlen(szBanana) + 1);
	O_free(szBuffer);

	OOOICall(iCache, get, "Banana", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(szBuffer == NULL);
	OOOCheck(uSize == 0);

	OOOICall(iCache, get, "Pear", (unsigned char **) &szBuffer, &uSize);
	OOOCheck(O_strcmp(szBuffer, szGoodbyeWorld) == 0);
	OOOCheck(uSize == O_strlen(szGoodbyeWorld) + 1);
	O_free(szBuffer);

	OOODestroy(pMockCache);
}
