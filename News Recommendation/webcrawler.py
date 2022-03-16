from bs4 import BeautifulSoup
from urllib.request import urlopen, urlretrieve, Request
import re
import time
import pickle
import os
import pandas as pd


def search(page_limit=None):
    news_url = 'https://news.google.com/rss/'
    client = urlopen(news_url)
    xml_page = client.read()
    client.close()
    soup_page = BeautifulSoup(xml_page, 'xml')
    news_list = soup_page.find_all('item')
    return news_list[:page_limit]


def archive(archive_path, news_list, df):
    try:
        file = open(archive_path + 'archive_dict.pkl', 'rb')
        archive_dict = pickle.load(file)
        file.close()
    except:
        archive_dict = dict()

    success = 0
    failed = 0
    for news in news_list:
        title = re.sub('[\/:*?"<>|]', '#', news.title.text)
        struc_time = time.strptime(news.pubDate.text[5:-4], '%d %b %Y %H:%M:%S')
        timestamp = time.strftime('%Y%m%d%H%M%S', struc_time)
        filename = timestamp + ' ' + title + '.html'
        url = news.link.text
        if filename not in archive_dict:
            try:  # try to download
                urlretrieve(url, archive_path + filename)
                archive_dict.update({filename: [url, 1, news.source.text]})
                success += 1
                print(news.title.text)
                print(news.link.text)
                print(news.pubDate.text)
                print(news.source.text)
                df2 = {'Title': news.title.text, 'Link': news.link.text, 'Date': news.pubDate.text, 'Source': news.source.text}
                df = df.append(df2, ignore_index = True)
            except Exception as e:
                print('Failed to Download: ' + url)
                print(e)
                failed += 1
            print('-' * 60)

    with open(archive_path + 'archive_dict.pkl', 'wb') as file:
        pickle.dump(archive_dict, file)

    return success, failed, df


def crawl(archive_path, page_limit=None):  # main
    #df = pd.DataFrame(columns = ['Title', 'Link', "Date", "Source"])
    df = pd.read_excel('output.xlsx', index_col=0)
    if not os.path.exists(archive_path):
        os.makedirs(archive_path)
    print('Crawling news...')
    print('-' * 60)
    news_list = search(page_limit)
    success, failed, df = archive(archive_path, news_list, df)
    print('Downloaded : ' + str(success), end=' | ')
    print('Failed: ' + str(failed))
    print('-' * 60)
    print(df.tail())
    df.to_excel("output.xlsx")
    

if __name__ == '__main__':
    path = os.getcwd() + '/News Archive/'
    crawl(path)
