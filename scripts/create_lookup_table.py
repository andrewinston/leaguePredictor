import sqlite3

f = open("data/champion_id.txt", "r")
id_list = [int(a.split(' ')[0]) for a in f.read().split('\n')[:-1]]
print(id_list)
ret = "//this file was generated automatically.\n#include \"winrate_lookup_table.h\"\nmap<pair<int, int>, double> winrate_lookup_table = {\n\t";
for c1 in id_list:
	print(c1)
	for c2 in id_list:
		if c1 == c2:
			ret += "{{"+str(c1)+", "+str(c2)+"}, 0},"
			continue
		conn = sqlite3.connect("data/teste.db")
		cur = conn.cursor()

		cur.execute("""select m1.champion_id, m1.team, m2.champion_id, m2.team, m.winner, count(*) from match_participant m1, match_participant m2, match m
						where m.match_id = m1.match_id and m1.match_id = m2.match_id and m1.champion_id = ? and m2.champion_id = ? and m1.team != m2.team
						group by m1.champion_id, m1.team, m2.champion_id, m2.team, m.winner""", (c1, c2))

		tot = 0
		c1w = 0
		rows = cur.fetchall()
		for row in rows:
			tot += row[5]
			if row[1] == row[4]:
				c1w += row[5]
		if tot == 0:
			ret += "{{"+str(c1)+", "+str(c2)+"}, "+str(-1)+"},"
		else:
			ret += "{{"+str(c1)+", "+str(c2)+"}, "+str(c1w/tot)+"},"
ret += "\n};\n";
f2 = open("src/winrate_lookup_table.cpp", "w+")
f2.write(ret)
print("file winrate_lookup_table.cpp was updated.")
