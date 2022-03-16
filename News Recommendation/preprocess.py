import numpy as np
import pandas as pd
import tensorflow as tf
from transformers import BertTokenizer, TFBertModel
import pickle

path_data = "C:\\Users\\Bogdan\\Desktop\\crawler\\Dataset\\dataset.xlsx"

df = pd.read_excel(path_data)
print(df.head())

tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')
model = TFBertModel.from_pretrained('bert-base-uncased')

x_bert = []
y_bert = []
i = 0
for index,row in df.iterrows():
    text = np.str_(row['headline'])
    input_ids = tf.constant(tokenizer.encode(text, max_length=512, truncation=True))[None, :]
    outputs = model(input_ids)
    x_bert.append(np.array(outputs["pooler_output"]).reshape(768))
    y_bert.append(row["category"])
    i += 1
    if i % 50 == 0:
        print(i)

with open('C:\\Users\\Bogdan\\Desktop\\crawler\\model\\data.pickle', 'wb') as f:
        pickle.dump([x_bert, y_bert], f)