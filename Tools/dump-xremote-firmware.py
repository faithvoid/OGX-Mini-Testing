import os
import sys
import platform
import subprocess

script_dir = os.path.dirname(os.path.realpath(__file__))
os.chdir(script_dir)

dumper_script = "dump-dvd-kit/dump-dvd-kit.py"
header_path = "../Firmware/RP2040/src/USBDevice/DeviceDriver/XboxOG/tud_xid/tud_xid_xremote_rom.h"
array_name = "ROM"

def run_command(command):
    print(f"Running command: {command}")
    process = subprocess.Popen(command, shell=True)
    process.wait()
    return process.returncode

def find_bin_file():
    for file in os.listdir("."):
        if file.endswith(".bin"):
            return file
    return None

def bin_to_header(bin_file, header_file):
    with open(bin_file, "rb") as f:
        byte_array = f.read()

    with open(header_file, "w") as f:
        f.write(f"// Auto-generated by dump-xremote-firmware.py\n\n")
        f.write(f"#ifndef _XREMOTE_ROM_H_\n")
        f.write(f"#define _XREMOTE_ROM_H_\n\n")
        f.write(f"#include <cstdint>\n\n")
        f.write(f"namespace tud_xid {{\nnamespace XRemote {{\n\n")
        f.write(f"static const uint8_t {array_name}[] = {{\n")
        for i, byte in enumerate(byte_array):
            if i % 12 == 0:
                f.write("\n")
            f.write(f"0x{byte:02x}, ")
        f.write("\n};\n\n")
        f.write(f"const unsigned int {array_name}_LEN = {len(byte_array)};\n\n")
        f.write(f"}} // namespace XRemote\n}} // namespace tud_xid\n\n")
        f.write(f"#endif // _XREMOTE_ROM_H_\n")

bin_file = find_bin_file()

if bin_file:
    print(f"Found .bin file: {bin_file}")
    bin_to_header(bin_file, header_path)
else:
    if platform.system() == "Windows":
        ret_code = run_command(f"python {dumper_script}")
        if ret_code == 0:
            bin_file = find_bin_file()
            if bin_file:
                bin_to_header(bin_file, header_path)
            else:
                print("Error: No .bin file found after running dumper script")
        else:
            print("Error: Python script failed")
    elif platform.system() in ["Linux", "Darwin"]:
        ret_code = run_command(f"python3 {dumper_script}")
        if ret_code == 0:
            bin_file = find_bin_file()
            if bin_file:
                bin_to_header(bin_file, header_path)
            else:
                print("Error: No .bin file found after running dumper script")
        else:
            print("Error: Python script failed")
    else:
        print(f"Unsupported OS: {platform.system()}")
        sys.exit(1)