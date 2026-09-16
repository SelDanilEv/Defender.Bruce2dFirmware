import datetime
import os


def generate_build_header():
    counter_path = "build_number.txt"

    try:
        with open(counter_path, "r") as f:
            current = int(f.read().strip())
    except (FileNotFoundError, ValueError):
        current = 0

    build_number = current + 1

    with open(counter_path, "w") as f:
        f.write(str(build_number))

    date_str = datetime.datetime.now().strftime("%Y%m%d")
    header_content = f'#pragma once\n#define BRUCE_BUILD "b{build_number} {date_str}"\n'

    output_path = os.path.join("include", "build_version.h")
    os.makedirs("include", exist_ok=True)

    with open(output_path, "w") as f:
        f.write(header_content)


def before_build(source, target, env):
    generate_build_header()


# Hook for PlatformIO
def on_pre_build(env):
    before_build(None, None, env)


# Register the pre-build hook
Import("env")
on_pre_build(env)
