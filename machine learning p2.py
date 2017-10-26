import pandas as pd
import quandl, math
import numpy as np
from sklearn import prepocessing, cross_validation, svm
from sklearn.linear_model import LinearRegression

df = quandl.get("WIKI/GOOGL") #df means dataframe
df = df[["Adj. Open","Adj. High","Adj. Low","Adj. Close", "Adj. Volume"]] # collums that show up/are used
df["HL_PCT"] = (df["Adj. High"] - df["Adj. Close"])/ df["Adj. Close"] *100
df["PCT_change"] = (df["Adj. Close"] - df["Adj. Open"])/ df["Adj. Open"] *100


df = df[["Adj. Close", "HL_PCT", "PCT_change", "Adj. Volume"]] #collums that actually appear (features)

forecast_col = "Adj. Close"
df.fillna(-99999, inplace = True)

forecast_out = int(math.ceil(0.01*len(df)))

df["label"] = df[forecast_col].shift(-forecast_out)

X = np.array(df.drop(["Label"],1))
y = np.array(df["Label"])

X = preprocessing.scale(X)

X = X[:-forecast_out+1]
df.dropna(inplace=True)
y = np.array(df["label"])

print(len(X),len(y))
