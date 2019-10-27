#-*- coding: utf-8 -*-
import urllib.request
import urllib.parse
import urllib.error
import json
import time
import configparser

config = configparser.ConfigParser()
config.read('scripts/config.ini')

f = open("data/users.txt")
user_list = f.read().split('\n')
f.close()

f = open("data/user_with_ids.txt", 'w+')

try:
	for username in user_list:
		username = "%s" % (urllib.parse.quote(username),)
		url = "https://br1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"+username+"?api_key="+config['RG-API']['key']
		try:
			obj = json.loads(urllib.request.urlopen(url).read())
			time.sleep(1.3)
			txt = urllib.parse.unquote(username) + " " + obj["id"]+"\n"
			print(txt, end='')
			f.write(txt)
		except urllib.error.HTTPError:
			continue
except KeyboardInterrupt:
	f.close()
	print("file saved successfully")