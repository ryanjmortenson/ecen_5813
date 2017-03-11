import argparse
import os
import serial
import multiprocessing
import sys
import traceback

process_char = None

def to_hex(char):
    return '0x{} '.format(char.encode('hex'))

def normal(char):
    return char

def recv_process(ser):
    try:
        while(True):
            sys.stdout.write(process_char(ser.read()))
            sys.stdout.flush()
    except:
        print("Done Receving")
        traceback.print_exc()


if __name__ == "__main__":

    # Setup parser for com port
    parser = argparse.ArgumentParser()
    parser.add_argument("port",
                        help="COM port for Linux usually /dev/ttyUSB* Windows usually COM*")
    parser.add_argument("baud_rate", type=int,
                        help="Baud rate to use for communication")
    parser.add_argument("--hex", "-H", action="store_true",
                        help="Display data received in hex")

    # Parse args
    args = parser.parse_args()

    if args.hex == True:
        process_char = to_hex
    else:
        process_char = normal


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

    recv = multiprocessing.Process(target=recv_process, args=(ser,), name=recv_process)
    recv.start()

    try:
        while(True):
            line = raw_input()
            ser.write(line)
    except:
        print("Done Receving")
        traceback.print_exc()


