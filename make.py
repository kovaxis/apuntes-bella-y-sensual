#!/usr/bin/env python3

from argparse import ArgumentParser
from dataclasses import dataclass
import os
from pathlib import Path
import platform
import subprocess
import sys
import time
import re

EXT_WHITELIST = [".cpp", ".c", ".typ", ".txt"]
PLATFORM_TYPST = {
    "Windows": "typst-windows.exe",
    "Linux": "typst-linux",
}

NEWLINE = "\n"

base_path = Path(__file__).parent

conf: "Conf"

def section_name(raw: str) -> str | None:
    if raw.startswith("."):
        return None
    return " ".join(w.capitalize() for w in raw.split())

def file_name(name: str) -> str | None:
    for ext in EXT_WHITELIST:
        if name.endswith(ext):
            name = name.removesuffix(ext)
            name = re.split("[-_\s]+", name)
            return " ".join(w.lower() for w in name)
    return None

def file_contents(filename: str, raw: str) -> str:
    if filename.endswith(".typ"):
        # Treat as typst source
        return "#[\n" + raw.strip() + "\n]"

    # Treat as code
    extension = ""
    if "." in filename:
        extension = filename.split(".")[-1]
    return "```"+extension+"\n"+raw.strip()+"\n```"

def compose_file(name: str, file: str) -> str:
    return f"""
== {name}

{file}
    """

def compose_section(name: str, section: list[tuple[str, str]]) -> str:
    return f"""
= {name}

{NEWLINE.join(compose_file(filename, file) for filename, file in section)}
    """

def compose(sections: list[tuple[str, list[tuple[str, str]]]]) -> str:
    template = """
// Document config

#set page(flipped: true, margin: margin, paper: paper)
#set text(font: "New Computer Modern")
#show raw: set text(font: "DejaVu Sans Mono", weight: 500, size: font_size)
#set raw(theme: "themes/"+theme+".tmTheme") if theme != ""

// Title

#align(center, {
  text(size: 10mm)[Team Notebook]
  v(-3mm)
  text(size: 6mm, uni + " - " + team)
})

// Index

#place(columns(cols, gutter: gutter, {
  for i in range(cols - 1) {
    colbreak()
    align(left+top, move(line(angle: 90deg, length: 164mm), dx: -gutter/2))
  }
}))
#columns(cols, gutter: gutter, {
  show outline.entry.where(level: 1): set text(weight: "bold")
  outline(title: none, indent: 5mm)
})

// Body setup

#pagebreak(weak: true)

#set page(header: {
  align(left, move(uni + " - " + team, dy: 100%))
  align(right, move(counter(page).display()))
})
#set page(background: pad(margin, {
  columns(cols, gutter: gutter, {
    for i in range(cols - 1) {
      colbreak()
      align(left+top, move(line(angle: 90deg, length: 100%), dx: -gutter/2))
    }
  })
}))
#show: columns.with(3, gutter: gutter)

#set heading(numbering: "1.1")
#show heading.where(level: 2): it => {
  it
  v(-3mm)
  move(line(length: 100% + gutter), dx: -gutter/2)
}

// Body contents
    """

    vars = {
        "font_size": conf.font_size,
        "uni": '"' + conf.university + '"',
        "team": '"' + conf.team + '"',
        "cols": conf.column_count,
        "gutter": conf.column_gutter,
        "margin": conf.margin,
        "paper": '"' + conf.paper + '"',
        "theme": '"' + conf.theme + '"',
    }
    var_defs = "\n".join(f"#let {key} = {val}" for key, val in vars.items())
    content = "\n".join(compose_section(name, section) for name, section in sections)
    return var_defs + template + content

def ingest() -> list[tuple[str, list[tuple[str, str]]]]:
    sections = []
    for dirname in os.listdir(base_path):
        dir = base_path.joinpath(dirname)
        if dir.is_dir():
            secname = section_name(dirname)
            if secname is not None:
                sec = []
                for filename in os.listdir(dir):
                    fname = file_name(filename)
                    if fname is not None:
                        filepath = dir.joinpath(filename)
                        txt = filepath.read_text()
                        sec.append((fname, file_contents(filename, txt)))
                sections.append((secname, sec))
    return sections

def compile(src: str):
    if conf.print_source:
        print("printing source code instead of compiling because --print-source flag was received")
        print("typst source code:")
        print(src)
    else:
        system = platform.system()
        exe_name = PLATFORM_TYPST.get(system)
        if exe_name is None:
            raise RuntimeError(f"typst binary not available for platform '{system}'")
        typst_dir = base_path.joinpath(".typst")
        exe_path = typst_dir.joinpath(exe_name)
        out_path = base_path.joinpath(conf.out_file)
        subprocess.run([exe_path, "compile", "--root", typst_dir, "--format", "pdf", "-", out_path], input=src.encode("utf-8"))
        print(f"wrote pdf to {conf.out_file}")


@dataclass
class Conf:
    out_file: str
    university: str
    team: str

    print_source: bool

    font_size: str
    column_count: str
    column_gutter: str
    margin: str
    paper: str
    theme: str

    @staticmethod
    def parse() -> "Conf":
        p = ArgumentParser(description="Make a competitive programming notebook from source files")
        p.add_argument("-o", "--out", required=True, help="Output file path")
        p.add_argument("--print-source", action="store_true", help="Print Typst source instead of compiling a PDF")
        p.add_argument("-u", "--university", default="<university>", help="University name")
        p.add_argument("-t", "--team", default="<team>", help="Team name")
        p.add_argument("--font-size", default="6.984pt", help="Size of the font used for code")
        p.add_argument("--column-count", default="3", help="Number of columns")
        p.add_argument("--column-gutter", default="5mm", help="Space between columns")
        p.add_argument("--margin", default="10mm", help="Page margin")
        p.add_argument("--paper", default="a4", help="Page paper size")
        p.add_argument("--theme", default="", help="Code highlighting theme")
        args = sys.argv[1:]
        confpath = base_path.joinpath("makeconf")
        if confpath.is_file():
            extra = confpath.read_text().splitlines()
            args = extra + args
        p = p.parse_args(args)
        return Conf(print_source=p.print_source, out_file=p.out, university=p.university, team=p.team, font_size=p.font_size, column_count=p.column_count, column_gutter=p.column_gutter, margin=p.margin, paper=p.paper, theme=p.theme)

def main():
    global conf
    start = time.monotonic()

    conf = Conf.parse()

    print("processing input files")
    sections = ingest()
    src = compose(sections)

    print("compiling to pdf")
    compile(src)
    
    print(f"done in {time.monotonic() - start:.2f}s")

if __name__ == "__main__":
    main()