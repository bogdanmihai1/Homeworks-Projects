import os
import glob

os.system('python webcrawler.py')
os.system('python process_news.py')
os.system('python mongo.py')

folder = "News Archive"

files = glob.glob(os.path.join(folder, "*"))
for f in files:
    if (f != os.path.join(folder, "archive_dict.pkl")):
        os.remove(f)