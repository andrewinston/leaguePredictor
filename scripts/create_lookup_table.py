import sqlite3

table = {}

f = open("data/samples/attempt2/winrate_samples.txt")
matches = [[int(x) for x in a.split(' ')] for a in f.read().split("\n")]
f.close()
for match in matches:
	for c1 in match[2:7]:
		for c2 in match[7:]:
			if (c1, c2) not in table.keys():
				table[(c1, c2)] = [1, 1] if match[0] == 1 else [0, 1]
				table[(c2, c1)] = [0, 1] if match[0] == 1 else [1, 1]
			else:
				table[(c1, c2)][1] += 1
				table[(c2, c1)][1] += 1
				table[(c1, c2)][0] += 1 if match[0] == 1 else 0
				table[(c2, c1)][0] += 0 if match[0] == 1 else 1

output_path = "data/winrate_lookup_table.txt"
f = open(output_path, "w+")
maxi = ((0, 0), (0, 0))
for (k, v) in table.items():
	if v[1] > maxi[1][1]:
		maxi = (k, tuple(v))
	f.write(str(k[0]) + " " + str(k[1]) + " " + str(float(v[0])/v[1]) + "\n")

#print(table)
print(maxi)