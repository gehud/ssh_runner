# SSH Command Runner

A console application for executing commands on remote devices via SSH, saving the results in JSON.

## Requirements

- CMake 3.19 or higher
- Qt6 (Core and Network modules)
- C++17 compatible compiler

## Building

```bash
# Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# Build
cmake --build build
```

## Usage

### Command Line Arguments

```
ssh_runner --input <file> --user <username> --output <file>
```

- `--input, -i`: Path to the file with the list of IP addresses
- `--user, -u`: Username for SSH connection
- `--output, -o`: Path to output JSON file

### Example

Create input file `devices.txt`:
```
192.168.1.10
192.168.1.11
192.168.1.12
```

Run:
```bash
./ssh_runner --input devices.txt --user ubuntu --output result.json
```

### Output Format

```json
{
  "192.168.1.10": {
    "output": "Hello from test_app",
  },
  "192.168.1.11": {
    "error": "timeout"
  },
  "192.168.1.12": {
    "error": "authentication failed"
  },
  "192.168.1.14": {
    "error": "empty output",
  },
  "192.168.1.15": {
    "error": "Other error",
  }
}
```

## License

This project is licensed under the MIT License — see `LICENSE` for details.