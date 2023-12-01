import re
with open("day1_input.txt", "r") as f:
    data = f.read()

f = data.split("\n")
word_to_num_dict = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four" : 4,
        "five" : 5,
        "six" : 6,
        "seven" : 7,
        "eight" : 8,
        "nine" : 9,
        }

for k, v in word_to_num_dict.items():
    data = data.replace(k, str(v))

data = re.sub("[a-zA-Z]", "", data)
data = data.replace(" ", "").split("\n")

cols = [10 * int(x[0]) +  int(x[-1]) for x in data if len(x) > 0 ]
s = 0
for i, x in enumerate(cols):
    s+=x
    print(f"{i}:value:{s}:{f[i]}")
print(sum(cols))


