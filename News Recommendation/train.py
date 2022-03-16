import pickle
import numpy as np
from keras.models import Sequential
from keras.layers import Dense, Dropout
from sklearn.model_selection import train_test_split
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.metrics import accuracy_score

with open('C:\\Users\\Bogdan\\Desktop\\crawler\\model\\data.pickle', 'rb') as f:
    X, Y = pickle.load(f)

categories = {'entertainment': 0.0, 'world': 1.0, 'politics': 2.0, 'sports': 3.0,
 'business':4.0, 'travel':5.0, 'science':6.0, 'wellness':7.0}


Y_final = []
for i in Y:
    Y_final.append(categories[i])
Y = np.array(Y_final)

X = np.array(X)
print(X.shape)

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.1, random_state=42)

def base_model():
    model = Sequential()
    # add the layers
    model.add(Dense(200, input_shape=(768, ), activation='relu'))
    model.add(Dropout(0.2))
    model.add(Dense(50, activation='relu'))
    model.add(Dense(8, activation='softmax'))
    # compile, train and evaluate
    model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer='adam')
    return model


estimator = KerasClassifier(build_fn=base_model, epochs=200, batch_size=256)
estimator.fit(X_train, Y_train)
Y_pred = estimator.predict(X_test)

print(accuracy_score(Y_test, Y_pred))
estimator.model.save("model.h5")
#print(f'Score: {model.metrics_names[0]} of {scores[0]}; {model.metrics_names[1]} of {scores[1]*100}%')

#model.save('C:\\Users\\Bogdan\\Desktop\\crawler\\finalModel')
