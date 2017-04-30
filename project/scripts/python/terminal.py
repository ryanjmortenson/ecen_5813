import argparse
import os
import serial
import multiprocessing
import sys
import traceback
import struct
from time import sleep

process_char = None

command = {
    "CMD_ALL": 0,
    "CMD_GET_TEMP": 1,
    "CMD_SET_SPEED": 2,
    "CMD_LED_CONFIG": 3,
    "CMD_SET_LPM": 4,
    "CMD_GET_TIMESTAMP": 5,
    "CMD_SYSTEM_RESET": 6,
}

def to_hex(char):
    '''
    Formats received data as hex

    :param char: character to format as hex

    :return: hex representation as string
    '''

    return '0x{} '.format(char.encode('hex'))

def normal(char):
    '''
    Formats received data as it is already formatted

    :param char: character to format as hex

    :return: character
    '''

    return char

def recv_process(ser):
    '''
    Process used for receiving and printing data

    :param ser: serial object
    '''

    try:
        while(True):
            sys.stdout.write(process_char(ser.read()))
            sys.stdout.flush()
    except:
        print("Done Receving")

def handle_packet(cmd_id, packet_list):
    '''
    Creates a packet to send of UART.  Will determine length and calculate
    checksum.

    :param cmd_id: command being sent over uart
    :param packet_list: list of data to packetize

    :return: binary data string
    '''

    data = str()

    # Pack the command id and the length
    data = struct.pack('B', cmd_id)
    data += struct.pack('B', len(packet_list))

    # Pack the checksum after calculating
    check_sum = 0
    if packet_list:
        check_sum = reduce(lambda x,y: x + y, packet_list)
    for item in packet_list:
        data += struct.pack('B', item)
    data += struct.pack('B', check_sum >> 8)
    data += struct.pack('B', check_sum & 0xff)

    # Display created data
    print("Created data: {}".format(" ".join([to_hex(x) for x in data])))
    return data

def handle_led_cmd(args):
    '''
    Create a led packet

    :param args: arguments from argparse

    :return: binary data string
    '''

    packet = list()

    # Create the control field of the packet with turns RGB on/off
    control = (args.ron << 2) | (args.gon << 1) | args.bon
    packet.append(control)

    # Create the 16-bit value used to set PWM counter
    packet.extend([args.rcnt >> 8, args.rcnt & 0xff])
    packet.extend([args.gcnt >> 8, args.gcnt & 0xff])
    packet.extend([args.bcnt >> 8, args.bcnt & 0xff])

    return handle_packet(command["CMD_LED_CONFIG"], packet)

def handle_rtc_cmd(args):
    '''
    Create a rtc timestamp packet

    :param args: arguments from argparse

    :return: binary data string
    '''

    return handle_packet(command["CMD_GET_TIMESTAMP"], [])

def handle_reset_cmd(args):
    '''
    Create a system reset packet

    :param args: arguments from argparse

    :return: binary data string
    '''

    return handle_packet(command["CMD_SYSTEM_RESET"], [])

if __name__ == "__main__":

    # Setup parser for com port
    parser = argparse.ArgumentParser()
    parser.add_argument("port",
                        help="COM port for Linux usually /dev/ttyUSB* Windows usually COM*")
    parser.add_argument("baud_rate", type=int,
                        help="Baud rate to use for communication")
    parser.add_argument("--hex", "-H", action="store_true",
                        help="Display data received in hex")

    sub = parser.add_subparsers(dest="command", help="Commands")
    led_cmd = sub.add_parser("led_cmd", help="Send and LED command via UART")
    led_cmd.add_argument("--ron", action="store_true", help="Turn Red on")
    led_cmd.add_argument("--gon", action="store_true", help="Turn Green on")
    led_cmd.add_argument("--bon", action="store_true", help="Turn Blue on")
    led_cmd.add_argument("--rcnt", type=int, default=0,
                         help="Red PWM Count 0-65535")
    led_cmd.add_argument("--gcnt", type=int, default=0,
                         help="Green PWM Count 0-65535")
    led_cmd.add_argument("--bcnt", type=int, default=0,
                         help="Blue PWM Count 0-65535")

    log_cmd = sub.add_parser("log", help="Just log don't send commands")
    reset = sub.add_parser("reset", help="Reset KL25Z")
    rtc = sub.add_parser("rtc", help="Get the RTC timestamp from KL25Z")

    # Parse args
    args = parser.parse_args()

    # Set the process character function
    if args.hex == True:
        process_char = to_hex
    else:
        process_char = normal

    # Build commands to be sent
    if args.command == "log":
        data = None
    elif args.command == "led_cmd":
        data = handle_led_cmd(args)
    elif args.command == "reset":
        data = handle_reset_cmd(args)
    elif args.command == "rtc":
        data = handle_rtc_cmd(args)

    # Instantiate serial object
    ser = serial.Serial(
        port=args.port,
        baudrate=args.baud_rate,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
    )

    # Open serial port
    ser.isOpen()

    # Kick off process for receive
    recv = multiprocessing.Process(target=recv_process,
                                   args=(ser,),
                                   name=recv_process)
    recv.start()

    # Either loop forever or send command
    try:
        if data and args.command != "log":
            line = raw_input("Waiting for Enter to send command\n")
            ser.write(data)
            sleep(30)
        elif args.command == "log":
            while(True):
                line = raw_input("Enter text and press enter to send\n")
                ser.write(data)
                pass
    except:
        print("Done Receving")
