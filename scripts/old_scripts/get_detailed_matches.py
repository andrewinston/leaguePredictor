import sys
from time import sleep
import urllib.request
from urllib.error import HTTPError
import sqlite3
import json
import configparser

config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']
f = open("matches.txt", "r+")
matches_found_sofar = [int(val) for val in sorted(f.read().split("\n")[:-1])]
matches_found_sofar = list(dict.fromkeys(matches_found_sofar))
matches_found_sofar.reverse()
f.close()
conn = sqlite3.connect("teste.db")
cur = conn.cursor()
try:
	traveled = []
	for match_id in matches_found_sofar:
		url = "https://br1.api.riotgames.com/lol/match/v4/matches/"+str(match_id)+"?api_key="+key
		match_detailed = ""
		try:
			match_detailed = json.loads(urllib.request.urlopen(url).read())
		except HTTPError:
			sleep(20)
			match_detailed = json.loads(urllib.request.urlopen(url).read())
		print(match_detailed['participantIdentities'])
		winner = 0
		if match_detailed['teams'][0]['win'] == "Win":
			winner = 1
		if match_detailed['teams'][1]['win'] == "Win":
			winner = 2
		match_id = match_detailed['gameId']
		cur.execute("INSERT INTO match(match_id, winner, game_creation) VALUES(?, ?, ?)", (match_id, winner, match_detailed['gameCreation']))
		for (participant, identity) in list(zip(match_detailed['participants'], match_detailed['participantIdentities'])):
			cur.execute("INSERT INTO match_participant(match_id, champion_id, username, team) VALUES(?, ?, ?, ?)", (match_id, participant['championId'], identity['player']['summonerName'], participant['teamId']/100))
		conn.commit()
		traveled.append(match_id)
		print("Salvo!")
except:
	print("Erro: " + str(sys.exc_info()[0]))
	matches_found_sofar = [a for a in matches_found_sofar if a not in traveled]
	print(traveled)
	f = open("matches.txt", "w+")
	for m in matches_found_sofar:
		f.write(str(m) + "\n")
		
