import os


def read_file_content(file_path):
    with open(file_path, "r") as file:
        content = file.read()
        return content


def write_file_content(file_path, content):
    with open(file_path, "w") as file:
        file.write(content)


if __name__ == "__main__":
    """This script replaces all backslashes with forward slashes in a file."""
    settings_file = "file_to_build.txt"

    cpp_file = read_file_content(settings_file)
    cpp_file = cpp_file.replace("\\", "/")

    # make the path in content relative to the script directory
    this_script_full_path = os.path.realpath(__file__)
    this_script_dir = os.path.dirname(this_script_full_path)
    this_script_dir = this_script_dir.replace("\\", "/")
    cpp_file = cpp_file.replace(this_script_dir, "../..")

    write_file_content(settings_file, cpp_file)
