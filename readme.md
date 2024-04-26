## nRF Connect SDK Minimal Example for PDM Microphone
Tested with NCS v2.3.0, nRF52840 DK (PCA10056)

### PDM Microphone Connection
| Microphone | nRF |
| --- | ---- |
| V   | VDD  |
| G   | GND  |
| CLK | P0.03|
| DIN | P0.02|

### Getting Started
- Setup NCS in vscode
- Open this folder in vscode
- Click nRF Connect on the left plugin bar, under applications, click "+ Add build configuration"
- Select "nrf52840dk_nrf52840" as the board, leave everything else default
- Click "Build Configuration" on bottom right

### Configure Logging
- Go to prj.conf
- Set `CONFIG_LOG` to y
- Set `CONFIG_UART_CONSOLE` or `CONFIG_RTT_CONSOLE` to y
- If you are using RTT, set `CONFIG_USE_SEGGER_RTT` and `CONFIG_LOG_BACKEND_RTT`
- If you are using UART, set `CONFIG_LOG_BACKEND_UART`

### Acknowledgements
Code modified from
[https://devzone.nordicsemi.com/f/nordic-q-a/57896/pdm-interface](https://devzone.nordicsemi.com/f/nordic-q-a/57896/pdm-interface)
[https://devzone.nordicsemi.com/f/nordic-q-a/68472/pdm-mic-on-nrf9160dk-and-spm](https://devzone.nordicsemi.com/f/nordic-q-a/68472/pdm-mic-on-nrf9160dk-and-spm)
