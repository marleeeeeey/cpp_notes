def read_file_content(file_path):
    with open(file_path, "r") as file:
        content = file.read()
        return content


def write_file_content(file_path, content):
    with open(file_path, "w") as file:
        file.write(content)


if __name__ == "__main__":
    """This script replaces all backslashes with forward slashes in a file."""
    file_path = "file_to_build.txt"
    content = read_file_content(file_path)
    content = content.replace("\\", "/")
    write_file_content(file_path, content)
