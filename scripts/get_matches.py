import sys
import urllib.request
from urllib.error import HTTPError
import json
import configparser
import constants
import time
import random

ONE_WEEK_MILLIS = 604700000
matches_found_sofar = set()

def save_contents(m):
	f = open("data/matches.txt", "w+")
	f.write("\n".join([str(x) for x in m]))
	f.close()
	print("file saved successfully")

def inclusive_range(a, b, step=1):
	l = list(range(a, b, step))
	l.append(b)
	return l

def query_on_interval(user, start_stamp, end_stamp):
	prev = start_stamp
	matches = set()
	for s in inclusive_range(int(start_stamp), int(end_stamp), ONE_WEEK_MILLIS)[1:]:
		try:
			url = "https://br1.api.riotgames.com/lol/match/v4/matchlists/by-account/"+user[1]+"?beginTime="+str(int(prev))+"&endTime="+str(int(s))+"&queue=420&api_key="+key
			matches = matches.union(set([m['gameId'] for m in json.loads(urllib.request.urlopen(url).read())['matches']]))
			matches = matches.difference(matches_found_sofar)
			time.sleep(1.3)
			prev = s
		except HTTPError:
			pass

	if matches != set():
		print(matches)
	return matches

config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']
patch = config['GENERAL-CONFIG']['patch']
f = open("data/user_with_ids.txt", "r+")
users = f.read()
f.close()
users = users.split('\n')
users = [(u.split(' ')[0], u.split(' ')[1]) for u in users]
f = open("data/matches.txt", "r+")
matches_found_sofar = set([int(val) for val in sorted(f.read().split("\n")[:-1])])
f.close()

while True:
	try:
		random.shuffle(users)
		for user in users:
			matches = query_on_interval(user, constants.patch_dates[patch][0], constants.patch_dates[patch][1])
			matches_found_sofar = matches_found_sofar.union(matches)
			
	except HTTPError as e:
		print("error: " + str(e))
		save_contents(matches_found_sofar)

	except KeyboardInterrupt as e:
		save_contents(matches_found_sofar)
		break