# Copyright (c) 2010 - 2017, Nordic Semiconductor ASA
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of Nordic Semiconductor ASA nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import logging
import IPython
import DateTime
import sys
import colorama
from argparse import ArgumentParser
from traitlets import config
from aci.aci_evt import Event
from aci.aci_cmd import *
from aci.aci_uart import Uart
from aci.aci_utils import STATUS_CODE_LUT


PRINT_ALL_EVENTS = True


USAGE_STRING = \
"""
    {c_default}{c_text}To control your device use {c_highlight}d[x]{c_text}, type {c_highlight}d[x].{c_text} and hit tab to see the available methods.
    x is for the device index; devices will be indexed based on the order of com ports
    given with the option -d(the first device, {c_highlight}d[0]{c_text}, can also be accessed using {c_highlight}device{c_text}).
    The log will be available in the calling directory as {log_name}.outlog{c_default}"""


def Num2Array(num):
    data = list()
    while num > 0:
        data.insert(0, num & 0xFF)
        num = num >> 8
    return data


def str2barray(_str):
    return [int(_str[i:i+2], 16) for i in range(0, len(_str), 2)]


class ConfigState(object):
    PRINT_ALL_EVENTS = True
    DEFAULT_NETWORK_KEY = [0xFA]*16
    DEFAULT_APP_KEY = [0xFA]*16
    DEFAULT_DEV_KEY = [0xFA]*16
    DEFAULT_VIRTUAL_ADDR = [0x34]*16
    DEFAULT_STATIC_AUTH_DATA = [0x12] * 16
    DEFAULT_RX_ADDR = 0x0101
    SOFTDEVICE_VERSION_NO = 0x0087
    NORDIC_COMPANY_ID = 0x00000059


class Interactive(object):
    def __init__(self, acidev):
        self.acidev = acidev
        # self.__ecdh_encryption = pyelliptic.ECC(curve='prime256v1')
        self.__peer_public_key = 0
        self.acidev.add_packet_recipient(self.__event_handler)
        self.logger = logging.getLogger(self.acidev.device_name)
        self._other_events = list()
        self._rx_addrs = list()
        self.send = self.acidev.write_aci_cmd

    def close(self):
        self.acidev.stop()

    def _event_filter(self, evts, match):
        for key in match:
            temp_evts = []
            for evt in evts:
                try:
                    if getattr(evt, key) == match[key]:
                        temp_evts.append(evt)
                except Exception as e:
                    self.logger.error(e)
            evts = temp_evts
        return evts

    def __event_handler(self, event):
        if event._opcode == Event.DEVICE_STARTED:
            self.logger.info("Device rebooted.")
            self._rx_addrs = []

        elif event._opcode == Event.CMD_RSP:
            if event._data["status"] != 0:
                self.logger.error("{}{}: {}{}".format(colorama.Fore.RED,
                                                      response_deserialize(event),
                                                      STATUS_CODE_LUT[event._data["status"]]["code"],
                                                      colorama.Style.RESET_ALL))
            else:
                self.logger.info(colorama.Fore.GREEN + str(response_deserialize(event)) + colorama.Style.RESET_ALL)
        else:
            if ConfigState.PRINT_ALL_EVENTS and event != None:
                self.logger.info(str(event))

        self._other_events.append(event)

    def filtered_events_clear(self):
        self._other_events.clear()

    def raw_events_clear(self):
        self.acidev.events_queue.clear()

    def raw_events_get(self, match={}):
        return self._event_filter(self.acidev.events_queue, match)

    def filtered_events_get(self, match={}):
        return self._event_filter(self._other_events, match)

    def device_port_get(self):
        return self.acidev.serial.port

    def quick_setup(self):
        self.send(aci_cmd.SubnetAdd(0, bytearray(ConfigState.DEFAULT_NETWORK_KEY)))
        self.send(aci_cmd.AppkeyAdd(0, 0, bytearray(ConfigState.DEFAULT_APP_KEY)))
        self.send(aci_cmd.AddrLocalUnicastSet(ConfigState.DEFAULT_RX_ADDR, 1))


def get_ipython_config(device, no_logfile):

    # os.environ['PYTHONSTARTUP'] = ''  # Prevent running this again
    c = config.get_config()
    c.TerminalInteractiveShell.confirm_exit = False
    c.InteractiveShellApp.multiline_history = True

    if not no_logfile:
        c.TerminalInteractiveShell.logstart     = True
        c.InteractiveShellApp.db_log_output = True
        c.TerminalInteractiveShell.logfile = '%s.log' %device
    else:
        c.TerminalInteractiveShell.logstart = False
        c.InteractiveShellApp.db_log_output = False

    c.InteractiveShellApp.log_level = 0
    return c


def configure_logger(log_name, no_logfile):
    logger = logging.getLogger(log_name)
    logger.setLevel(logging.INFO)

    ch = logging.StreamHandler(sys.stdout)
    ch.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    ch.setFormatter(formatter)
    logger.addHandler(ch)

    if not no_logfile:
        fh = logging.FileHandler(log_name + '.outlog')
        fh.setLevel(logging.INFO)
        fh.setFormatter(formatter)
        logger.addHandler(fh)


def start_ipython(options, log_name):
    colorama.init()
    comports = options.device.split(',')
    d = list()
    #Print out a mini intro to the interactive session -- Start with white and then magenta to keep the session white (workaround for a bug in ipython)
    colors = {"c_default": colorama.Fore.WHITE,
              "c_highlight": colorama.Fore.YELLOW,
              "c_text": colorama.Fore.MAGENTA}

    print(USAGE_STRING.format(log_name=log_name, **colors))

    for dev_com in comports:
        d.append(Interactive(Uart(port=dev_com,
                                  baudrate=options.baudrate,
                                  device_name=log_name)))

    device = d[0]

    send = device.acidev.write_aci_cmd

    IPython.embed(config=get_ipython_config(log_name, options.no_logfile))
    for dev in d:
        dev.close()
    raise SystemExit(0)

if __name__ == '__main__':
    parser = ArgumentParser(description="Nordic BLE Mesh Interactive Serial Interface")
    parser.add_argument("-d", "--device", dest="device", required=True, help="Device Communication port, e.g., COM216 or /dev/ttyACM0. Separate ports with ','")
    parser.add_argument("-b", "--baudrate", dest="baudrate", required=False, default='115200', help="Baud rate. Default: 115200")
    parser.add_argument("--no-logfile", dest="no_logfile", action="store_true", required=False, default=False, help="Disables logging to file.")
    options = parser.parse_args()

    dt = DateTime.DateTime()
    device_log_name = "%s_%s-%d-%d-%d" %(options.device.split("/")[-1], dt.yy(), dt.dayOfYear(), dt.hour(), dt.minute())
    configure_logger(device_log_name, options.no_logfile)

    start_ipython(options, device_log_name)
