#-*- coding: utf-8 -*-
import urllib.request
import json
import time
import configparser
config = configparser.ConfigParser()
config.read('scripts/config.ini')
user_list = ['ZVJK', 'iDarkxD', 'BestMFBrazil', 'Zsafyre', 'Effect', 'Artreety', 'LaioCisboa', 'LOPES', 'NickJagers', 'yungumpas', 'yungdemon', 'Clöse', 'KingOtaku', 'torelaxando', 'LilXxiquinho', 'grimesoficial', 'Fhaeul', 'KizaruPipo', 'Mlkinhosolto', 'monkie', 'JINXAPISGOD', '2god']
f = open("scripts/user_ids.txt", 'a+')

for username in user_list:
    print("Fetching user: " + username)
    obj = json.loads(urllib.request.urlopen("https://br1.api.riotgames.com/lol/summoner/v4/summoners/by-name/"+username+"?api_key="+config['RG-API']['key']).read())
    time.sleep(1)
    print("Writing content")
    f.write(username + "," + obj["id"]+"\n")
    print("Done!")


