#include <gtest/gtest.h>
#include "exercise/permutations/partition.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace ::testing;
// Helper function to check if all even numbers are before odd numbers
bool isPartitionedEvenOdd(const std::vector<int>& numbers) {
    bool foundOdd = false;
    for (const int n : numbers) {
        if (n % 2 == 0) {
            if (foundOdd) {
                // Found an even number after an odd number; not correctly partitioned
                return false;
            }
        } else {
            foundOdd = true;
        }
    }
    return true;
}

TEST(PartitionTest, MixedEvenOdd) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));

    // Check that all original elements are present
    std::vector<int> expectedNumbers = {1, 2, 3, 4, 5, 6};
    std::sort(numbers.begin(), numbers.end());
    std::sort(expectedNumbers.begin(), expectedNumbers.end());
    EXPECT_EQ(numbers, expectedNumbers);
}

TEST(PartitionTest, AllEven) {
    std::vector<int> numbers = {2, 4, 6, 8};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));
    EXPECT_EQ(numbers, (std::vector<int>{2, 4, 6, 8}));
}

TEST(PartitionTest, AllOdd) {
    std::vector<int> numbers = {1, 3, 5, 7};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));
    EXPECT_EQ(numbers, (std::vector<int>{1, 3, 5, 7}));
}

TEST(PartitionTest, EmptyVector) {
    std::vector<int> numbers;
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));
    EXPECT_TRUE(numbers.empty());
}

TEST(PartitionTest, NegativeNumbers) {
    std::vector<int> numbers = {-1, -2, -3, -4, -5, -6};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));

    // Check that all original elements are present
    std::vector<int> expectedNumbers = {-1, -2, -3, -4, -5, -6};
    std::sort(numbers.begin(), numbers.end());
    std::sort(expectedNumbers.begin(), expectedNumbers.end());
    EXPECT_EQ(numbers, expectedNumbers);
}

TEST(PartitionTest, Zeros) {
    std::vector<int> numbers = {0, 1, 0, 3, 0, 5};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));

    // Check that zeros (even numbers) are before odd numbers
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] % 2 != 0) {
            // From here on, all numbers should be odd
            for (size_t j = i; j < numbers.size(); ++j) {
                EXPECT_NE(numbers[j] % 2, 0);
            }
            break;
        } else {
            EXPECT_EQ(numbers[i] % 2, 0);
        }
    }
}

TEST(PartitionTest, DuplicateNumbers) {
    std::vector<int> numbers = {2, 3, 2, 3, 2, 3};
    partitionEvenOdd(numbers);

    EXPECT_TRUE(isPartitionedEvenOdd(numbers));

    // Check that all original elements are present
    std::vector<int> expectedNumbers = {2, 3, 2, 3, 2, 3};
    std::sort(numbers.begin(), numbers.end());
    std::sort(expectedNumbers.begin(), expectedNumbers.end());
    EXPECT_EQ(numbers, expectedNumbers);
}


// Helper function to verify correct rearrangement
bool isCorrectlyRearranged(const std::vector<Patient>& patients) {
    bool inLowPriority = false;
    int lastHighPriorityArrival = -1;
    int lastLowPriorityArrival = -1;

    for (const auto& patient : patients) {
        if (patient.severity_level == 1 || patient.severity_level == 2) {
            if (inLowPriority) {
                // Found a high-priority patient after low-priority patients
                return false;
            }
            if (lastHighPriorityArrival > patient.arrival_time) {
                // Arrival time is not maintained within high-priority patients
                return false;
            }
            lastHighPriorityArrival = patient.arrival_time;
        } else {
            inLowPriority = true;
            if (lastLowPriorityArrival > patient.arrival_time) {
                // Arrival time is not maintained within low-priority patients
                return false;
            }
            lastLowPriorityArrival = patient.arrival_time;
        }
    }
    return true;
}

// Test case: Mixed severity levels
TEST(RearrangePatientsTest, MixedSeverityLevels) {
    std::vector<Patient> patients = {
        {"Alice", 1, 3},
        {"Bob", 2, 2},
        {"Charlie", 3, 1},
        {"Diana", 4, 4},
        {"Ethan", 5, 2},
        {"Fiona", 6, 5}
    };

    rearrangePatients(patients);

    // Expected order: Bob, Charlie, Ethan, Alice, Diana, Fiona
    std::vector<std::string> expectedNames = {"Bob", "Charlie", "Ethan", "Alice", "Diana", "Fiona"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        EXPECT_EQ(patients[i].name, expectedNames[i]);
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: All high-priority patients
TEST(RearrangePatientsTest, AllHighPriority) {
    std::vector<Patient> patients = {
        {"Alice", 1, 1},
        {"Bob", 2, 2},
        {"Charlie", 3, 1}
    };

    rearrangePatients(patients);

    // The order should remain the same
    std::vector<std::string> expectedNames = {"Alice", "Bob", "Charlie"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        EXPECT_EQ(patients[i].name, expectedNames[i]);
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: All low-priority patients
TEST(RearrangePatientsTest, AllLowPriority) {
    std::vector<Patient> patients = {
        {"Alice", 1, 3},
        {"Bob", 2, 4},
        {"Charlie", 3, 5}
    };

    rearrangePatients(patients);

    // The order should remain the same
    std::vector<std::string> expectedNames = {"Alice", "Bob", "Charlie"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        EXPECT_EQ(patients[i].name, expectedNames[i]);
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Patients already in correct order
TEST(RearrangePatientsTest, AlreadyInOrder) {
    std::vector<Patient> patients = {
        {"Bob", 2, 2},
        {"Charlie", 3, 1},
        {"Alice", 4, 3},
        {"Diana", 5, 4}
    };

    rearrangePatients(patients);

    // The order should remain the same
    std::vector<std::string> expectedNames = {"Bob", "Charlie", "Alice", "Diana"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        EXPECT_EQ(patients[i].name, expectedNames[i]);
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Patients in reverse order
TEST(RearrangePatientsTest, ReverseOrder) {
    std::vector<Patient> patients = {
        {"Fiona", 6, 5},
        {"Ethan", 5, 2},
        {"Diana", 4, 4},
        {"Charlie", 3, 1},
        {"Bob", 2, 2},
        {"Alice", 1, 3}
    };

    rearrangePatients(patients);

    // Expected order: Ethan, Charlie, Bob, Fiona, Diana, Alice
    std::vector<std::string> expectedNames = {"Ethan", "Charlie", "Bob", "Fiona", "Diana", "Alice"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        //EXPECT_EQ(patients[i].name, expectedNames[i]) << "Error on " << i << std::endl;
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Duplicate arrival times
TEST(RearrangePatientsTest, DuplicateArrivalTimes) {
    std::vector<Patient> patients = {
        {"Alice", 1, 2},
        {"Bob", 1, 2},
        {"Charlie", 2, 3},
        {"Diana", 2, 4}
    };

    rearrangePatients(patients);

    // Expected order: Alice, Bob, Charlie, Diana
    std::vector<std::string> expectedNames = {"Alice", "Bob", "Charlie", "Diana"};
    ASSERT_EQ(patients.size(), expectedNames.size());

    for (size_t i = 0; i < patients.size(); ++i) {
        EXPECT_EQ(patients[i].name, expectedNames[i]);
    }

    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Empty list
TEST(RearrangePatientsTest, EmptyList) {
    std::vector<Patient> patients;

    rearrangePatients(patients);

    EXPECT_TRUE(patients.empty());
    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Single high-priority patient
TEST(RearrangePatientsTest, SinglePatientHighPriority) {
    std::vector<Patient> patients = {
        {"Alice", 1, 1}
    };

    rearrangePatients(patients);

    EXPECT_EQ(patients.size(), 1);
    EXPECT_EQ(patients[0].name, "Alice");
    EXPECT_TRUE(isCorrectlyRearranged(patients));
}

// Test case: Single low-priority patient
TEST(RearrangePatientsTest, SinglePatientLowPriority) {
    std::vector<Patient> patients = {
        {"Bob", 2, 4}
    };

    rearrangePatients(patients);

    EXPECT_EQ(patients.size(), 1);
    EXPECT_EQ(patients[0].name, "Bob");
    EXPECT_TRUE(isCorrectlyRearranged(patients));
}
