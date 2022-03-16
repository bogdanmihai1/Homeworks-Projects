import pandas as pd
import tensorflow as tf
from transformers import BertTokenizer, TFBertModel
import numpy as np
import keras

df = pd.read_excel("output.xlsx")
tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')
model = TFBertModel.from_pretrained('bert-base-uncased')
x_bert = []
i=0
print(i)
for index,row in df.iterrows():
    text = np.str_(row['Title'])
    input_ids = tf.constant(tokenizer.encode(text, max_length=512, truncation=True))[None, :]
    outputs = model(input_ids)
    x_bert.append(np.array(outputs["pooler_output"]).reshape(768))
    i += 1
    if i % 10 == 0:
        print(i)

classification_model = keras.models.load_model("model.h5")
x_bert = np.array(x_bert)
y_pred = classification_model.predict(x_bert)
y = np.argmax(y_pred, axis=1)

df["prediction"] = y
print(y_pred)

df.to_excel("output_classified.xlsx")

empty_df = pd.DataFrame(columns=["Title", "Link", "Date", "Source"])
empty_df.to_excel("output.xlsx")