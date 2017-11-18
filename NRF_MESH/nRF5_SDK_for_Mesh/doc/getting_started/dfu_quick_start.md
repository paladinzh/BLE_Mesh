# DFU Quick Start Guide

Let's create a DFU file and transfer it!

This quick start guide offers step by step instructions on how you can do a Direct Firmware Upgrade (DFU) of your own, using example firmware. It should provide a reasonable basis for using the mesh DFU to transfer any firmware to any mesh.

The steps are listed below, with a more detailed explanation for each step at the end. The pc-nrfutil tool is available (and open source) at https://github.com/NordicSemiconductor/pc-nrfutil/tree/mesh_dfu.

**Note:** The master branch does not contain the additional code to handle a mesh DFU. To use the tool with the mesh DFU, use the `mesh_dfu` branch. See the tool's documentation for more information about installation and prerequisites.

This guide assumes that you have at least 2 development kits or devices, where one is to be interfaced over the serial port, while the other gets the DFU from the first device over the mesh.

**Note:** For each call to the `nrfjprog` command, you are expected to add the `-s <serial-number>` option, to match the Segger ID of your device.

**IMPORTANT:** Make sure you use the correct precompiled bootloader for your chip variant (nRF51/nRF52, xxAA, xxAB, xxAC). These variants have different flash and RAM sizes, as specified in the product specification for [nRF51](http://infocenter.nordicsemi.com/pdf/nRF51822_PS_v3.3.pdf) and [nRF52](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.3.pdf).

## Steps

1. Generate a signing key file with pc-nrfutil (optional)
2. Paste the public key from pc-nrfutil into your device-page (optional)
3. Generate a hex version of your device-page with the tool in `tools/dfu`.
4. Erase all chip memory including the UICR on all devices.
5. Flash the Softdevice on all devices.
6. Flash the serial bootloader on all devices.
7. Flash the first application on all devices.
8. Flash the device page on all devices.
9. Generate a DFU archive with the pc-nrfutil tool, giving arguments that match the device-page.
10. Transfer the DFU archive over serial with the pc-nrfutil tool.

## 1. Generate a signing key file with pc-nrfutil (optional)

If you want to use the signature verification functionality of the DFU, you need a signing key. The nrfutil tool can be used to generate a signing key:

```
nrfutil keys --gen-key private_key.txt
```

This will create a text file in your current directory named `private_key.txt`. This key is top secret, and must not be shared with anyone! Also make sure you don't lose it, because you'd also lose authorization to do DFU updates to your devices in the future, and the only way to recover from this is to reflash the device manually.

## 2. Paste the public key from pc-nrfutil into your device-page (optional)

Now that you have a private key, you can generate the public key for it:

```
nrfutil keys --show-vk hex private_key.txt
```

This will output something like:

```
Verification key Qx: ed09a58df6db5cd15b8637304f31d31f4042492ed7c7e4839fbe903f260a2ba1
Verification key Qy: a855e92b72885825481ad56282bcf549ad7455ec46f000f0f62d97eeec883ba6
```

These two hex-strings make up your public key, which you may safely show off to everyone. The keys above are example keys and will only work with a specific private key.

The device page is generated from a device page file. Example files for nRF51 and nRF52 are available in `tools/dfu`. The example file already has entries for Softdevice (S110 or S132 for nRF51 and nRF52 respectively), application and bootloader sections and firmware IDs. Paste the public key entry you generated above to two empty lines in the file. This allows your device to verify that the person that initiated the DFU transfer has your private key.

You may also want to change the company-id entry. In the example, the company-ID is set to 0x00000059, which is the 32-bit version of Nordic Semiconductor's [Bluetooth SIG assigned Company ID](https://www.bluetooth.com/specifications/assigned-numbers/company-identifiers). If your company has an assigned ID, you use yours, but if you don't represent a company with an assigned ID, you may use a random 32-bit number higher than 65535. The company ID works as a namespace for application IDs in the mesh DFU. This way, any company with an assigned company ID may safely use any application ID for their products, without risking an application ID conflict. If you use a random number, the risk of getting conflicts is present but unlikely given the large pool of numbers. You might still want to go with something more clever than 0x12345678 though, as someone else might have been just as lazy.

## 3. Generate a hex version of your device page

In the same folder as the example device page file, there is a Python script that can generate device pages, `device_page.py` (works for both Python 2.7 and Python 3, requires the `intelhex` package from PyPi). See the README file in the `tools/dfu` folder for instructions. Run the following command from inside the `tools/dfu` folder to generate an example device page file:

For nRF51
```
python device_page.py example
```

For nRF52
```
python device_page.py example52 --nrf52
```

This creates a device page .hex file (called `example.hex` or `example52.hex`). Hang onto this file, for we will use it in step 8.

## 4. Erase all chip memory, including UICR, on all devices

Using nrfjprog (available on http://www.nordicsemi.com), erase all previous data on your device (including UICR):

```
nrfjprog --eraseall
```

## 5. Flash the SoftDevice on all devices.

**Note:** It is important that the steps 6--9 are executed in order.

SoftDevices for nRF51 and nRF52 are located in the `lib/softdevices` folder. If you used the example device page file for nRF51, use the S110 SoftDevice. For nRF52, use S132.

```
nrfjprog --program <Softdevice hex-file>
```

## 6. Flash the serial bootloader on all devices.

Flash the precompiled `bootloader_serial.hex` (in `bin/`) to your device using nrfjprog:

```
nrfjprog --program <bootloader serial hex-file>
```

## 7. Flash the first application on all devices

This uses the DFU example application. The code for this application can be found in `examples/dfu/`.

*nRF51:*
From your build folder, flash the hexfile available in `examples/dfu/51_dfu.hex` to all devices.

*nRF52:*
From your build folder, flash the hexfile available in `examples/dfu/52_dfu.hex` to all devices.

*For both cases:*
Flash the file with the following command:
```
nrfjprog --family <nRF51|nRF52> --program <app hex-file>
```

Then reset the device to start the application:
```
nrfjprog --reset
```

## 8. Flash the device page on all devices.

Flash the device page hexfile that you generated in step 4 to the devices:

```
nrfjprog --program <device page hex-file>
```

## 9. Generate a DFU-file with the pc-nrfutil tool, giving arguments that match the device-page.

To do a DFU transfer, you need to create a DFU archive. The DFU archive is a zip file, which contains the application binary, along with some metadata. We are going to flash a small application that will cause an LED to blink on the boards. The hexfile for this application is located in `examples/dfu/bin`. Use the hexfile corresponding to the SoftDevice you are using.

Matching the FWIDs in your device page file, use the `nrfutil` tool to generate the DFU archive:

*nRF51:*
```
nrfutil dfu genpkg --application examples/dfu/bin/app_green_s110.hex \
    --company-id 0x00000059 \
    --application-id 1 \
    --application-version 2 \
    --key-file private.txt \
    --sd-req 0x0064 \
    --mesh dfu_test.zip
```

*nRF52:*
```
nrfutil dfu genpkg --application examples/dfu/bin/app_green_s132.hex \
    --company-id 0x00000059 \
    --application-id 1 \
    --application-version 2 \
    --key-file private.txt \
    --sd-req 0x0064 \
    --mesh dfu_test.zip
```

This will generate a DFU archive called `dfu_test.zip` in the current directory. You can call `nrfutil dfu genpkg --help` to get a list of possible command line arguments and their meaning. Note that some of the options do not apply to the mesh DFU, as the tool also supports the regular Nordic Semiconductor DFU transfer.

You can see that we still used the Nordic Semiconductor company ID, make sure you use your own. Also note that the application version is set to 2. A device will only accept application transfers that match its current company and application IDs, and that has a higher version number.

## 10. Transfer the DFU archive over serial with the nrfutil tool

**Warning:** For this step, it is important that you close any running instance of nRFgo Studio,
as it has been known to cause problems with the reset procedure for the nRF51.

Now we come to the interesting part: doing the DFU! First, figure out which COM-port your serial device is on.

On Windows, serial ports are called COMxx, where xx is an integer. To figure out which COM port is used for a device, open Windows Device Manager and look under "Ports (COM & LPT)" for the number of the port.

On Linux, serial ports for JLink devices are called ttyACMx, where x is an integer, and live in the `/dev` directory. Using the `dmesg` command after you have plugged in a device, you can see which serial port file has been assigned to the device.

To start the DFU, run the following command:
```
nrfutil dfu serial -pkg dfu_test.zip -p <comport> -b 115200 -fc --mesh
```

A progress bar should pop up, and the transfer should take a couple of minutes.

Once finished, the bootloader should switch to the application, and the LEDs should start blinking. You will not be able to do the DFU twice with the same DFU archive, as the application version in the device page on your device will have incremented to 2, and the bootloader will reject any attempt to retransfer the firmware.

To try another DFU, re-run step 10--11 with an increased version number, for example `--application-version 3`, and use the zip file to do the DFU again.

## Troubleshooting: Verifying your bootloader with the bootloader_verify.py script (optional)

Run the bootloader verification script located in `tools/dfu`:

**Note:** `bootloader_verify.py` requires the [pyserial package](https://pypi.python.org/pypi/pyserial), and that `nrfjprog` is present in your `PATH`.

*nRF51:*
```
python bootloader_verify_nRF51.py <serial number> <COM-port>
```

*nRF52:*
```
python bootloader_verify_nRF52.py <serial number> <COM-port>
```

The output should look like this:

```
Reading UICR..                  OK.
Reading Device page..           OK.
Resetting device..              OK.
Checking serial connection..    OK.

Bootloader verification OK
```

Run `nrfjprog --reset` to reset the board back to a well known state of operation after running the boot loader verification script.
