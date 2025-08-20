# Testing Framework

This directory contains comprehensive tests for the BST implementation using Google Test (gtest).

## Test Files

- `test-bst.cpp` - Comprehensive tests for the Binary Search Tree implementation

## Test Coverage

The BST tests cover:

### Basic Operations
- Constructor and destructor
- Insert operations (including duplicate handling)
- Contains operations
- Size tracking

### Tree Traversal
- Inorder traversal (ascending order)
- Verification of sorted output

### Tree Validation
- BST property validation
- Structure integrity checks

### Deletion Operations
- Leaf node deletion
- Single child node deletion
- Two children node deletion (using successor)
- Non-existent item deletion
- Empty tree operations

### Edge Cases
- Single item operations
- Empty tree operations
- Complex operation sequences
- Stress testing with many items

### Data Types
- Different item categories (Book, Clothing, Electronics)
- String-based item names

## Building and Running Tests

### Prerequisites
- CMake 3.16 or higher
- Google Test library
- C++17 compatible compiler

### Quick Build
```bash
./build.sh --test
```

### Manual Build
```bash
mkdir -p build
cd build
cmake ..
make
make test
```

### Running Specific Tests
```bash
# Run all tests
./build/test-bst

# Run with verbose output
./build/test-bst --gtest_verbose
```

## Test Structure

Each test class inherits from `::testing::Test` and uses the `TEST_F` macro for test methods. The `SetUp()` method initializes common test data, and `TearDown()` handles cleanup.

## Adding New Tests

To add new tests:

1. Create a new test method using `TEST_F(ClassName, TestName)`
2. Use appropriate assertions (`EXPECT_*`, `ASSERT_*`)
3. Test both normal cases and edge cases
4. Verify BST properties after operations

## Example Test Pattern

```cpp
TEST_F(BSTTest, NewFeature) {
    BST bst;
    
    // Setup
    bst.insert(testItem);
    
    // Action
    bool result = bst.someOperation();
    
    // Verification
    EXPECT_TRUE(result);
    EXPECT_EQ(bst.size(), expectedSize);
    EXPECT_TRUE(bst.isValidBST());
}
```
