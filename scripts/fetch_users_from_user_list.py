#-*- coding: utf-8 -*-
import urllib.request
import urllib.parse
import urllib.error
import json
import time
import configparser

config = configparser.ConfigParser()
config.read('scripts/config.ini')

f = open("data/users.txt", "r+")
user_list = set(f.read().split('\n'))
f.close()

f = open("data/user_with_ids.txt", 'r+')
fcontent = f.read()
f.close()

fcontent = [a.split(' ') for a in fcontent.split('\n')]
users_fetched_sofar = set([a[0] for a in fcontent])

user_list = user_list.difference(users_fetched_sofar)
try:
	for username in user_list:
		username = "%s" % (urllib.parse.quote(username.replace(" ", "")),)
		url = "https://br1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"+username+"?api_key="+config['RG-API']['key']
		try:
			obj = json.loads(urllib.request.urlopen(url).read())
			time.sleep(1.3)
			new_usr = [urllib.parse.unquote(username), obj["accountId"]]
			fcontent.append(new_usr)
			txt = " ".join(new_usr) + "\n"
			print(txt, end='')
		except urllib.error.HTTPError:
			continue
except KeyboardInterrupt:
	f = open("data/user_with_ids.txt", "w+")
	f.write("\n".join([" ".join(x) for x in fcontent]))
	f.close()
	print("file saved successfully")