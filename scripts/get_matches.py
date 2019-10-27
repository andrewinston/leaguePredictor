import sys
import urllib.request
from urllib.error import HTTPError
import json
import configparser

config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']

f = open("data/user_with_ids.txt", "r+")
users = f.read()
f.close()
users = users.split('\n')
users = [(u.split(' ')[0], u.split(' ')[1]) for u in users]
f = open("data/matches.txt", "r+")
matches_found_sofar = set([int(val) for val in sorted(f.read().split("\n")[:-1])])
f.close()
try:
	for user in users:
		print(user)
		url = "https://br1.api.riotgames.com/lol/match/v4/matchlists/by-account/"+user[1]+"?queue=420&api_key="+key
		print(url)
		matches = json.loads(urllib.request.urlopen(url).read())['matches']
		matches = set([m['gameId'] for m in matches])
		matches_found_sofar = matches_found_sofar.union(matches)
		
except (KeyboardInterrupt, HTTPError) as e:
	print(str(e))
	f = open("data/matches.txt", "w+")
	f.write("\n".join([str(x) for x in matches_found_sofar]))
	f.close()