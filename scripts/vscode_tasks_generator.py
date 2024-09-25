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
            print(f"Replaced {carousel[i]} with {carousel[i + 1]}")
            break  # only one replacement

    with open(VSCODE_FILE_PATH, "w") as file:
        file.write(content)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--test", action="store_true", default=False, help="Toogle Google Test Linking")
    parser.add_argument("--benchmark", action="store_true", default=False, help="Toogle Google Benchmark Linking")
    parser.add_argument("--config", action="store_true", default=False, help="Toogle Debug/Release Configuration")
    parser.add_argument("--standard", action="store_true", default=False, help="Toogle C++ Standard")
    parser.add_argument("--deleaker_verbose", action="store_true", default=False, help="Toogle Deleaker Verbose")
    parser.add_argument("--boost", action="store_true", default=False, help="Toogle Boost Linking")
    parser.add_argument("--toggle_vcpkg", action="store_true", default=False, help="Toogle Vcpkg As Dependency Manager")
    parser.add_argument("--openssl", action="store_true", default=False, help="Toogle OpenSSL Linking")
    parser.add_argument("--libpng", action="store_true", default=False, help="Toogle LibPNG Linking")
    parser.add_argument("--toggle_cmake_generator", action="store_true", default=False, help="Toogle CMake Generator")
    parser.add_argument("--toggle_enable_sanitizers", action="store_true", default=False, help="Toogle Enable Sanitizers")
    # Projects:
    parser.add_argument("--boost_beast_chat_multi", action="store_true", default=False, help="Boost Beast Chat Multi")

    args = parser.parse_args()

    if args.test:
        toggle_text_in_vscode_task_content(["-DLINK_GOOGLE_TEST=ON", "-DLINK_GOOGLE_TEST=OFF"])

    if args.benchmark:
        toggle_text_in_vscode_task_content(["-DLINK_GOOGLE_BENCHMARK=ON", "-DLINK_GOOGLE_BENCHMARK=OFF"])

    if args.config:
        toggle_text_in_vscode_task_content(["-DCMAKE_BUILD_TYPE=Debug", "-DCMAKE_BUILD_TYPE=Release"])
        toggle_text_in_vscode_task_content(["build/debug", "build/release"])

    if args.standard:
        toggle_text_in_vscode_task_content(
            ["-DCMAKE_CXX_STANDARD=11", "-DCMAKE_CXX_STANDARD=17", "-DCMAKE_CXX_STANDARD=20", "-DCMAKE_CXX_STANDARD=23"]
        )

    if args.deleaker_verbose:
        toggle_text_in_vscode_task_content(
            ["parse_deleaker_report.py --verbose", "parse_deleaker_report.py --no-verbose"]
        )

    if args.boost:
        toggle_text_in_vscode_task_content(["-DLINK_BOOST=ON", "-DLINK_BOOST=OFF"])

    if args.toggle_vcpkg:
        toggle_text_in_vscode_task_content(["--preset use_global_vcpkg", "--preset use_native", "--preset use_local_vcpkg"])

    if args.openssl:
        toggle_text_in_vscode_task_content(["-DLINK_OPENSSL=ON", "-DLINK_OPENSSL=OFF"])

    if args.libpng:
        toggle_text_in_vscode_task_content(["-DLINK_LIBPNG=ON", "-DLINK_LIBPNG=OFF"])

    if args.boost_beast_chat_multi:
        toggle_text_in_vscode_task_content(
            ["-DPROJECT_BOOST_BEAST_CHAT_MULTI=ON", "-DPROJECT_BOOST_BEAST_CHAT_MULTI=OFF"]
        )

    if args.toggle_cmake_generator:
        toggle_text_in_vscode_task_content(
            ['-G \\"Ninja\\"', '-G \\"Unix Makefiles\\"']
        )

    if args.toggle_enable_sanitizers:
        toggle_text_in_vscode_task_content(
            ["-DENABLE_SANITIZERS=ON", "-DENABLE_SANITIZERS=OFF"]
        )

