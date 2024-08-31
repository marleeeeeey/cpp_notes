import re
from collections import Counter
from datetime import datetime


def parse_md_file(md_content, tag_pattern):
    """Parse the markdown content and count the tags."""

    tags = []

    # Split the markdown content into lines
    lines = md_content.splitlines()

    for line in lines:
        # Search for tags in each line
        match = tag_pattern.search(line)
        if match:
            tags.append(match.group(1))

    # Sort the tags
    tags.sort()

    return Counter(tags)


def generate_mermaid_pie_chart(tag_counts):
    """Generate a pie chart diagram in Mermaid syntax."""
    chart = "pie\n"
    for tag, count in tag_counts.items():
        chart += f'  "{tag}" : {count}\n'
    return chart


def dump_chart_to_file(tag_counts, filename="DEBUG.md"):
    """Dump the pie chart to a file."""
    # Generate a pie chart diagram in Mermaid syntax
    mermaid_chart = generate_mermaid_pie_chart(tag_counts)

    # Get the current date in YYYY-MM-DD format
    current_date = datetime.now().strftime("%Y-%m-%d")

    # Content to be added to PROGRESS.md
    mermaid_section = f"### {current_date}\n\n```mermaid\n{mermaid_chart}```\n\n"

    # Append the new section to PROGRESS.md
    with open(filename, "a") as progress_file:
        progress_file.write(mermaid_section)

    print(f"Mermaid diagram appended to {filename}.")


# BUSINESS LOGIC
# ##############


def update_debug_file(md_content):
    tag_pattern = re.compile(r"\[([\S_]*)\]")
    tag_counts = parse_md_file(md_content, tag_pattern)
    dump_chart_to_file(tag_counts, "PROGRESS.md")


# MAIN
# ####


def main():
    # read md_content from file `LINKS.md`
    with open("LINKS.md", "r", encoding="utf8") as file:
        md_content = file.read()

    update_debug_file(md_content)


if __name__ == "__main__":
    main()
