# ADC Sensor Log Parser

Reads a binary ADC sensor log file (`adc_sensor_log.bin`), converts raw values
to voltage, checks for faults and sequence gaps, computes per-channel
statistics, and writes the results to `results.txt`.

## Files

- `main.c` – entry point
- `io.c` / `io.h` – file reading and writing
- `ADC.c` / `ADC.h` – voltage conversion, fault detection, sampling integrity
- `stats.c` / `stats.h` – per-channel statistics (min, max, mean, std dev)

## Build with CLion

1. Open the project folder in CLion.
2. Make sure `adc_sensor_log.bin` is in the project's working directory (usually `cmake-build-debug`, or set the working directory in Run > Edit Configurations).
3. Click **Build**, then **Run**.

## Build with gcc (command line)

```bash
gcc -std=c99 -Wall -o adc_prog main.c io.c ADC.c stats.c -lm
./adc_prog
```

Make sure `adc_sensor_log.bin` is in the same folder before running.

## Output

- Results are printed to the console
- Results are also written to `results.txt`
