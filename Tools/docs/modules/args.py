# Created by Henry Jooste

import os
import argparse


class Args:
    parser = None
    input_file = None
    output_file = None
    widget = None

    def __init__(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument("-i", "--input", metavar="\b",
                                 help="Specify the file used to generate the docs", required=True)
        self.parser.add_argument("-o", "--output", metavar="\b",
                                 help="Specify the name of the output file", required=True)
        self.parser.add_argument("-w", "--widget", metavar="\b",
                                 help="Specify the name of the widget implementation", required=False)
        self.parse()

    def parse(self):
        args = self.parser.parse_args()
        self.input_file = args.input.replace(".h", "").replace(".cpp", "") + ".h"
        self.input_file = os.path.abspath(os.path.join(os.path.dirname(__file__), "..\\..\\..\\Source\\USK", self.input_file))
        self.output_file = args.output.replace(".md", "") + ".md"
        self.output_file = os.path.abspath(os.path.join(os.path.dirname(__file__), "..\\..\\..\\docs", self.output_file))
        self.widget = args.widget
        if not os.path.exists(self.input_file):
            raise Exception(f"File {self.input_file} does not exist")
