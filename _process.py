with open('files_F.txt') as f:
    # s = 'std::vector<std::string> fs = {"' + f.readline().strip() + '"'
    # for line in f:
    #     s += ', "' + line.strip() + '"'
    # s += '}'
    s = '    std::vector<std::string> fs = {\n        "' + '",\n        "'.join([item.strip() for item in f.readlines()]) + '"' + '\n    };'
print(s)