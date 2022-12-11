#include "command.h"
#include <iostream>

#define HLINE "---------------------------------------------\n"
#define TSTART std::cout << "Grep: " << __func__ << " started\n" << HLINE; int ans;
#define TEND do { \
    std::cout << HLINE "Grep: " << __func__ << " finished " << (ans == 0 ? "SUCCESSFULLY" : "WITH ERROR") << "\n\n"; \
    return ans; \
} while(false)

#define FAIL(error) do { \
    ans = 1; std::cout << "Error: " << error << "\n"; TEND; \
} while(false)

#define OK do { \
    ans = 0; \
    TEND; \
} while(false)

#define TEQUAL(testVal, trueVal) if (testVal != trueVal) \
    FAIL("Incorrect resutl, test value: \n'''\n" + testVal + "\n'''\nshould be equal to:\n'''\n" + trueVal + "\n'''")

int BasicTest();

int WordModeTest();
int LinesAfterTest();
int CaseSensitivityTest();
int MultiflagTest();
int BadFlagTest();

int PipeTest();
int ManyArgsTest();
int ManyFoundTest();
int RegexTest();
int BadUsageTest();

typedef int (*Test)(void);

int main() {
    Test tests[] = {
        BasicTest,
        WordModeTest,
        LinesAfterTest,
        CaseSensitivityTest,
        MultiflagTest,
        BadFlagTest,
        PipeTest,
        ManyArgsTest,
        ManyFoundTest,
        RegexTest,
        BadUsageTest
    };
    
    int allGood = 0;
    for (Test test : tests) {
        allGood += test();
        if (allGood != 0) break;
    }
    
    return allGood;
}

int BasicTest() {
    TSTART;
    
    std::vector<std::string> args = {"some", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "some code some some code code\n");
    
    OK;
}

int WordModeTest() {
    TSTART;
    
    std::vector<std::string> args = {"so", "-w", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "");
    
    args = {"some", "-w", "testInput.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "some code some some code code\n");
    
    OK;
}

int LinesAfterTest() {
    TSTART;
    
    std::vector<std::string> args = {"more", "-A", "1" ,"testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "more words more words\n"
           "there will be a leading space in this line here -->\n");
    
    args = {"more", "-A", "0" ,"testInput.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "more words more words\n");
    
    OK;
}

int CaseSensitivityTest() {
    TSTART;
    
    std::vector<std::string> args = {"WILL", "-i", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "there will be a leading space in this line here -->\n");
    
    args = {"WILL", "testInput.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "");
    
    OK;
}

int MultiflagTest() {
    TSTART;
    
    std::vector<std::string> args = {"just", "-i", "-A", "1", "-w", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    
    TEQUAL(res.unwrap(),
           "Not it wOn't be huh my ide JusT won't let me make it that easily\n"
           "'' is this CouNts as words?\n");
    
    args = {"won", "-iwA", "0", "testInput.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "Not it wOn't be huh my ide JusT won't let me make it that easily\n");
    
    OK;
}

int BadFlagTest() {
    TSTART;
    
    std::vector<std::string> args = {"just", "-i", "-A", "-1", "-w", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "Number of lines must be a non-negative number, got: -1");
    
    args = {"won", "-iB", "testInput.txt"};
    res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "Unknown flag: B");
    
    OK;
}

int PipeTest() {
    TSTART;
    
    std::string input =
    "soem\n"
    "some more\n"
    "and also a LITTLE more\n"
    "a little mooooore\n";
    
    std::vector<std::string> args = {"a little", "-i", "testInput.txt"};
    Grep cmd;
    Result res = cmd.execute(args, input);
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), ""); // if args are given, should ignore the input
    
    args = {"a little", "-i"};
    res = cmd.execute(args, input);
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "and also a LITTLE more\n"
           "a little mooooore\n");
    
    OK;
}

int ManyArgsTest() {
    TSTART;
    
    std::vector<std::string> args = {"there", "-i", "testInput.txt", "testInput3.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "testInput.txt: there will be a leading space in this line here -->\n"
           "--\n"
           "testInput3.txt: \"Like us, there is more to them than meets the eye\" -- Optimus Prime\n"
           "testInput3.txt: si erehthere is\n"
           "testInput3.txt: There was a farmer who had a dog,\n"
           "testInput3.txt: There is a farmer who has a dog,\n"
           "testInput3.txt: There is, in fact, a farmer who has a dog,\n");
    
    args = {"there will", "testInput.txt", "testInput3.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(), "testInput.txt: there will be a leading space in this line here -->\n");
    
    args = {"there", "-wiA", "1", "testInput.txt", "testInput3.txt"};
    res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "testInput.txt: there will be a leading space in this line here -->\n"
           "testInput.txt- Not it wOn't be huh my ide JusT won't let me make it that easily\n"
           "--\n"
           "testInput3.txt: \"Like us, there is more to them than meets the eye\" -- Optimus Prime\n"
           "testInput3.txt- #¡ /bin/bash\n"
           "testInput3.txt: There was a farmer who had a dog,\n"
           "testInput3.txt- And Bingo was his name-o.\n"
           "testInput3.txt: There is a farmer who has a dog,\n"
           "testInput3.txt- And Bingo is his name-o.\n"
           "testInput3.txt: There is, in fact, a farmer who has a dog,\n"
           "testInput3.txt- And Bingo is his name-o.\n"
           );
    
    OK;
}

int ManyFoundTest() {
    TSTART;
    
    std::vector<std::string> args = {"\\-N\\-", "-A", "1", "testInput3.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "B-I-N-G-O\n"
           "B-I-N-G-O\n"
           "And Bingo was his name-o.\n"
           "B-I-N-G-O\n"
           "B-I-N-G-O\n"
           "And Bingo is his name-o.\n"
           "(clap)-I-N-G-O\n"
           "(clap)-I-N-G-O\n"
           "And Bingo is his name-o.\n"
           "(clap)-(clap)-N-G-O\n"
           "(clap)-(clap)-N-G-O\n"
           "And Bingo is his name-o.\n"
           );
    
    args = {"th", "-iA", "100", "testInput.txt"};
    res = cmd.execute(args, "");

    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "there will be a leading space in this line here -->\n"
           "Not it wOn't be huh my ide JusT won't let me make it that easily\n"
           "'' is this CouNts as words?\n"
           "\n");
    
    OK;
}

int RegexTest() {
    TSTART;
    
    std::vector<std::string> args = {"[\'\"].*[\'\"]", "testInput.txt", "testInput3.txt"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (!res.isOk()) FAIL(res.unwrap());
    TEQUAL(res.unwrap(),
           "testInput.txt: Not it wOn't be huh my ide JusT won't let me make it that easily\n"
           "testInput.txt: '' is this CouNts as words?\n"
           "--\n"
           "testInput3.txt: \"Like us, there is more to them than meets the eye\" -- Optimus Prime\n");
    
    OK;
}

int BadUsageTest() {
    TSTART;
    
    std::vector<std::string> args = {"tralala", "-i", "-A", "10"};
    Grep cmd;
    Result res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "Not enough arguments");
    
    args = {"obama's password", "pentagon-secret-codes.txt"};
    res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "pentagon-secret-codes.txt: No such file or directory");
    
    args = {"grepAll.cpp", "./"};
    res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "./ is a directory");
    
    args = {"some", "-A", "-i", "testInput.txt"};
    res = cmd.execute(args, "");
    
    if (res.isOk()) FAIL("Was supposed to return an error, but instead got: " + res.unwrap());
    TEQUAL(res.unwrap(), "Unknown flag: A");
    
    OK;
}
