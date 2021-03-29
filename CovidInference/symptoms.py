from collections import Counter
from joblib import dump

def readFile(fileName):
        fileObj = open(fileName, "r")
        words = fileObj.read().splitlines()
        fileObj.close()
        return words

symptoms = readFile("all-positive-symptoms.txt")
symp_list = []
for symp in symptoms:
	symp = str(symp).lower()
	symp = symp.replace(",", " ")
	symp = symp.replace(".", " ")
	symp = symp.replace("-", " ")
	split_symp = symp.split(" ")
	if split_symp != '':
		symp_list.append(split_symp)

flat_list = []
for i in symp_list:
	for j in i:
		if j != '':
			flat_list.append(j)

c = Counter(flat_list)
dump(c, 'symptomsCounter.joblib')