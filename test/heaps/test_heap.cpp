#include <gtest/gtest.h>
#include "exercise/heaps/event_scheduler.h"

// Test the event scheduler with the example provided in the exercise
TEST(EventSchedulerTest, ExampleSimulation) {
    // Initialize events as per the example
    std::vector<Event> events = {
        {1, 5, 0, 3, {}},
        {2, 3, 1, 2, {1}},
        {3, 4, 2, 1, {}},
        {4, 2, 3, 2, {2, 3}},
        {5, 5, 1, 1, {}}
    };


    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected processing order based on the exercise
    std::vector<int> expectedOrder = {1, 5, 3, 4, 2};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());

    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(processedEvents[i].id, expectedOrder[i]) << "Mismatch at position " << i;
    }
}

// Test with events having the same priority and timestamp
TEST(EventSchedulerTest, SamePriorityAndTimestamp) {
    std::vector<Event> events = {
        {1, 5, 0, 3, {}},
        {2, 5, 0, 2, {}},
        {3, 5, 0, 1, {}}
    };

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected order: IDs 1, 2, 3 (since IDs are in ascending order)
    std::vector<int> expectedOrder = {1, 2, 3};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());

    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(processedEvents[i].id, expectedOrder[i]) << "Mismatch at position " << i;
    }
}

// Test dynamic priority updates
TEST(EventSchedulerTest, DynamicPriorityUpdate) {
    std::vector<Event> events = {
        {1, 2, 0, 1, {}},
        {2, 2, 1, 1, {}},
        {3, 2, 2, 1, {}}
    };

    EventScheduler scheduler(events);

    // Update priorities before running the simulation
    scheduler.updateEventPriority(2, 5);
    scheduler.updateEventPriority(3, 4);

    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected order: 2 (priority 5), 3 (priority 4), 1 (priority 2)
    std::vector<int> expectedOrder = {2, 3, 1};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());

    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(processedEvents[i].id, expectedOrder[i]) << "Mismatch at position " << i;
    }
}

// Test event dependencies
TEST(EventSchedulerTest, EventDependencies) {
    std::vector<Event> events = {
        {1, 5, 0, 1, {}},
        {2, 4, 0, 1, {1}},
        {3, 3, 0, 1, {2}},
        {4, 6, 0, 1, {3}}
    };

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected order: 1, 2, 3, 4
    std::vector<int> expectedOrder = {1, 2, 3, 4};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());

    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(processedEvents[i].id, expectedOrder[i]) << "Mismatch at position " << i;
    }
}

// Test events with same priority but different timestamps
TEST(EventSchedulerTest, SamePriorityDifferentTimestamps) {
    std::vector<Event> events = {
        {1, 5, 1, 1, {}},
        {2, 5, 0, 1, {}},
        {3, 5, 2, 1, {}}
    };

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected order: 2, 1, 3 (earlier timestamp first)
    std::vector<int> expectedOrder = {2, 1, 3};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());

    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(processedEvents[i].id, expectedOrder[i]) << "Mismatch at position " << i;
    }
}

// Test events with dependencies that cannot be met
TEST(EventSchedulerTest, UnresolvableDependencies) {
    std::vector<Event> events = {
        {1, 5, 0, 1, {2}}, // Depends on Event 2
        {2, 4, 0, 1, {1}}  // Depends on Event 1
    };

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // No events should be processed due to circular dependency
    EXPECT_EQ(processedEvents.size(), 0);
}

// Test processing when all events have been processed
TEST(EventSchedulerTest, AllEventsProcessed) {
    std::vector<Event> events = {
        {1, 5, 0, 1, {}},
        {2, 4, 1, 1, {}},
        {3, 3, 2, 1, {}}
    };

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // Expected order: 1, 2, 3
    std::vector<int> expectedOrder = {1, 2, 3};
    ASSERT_EQ(processedEvents.size(), expectedOrder.size());
}

// Test with no events
TEST(EventSchedulerTest, NoEvents) {
    std::vector<Event> events;

    EventScheduler scheduler(events);
    scheduler.runSimulation();

    const auto& processedEvents = scheduler.getProcessedEvents();

    // No events to process
    EXPECT_TRUE(processedEvents.empty());
}
