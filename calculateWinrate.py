import sqlite3

print("write first champion's id:")
c1 = int(input())
print("write second champion's id:")
c2 = int(input())

conn = sqlite3.connect("teste.db")
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

print("winrate: " + str(100.0*c1w/tot) + "%")
print(str(tot) + " games analyzed")
	

