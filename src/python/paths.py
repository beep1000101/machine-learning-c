from enum import StrEnum
from pathlib import Path


class Directories(StrEnum):
    DATA = "data"


ROOT = Path(__file__).parents[2]
DATA_DIR = ROOT / Directories.DATA
