import pandas as pd

path_orig = ".\\Dataset\\News_Category_Dataset_v2.json"
path_new = ".\\Dataset\\dataset.xlsx"
category_limit = 10000


df = pd.read_json(path_orig, lines=True)
df['category_merged']=df['category'].replace({"HEALTHY LIVING": "WELLNESS",
"QUEER VOICES": "GROUPS VOICES",
"BUSINESS": "BUSINESS & FINANCES",
"PARENTS": "PARENTING",
"BLACK VOICES": "GROUPS VOICES",
"THE WORLDPOST": "WORLD NEWS",
"STYLE": "STYLE & BEAUTY",
"GREEN": "ENVIRONMENT",
"TASTE": "FOOD & DRINK",
"WORLDPOST": "WORLD NEWS",
"SCIENCE": "SCIENCE & TECH",
"TECH": "SCIENCE & TECH",
"MONEY": "BUSINESS & FINANCES",
"ARTS": "ARTS & CULTURE",
"COLLEGE": "EDUCATION",
"LATINO VOICES": "GROUPS VOICES",
"CULTURE & ARTS": "ARTS & CULTURE",
"FIFTY": "MISCELLANEOUS",
"GOOD NEWS": "MISCELLANEOUS"})

categories = df['category_merged'].unique()
new_categories = ['ENTERTAINMENT', 'WORLD NEWS', 'POLITICS', 'SPORTS',
 'BUSINESS & FINANCES', 'TRAVEL', 'SCIENCE & TECH', 'WELLNESS']

#new_df = df[df[['category_merged', 'headline', 'short_description']].category_merged.isin(new_categories)]
new_df = df[['category_merged', 'headline', 'short_description']]
new_df = new_df[new_df.category_merged.isin(new_categories)]
new_df = new_df.rename(columns={"category_merged": "category"})

df_aux = new_df.groupby("category").head(10000)
   
print(new_df.head())
df_aux.to_excel(path_new)
