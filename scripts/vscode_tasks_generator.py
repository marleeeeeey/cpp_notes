import argparse

VSCODE_FILE_PATH = ".vscode/tasks.json"


def toggle_text_in_vscode_task_content(carousel: list):
    """
    Toggles the text in the vscode task file.
    Example: carousel = ["a", "b"]
    """

    if len(carousel) < 2:
        return

    carousel.append(carousel[0])  # carousel = ["a", "b", "a"]

    with open(VSCODE_FILE_PATH, "r") as file:
        content = file.read()

    for i in range(len(carousel) - 1):
        if carousel[i] in content:
            content = content.replace(carousel[i], carousel[i + 1])  # replace a with b
            break  # only one replacement

    with open(VSCODE_FILE_PATH, "w") as file:
        file.write(content)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--test", action="store_true", default=False, help="Toogle Google Test Linking")
    parser.add_argument("--benchmark", action="store_true", default=False, help="Toogle Google Benchmark Linking")
    parser.add_argument("--config", action="store_true", default=False, help="Toogle Debug/Release Configuration")
    parser.add_argument("--standard", action="store_true", default=False, help="Toogle C++ Standard")
    args = parser.parse_args()

    if args.test:
        toggle_text_in_vscode_task_content(["-DLINK_GOOGLE_TEST=ON", "-DLINK_GOOGLE_TEST=OFF"])

    if args.benchmark:
        toggle_text_in_vscode_task_content(["-DLINK_GOOGLE_BENCHMARK=ON", "-DLINK_GOOGLE_BENCHMARK=OFF"])

    # -DCMAKE_BUILD_TYPE=Debug
    if args.config:
        toggle_text_in_vscode_task_content(["-DCMAKE_BUILD_TYPE=Debug", "-DCMAKE_BUILD_TYPE=Release"])
        toggle_text_in_vscode_task_content(["build/debug", "build/release"])

    if args.standard:
        toggle_text_in_vscode_task_content(
            ["-DCMAKE_CXX_STANDARD=11", "-DCMAKE_CXX_STANDARD=17", "-DCMAKE_CXX_STANDARD=20", "-DCMAKE_CXX_STANDARD=23"]
        )
