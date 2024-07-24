import xml.etree.ElementTree as ET
import re
import argparse

VERBOSE = False


def read_stack_entry(stack_entry, ignore_paths_regexs=None):
    function_name = stack_entry.get("FunctionName")
    file_name = stack_entry.get("FileName")

    if ignore_paths_regexs:
        for ignore_path_regex in ignore_paths_regexs:
            if re.search(ignore_path_regex, file_name):
                return None

    line = stack_entry.get("Line")
    return f"{function_name:50} in {file_name}:{line}"


def read_stack_trace_as_lines(stack_trace_nodes, ignore_path_regexs=None):
    stack_lines = []
    for stack_entry in stack_trace_nodes.findall("StackEntry"):
        stack_entry_str = read_stack_entry(stack_entry, ignore_path_regexs)
        if stack_entry_str:
            stack_lines.append(stack_entry_str)
    return stack_lines


def print_deleaker_report(xml_path):
    tree = ET.parse(xml_path)
    root = tree.getroot()

    for snapshot in root.findall("Snapshot"):
        for allocation in snapshot.findall("Allocation"):

            address = allocation.get("Value")
            type = allocation.get("Type")
            hit_count = allocation.get("HitCount")
            size = allocation.get("Size")
            file_line = f"{allocation.get('FileName')}:{allocation.get('Line')}"
            module = allocation.get("ModuleName")

            if VERBOSE:
                print("Leak detected:")
                print(f"  Address: {address}")
                print(f"  Type: {type}")
                print(f"  HitCount: {hit_count}")
                print(f"  Size: {size} bytes")
            print(f"  File: {file_line}")
            if VERBOSE:
                print(f"  Module: {module}")
                print("  Stack trace:")
                stack_trace_nodes = allocation.find("StackTrace")
                stack_trace_lines = read_stack_trace_as_lines(stack_trace_nodes, {"vctools.*startup"})
                for stack_line in stack_trace_lines:
                    print(f"    {stack_line}")
                print("----------------------------")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
    args = parser.parse_args()
    VERBOSE = args.verbose

    print("************************************")
    print("DELEAKER REPORT")
    print_deleaker_report("leak_report.xml")
    print("************************************")
