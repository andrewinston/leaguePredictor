string = "select m.winner, m0.match_id,"
for i in range(10):
    string += " m"+str(i)+".champion_id"
    if i < 9:
        string += ","
string += " from match m, "
for i in range(10):
    string += " match_participant m" + str(i)
    if i < 9:
        string += ","
MATCH_ID = "1752530143"  
string += " where m.match_id = " + MATCH_ID + " and "

for i in range(10):
    string += "m"+str(i)+".match_id = "+MATCH_ID+" and " 

for i in range(5):
    string += "m"+str(i)+".team = 1 and "

for i in range(5):
    string += "m"+str(i+5)+".team = 2 and "

for i in range(1, 5):
    string += "m"+str(i-1)+".champion_id < m"+str(i)+".champion_id and "

for i in range(1, 5):
    string += "m"+str(i-1+5)+".champion_id < m"+str(i+5)+".champion_id "
    if i < 4:
        string += " and "
    
print(string)
