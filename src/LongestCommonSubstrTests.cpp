#include "suffixTree.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using testing::Test;

/*
 * Test class for generalized suffix tree. In this test, the input strings are
 * "aba" and "ba". The first string is ended by "$" and the second string is
 * ended by "#".
 */

class GeneralizedSuffixTree: public Test {
    public:
        suffixTree tree;
        std::string s1;
        std::string s2;
        std::string input;
        int firstLength;
        int secondLength;

        virtual void SetUp(){
            s1 = "aba";
            s2 = "ba";
            input = s1 + "$" + s2 + "#";

            firstLength = s1.length();
            secondLength = s2.length();

            tree = suffixTree(0, 0, -1);
            tree.Input = input;
            tree.inputLength = input.length() - 1;
            tree.nodeArray.resize(2*(tree.inputLength));
            tree.noOfNodes = 1;

            for (int i = 0; i <= tree.inputLength; i++){
                tree.carryPhase(tree, i, firstLength, secondLength);
            }
            //tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);
        }

        virtual void TearDown(){
            tree.clearTree();
        }
};

/*
 * This test searches all possible substrings of the two input strings and
 * confirms they exist somewhere in the tree.
 */
TEST_F(GeneralizedSuffixTree, subStringSearchTest){
    std::vector<string> subStrings = {"aba", "ba", "a", "ab", "b"};
    //tree.printAllEdges();
    for (auto s : subStrings) {
        EXPECT_EQ(tree.search(s), true);
    }
}

TEST_F(GeneralizedSuffixTree, linkNodesTest){
    // TODO Think of a way to test this.
}

/*
 * This test compare all node depth set by setDepth() fucntion to their expected
 * values, make sure the depths are correctly assigned.
 */
TEST_F(GeneralizedSuffixTree, setDepthTest){
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();
    tree.setDepth(&(tree.nodeArray[0]));

    EXPECT_EQ(tree.nodeArray[0].depth, 0);
    EXPECT_EQ(tree.nodeArray[1].depth, 0);
    EXPECT_EQ(tree.nodeArray[2].depth, 0);
    EXPECT_EQ(tree.nodeArray[3].depth, 1);
    EXPECT_EQ(tree.nodeArray[4].depth, 0);
    EXPECT_EQ(tree.nodeArray[5].depth, 0);
    EXPECT_EQ(tree.nodeArray[6].depth, 2);
    EXPECT_EQ(tree.nodeArray[7].depth, 0);
    EXPECT_EQ(tree.nodeArray[8].depth, 0);
    EXPECT_EQ(tree.nodeArray[9].depth, 0);
}

/*
 * This test compares the strings labels assigned by collectLabel() funciton to their
 * expected values. Compares both C(v) values and the actual label for leaf nodes.
 */
TEST_F(GeneralizedSuffixTree, collectLabelTest){
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();
    tree.collectLabel(&(tree.nodeArray[0]));

    std::vector<Node> nodeArray = tree.nodeArray;

    EXPECT_EQ(tree.nodeArray[0].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[1].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[2].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[3].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[4].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[5].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[6].getCv(), 2);
    EXPECT_EQ(tree.nodeArray[7].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[8].getCv(), 1);
    EXPECT_EQ(tree.nodeArray[9].getCv(), 1);

    EXPECT_EQ(tree.nodeArray[1].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[2].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[4].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[5].stringLabels[0], 1);
    EXPECT_EQ(tree.nodeArray[7].stringLabels[0], 2);
    EXPECT_EQ(tree.nodeArray[8].stringLabels[0], 2);
    EXPECT_EQ(tree.nodeArray[9].stringLabels[0], 2);
}

/*
 * This test compares the strings returns by getString() function to their
 * expected values.
 */
TEST_F(GeneralizedSuffixTree, getStringTest) {
    ASSERT_GE(tree.nodeArray.size(), 0);
    tree.linkNodes();

    EXPECT_EQ(tree.getString(&tree.nodeArray[0]), "");
    EXPECT_EQ(tree.getString(&tree.nodeArray[1]), "aba$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[2]), "ba$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[3]), "a");
    EXPECT_EQ(tree.getString(&tree.nodeArray[4]), "a$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[5]), "$");
    EXPECT_EQ(tree.getString(&tree.nodeArray[6]), "ba");
    EXPECT_EQ(tree.getString(&tree.nodeArray[7]), "ba#");
    EXPECT_EQ(tree.getString(&tree.nodeArray[8]), "a#");
    EXPECT_EQ(tree.getString(&tree.nodeArray[9]), "#");
}

/*
 * This test confirms the findLongestCommonSubstr() function returns the actual
 * longest common substring of the two input strings
 */
TEST_F(GeneralizedSuffixTree, findLongestCommonSubstrTest) {
    tree.linkNodes();
    tree.collectLabel(&(tree.nodeArray[0]));
    tree.setDepth(&(tree.nodeArray[0]));

    EXPECT_EQ(tree.findLongestCommonSubstr(), "ba");
}

/*
 *
 */

TEST(LongestCommonSubstringTest, EmptyStringTest) {
    std::string s1 = "cadabd";
    std::string s2 = "";
    std::string input = "";
    std::string LCS = "";
    std::string result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();

    EXPECT_EQ(result.length(), maxLength);
    EXPECT_EQ(LCS.compare(result), 0);

    tree.clearTree();
}

/*
 *
 */

TEST(LongestCommonSubstringTest, SameStringTest) {
    std::string s1 = "cadabd";
    std::string s2 = s1;
    std::string input = "";
    std::string LCS = s1;
    std::string result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = s1.length();

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();

    EXPECT_EQ(result.length(), maxLength);
    EXPECT_EQ(LCS.compare(result), 0);

    tree.clearTree();
}

/*
 *
 */

TEST(LongestCommonSubstringTest, TestCase1) {
    std::string s1 = "cadabd";
    std::string s2 = "adadb";
    std::string input = "";
    std::string LCS;
    std::string result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);

    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();
    // O(m^2n^2) naive method of finding LCS
    for (int i = 0; i < firstLength; i++) {
        for (int j = i + 1; j < firstLength; j++) {
            auto substr = s1.substr(i, j - i);
            if (s2.find(substr) != std::string::npos){
                if (substr.length() > maxLength) {
                    maxLength = substr.length();
                    LCS = substr;
                }
            }
            else {

            }
        }
    }

    EXPECT_EQ(result.length(), maxLength);
    EXPECT_EQ(LCS.compare(result), 0);

    tree.clearTree();
}

/*
 *
 */
 // TODO This test fails, fix this.
TEST(LongestCommonSubstringTest, TestCase2) {
    std::string s1 = "fdsafd";
    std::string s2 = "afsdfadsffasfr";
    std::string input = "";
    std::string LCS;
    std::string result;

    suffixTree tree;
    int firstLength;
    int secondLength;
    int maxLength = 0;

    firstLength = s1.length();
    secondLength = s2.length();

    input = s1 + "$" + s2 + "#";

    tree = suffixTree(0, 0, -1);
    tree.buildGeneralizedSuffixTree(input, firstLength, secondLength);

    result = tree.findLongestCommonSubstr();
    // O(m^2n^2) naive method of finding LCS
    for (int i = 0; i < firstLength; i++) {
        for (int j = i + 1; j < firstLength; j++) {
            auto substr = s1.substr(i, j - i);
            if (s2.find(substr) != std::string::npos){
                if (substr.length() > maxLength) {
                    maxLength = substr.length();
                    LCS = substr;
                }
            }
            else {

            }
        }
    }

    EXPECT_EQ(result.length(), maxLength);
    //EXPECT_EQ(LCS.compare(result), 0) << "Found: " << result << " Expecting: " << LCS << std::endl;

    tree.clearTree();
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
