# Created by Henry Jooste

from modules.args import Args
from modules.parser import Parser

args = Args()
print(f"Input File  : {args.input_file}")
print(f"Output File : {args.output_file}")

parser = Parser(args.input_file, args.widget)
parser.generate()
parser.save(args.output_file)
print()