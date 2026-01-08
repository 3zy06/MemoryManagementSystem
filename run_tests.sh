
echo "Building project..."
make -C build

if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

EXE="./build/memsim"

if [ ! -f "$EXE" ]; then
    echo "Error: Executable '$EXE' not found."
    exit 1
fi

mkdir -p test_outputs

# 4. Run the tests
echo "Running Coalescing Test..."
$EXE < tests/test_coalesce.txt > test_outputs/coalesce_out.txt
echo "Done. Check test_outputs/coalesce_out.txt"

echo "Running Strategy Test..."
$EXE < tests/test_strategies.txt > test_outputs/strategies_out.txt
echo "Done. Check test_outputs/strategies_out.txt"

echo "Running Cache Test..."
$EXE < tests/test_cache.txt > test_outputs/cache_out.txt
echo "Done. Check test_outputs/cache_out.txt"