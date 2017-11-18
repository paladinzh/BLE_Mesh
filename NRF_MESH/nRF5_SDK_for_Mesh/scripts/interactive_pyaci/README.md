# Interactive PyACI

The Interactive Python Application Controller Interface (PyACI), `interactive_pyaci.py`, can be used to
interactively control devices running the mesh stack and the serial interface. The script opens
up one or more COM ports and enables an interactive Python command line.

The interface consists of
- `aci/aci_cmd.py`: command class definitions (serialization)
- `aci/aci_evt.py`: event class definitions (de-serialization)
- `aci/aci_uart.py`: the UART serial driver
- `aci/aci_utils.py`: Utility functions and class definitions

**Note:** `aci/aci_cmd.py` and `aci/aci_evt.py` are auto-generated from the C header files of the
serial interface with the `tools/serial_doc` scripts. To re-generate the files, use the command

```
    $ cd <path-to-build-directory>
    $ <build-command> serial_pyaci
```

where `<build-command>` is `ninja`, `make` or something else
depending on your build setup.


## Prerequisites

The interactive console is written for Python 3.5. Install the requirements using `pip` like this

```
    $ pip install -r requirements.txt
```

To follow this guide, you will at least need two boards running
the [serial example](@ref md_examples_serial_README). Either `PCA10028`, `PCA10030`, or `PCA10040`.

## Using the interface

To start the serial interface, simply call `python interactive_console.py -d <com port>`. The baud
rate is set to the default value used in the mesh serial stack. To disable logging to file, append
the `--no-logfile` argument.

### Hello World

After building and flashing the serial example, connect to the device with the interactive console:

```
    $ python interactive_pyaci.py -d /dev/ttyACM0 --no-logfile

        To control your device use d[x], type d[x]. and hit tab to see the available methods.
        x is for the device index; devices will be indexed based on the order of com ports
        given with the option -d(the first device, d[0], can also be accessed using device).
        The log will be available in the calling directory as ttyACM0_17-185-13-32.outlog

    Python 3.5.2 (default, Nov 17 2016, 17:05:23)
    Type 'copyright', 'credits' or 'license' for more information
    IPython 6.1.0 -- An enhanced Interactive Python. Type '?' for help.
```

Send an `echo` command to test that the device is connected

```
    In [1]: send(Echo("hello world"))
    2017-07-04 15:09:58,950 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'hello world')}}
```

The `send` function is a helper function for sending commands to the first device. It accepts a
`CommandPacket` object as a parameter. All of these are imported from `aci/aci_cmd.py` by the
interactive script.

### Sending mesh packets

Let us try to set up a tiny mesh network. Connect two devices, and start the serial interface.

```
    $ python interactive_pyaci.py -d /dev/ttyACM0,/dev/ttyACM1 --no-logfile
```

Next, we add a network key, application key and a local unicast address.

```
    In [1]: for i in range(0, len(d)):
       ...:     d[i].send(SubnetAdd(0, ConfigState.DEFAULT_NETWORK_KEY))
       ...:     d[i].send(AppkeyAdd(0, 0, ConfigState.DEFAULT_APP_KEY))
       ...:     d[i].send(AddrLocalUnicastSet(ConfigState.DEFAULT_RX_ADDR + i, 1))
       ...:
    2017-07-05 14:51:03,501 - INFO - SubnetAdd: {'subnet_handle': 0}
    2017-07-05 14:51:03,507 - INFO - AppkeyAdd: {'appkey_handle': 0}
    2017-07-05 14:51:03,512 - INFO - None
    2017-07-05 14:51:03,521 - INFO - SubnetAdd: {'subnet_handle': 0}
    2017-07-05 14:51:03,530 - INFO - AppkeyAdd: {'appkey_handle': 0}
    2017-07-05 14:51:03,534 - INFO - None
```

Add publish addresses

```
    In [2]: d[0].send(AddrPublicationAdd(ConfigState.DEFAULT_RX_ADDR + 1))
    2017-07-05 14:56:00,891 - INFO - AddrPublicationAdd: {'address_handle': 15}

    In [3]: d[1].send(AddrPublicationAdd(ConfigState.DEFAULT_RX_ADDR))
    2017-07-05 14:56:12,027 - INFO - AddrPublicationAdd: {'address_handle': 15}
```

Notice the handles, they are used to reference the addresses and keys at a later point.
Let us store them in some variables

```
    In [4]: publish_handle = 15
    In [5]: appkey_handle = 0
    In [6]: netkey_handle = 0
```

Next, we test out sending a message between the devices

```
    In [3]: device.send(PacketSend(0, ConfigState.DEFAULT_RX_ADDR, 15, 1, 0, 'Hello World'))
    2017-07-05 09:28:19,040 - INFO - None

    In [4]: 2017-07-05 09:28:19,067 - INFO - {event: MeshMessageReceivedUnicast, data: {'data': bytearray(b'Hello World}
```

### Getting help

To read the documentation for one of the commands, enter a `?` before the command
object and press `<enter>`. E.g., for the the `BeaconParamsSet` command, you would get

```
    In [2]: ?BeaconParamsSet
    Init signature: BeaconParamsSet(beacon_slot, tx_power, channel_map, interval_ms)
    Docstring:      Set parameters for application controlled beacon.
    File:           ~/dev/mbtle/scripts/interactive_pyaci/aci/aci_cmd.py
    Type:           type
```

The help prompt may be used for any python object or function.

The console also provides auto-completion, i.e., typing `?BeaconParamsS` and pressing `<tab>`
will complete the command packet object.

For a more details about the commands, please refer to the [serial commands documentation](@ref md_doc_libraries_serial_cmd).

### Miscellaneous

As with the normal Python shell, you can do more complex scripting, e.g.:

```
    In [3]: import time
    In [4]: for i in range(0, 10): send(Echo("Hello: " + str(i))); time.sleep(1)
    2017-07-04 15:46:22,822 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 0')}}
    2017-07-04 15:46:23,833 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 1')}}
    2017-07-04 15:46:24,840 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 2')}}
    2017-07-04 15:46:25,849 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 3')}}
    2017-07-04 15:46:26,855 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 4')}}
    2017-07-04 15:46:27,863 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 5')}}
    2017-07-04 15:46:28,872 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 6')}}
    2017-07-04 15:46:29,881 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 7')}}
    2017-07-04 15:46:30,890 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 8')}}
    2017-07-04 15:46:31,900 - INFO - {event: DeviceEchoRsp, data: {'data': bytearray(b'Hello: 9')}}
```

Where we use a simple `for`-loop to send 10 echo commands with a one second delay.
