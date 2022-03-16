from pymongo import MongoClient
import pymongo
import datetime
import pandas as pd
import os

def get_database():
    CONNECTION_STRING = "mongodb+srv://bogdan_mf1:8igb3L!!MJjhZnK@cluster0.yuz4h.mongodb.net/myFirstDatabase?retryWrites=true&w=majority"
    client = MongoClient(CONNECTION_STRING)
    return client['myFirstDatabase']

categories = {0: 'entertainment', 1: 'world', 2: 'politics', 3: 'sports',
 4: 'business', 5: 'travel', 6: 'science', 7: 'wellness'}

df = pd.read_excel("output_classified.xlsx")

dbname = get_database()
collection_name = dbname["news"]

for index, row in df.iterrows():
    item = {
        "title": row["Title"],
        "link": row["Link"],
        "date": datetime.datetime.strptime(row["Date"], "%a, %d %b %Y %X GMT"),
        "category": categories[row["prediction"]],
        "source": row["Source"]
    }

    collection_name.insert_one(item)

os.remove("output_classified.xlsx")