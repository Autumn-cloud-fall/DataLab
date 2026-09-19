#!/usr/bin/env python3
"""Run the bundled legacy dlc against both original and renamed puzzles."""

import re
import subprocess
import sys
import tempfile
from pathlib import Path


PUZZLES = [
    ("signMask", "signMask", 2),
    ("bitXor", "bitXor", 8),
    ("negativePart", "negativePart", 6),
    ("copyByteWithin", "overflowCalc", 12),
    ("logicalShift", "logicalShift", 20),
    ("swapNibblePairs", "swapNibblePairs", 18),
    ("secondLowestZeroBit", "secondLowestZeroBit", 8),
    ("oddParity", "oddParity", 56),
    ("rotateRightBits", "rotateRightBits", 16),
    ("roundEvenPow2", "isLargerOrEqual", 24),
    ("midpointTowardFirst", "isLargerOrEqual", 32),
    ("isBetweenEitherOrder", "overflowCalc", 48),
    ("mul5Sat", "mul5Sat", 30),
    ("classifyAdd3", "overflowCalc", 52),
    ("floatScaleThreeHalves", "float_half", 60),
    ("floatRoundEven", "float_half", 65),
    ("float_i2f", "float_i2f", 40),
    ("bitCount", "bitCount", 40),
    ("bitReverse", "bitReverse", 34),
]


def extract_function(source: str, name: str) -> str:
    pattern = re.compile(r"\b(?:int|unsigned)\s+" + re.escape(name) + r"\s*\(")
    match = pattern.search(source)
    if not match:
        raise ValueError(f"function {name} was not found")
    brace = source.find("{", match.end())
    if brace < 0:
        raise ValueError(f"function {name} has no body")
    depth = 0
    for pos in range(brace, len(source)):
        if source[pos] == "{":
            depth += 1
        elif source[pos] == "}":
            depth -= 1
            if depth == 0:
                return source[match.start():pos + 1]
    raise ValueError(f"function {name} has an unterminated body")


def main() -> int:
    source_path = Path(sys.argv[1] if len(sys.argv) > 1 else "bits.c")
    source = source_path.read_text(encoding="utf-8")
    dlc = Path(__file__).resolve().with_name("dlc")
    failures = []

    for name, proxy, maximum in PUZZLES:
        try:
            body = extract_function(source, name)
        except ValueError as error:
            failures.append(str(error))
            continue
        if name != proxy:
            body = re.sub(r"\b" + re.escape(name) + r"(?=\s*\()", proxy, body,
                          count=1)
        with tempfile.NamedTemporaryFile("w", suffix=".c", encoding="utf-8") as temp:
            temp.write(body + "\n")
            temp.flush()
            result = subprocess.run(
                [str(dlc), "-e", temp.name], text=True,
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=False
            )
        output = result.stdout.strip()
        count_match = re.search(
            rf"\b{re.escape(proxy)}: (?:Warning: )?(\d+) operators", output
        )
        illegal = [line for line in output.splitlines() if "Illegal" in line]
        if not count_match:
            failures.append(f"{name}: dlc did not report an operator count\n{output}")
            continue
        count = int(count_match.group(1))
        if illegal:
            failures.append(f"{name}:\n" + "\n".join(illegal))
        elif count > maximum:
            failures.append(f"{name}: {count} operators exceeds limit {maximum}")
        else:
            print(f"{name}: {count}/{maximum} operators")

    if failures:
        print("\nOperator check failed:", file=sys.stderr)
        print("\n".join(failures), file=sys.stderr)
        return 1
    print("All 19 functions passed operator checks.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
