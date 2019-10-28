import urllib.request
import configparser
import json
from time import sleep
import random

config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']

def save_contents(winrate_matches, training_matches, validation_matches):
	winrate_matches = set(winrate_matches)
	training_matches = set(training_matches)
	validation_matches = set(validation_matches)
	
	f = open("data/samples/attempt2/winrate_samples.txt", "w+")
	f.write("\n".join([(" ".join([str(x) for x in a])) for a in winrate_matches]))
	f.close()

	f = open("data/samples/attempt2/training_samples.txt", "w+")
	f.write("\n".join([(" ".join([str(x) for x in a])) for a in training_matches]))
	f.close()

	f = open("data/samples/attempt2/validation_samples.txt", "w+")
	f.write("\n".join([(" ".join([str(x) for x in a])) for a in validation_matches]))
	f.close()
	print("files saved successfully")

def query(match_id):
	url = "https://br1.api.riotgames.com/lol/match/v4/matches/"+str(match_id)+"?api_key="+key
	match_detailed = json.loads(urllib.request.urlopen(url).read())
	sleep(1.3)
	winner = 0
	if match_detailed['teams'][0]['win'] == "Win":
			winner = 1
	if match_detailed['teams'][1]['win'] == "Win":
		winner = 2
	team = []
	team.append([])
	team.append([])
	for (participant, identity) in list(zip(match_detailed['participants'], match_detailed['participantIdentities'])):
		team[-1+participant['teamId']//100].append(participant['championId'])
	team[0] = sorted(team[0])
	team[1] = sorted(team[1])
	ret = tuple([winner, match_id]+team[0]+team[1])
	return ret

f = open("data/matches.txt", "r+")
matches = f.read()
f.close()
matches = set([int(a) for a in matches.split('\n')])

f = open("data/samples/attempt2/winrate_samples.txt", "r+")
winrate_matches = [tuple(int(x) for x in a.split(' ')) for a in f.read().split('\n')[1:]]
winrate_matches_ids = set([int(a[1]) for a in winrate_matches] if len(winrate_matches) > 0 else [])
f.close()

f = open("data/samples/attempt2/training_samples.txt", "r+")
training_matches = [tuple(int(x) for x in a.split(' ')) for a in f.read().split('\n')[1:]]
training_matches_ids = set([int(a[1]) for a in training_matches] if len(training_matches) > 0 else [])
f.close()

f = open("data/samples/attempt2/validation_samples.txt", "r+")
validation_matches = [tuple(int(x) for x in a.split(' ')) for a in f.read().split('\n')[1:]]
validation_matches_ids = set([int(a[1]) for a in validation_matches] if len(validation_matches) > 0 else [])
f.close()

i = 0
while True:
	matches = matches.difference(validation_matches_ids).difference(training_matches_ids).difference(winrate_matches_ids)
	random.shuffle(list(matches))
	try:
		for match in matches:
			print("trying to fetch match " + str(match))
			content = query(match)
			if i%6 < 3:
				winrate_matches_ids.union([match])
				winrate_matches.append(content)
			elif i%6 < 5:
				training_matches_ids.union([match])
				training_matches.append(content)
			else:
				validation_matches_ids.union([match])
				validation_matches.append(content)
			print("match " + str(match) + " added.")
			i+=1
	except Exception as e:
		print("Error: " + str(e))
		save_contents(winrate_matches, training_matches, validation_matches)
	except KeyboardInterrupt as e:
		save_contents(winrate_matches, training_matches, validation_matches)
		break