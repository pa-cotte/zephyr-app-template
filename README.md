# zephyr-app-template

Basic template for zephyr app

## Prerequisites

### Git & Docker

```bash
sudo apt install git
sudo apt install docker
sudo apt install docker-buildx
sudo usermod -aG docker $USER
```

### UDEV rules

```bash
wget -O 60-openocd.rules https://sf.net/p/openocd/code/ci/master/tree/contrib/60-openocd.rules?format=raw
sudo cp 60-openocd.rules /etc/udev/rules.d
sudo udevadm control --reload
```

## Setup

- Open the project in the `devcontainer` via vscode
- `west init -l project`
- `west update`

### ALIF / MURATA 1LV

- `west blobs fetch hal_infineon`
- backport this PR : https://github.com/zephyrproject-rtos/zephyr/pull/77039/files
- Modify the Infineon HAL CMakeLists.txt by moving the following lines outside the `if (CONFIG_SOC_FAMILY_INFINEON_CAT1A OR CONFIG_SOC_FAMILY_PSOC6)` block:
    ```
    add_subdirectory(core-lib)
    add_subdirectory(abstraction-rtos)
    ```  

## Build & Flash

- Click on the "Configure" button in the bottom bar of vscode
    - select "Configure the app"
    - select the board to use
- Click on the "Build" button
- Click on the "Flash" button

## Debug

- Build the app (see previous section)
- uncomment in the `base.conf` file the debug section to enable the necessary KCONFIG options
- Launch the debug with vscode's debug tab by selecting the target board