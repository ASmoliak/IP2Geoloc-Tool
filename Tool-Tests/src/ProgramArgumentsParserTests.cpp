#include "pch.h"
#include "../IP2Geoloc/include/ProgramArgumentsParser.h"

constexpr auto VALID_TARGET_IP = "8.8.8.8";
constexpr auto PROGARM_PATH = "C:\\Users\\Luka\\source\\repos\\IP2Geoloc Tool\\bin\\Unit Testing\\IP2Geoloc.exe";
constexpr auto IP_ARGUMENT = "--ip";
constexpr auto SELF_RESOLVE_ARGUMENT = "--self";
constexpr auto HELP_ARGUMENT = "--help";

TEST(ProgramArgumentsParser_Tests, IPv4_Result_Validity)
{
	const char *valid_resolve_arguments[] = { PROGARM_PATH, IP_ARGUMENT, VALID_TARGET_IP };
	int valid_argument_count = 3;

	ProgramArgumentsParser parser(valid_argument_count, valid_resolve_arguments);
	Settings result = parser.getParsedSettings();

	bool areValuesEqual = !strcmp(VALID_TARGET_IP, result.IPv4_to_scan.c_str());
	EXPECT_TRUE(areValuesEqual) << "The input IP argument is not the same as the parsed IP in Settings";
}

TEST(ProgramArgumentsParser_Tests, Bad_Argument_Count)
{
	const char *valid_resolve_arguments[] = { PROGARM_PATH, IP_ARGUMENT, VALID_TARGET_IP };
	int invalid_argument_count = 2;

	EXPECT_ANY_THROW(ProgramArgumentsParser(invalid_argument_count, valid_resolve_arguments))
		<< "Our code did not throw an exception on invalid argument count";
}

TEST(ProgramArgumentsParser_Tests, Self_Result_Validity)
{
	const char *valid_resolve_arguments[] = { PROGARM_PATH, SELF_RESOLVE_ARGUMENT };
	int valid_argument_count = 2;

	ProgramArgumentsParser parser(valid_argument_count, valid_resolve_arguments);
	Settings result = parser.getParsedSettings();

	EXPECT_TRUE(result.resolve_self) << "The settings struct's resolve self boolean was not set to true on correct input";
}

TEST(ProgramArgumentsParser_Tests, Conflicting_Option_Detection)
{
	const char *conflicting_arguments1[] = { PROGARM_PATH, SELF_RESOLVE_ARGUMENT, IP_ARGUMENT };
	const char *conflicting_arguments2[] = { PROGARM_PATH, SELF_RESOLVE_ARGUMENT, HELP_ARGUMENT };
	const char *conflicting_arguments3[] = { PROGARM_PATH, IP_ARGUMENT,  SELF_RESOLVE_ARGUMENT };
	const char *conflicting_arguments4[] = { PROGARM_PATH, IP_ARGUMENT, HELP_ARGUMENT };
	const char *conflicting_arguments5[] = { PROGARM_PATH, HELP_ARGUMENT, IP_ARGUMENT };
	const char *conflicting_arguments6[] = { PROGARM_PATH, HELP_ARGUMENT, SELF_RESOLVE_ARGUMENT };
	int three_arguments = 3;
	const char *conflicting_arguments7[] = { PROGARM_PATH, HELP_ARGUMENT, SELF_RESOLVE_ARGUMENT, IP_ARGUMENT };
	const char *conflicting_arguments8[] = { PROGARM_PATH, HELP_ARGUMENT, IP_ARGUMENT, SELF_RESOLVE_ARGUMENT };
	const char *conflicting_arguments9[] = { PROGARM_PATH, IP_ARGUMENT, SELF_RESOLVE_ARGUMENT, HELP_ARGUMENT };
	const char *conflicting_arguments10[] = { PROGARM_PATH, IP_ARGUMENT, HELP_ARGUMENT, SELF_RESOLVE_ARGUMENT };
	const char *conflicting_arguments11[] = { PROGARM_PATH, SELF_RESOLVE_ARGUMENT, HELP_ARGUMENT, IP_ARGUMENT };
	const char *conflicting_arguments12[] = { PROGARM_PATH, SELF_RESOLVE_ARGUMENT, IP_ARGUMENT, HELP_ARGUMENT };
	int four_arguments = 4;

	std::string error_string = "The argument parser did not throw on conflicting arguments";
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments1)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments2)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments3)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments4)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments5)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(three_arguments, conflicting_arguments6)) << error_string;

	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments7)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments8)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments9)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments10)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments11)) << error_string;
	EXPECT_ANY_THROW(ProgramArgumentsParser(four_arguments, conflicting_arguments12)) << error_string;
}

