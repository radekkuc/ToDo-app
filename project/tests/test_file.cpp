#include <gtest/gtest.h>
#include <stdexcept>
#include "../project/project.cpp"


TEST(TaskTest, TaskInitialization) {
    Task task("Sample Task");

    EXPECT_EQ(task.getDescription(), "Sample Task");

    EXPECT_FALSE(task.isCompleted());
}

TEST(TaskTest, MarkTaskAsCompleted) {
    Task task("Sample Task");

    task.markAsCompleted();

    EXPECT_TRUE(task.isCompleted());
}

TEST(ToDoListTest, AddTask) {
    ToDoList todoList("test_tasks.txt");

    todoList.addTask("New Task");
    EXPECT_NO_THROW(todoList.addTask("New Task"));
}

TEST(ToDoListTest, AddEmptyTaskShouldThrow) {
    ToDoList todoList("test_tasks.txt");

    EXPECT_THROW(todoList.addTask(""), std::invalid_argument);
}

TEST(ToDoListTest, MarkTaskAsCompleted) {
    ToDoList todoList("test_tasks.txt");

    todoList.addTask("New Task");

    todoList.markTaskAsCompleted(0);

    todoList.displayTasks(); // Sprawdza, czy lista zadań wyświetla się poprawnie
}

TEST(ToDoListTest, MarkTaskOutOfRangeShouldThrow) {
    ToDoList todoList("test_tasks.txt");

    EXPECT_THROW(todoList.markTaskAsCompleted(10), std::out_of_range);
}

TEST(ToDoListTest, LoadAndSaveTasks) {
    ToDoList todoList("test_tasks.txt");
    todoList.addTask("Task 1");
    todoList.addTask("Task 2");

    todoList.saveTasksToFile();

    ToDoList newToDoList("test_tasks.txt");
    newToDoList.loadTasksFromFile();

    newToDoList.displayTasks();
}

