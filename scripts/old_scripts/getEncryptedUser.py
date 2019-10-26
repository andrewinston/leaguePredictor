#-*- coding: utf-8 -*-
import sys
import urllib.request
from urllib.error import HTTPError
import json
config = configparser.ConfigParser()
config.read('scripts/config.ini')
key = config['RG-API']['key']
f = open("users.txt", "r+")
userlist = (f.read().split('\n'))
userlist = [a.split(',')[0].replace(" ", "").lower() for a in userlist]
print(userlist)
while True:
	username = input()
	if username.replace(" ", "").lower() in userlist:
		print('user already fetched.')
		continue
	try:
		obj = json.loads(urllib.request.urlopen("https://br1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"+username+"?api_key="+key).read())
		print(obj['accountId'])
		f = open("users.txt","a+")
		f.write(username+","+obj['accountId']+"\n")
		userlist.append(username)
		f.close()
	except HTTPError:
		print("Erro!")

