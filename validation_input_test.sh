#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
PASSED=0
FAILED=0
TOTAL=0

# Push_swap executable path
PUSH_SWAP="./push_swap"

# Function to run a test
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_behavior="$3"

    TOTAL=$((TOTAL + 1))

    echo -e "${BLUE}Test $TOTAL: $test_name${NC}"
    echo "Input: $PUSH_SWAP $input"

    # Run the command and capture output and exit code
    if [ "$input" = "NO_ARGS" ]; then
        output=$($PUSH_SWAP 2>&1)
        exit_code=$?
    else
        output=$(eval "$PUSH_SWAP $input" 2>&1)
        exit_code=$?
    fi

    # Check if output contains "Error"
    if echo "$output" | grep -q "Error"; then
        result="ERROR"
    elif [ -z "$output" ]; then
        result="NO_OUTPUT"
    else
        result="OUTPUT"
    fi

    # Verify expected behavior
    if [ "$result" = "$expected_behavior" ]; then
        echo -e "${GREEN}✓ PASSED${NC} - Got expected: $expected_behavior"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAILED${NC} - Expected: $expected_behavior, Got: $result"
        if [ ! -z "$output" ]; then
            echo "Output: $output"
        fi
        FAILED=$((FAILED + 1))
    fi
    echo ""
}

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}    PUSH_SWAP INPUT VALIDATION TESTS${NC}"
echo -e "${YELLOW}========================================${NC}"
echo ""

# Check if push_swap exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: $PUSH_SWAP not found!${NC}"
    echo "Please compile your push_swap first."
    exit 1
fi

echo -e "${YELLOW}=== VALID INPUT TESTS ===${NC}"
echo ""

run_test "No arguments" "NO_ARGS" "NO_OUTPUT"
run_test "Single element" "42" "NO_OUTPUT"
run_test "Already sorted (2 elements)" "1 2" "NO_OUTPUT"
run_test "Already sorted (5 elements)" "1 2 3 4 5" "NO_OUTPUT"
run_test "Simple unsorted (2 elements)" "2 1" "OUTPUT"
run_test "Simple unsorted (3 elements)" "3 2 1" "OUTPUT"
run_test "Random unsorted" "5 2 8 1 9" "OUTPUT"
run_test "Negative numbers" "-5 -2 -8 -1" "OUTPUT"
run_test "Mixed positive/negative" "-5 0 3 -2 1" "OUTPUT"
run_test "INT_MIN" "-2147483648 0 5" "NO_OUTPUT"
run_test "INT_MAX" "2147483647 0 5" "OUTPUT"
run_test "INT_MIN and INT_MAX" "-2147483648 2147483647" "NO_OUTPUT"

echo -e "${YELLOW}=== ERROR: NON-INTEGER INPUTS ===${NC}"
echo ""

run_test "String in input" "1 2 abc 3" "ERROR"
run_test "String only" "hello" "ERROR"
run_test "Float number" "1.5 2 3" "ERROR"
run_test "Float with zero" "1 2.0 3" "ERROR"
run_test "Special characters" "1 @ 3" "ERROR"
run_test "Plus sign alone" "1 + 3" "ERROR"
run_test "Minus sign alone" "1 - 3" "ERROR"
run_test "Empty string mixed" "\"\" 1 2" "ERROR"

echo -e "${YELLOW}=== ERROR: INTEGER OVERFLOW/UNDERFLOW ===${NC}"
echo ""

run_test "INT_MAX + 1" "2147483648" "ERROR"
run_test "INT_MAX + 100" "2147483748" "ERROR"
run_test "INT_MIN - 1" "-2147483649" "ERROR"
run_test "INT_MIN - 100" "-2147483749" "ERROR"
run_test "Very large positive" "999999999999" "ERROR"
run_test "Very large negative" "-999999999999" "ERROR"
run_test "Mixed with overflow" "1 2 2147483648 3" "ERROR"

echo -e "${YELLOW}=== ERROR: DUPLICATE VALUES ===${NC}"
echo ""

run_test "Simple duplicate" "1 2 1" "ERROR"
run_test "Consecutive duplicates" "1 2 2 3" "ERROR"
run_test "Multiple duplicates" "1 2 3 2 1" "ERROR"
run_test "All same" "5 5 5 5" "ERROR"
run_test "Duplicate zeros" "0 1 0 2" "ERROR"
run_test "Duplicate negatives" "-5 -2 -5 -1" "ERROR"
run_test "Duplicate at end" "1 2 3 4 3" "ERROR"

echo -e "${YELLOW}=== ERROR: INVALID SIGNS ===${NC}"
echo ""

run_test "Double positive sign" "++5" "ERROR"
run_test "Double negative sign" "--5" "ERROR"
run_test "Mixed signs" "+-5" "ERROR"
run_test "Mixed signs 2" "-+5" "ERROR"
run_test "Multiple signs" "+++5" "ERROR"
run_test "Sign in middle" "1 2+3 4" "ERROR"

echo -e "${YELLOW}=== ERROR: WHITESPACE AND EMPTY ===${NC}"
echo ""

run_test "Only spaces" "\"   \"" "ERROR"
run_test "Tab character" "\"\t\"" "ERROR"
run_test "Empty string" "\"\"" "ERROR"
run_test "Multiple empty strings" "\"\" \"\" \"\"" "ERROR"
run_test "Multiple split" "\"7 9 -1\"" "OUTPUT"
run_test "Multiple split strings" "\"7 9 -1\" \"8\" \"--simple\"" "OUTPUT"
run_test "Multiple split strings err" "\"a7 9 -1\" \"8\" \"--simple\"" "ERROR"

echo -e "${YELLOW}=== EDGE CASES ===${NC}"
echo ""

run_test "Single zero" "0" "NO_OUTPUT"
run_test "Negative zero (if different)" "-0" "NO_OUTPUT"

# Fix for large sorted set - use proper quoting
LARGE_SORTED=$(seq 1 100 | tr '\n' ' ')
run_test "Large sorted set" "$LARGE_SORTED" "NO_OUTPUT"

# Fix for large reverse set - use proper quoting
LARGE_REVERSE=$(seq 100 -1 1 | tr '\n' ' ')
run_test "Large reverse set" "$LARGE_REVERSE" "OUTPUT"

run_test "Two negatives sorted" "-2 -1" "NO_OUTPUT"
run_test "Two negatives unsorted" "-1 -2" "OUTPUT"

echo -e "${YELLOW}=== STRATEGY FLAGS (if implemented) ===${NC}"
echo ""

# Test with --simple flag
if $PUSH_SWAP --simple 3 2 1 &>/dev/null; then
    run_test "Simple strategy flag" "--simple 3 2 1" "OUTPUT"
    run_test "Medium strategy flag" "--medium 3 2 1" "OUTPUT"
    run_test "Complex strategy flag" "--complex 3 2 1" "OUTPUT"
    run_test "Adaptive strategy flag" "--adaptive 3 2 1" "OUTPUT"
    run_test "Invalid strategy flag" "--invalid 3 2 1" "ERROR"
    run_test "Invalid strategy flag" "--simple --adaptive 3 2 1" "OUTPUT"
else
    echo "Strategy flags not implemented or not working - skipping"
fi

echo ""
echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}           TEST SUMMARY${NC}"
echo -e "${YELLOW}========================================${NC}"
echo -e "Total tests: ${BLUE}$TOTAL${NC}"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed! ✓${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed! ✗${NC}"
    exit 1
fi
