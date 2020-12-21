import re
import json

valid_passports = 0

checker = {
    "byr": lambda x: re.match("\d{4}", x) and 1920 <= int(x) <= 2002,
    "iyr": lambda x: re.match("\d{4}", x) and 2010 <= int(x) <= 2020,
    "eyr": lambda x: re.match("\d{4}", x) and 2020 <= int(x) <= 2030,
    "ecl": lambda x: re.match("amb|blu|brn|gry|grn|hzl|oth", x),
    "hcl": lambda x: re.match("#[0-9a-f]{6}", x),
    "pid": lambda x: re.match("^\d{9}$", x),
    "hgt": lambda x: \
                (re.match("\d+(cm|in)", x)) and \
                ((x[-2:] == "cm" and 150 <= (int(x[:-2])) <= 193) or (x[-2:] == "in" and 59 <= (int(x[:-2])) <= 76))
}

with open("day4-input.txt", "r") as f:
    passport_data = f.read()
    passport_data = passport_data.split("\n\n")

    for passport in passport_data:
        passport = passport.split()
        
        data = {}
        valid = True

        for i in passport:
            key, value = i.split(":")
            data[key] = value
        
        for field in checker:
            check = checker[field]
            value = data.get(field)

            if value is None and field != "cid":
                valid = False

            if value is not None:
                if not check(value):
                    valid = False

        if valid:
            print(json.dumps(data, indent = 4))
            valid_passports += 1

print(valid_passports)