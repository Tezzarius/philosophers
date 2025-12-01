#!/bin/bash

# ===== CONFIGURATION =====
MEAL_COUNT=5  # Change this value to set the number of meals
# =========================

# Check if enough arguments are provided
if [ $# -lt 4 ]; then
    echo "Usage: $0 <num_philos> <time_to_die> <time_to_eat> <time_to_sleep>"
    exit 1
fi

num_philos=$1
time_to_die=$2
time_to_eat=$3
time_to_sleep=$4

# Create logs directory if it doesn't exist
mkdir -p logs

# Base log file name
base_name="logs/log_${num_philos}_${time_to_die}_${time_to_eat}_${time_to_sleep}_${MEAL_COUNT}"

# Find the next available filename
counter=1
log_file="${base_name}.txt"
while [[ -f "$log_file" ]]; do
    log_file="${base_name}_${counter}.txt"
    ((counter++))
done

summary_file="temp_summary.txt"
meal_stats="temp_meals.txt"

# Clear files
> "$log_file"
> "$summary_file"
> "$meal_stats"

echo "Running 10 tests for: $num_philos $time_to_die $time_to_eat $time_to_sleep $MEAL_COUNT"
echo "Log file: $log_file"
echo

# Run all tests first
for ((i=0; i<10; i++))
do
    echo "Running test #$i..."
    
    # Run the test and capture output
    ./philo $num_philos $time_to_die $time_to_eat $time_to_sleep $MEAL_COUNT > temp_output.txt 2>&1
    
    # Write to log file
    echo "=== Test #$i ===" >> "$log_file"
    echo "---- Raw Output ----" >> "$log_file"
    cat temp_output.txt >> "$log_file"
    echo "-------------------" >> "$log_file"
    
    # Check each philosopher's meal count and collect stats
    echo "Meal counts:" >> "$log_file"
    for ((philo=1; philo<=num_philos; philo++))
    do
        meals=$(grep -c "$philo is eating" temp_output.txt)
        echo "  Philosopher $philo: $meals meals" >> "$log_file"
        echo "$i,$philo,$meals" >> "$meal_stats"
    done
    
    # Check for deaths and store summary
    deaths=$(grep -c "died" temp_output.txt)
    if [ $deaths -gt 0 ]; then
        death_msg=$(grep "died" temp_output.txt | tail -1)
        echo "  ❌ Deaths detected: $deaths - $death_msg" >> "$log_file"
        echo "Test $i: ❌ Death - $death_msg" >> "$summary_file"
    else
        echo "  ✅ No deaths" >> "$log_file"
        echo "Test $i: ✅ Success" >> "$summary_file"
    fi
    
    echo "==================" >> "$log_file"
    echo >> "$log_file"
    
    rm -f temp_output.txt
    sleep 0.5
done

# Calculate meal statistics
if [ -s "$meal_stats" ]; then
    avg_meals=$(awk -F',' '{sum+=$3} END {if (NR>0) print sum/NR}' "$meal_stats")
    min_meals=$(awk -F',' 'NR==1 {min=$3} {if ($3<min) min=$3} END {print min}' "$meal_stats")
    max_meals=$(awk -F',' 'NR==1 {max=$3} {if ($3>max) max=$3} END {print max}' "$meal_stats")
else
    avg_meals=0
    min_meals=0
    max_meals=0
fi

# Create final summary
total_tests=10
success_count=$(grep -c "✅ Success" "$summary_file")
death_count=$(grep -c "❌ Death" "$summary_file")

# Write comprehensive summary to beginning of log file
{
    echo "=== COMPREHENSIVE SUMMARY ==="
    echo "Parameters: $num_philos $time_to_die $time_to_eat $time_to_sleep $MEAL_COUNT"
    echo "Total tests: $total_tests"
    echo "Successful tests: $success_count"
    echo "Tests with deaths: $death_count"
    echo "Success rate: $((success_count * 100 / total_tests))%"
    echo
    echo "Meal Statistics:"
    echo "  Average meals per philosopher: $(printf "%.1f" $avg_meals)"
    echo "  Minimum meals: $min_meals"
    echo "  Maximum meals: $max_meals"
    echo
    echo "=== DETAILED TEST RESULTS ==="
    cat "$summary_file"
    echo
    echo "=== FULL TEST LOG ==="
    echo
} | cat - "$log_file" > temp_log_complete.txt && mv temp_log_complete.txt "$log_file"

# Show summary in terminal
echo
echo "=== SUMMARY ==="
echo "Parameters: $num_philos $time_to_die $time_to_eat $time_to_sleep $MEAL_COUNT"
echo "Total tests: $total_tests"
echo "Successful tests: $success_count"
echo "Tests with deaths: $death_count"
echo "Success rate: $((success_count * 100 / total_tests))%"
echo
echo "Meal Statistics:"
echo "  Average meals per philosopher: $(printf "%.1f" $avg_meals)"
echo "  Minimum meals: $min_meals"
echo "  Maximum meals: $max_meals"
echo
echo "Detailed results:"
cat "$summary_file"

echo
echo "All tests completed!"
echo "Full log saved to: $log_file"

# Clean up
rm -f "$summary_file" "$meal_stats" temp_output.txt temp_log_complete.txt