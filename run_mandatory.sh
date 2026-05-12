CHECKER="./checker_linux"

# Colors
RED='\033[0;31m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

# Push_swap executable path
PUSH_SWAP="./push_swap"

# Counters
PASSED=0
FAILED=0
TOTAL=0

pause() {
    printf "${BOLD}${RESET}Press Enter to continue...${RESET}"
    read _
	clear
}

run_mandatory() {
    local args="$1"
    local flag="$2"
    local res=""
    local line="0"

	TOTAL=$((TOTAL + 1))
    echo "${CYAN}$PUSH_SWAP $1 $flag${RED}"
	( $PUSH_SWAP $flag --bench $args 2> bench.txt | wc -l ) > line.txt
    ( $PUSH_SWAP $flag $args ) > res.txt
	res=$( cat res.txt )
	line=$( cat line.txt )
	echo "${RED}$res"
}

run_mandatory_with_checker() {
    local args="$1"
    local flag="$2"
    local res=""
    local line="0"
	local bench="[bench]"

	TOTAL=$((TOTAL + 1))
    echo "${CYAN}$PUSH_SWAP $1 $flag | $CHECKER $1"
	( $PUSH_SWAP $args $flag --bench 2> bench.txt | wc -l ) > line.txt
    ( $PUSH_SWAP $args $flag | $CHECKER $args ) > res.txt
	res=$( cat res.txt )
	line=$( cat line.txt )
	bench=$( cat bench.txt )
	if [ $res ] && [ "$res" = "OK" ] ; then
		echo "${GREEN}$res | $line"
		echo "${RESET}$bench"
		PASSED=$((PASSED + 1))
	elif [ $res ] && [ "$res" = "KO" ] ; then
		echo "${RED}$res"
		FAILED=$((FAILED + 1))
	elif [ $res ] && [ "$res" = "Error" ] ; then
		echo "${RED}$res"
		FAILED=$((FAILED + 1))
	else
		echo "${RED}!!! ERROR !!!"
		FAILED=$((FAILED + 1))
	fi
}

run_shuf_test() {
	local temp_file="$1"
	local name="$2"
	local no="$3"

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )"
	pause

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )" --simple
	pause

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )" --medium
	pause

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )" --complex
	pause

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )" --adaptive
	pause

	echo "${YELLOW}$name"
	echo "[no.$no]"
	run_mandatory_with_checker "$( cat $temp_file | tr '\n' ' ' )" --adaptive
	pause
}


echo "${YELLOW}Review"
run_mandatory "5 4 7 one 8"
run_mandatory "5 4 7 5 8"
run_mandatory "2147483648"
run_mandatory "2147483648 0 3 8"
run_mandatory
echo ""
pause

echo "${YELLOW}Invert sorted"
run_mandatory_with_checker "5 4 3 2 1" --simple
run_mandatory_with_checker "5 4 3 2 1" --medium
run_mandatory_with_checker "5 4 3 2 1" --complex
run_mandatory_with_checker "5 4 3 2 1" --adaptive
run_mandatory_with_checker "5 4 3 2 1"
echo ""
pause

echo "${YELLOW}Already sorted"
run_mandatory_with_checker "42"
run_mandatory_with_checker "2 3"
run_mandatory_with_checker "0 1 2 3"
run_mandatory_with_checker "0 1 2 3 4 5 6 7 8 9"
echo ""
pause

echo "${YELLOW}Already sorted again (OPTIONAL)"
run_mandatory_with_checker "1 2 3 4 5"
run_mandatory_with_checker "1 2 3 4 5" --simple
run_mandatory_with_checker "1 2 3 4 5" --medium
run_mandatory_with_checker "1 2 3 4 5" --complex
run_mandatory_with_checker "1 2 3 4 5" --adaptive
echo ""
pause

echo "${YELLOW}One Element (OPTIONAL)"
run_mandatory_with_checker "42"
run_mandatory_with_checker "42" --simple
run_mandatory_with_checker "42" --medium
run_mandatory_with_checker "42" --complex
run_mandatory_with_checker "42" --adaptive
echo ""
pause

echo "${YELLOW}2 digit sorted (OPTIONAL)"
run_mandatory_with_checker "0 1"
run_mandatory_with_checker "0 1" --simple
run_mandatory_with_checker "0 1" --medium
run_mandatory_with_checker "0 1" --complex
run_mandatory_with_checker "0 1" --adaptive
echo ""
pause

echo "${YELLOW}2 digit unsorted (OPTIONAL)"
run_mandatory_with_checker "1 0"
run_mandatory_with_checker "1 0" --simple
run_mandatory_with_checker "1 0" --medium
run_mandatory_with_checker "1 0" --complex
run_mandatory_with_checker "1 0" --adaptive
echo ""
pause

echo "${YELLOW}3 digits"
run_mandatory_with_checker "0 1 2"
run_mandatory_with_checker "2 1 0"
run_mandatory_with_checker "0 2 1"
run_mandatory_with_checker "1 0 2"
echo ""
pause
echo "${RESET}3 digits (OPTIONAL)"
run_mandatory_with_checker "1 2 0"
run_mandatory_with_checker "2 0 1"
run_mandatory_with_checker "0 2 1" --simple
run_mandatory_with_checker "1 0 2" --medium
run_mandatory_with_checker "1 2 0" --complex
run_mandatory_with_checker "2 0 1" --adaptive
echo ""
pause

echo "${YELLOW}4 digits (OPTIONAL)"
run_mandatory_with_checker "1 0 2 3"
run_mandatory_with_checker "2 1 0 3"
run_mandatory_with_checker "3 0 1 2"
run_mandatory_with_checker "3 0 1 2" --simple
run_mandatory_with_checker "3 0 1 2" --medium
run_mandatory_with_checker "3 0 1 2" --complex
run_mandatory_with_checker "3 0 1 2" --adaptive
echo ""
pause

echo "${YELLOW}5 digits"
run_mandatory_with_checker "1 5 2 4 3"
run_mandatory_with_checker "5 1 4 2 3"
run_mandatory_with_checker "3 5 1 4 2"
echo ""
pause
echo "${YELLOW}5 digits (OPTIONAL)"
run_mandatory_with_checker "4 3 1 0 2"
run_mandatory_with_checker "0 2 4 1 3"
run_mandatory_with_checker "0 1 3 4 2"
run_mandatory_with_checker "0 1 2 4 3"
run_mandatory_with_checker "0 2 1 3 4"
run_mandatory_with_checker "3 5 1 4 2"
run_mandatory_with_checker "3 5 1 4 2" --simple
run_mandatory_with_checker "3 5 1 4 2" --medium
run_mandatory_with_checker "3 5 1 4 2" --complex
run_mandatory_with_checker "3 5 1 4 2" --adaptive
echo ""
pause

shuf -i 1-1000 -n 50 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 50" 1

shuf -i 1-1000 -n 50 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 50" 2

shuf -i 1-1000 -n 50 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 50" 3


shuf -i 1-1000 -n 100 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 100" 1

shuf -i 1-1000 -n 100 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 100" 2

shuf -i 1-1000 -n 100 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 100" 3


shuf -i 1-1000 -n 500 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 500" 1

shuf -i 1-1000 -n 500 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 500" 2

shuf -i 1-1000 -n 500 > temp.txt
run_shuf_test temp.txt "shuf -i 1-1000 -n 500" 3

echo "${YELLOW}===========================================${RESET}"
echo "${YELLOW}===========TEST SUMMARY${RESET}"===========
echo "${YELLOW}===========================================${RESET}"
echo "Total tests: ${BLUE}$TOTAL${RESET}"
echo "Passed: ${GREEN}$PASSED${RESET}"
echo "Failed: ${RED}$FAILED${RESET}"
echo "==========================================="
