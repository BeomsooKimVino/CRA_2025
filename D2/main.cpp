#include <gmock/gmock.h>

#ifdef _DEBUG
int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#elif NDEBUG
#include "assemble.h"
int main()
{
	return run_assemble();
}
#endif