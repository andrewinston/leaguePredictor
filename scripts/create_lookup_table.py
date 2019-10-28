import sqlite3

table = {}

f = open("data/samples/attempt2/winrate_samples")
matches = [[int(x) for x in a.split(' ')] for a in f.read().split("\n")]

for match in matches:
	for c1 in match[2:7]:
		for c2 in match[7:]
			if (c1, c2) not in table.keys():
				table[(c1, c2)] = [1, 1] if match[0] == 1 else [0, 1]
				table[(c2, c1)] = [0, 1] if match[0] == 1 else [1, 0]
			else:
				table[(c1, c2)][1] += 1
				table[(c2, c1)][1] += 1
				table[(c1, c2)][0] += 1 if match[0] == 1 else 0
				table[(c2, c1)][0] += 0 if match[0] == 1 else 1

print(table)