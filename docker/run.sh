#!/bin/bash

g++ /app/user_code.cpp -o /app/program.out 2> /app/compile_errors.txt
if [ $? -ne 0 ]; then
    echo "❌ Compile error:"
    cat /app/compile_errors.txt
    exit 1
fi

echo "✅ Compilation successful."

i=1
all_passed=true

while [ -f /app/tests/input${i}.txt ]; do
    input="/app/tests/input${i}.txt"
    expected="/app/tests/output${i}.txt"
    actual="/app/user_output.txt"
    trimmed_expected="/app/tests/trimmed_expected.txt"
    trimmed_actual="/app/tests/trimmed_actual.txt"

    start_time=$(date +%s%3N)
    timeout 2s bash -c "ulimit -v 65536 && /app/program.out < $input > $actual" 2> /app/runtime_error.txt
    exit_code=$?
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))

    if [ $exit_code -eq 124 ]; then
        echo "❌ Time limit exceeded (more than 2 seconds)"
        all_passed=false
        break
    elif [ $exit_code -ne 0 ]; then
        echo "❌ Runtime error:"
        cat /app/runtime_error.txt
        all_passed=false
        break
    else
        grep -v '^[[:space:]]*$' "$expected" | sed 's/^[[:space:]]*//; s/[[:space:]]*$//' > "$trimmed_expected"
        grep -v '^[[:space:]]*$' "$actual" | sed 's/^[[:space:]]*//; s/[[:space:]]*$//' > "$trimmed_actual"

        if diff -q "$trimmed_expected" "$trimmed_actual" > /dev/null; then
            echo "✅ Test #$i passed (time: ${elapsed} ms)"
        else
            echo "❌ Test #$i not passed"
            all_passed=false
            break
        fi
    fi
    i=$((i+1))
done

if [ "$all_passed" = true ]; then
    echo "🎉 All tests passed"
fi