import pandas as pd
import sklearn as sk
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics
from joblib import load
import sys, getopt
import matplotlib.pyplot as plt

#read data
inputFile = sys.argv[1]
col_names = ['sex', 'vârstă', 'simptome declarate', 'simptome raportate la internare', 'confirmare contact cu o persoană infectată']
data = pd.read_excel(inputFile)
rezultat = pd.DataFrame(data, columns= ['rezultat testare'])
x = data[col_names]
y = rezultat

#convert data
i=0
sex_column = {}
for sex in x.get("sex"):
	if sex == "FEMININ":
		sex = 0
		sex_column[i] = sex
		i=i+1
	else:
		sex = 1
		sex_column[i] = sex
		i=i+1

i=0
age_column = {}
for age in x.get("vârstă"):
	if isinstance(age, int):
		age_column[i] = age
		i=i+1
	else:
		age = 0
		age_column[i] = age
		i=i+1

counter = load("symptomsCounter.joblib")

j=0
symp_column = {}
for symp in x.get("simptome declarate"):
	symp = str(symp).lower()
	symp = symp.replace(",", " ")
	symp = symp.replace(".", " ")
	symp = symp.replace("-", " ")
	split_symp = symp.split(" ")
	i=0
	for word in split_symp:
		if word in counter:
			i = i + counter[word]
	symp_column[j] = i
	j = j + 1

j=0
reported_column = {}
for symp in x.get("simptome raportate la internare"):
	symp = str(symp).lower()
	symp = symp.replace(",", " ")
	symp = symp.replace(".", " ")
	symp = symp.replace("-", " ")
	split_symp = symp.split(" ")
	i=0
	for word in split_symp:
		if word in counter:
			i = i + counter[word]
	reported_column[j] = i
	j = j + 1

i=0
contact_column = {}
for answer in x.get("confirmare contact cu o persoană infectată"):
	answer = str(answer).lower()
	if answer[0] == "d" or answer[0] == "c":
		contact_column[i] = 1
		i=i+1
	else:
		contact_column[i] = 0
		i=i+1
	
i=0
result_column = {}
for result in y.get("rezultat testare"):
	result = str(result).lower()
	if result == "pozitiv":
		result_column[i] = 2
		i=i+1
	elif result == "negativ":
		result_column[i] = 0
		i=i+1
	else:
		result_column[i] = 1
		i=i+1

#fit data into a matrix
Matrix = [[0 for x in range(5)] for y in range(len(contact_column))] 

for i in range(len(contact_column)):
	Matrix[i][0] = sex_column[i]
	Matrix[i][1] = age_column[i]
	Matrix[i][2] = symp_column[i]
	Matrix[i][3] = reported_column[i]
	Matrix[i][4] = contact_column[i]

#split matrix into train and test
x_train, x_test, y_train, y_test = train_test_split(Matrix, result_column, train_size=0.9, test_size=0.1, random_state=2, shuffle=False)

#create decision tree
clf = DecisionTreeClassifier()
#load decision tree from the other script
clf = load('trainedTree.joblib')

#predict outcome
y_pred = clf.predict(x_test)

#print the score
print("Accuracy:",metrics.accuracy_score(y_test, y_pred))
print("Precision:",metrics.precision_score(y_test, y_pred, labels=[2], average='micro'))
# rapelul
print("Recall:",metrics.recall_score(y_test,y_pred, labels=[2], average='micro'))
#F1
print("F1:",metrics.f1_score(y_test,y_pred, labels=[2], average='micro'))

print("Confusion Matrix:\n",metrics.confusion_matrix(y_test,y_pred))


metrics.plot_confusion_matrix(clf,x_test,y_test)
plt.show()