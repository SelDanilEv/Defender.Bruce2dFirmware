import os

Import("env")

proj_dir = env.subst("$PROJECT_DIR")


def _read_minor_version():
    with open(os.path.join(proj_dir, "VERSION"), "r") as f:
        return f.read().strip()


def _read_last_full_version(minor_version):
    counter_path = os.path.join(proj_dir, "build_version.txt")
    try:
        with open(counter_path, "r") as f:
            last = f.read().strip()
    except FileNotFoundError:
        return None

    parts = last.split(".")
    if len(parts) != 3 or not all(p.isdigit() for p in parts):
        return None
    if f"{parts[0]}.{parts[1]}" != minor_version:
        return None
    return last


def compute_full_version():
    minor_version = _read_minor_version()
    last_full_version = _read_last_full_version(minor_version)

    if last_full_version is None:
        patch = 0
    else:
        patch = int(last_full_version.split(".")[2]) + 1

    return f"{minor_version}.{patch}"


def generate_build_header():
    full_version = compute_full_version()

    with open(os.path.join(proj_dir, "build_version.txt"), "w") as f:
        f.write(full_version)

    header_content = f'#pragma once\n#define BRUCE_BUILD "v{full_version}"\n'

    output_path = os.path.join(proj_dir, "include", "build_version.h")
    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    with open(output_path, "w") as f:
        f.write(header_content)


def before_build(source, target, env):
    generate_build_header()


def on_pre_build(env):
    before_build(None, None, env)


on_pre_build(env)
