import json
import urllib.request
import configparser

champions = ["Annie","Olaf","Galio","TwistedFate","XinZhao","Urgot","Leblanc","Vladimir","Fiddlesticks","Kayle","MasterYi","Alistar","Ryze","Sion","Sivir","Soraka","Teemo","Tristana","Warwick","Nunu","MissFortune","Ashe","Tryndamere","Jax","Morgana","Zilean","Singed","Evelynn","Twitch","Karthus","Chogath","Amumu","Rammus","Anivia","Shaco","DrMundo","Sona","Kassadin","Irelia","Janna","Gangplank","Corki","Karma","Taric","Veigar","Trundle","Swain","Caitlyn","Blitzcrank","Malphite","Katarina","Nocturne","Maokai","Renekton","JarvanIV","Elise","Orianna","MonkeyKing","Brand","LeeSin","Vayne","Rumble","Cassiopeia","Skarner","Heimerdinger","Nasus","Nidalee","Udyr","Poppy","Gragas","Pantheon","Ezreal","Mordekaiser","Yorick","Akali","Kennen","Garen","Leona","Malzahar","Talon","Riven","KogMaw","Shen","Lux","Xerath","Shyvana","Ahri","Graves","Fizz","Volibear","Rengar","Varus","Nautilus","Viktor","Sejuani","Fiora","Ziggs","Lulu","Draven","Hecarim","Khazix","Darius","Jayce","Lissandra","Diana","Quinn","Syndra","AurelionSol","Kayn","Zoe","Zyra","Kaisa","Gnar","Zac","Yasuo","Velkoz","Taliyah","Camille","Braum","Jhin","Kindred","Jinx","TahmKench","Lucian","Zed","Kled","Ekko","Qiyana","Vi","Aatrox","Nami","Azir","Yuumi","Thresh","Illaoi","RekSai","Ivern","Kalista","Bard","Rakan","Xayah","Ornn","Sylas","Neeko","Pyke"]

config = configparser.ConfigParser()
config.read('scripts/config.ini')
patch = config['GENERAL-CONFIG']['patch']

ret = []

for champion in champions:
	obj = json.loads(urllib.request.urlopen("http://ddragon.leagueoflegends.com/cdn/"+patch+".1/data/en_US/champion/"+champion+".json").read())
	i = obj['data'][champion]['key']
	aux = [i]
	for k in sorted(obj['data'][champion]['stats']):
		aux.append(obj['data'][champion]['stats'][k])

	print(aux)
	ret.append(tuple(aux))

f = open("data/champion_stats.txt", 'w+')
f.write("\n".join([" ".join(str(x) for x in a) for a in ret]))
f.close()
print(ret)