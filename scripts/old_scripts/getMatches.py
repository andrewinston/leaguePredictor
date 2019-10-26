import sys
import urllib.request
from urllib.error import HTTPError
import json
config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']

f = open("users.txt", "r+")
users = f.read()
f.close()

users = users.split('\n')[:-1]
users = [(u.split(',')[0], u.split(',')[1]) for u in users]
f = open("matches.txt", "r+")
matches_found_sofar = [int(val) for val in sorted(f.read().split("\n")[:-1])]
f.close()
f = open("matches.txt", "a+")
for user in users:
	print(user)
	url = "https://br1.api.riotgames.com/lol/match/v4/matchlists/by-account/"+user[1]+"?queue=420&api_key="+key
	matches = json.loads(urllib.request.urlopen(url).read())['matches']
	for match in matches:
		if match['gameId'] not in matches_found_sofar:
			matches_found_sofar.append(match['gameId'])
			f.write(str(match['gameId'])+"\n")
		

