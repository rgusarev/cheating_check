with open('files_M.txt') as f:
    s = 'std::vector<std::string> fs = {"' + f.readline().strip() + '"'
    for line in f:
        s += ', "' + line.strip() + '"'
    s += '}'
print(s)