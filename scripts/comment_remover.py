import sys
import fileinput
import re

def remove_comments(file_path):
    with fileinput.input(file_path, inplace=True) as f:
        for line in f:
            print(re.sub(r'#.*?\n', '\n', line), end='')

def main():
    if len(sys.argv) < 2:
        print("Error -- Usage: python comment_remover.py <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    
    remove_comments(file_path)

if __name__ == "__main__":
    main()
