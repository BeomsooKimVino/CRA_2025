#include "assemble.h"

#include <gmock/gmock.h>
#include <utility>
#include <vector>
#include <unordered_map>

using pii = std::pair<int, int>;

std::vector<QuestionType> qtype = {
	QuestionType::CarType_Q,
	QuestionType::Engine_Q,
	QuestionType::brakeSystem_Q,
	QuestionType::SteeringSystem_Q,
	QuestionType::Run_Test
};

std::unordered_map<QuestionType, pii> validRangeMenu = {
	{QuestionType::CarType_Q, {1, 3}},
	{QuestionType::Engine_Q, {0, 4}},
	{QuestionType::brakeSystem_Q, {0, 3}},
	{QuestionType::SteeringSystem_Q, {0, 2}},
	{QuestionType::Run_Test, {0, 2}}
};

TEST(TestCaseInputVaidation, TestInputInvalidNonDigit)
{
	char* input = (char*)"a";
	int answer = 0;

	for (QuestionType step : qtype)
	{
		InputValidationResult expected = InputValidationResult::Invalid;
		InputValidationResult actual = InputVaildation(input, step, answer);
		EXPECT_EQ(actual, expected);
	}
}

TEST(TestCaseInputVaidation, TestInputInvalidDigit)
{
	char input[10];
	int answer = 0;

	for (QuestionType step : qtype)
	{
		QuestionType varstep = QuestionType::CarType_Q;
		InputValidationResult expected = InputValidationResult::Invalid;
		InputValidationResult actual = InputValidationResult::Valid;
		int validStart = validRangeMenu[step].first - 1;
		int validEnd = validRangeMenu[step].second + 1;

		varstep = step;
		sprintf_s(input, "%d", validStart);
		if(step >= QuestionType::Engine_Q)
			expected = InputValidationResult::Invalid;
		actual = InputVaildation(input, varstep, answer);
		EXPECT_EQ(actual, expected);

		varstep = step;
		sprintf_s(input, "%d", validEnd);
		expected = InputValidationResult::Invalid;
		actual = InputVaildation(input, varstep, answer);
		EXPECT_EQ(actual, expected);
	}
}

TEST(TestCaseInputVaidation, TestInputValidDigit)
{
	char input[10];
	int answer = 0;

	for (QuestionType step : qtype)
	{
		InputValidationResult expected = InputValidationResult::Valid;
		InputValidationResult actual = InputValidationResult::Valid;
		int validStart = validRangeMenu[step].first;
		int validEnd = validRangeMenu[step].second;

		sprintf_s(input, "%d", validStart);
		actual = InputVaildation(input, step, answer);
		EXPECT_EQ(actual, expected);

		sprintf_s(input, "%d", validEnd);
		actual = InputVaildation(input, step, answer);
		EXPECT_EQ(actual, expected);
	}
}

TEST(TestCaseInputVaidation, TestInputTransitionBackward)
{
	char input[10];
	int answer = 0;

	for (QuestionType step : qtype)
	{
		InputValidationResult expected = InputValidationResult::Valid;
		InputValidationResult actual = InputValidationResult::Valid;
		int validStart = validRangeMenu[step].first;
		int validEnd = validRangeMenu[step].second;

		sprintf_s(input, "%d", validStart);
		actual = InputVaildation(input, step, answer);
		EXPECT_EQ(actual, expected);

		sprintf_s(input, "%d", validEnd);
		actual = InputVaildation(input, step, answer);
		EXPECT_EQ(actual, expected);
	}
}