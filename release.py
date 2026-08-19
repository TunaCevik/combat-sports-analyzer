import subprocess
import sys

def run_cmd(command):
    result = subprocess.run(command, shell=True, text=True, capture_output=True)
    return result.stdout.strip()

def get_latest_tag():
    tag = run_cmd("git describe --tags --abbrev=0")
    if not tag:
        return "v0.0.0"
    return tag

def bump_version():
    latest_tag = get_latest_tag()
    print(f"Current Latest Version: {latest_tag}")

    version_clean = latest_tag.lstrip("v")
    parts = version_clean.split(".")
    major, minor, patch = int(parts[0]), int(parts[1]), int(parts[2])

    commit_msgs = run_cmd(f"git log {latest_tag}..HEAD --pretty=format:%s").split("\n")

    bump_type = "patch"  # Default is patch
    for msg in commit_msgs:
        # Minor bump if a brand new feature is added
        if msg.startswith("feat:") or msg.startswith("new-project"):
            bump_type = "minor"

        # Patch bump for fixes, docs, errors, or refactoring
        elif (
            msg.startswith("fix:")
            or msg.startswith("docs:")
            or msg.startswith("error:")
            or msg.startswith("refactor:")
        ):
            pass

        # Major bump for breaking changes
        elif "BREAKING CHANGE" in msg or "!" in msg.split(":")[0]:
            bump_type = "major"
            break

    if bump_type == "major":
        major += 1
        minor = 0
        patch = 0
    elif bump_type == "minor":
        minor += 1
        patch = 0
    else:
        patch += 1

    new_tag = f"v{major}.{minor}.{patch}"
    print(f"New Version Determined: {new_tag} ({bump_type} bump)")
    return new_tag

if __name__ == "__main__":
    new_version = bump_version()
    
    confirm = input(f"Do you want to create and push tag '{new_version}'? (y/n): ")
    if confirm.lower() == "y":
        print(run_cmd(f"git tag {new_version}"))
        print(run_cmd(f"git push origin {new_version}"))
        print("Success! New tag pushed to remote repository.")
    else:
        print("Cancelled.")
