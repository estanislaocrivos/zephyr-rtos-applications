# Zephyr RTOS Applications Collection 🧪

This directory contains out-of-tree Zephyr applications that are part of a Zephyr workspace following the **T1 (Forest) topology**.

## Workspace Setup

This workspace was set up following the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html).

### Main dependencies

Follow the [Install Dependencies](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-dependencies) section.

### Initial Workspace Setup

The workspace was initialized with:

```sh
# Create workspace directory. This workspace will contain Zephyr sources and applications
mkdir zephyr-workspace
cd zephyr-workspace

# Create and activate Python virtual environment
python3 -m venv .venv
source .venv/bin/activate

# Install West
pip3 install west

# Initialize West with Zephyr manifest
west init .

# Clone Zephyr and all modules
west update

# Export Zephyr CMake package
west zephyr-export

# Install Python dependencies
west packages pip --install

# Install Zephyr SDK (if not already installed)
cd zephyr/
west sdk install
```

### Resulting Directory Structure

```txt
zephyr-workspace/
├── .west/                      # West configuration
│   └── config
├── zephyr/                     # Zephyr RTOS (managed by West)
│   ├── include/
│   ├── kernel/
│   ├── drivers/
│   ├── samples/
│   └── ...
├── modules/                    # Zephyr modules (managed by West)
│   ├── hal/
│   ├── crypto/
│   ├── debug/
│   └── ...
├── bootloader/                 # MCUboot (managed by West)
│   └── mcuboot/
├── tools/                      # Build tools (managed by West)
│   └── ...
└── applications/               # YOUR APPLICATIONS (this repository)
    ├── test-application/       # Example application
    │   ├── CMakeLists.txt
    │   ├── prj.conf
    │   ├── README.md
    │   └── src/
    │       └── main.c
    └── your-app/               # Add more applications here
        ├── CMakeLists.txt
        ├── prj.conf
        └── src/
```

## How This Fits Together

### T1 (Forest) Topology

This workspace uses the **Forest topology** where:

- **Zephyr is the manifest repository** (contains `west.yml`)
- All projects (`zephyr/`, `modules/`, `applications/`) are siblings
- West manages Zephyr and its dependencies
- Your applications live in `applications/` as **out-of-tree apps**

### Why Out-of-Tree Applications?

Applications in this directory are **out-of-tree** because they:

- ✅ Are **outside** the Zephyr source tree
- ✅ Are **version controlled separately** (each can be its own Git repo)
- ✅ **Don't require** modifying Zephyr itself
- ✅ Can be **shared and reused** independently
- ✅ Are **cleaner** and easier to maintain

## Creating a New Application

### 1. Create the application directory

```sh
cd applications
mkdir my-new-app
cd my-new-app
```

### 2. Create the required files

**CMakeLists.txt:**

```cmake
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_new_app)

target_sources(app PRIVATE src/main.c)
```

**prj.conf:**

```ini
CONFIG_PRINTK=y
```

**src/main.c:**

```c
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("Hello from my-new-app!\n");
    return 0;
}
```

### 3. Build the application

```sh
# From within your application directory
west build -b <board_name>

# Example for native simulation
west build -b native_sim

# Example for STM32 Nucleo F401RE
west build -b nucleo_f401re
```

### 4. Flash to hardware (if applicable)

```sh
west flash
```

### 5. Run (for native_sim)

```sh
west build -t run
```

## Updating Zephyr and Modules

To update Zephyr and all managed modules:

```sh
cd zephyr-workspace
west update
```

Your applications in `applications/` are **not affected** by this update.

## Finding Your Board

To list all supported boards:

```sh
west boards
```

To search for a specific board:

```sh
west boards | grep nucleo
west boards | grep nrf
```

## Console Output

### On native_sim

Output goes to **stdout** (your terminal).

### On hardware boards

Output typically goes to **UART** (via USB):

```sh
# macOS/Linux
screen /dev/ttyACM0 115200

# Or use minicom
minicom -D /dev/ttyACM0 -b 115200
```

Check your board's documentation for the correct serial port.

## Useful Commands

```sh
# Build
west build -b <board>

# Clean build
west build -b <board> --pristine

# Flash to board
west flash

# Debug
west debug

# Attach debugger
west attach

# List boards
west boards

# Update workspace
west update
```

## Resources

- [Zephyr Documentation](https://docs.zephyrproject.org/)
- [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)
- [Application Development](https://docs.zephyrproject.org/latest/develop/application/index.html)
- [West Tool](https://docs.zephyrproject.org/latest/develop/west/index.html)
- [Board Support](https://docs.zephyrproject.org/latest/boards/index.html)

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENCE) file for details.
