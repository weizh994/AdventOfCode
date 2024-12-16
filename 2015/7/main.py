import re

pattern = re.compile(r"^(.*)\s->\s(.*)$")
mode = re.compile(
    r"""
    ^                           
    (?:
        (?P<lhs>[\w\-]+)            
        \s+                     
        (?P<operate>AND|OR|LSHIFT|RSHIFT)  
        \s+                     
        (?P<rhs>[\w\-]+)            
    )
    |
    (?:
        NOT                     
        \s+                     
        (?P<not_rhs>[\w\-]+)        
    )
    |
    (?:
        (?P<assign>[\w\-]+)         
    )
    $
    """,
    re.VERBOSE,
)


def operate(line):
    match = mode.match(line)
    if match:
        if match.group("operate"):
            pass
        elif match.group("not_rhs"):
            pass
        elif match.group("assign"):
            lhs = match.group("assign")
            if lhs.isnumeric():
                return lhs
            else:
                return cache[lhs]
    else:
        print(f"无法解析行: {line}")
        return None


if __name__ == "__main__":
    with open("input", "r") as file:
        data = file.readlines()
    global cache
    cache = {}
    for line in data:
        match = pattern.match(line)
        if match:
            lhs = match.group(1)
            rhs = match.group(2)
            cache[rhs] = operate(lhs)
        else:
            print(f"无法解析行: {line}")
