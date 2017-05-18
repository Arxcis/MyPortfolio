# !usr/bin/env python3
# -*- coding: utf-8 -*-

import codecs

class Time:
	def __init__(self):
	def __sub__(self):

def leadingZero(tid):
	tid = str(tid)
	if len(tid) == 1:
		return "0" + tid
	return tid


def leggTilSekund(tid, iSekund):

	tid    = tid.split(":")
	time   = int(tid[0])
	minutt = int(tid[1])
	sek    = tid[2].split(",")
	sekund = float(sek[0]) + (float(sek[1]) / 1000)

	nysek = sekund + iSekund

	if nysek < 60 and nysek >= 0:
		pass

	elif nysek >= 60 and minutt < 59:
		nysek = nysek - 60
		minutt += 1

	elif nysek >= 60 and minutt >= 59:
		nysek  = nysek - 60
		minutt = 0
		time += 1

	elif nysek < 0 and minutt > 0:
		nysek = 60 - abs(nysek)
		minutt -= 1

	elif nysek < 0 and minutt == 0:
		nysek = 60 - abs(nysek)
		minutt == 59
		time -= 1

	time   = leadingZero(time)
	minutt = leadingZero(minutt)

	return time + ":" + minutt + ":" + leadingZero(int(nysek)) + "," \
			+ (str(nysek - int(nysek)).split(".")[1])[0:3]

def finnMellomtid(filename):
	i=0
	start = ""
	temp  = ""
	slutt = ""

	with codecs.open(filename, "r", encoding="latin-1") as srt:
		for line in srt:
			if i==0:
				i += 1
				start = Time( line.split(" --> ")[0] )
			else:
				temp = Time( line.split(" --> ")[0] )

	slutt = temp            # operator def __equal__(self):
	return slutt - start    # operator def __sub__(self):


def main():
	filename = input("File name:")
	startSek = float(input("Start forskjell i sekunder:"))
	sluttSek = float(input("Slutt forskjell i sekunder"))

	mellomTid = finnMellomtid(filename)

	with codecs.open(filename, "r", encoding="latin-1") as srt:
		with codecs.open("fix_" + filename, "w", encoding="utf-8") as srtfix:

			for line in srt:									     	# Går igjennom hver linje i srt fil
				check = line.find("-->")								# Finner linjer med -->

				if check > -1:
					tider = line.split(" --> ")

					nytid1 = leggTilSekund( tider[0], sekunder )
					nytid2 = leggTilSekund( tider[1], sekunder )

					srtfix.write(nytid1 + " --> " + nytid2 "\n")

				else:
					srtfix.write(line)


if __name__ == "__main__":
	main()
